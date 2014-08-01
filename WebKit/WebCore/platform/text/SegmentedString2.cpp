/*
    Copyright (C) 2004, 2005, 2006, 2007, 2008 Apple Inc. All rights reserved.
    Copyright (C) 2014 FactorY Media Production GmbH

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

// FYMP - file integrated from r152754. SegmentedString changed a lot, decided to keep both.

#include "config.h"
#include "SegmentedString2.h"

namespace WebCore {

SegmentedString2::SegmentedString2(const SegmentedString2& other)
    : m_pushedChar1(other.m_pushedChar1)
    , m_pushedChar2(other.m_pushedChar2)
    , m_currentString(other.m_currentString)
    , m_numberOfCharactersConsumedPriorToCurrentString(other.m_numberOfCharactersConsumedPriorToCurrentString)
    , m_numberOfCharactersConsumedPriorToCurrentLine(other.m_numberOfCharactersConsumedPriorToCurrentLine)
    , m_currentLine(other.m_currentLine)
    , m_substrings(other.m_substrings)
    , m_closed(other.m_closed)
    , m_empty(other.m_empty)
    , m_fastPathFlags(other.m_fastPathFlags)
    , m_advanceFunc(other.m_advanceFunc)
    , m_advanceAndUpdateLineNumberFunc(other.m_advanceAndUpdateLineNumberFunc)
{
    if (m_pushedChar2)
        m_currentChar = m_pushedChar2;
    else if (m_pushedChar1)
        m_currentChar = m_pushedChar1;
    else
        m_currentChar = m_currentString.m_length ? m_currentString.getCurrentChar() : 0;
}

const SegmentedString2& SegmentedString2::operator=(const SegmentedString2& other)
{
    m_pushedChar1 = other.m_pushedChar1;
    m_pushedChar2 = other.m_pushedChar2;
    m_currentString = other.m_currentString;
    m_substrings = other.m_substrings;
    if (m_pushedChar2)
        m_currentChar = m_pushedChar2;
    else if (m_pushedChar1)
        m_currentChar = m_pushedChar1;
    else
        m_currentChar = m_currentString.m_length ? m_currentString.getCurrentChar() : 0;

    m_closed = other.m_closed;
    m_empty = other.m_empty;
    m_fastPathFlags = other.m_fastPathFlags;
    m_numberOfCharactersConsumedPriorToCurrentString = other.m_numberOfCharactersConsumedPriorToCurrentString;
    m_numberOfCharactersConsumedPriorToCurrentLine = other.m_numberOfCharactersConsumedPriorToCurrentLine;
    m_currentLine = other.m_currentLine;

    m_advanceFunc = other.m_advanceFunc;
    m_advanceAndUpdateLineNumberFunc = other.m_advanceAndUpdateLineNumberFunc;

    return *this;
}

unsigned SegmentedString2::length() const
{
    unsigned length = m_currentString.m_length;
    if (m_pushedChar1) {
        ++length;
        if (m_pushedChar2)
            ++length;
    }
    if (isComposite()) {
        Deque<SegmentedSubstring2>::const_iterator it = m_substrings.begin();
        Deque<SegmentedSubstring2>::const_iterator e = m_substrings.end();
        for (; it != e; ++it)
            length += it->m_length;
    }
    return length;
}

void SegmentedString2::setExcludeLineNumbers()
{
    m_currentString.setExcludeLineNumbers();
    if (isComposite()) {
        Deque<SegmentedSubstring2>::iterator it = m_substrings.begin();
        Deque<SegmentedSubstring2>::iterator e = m_substrings.end();
        for (; it != e; ++it)
            it->setExcludeLineNumbers();
    }
}

void SegmentedString2::clear()
{
    m_pushedChar1 = 0;
    m_pushedChar2 = 0;
    m_currentChar = 0;
    m_currentString.clear();
    m_numberOfCharactersConsumedPriorToCurrentString = 0;
    m_numberOfCharactersConsumedPriorToCurrentLine = 0;
    m_currentLine = 0;
    m_substrings.clear();
    m_closed = false;
    m_empty = true;
    m_fastPathFlags = NoFastPath;
    m_advanceFunc = &SegmentedString2::advanceEmpty;
    m_advanceAndUpdateLineNumberFunc = &SegmentedString2::advanceEmpty;
}

void SegmentedString2::append(const SegmentedSubstring2& s)
{
    ASSERT(!m_closed);
    if (!s.m_length)
        return;

    if (!m_currentString.m_length) {
        m_numberOfCharactersConsumedPriorToCurrentString += m_currentString.numberOfCharactersConsumed();
        m_currentString = s;
        updateAdvanceFunctionPointers();
    } else
        m_substrings.append(s);
    m_empty = false;
}

void SegmentedString2::prepend(const SegmentedSubstring2& s)
{
    ASSERT(!escaped());
    ASSERT(!s.numberOfCharactersConsumed());
    if (!s.m_length)
        return;

    // FIXME: We're assuming that the prepend were originally consumed by
    //        this SegmentedString2.  We're also ASSERTing that s is a fresh
    //        SegmentedSubstring2.  These assumptions are sufficient for our
    //        current use, but we might need to handle the more elaborate
    //        cases in the future.
    m_numberOfCharactersConsumedPriorToCurrentString += m_currentString.numberOfCharactersConsumed();
    m_numberOfCharactersConsumedPriorToCurrentString -= s.m_length;
    if (!m_currentString.m_length) {
        m_currentString = s;
        updateAdvanceFunctionPointers();
    } else {
        // Shift our m_currentString into our list.
        m_substrings.prepend(m_currentString);
        m_currentString = s;
        updateAdvanceFunctionPointers();
    }
    m_empty = false;
}

void SegmentedString2::close()
{
    // Closing a stream twice is likely a coding mistake.
    ASSERT(!m_closed);
    m_closed = true;
}

void SegmentedString2::append(const SegmentedString2& s)
{
    ASSERT(!m_closed);
    ASSERT(!s.escaped());
    append(s.m_currentString);
    if (s.isComposite()) {
        Deque<SegmentedSubstring2>::const_iterator it = s.m_substrings.begin();
        Deque<SegmentedSubstring2>::const_iterator e = s.m_substrings.end();
        for (; it != e; ++it)
            append(*it);
    }
    m_currentChar = m_pushedChar1 ? m_pushedChar1 : (m_currentString.m_length ? m_currentString.getCurrentChar() : 0);
}

void SegmentedString2::prepend(const SegmentedString2& s)
{
    ASSERT(!escaped());
    ASSERT(!s.escaped());
    if (s.isComposite()) {
        Deque<SegmentedSubstring2>::const_reverse_iterator it = s.m_substrings.rbegin();
        Deque<SegmentedSubstring2>::const_reverse_iterator e = s.m_substrings.rend();
        for (; it != e; ++it)
            prepend(*it);
    }
    prepend(s.m_currentString);
    m_currentChar = m_pushedChar1 ? m_pushedChar1 : (m_currentString.m_length ? m_currentString.getCurrentChar() : 0);
}

void SegmentedString2::advanceSubstring()
{
    if (isComposite()) {
        m_numberOfCharactersConsumedPriorToCurrentString += m_currentString.numberOfCharactersConsumed();
        m_currentString = m_substrings.takeFirst();
        // If we've previously consumed some characters of the non-current
        // string, we now account for those characters as part of the current
        // string, not as part of "prior to current string."
        m_numberOfCharactersConsumedPriorToCurrentString -= m_currentString.numberOfCharactersConsumed();
        updateAdvanceFunctionPointers();
    } else {
        m_currentString.clear();
        m_empty = true;
        m_fastPathFlags = NoFastPath;
        m_advanceFunc = &SegmentedString2::advanceEmpty;
        m_advanceAndUpdateLineNumberFunc = &SegmentedString2::advanceEmpty;
    }
}

String SegmentedString2::toString() const
{
    WTF::StringBuilder2 result;
    if (m_pushedChar1) {
        result.append(m_pushedChar1);
        if (m_pushedChar2)
            result.append(m_pushedChar2);
    }
    m_currentString.appendTo(result);
    if (isComposite()) {
        Deque<SegmentedSubstring2>::const_iterator it = m_substrings.begin();
        Deque<SegmentedSubstring2>::const_iterator e = m_substrings.end();
        for (; it != e; ++it)
            it->appendTo(result);
    }
    return result.toString();
}

void SegmentedString2::advance(unsigned count, UChar* consumedCharacters)
{
    ASSERT_WITH_SECURITY_IMPLICATION(count <= length());
    for (unsigned i = 0; i < count; ++i) {
        consumedCharacters[i] = currentChar();
        advance();
    }
}

/* FYWEBKITMOD BEGIN - using old 16bit WTFString behind the scenes.
void SegmentedString2::advance8()
{
    ASSERT(!m_pushedChar1);
    decrementAndCheckLength();
    m_currentChar = m_currentString.incrementAndGetCurrentChar8();
}
FYWEBKITMOD END */

void SegmentedString2::advance16()
{
    ASSERT(!m_pushedChar1);
    decrementAndCheckLength();
    m_currentChar = m_currentString.incrementAndGetCurrentChar16();
}

/* FYWEBKITMOD BEGIN - using old 16bit WTFString behind the scenes.
void SegmentedString2::advanceAndUpdateLineNumber8()
{
    ASSERT(!m_pushedChar1);
    ASSERT(m_currentString.getCurrentChar() == m_currentChar);
    if (m_currentChar == '\n') {
        ++m_currentLine;
        m_numberOfCharactersConsumedPriorToCurrentLine = numberOfCharactersConsumed() + 1;
    }
    decrementAndCheckLength();
    m_currentChar = m_currentString.incrementAndGetCurrentChar8();
}
FYWEBKITMOD END */

void SegmentedString2::advanceAndUpdateLineNumber16()
{
    ASSERT(!m_pushedChar1);
    ASSERT(m_currentString.getCurrentChar() == m_currentChar);
    if (m_currentChar == '\n') {
        ++m_currentLine;
        m_numberOfCharactersConsumedPriorToCurrentLine = numberOfCharactersConsumed() + 1;
    }
    decrementAndCheckLength();
    m_currentChar = m_currentString.incrementAndGetCurrentChar16();
}

void SegmentedString2::advanceSlowCase()
{
    if (m_pushedChar1) {
        m_pushedChar1 = m_pushedChar2;
        m_pushedChar2 = 0;

        if (m_pushedChar1) {
            m_currentChar = m_pushedChar1;
            return;
        }

        updateAdvanceFunctionPointers();
    } else if (m_currentString.m_length) {
        if (--m_currentString.m_length == 0)
            advanceSubstring();
    } else if (!isComposite()) {
        m_currentString.clear();
        m_empty = true;
        m_fastPathFlags = NoFastPath;
        m_advanceFunc = &SegmentedString2::advanceEmpty;
        m_advanceAndUpdateLineNumberFunc = &SegmentedString2::advanceEmpty;
    }
    m_currentChar = m_currentString.m_length ? m_currentString.getCurrentChar() : 0;
}

void SegmentedString2::advanceAndUpdateLineNumberSlowCase()
{
    if (m_pushedChar1) {
        m_pushedChar1 = m_pushedChar2;
        m_pushedChar2 = 0;

        if (m_pushedChar1) {
            m_currentChar = m_pushedChar1;
            return;
        }

        updateAdvanceFunctionPointers();
    } else if (m_currentString.m_length) {
        if (m_currentString.getCurrentChar() == '\n' && m_currentString.doNotExcludeLineNumbers()) {
            ++m_currentLine;
            // Plus 1 because numberOfCharactersConsumed value hasn't incremented yet; it does with m_length decrement below.
            m_numberOfCharactersConsumedPriorToCurrentLine = numberOfCharactersConsumed() + 1;
        }
        if (--m_currentString.m_length == 0)
            advanceSubstring();
        else
            m_currentString.incrementAndGetCurrentChar(); // Only need the ++
    } else if (!isComposite()) {
        m_currentString.clear();
        m_empty = true;
        m_fastPathFlags = NoFastPath;
        m_advanceFunc = &SegmentedString2::advanceEmpty;
        m_advanceAndUpdateLineNumberFunc = &SegmentedString2::advanceEmpty;
    }

    m_currentChar = m_currentString.m_length ? m_currentString.getCurrentChar() : 0;
}

void SegmentedString2::advanceEmpty()
{
    ASSERT(!m_currentString.m_length && !isComposite());
    m_currentChar = 0;
}

void SegmentedString2::updateSlowCaseFunctionPointers()
{
    m_fastPathFlags = NoFastPath;
    m_advanceFunc = &SegmentedString2::advanceSlowCase;
    m_advanceAndUpdateLineNumberFunc = &SegmentedString2::advanceAndUpdateLineNumberSlowCase;
}

OrdinalNumber SegmentedString2::currentLine() const
{
    return OrdinalNumber::fromZeroBasedInt(m_currentLine);
}

OrdinalNumber SegmentedString2::currentColumn() const
{
    int zeroBasedColumn = numberOfCharactersConsumed() - m_numberOfCharactersConsumedPriorToCurrentLine;
    return OrdinalNumber::fromZeroBasedInt(zeroBasedColumn);
}

void SegmentedString2::setCurrentPosition(OrdinalNumber line, OrdinalNumber columnAftreProlog, int prologLength)
{
    m_currentLine = line.zeroBasedInt();
    m_numberOfCharactersConsumedPriorToCurrentLine = numberOfCharactersConsumed() + prologLength - columnAftreProlog.zeroBasedInt();
}

}
