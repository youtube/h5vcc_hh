/*
 * Copyright (C) 2009, 2010, 2012, 2013 Apple Inc. All rights reserved.
 * Copyright (C) 2012 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

// FYMP - file integrated from r152754

/* FYMP
You ask yourself, what happened to this file? 
It was integrated from r152754 when we needed TextTrack functionality. 
Decision was made, that the old WTFString is kept. 
That old string class is always utf-16 and is in WebCore namespace (just like AtomicString and StringImpl) 
in contrast to the new classes which are in namespace WTF. 
I have marked all changes except the explicit namespaces added to the String classes mentioned above.
*/

#ifndef StringBuilder2_h
#define StringBuilder2_h

#include <wtf/text/AtomicString.h>
#include <wtf/text/WTFString.h>

namespace WTF {

class StringBuilder2 : public Noncopyable { // FYMP - integrating parts of r152754. Derive instead of below macro.
    // Disallow copying since it's expensive and we don't want code to do it by accident.
    // WTF_MAKE_NONCOPYABLE(StringBuilder2);

public:
    StringBuilder2()
        : m_length(0)
/* FYMP begin - integrating parts of t152754 but keeping old WTFString, which is always utf16.
        , m_is8Bit(false) 
        , m_valid16BitShadowLength(0) 
    	, m_bufferCharacters8(0)
    	*/
		, m_bufferCharacters16(0)
// FYMP end
    {
    }

    void append(const UChar*, unsigned);
    void append(const LChar*, unsigned);

    ALWAYS_INLINE void append(const char* characters, unsigned length) { append(reinterpret_cast<const LChar*>(characters), length); }

    void append(const WebCore::String& string)
    {
        if (!string.length())
            return;

        // If we're appending to an empty string, and there is not a buffer (reserveCapacity has not been called)
        // then just retain the string.
        if (!m_length && !m_buffer) {
            m_string = string;
            m_length = string.length();
//            m_is8Bit = m_string.is8Bit(); // FYMP
            return;
        }

// FYMP begin - integrating part of r152754 but keep old WTFString.
		append(string.characters(), string.length());
/*
        if (string.is8Bit())
            append(string.characters8(), string.length());
        else
            append(string.characters16(), string.length());
*/
// FYMP end
    }

    void append(const StringBuilder2& other)
    {
        if (!other.m_length)
            return;

        // If we're appending to an empty string, and there is not a buffer (reserveCapacity has not been called)
        // then just retain the string.
        if (!m_length && !m_buffer && !other.m_string.isNull()) {
            m_string = other.m_string;
            m_length = other.m_length;
            return;
        }
// FYMP begin - integrating parts of t152754 but keeping old WTFString which is always utf-16
		/*
        if (other.is8Bit())
            append(other.characters8(), other.m_length);
        else
            append(other.characters16(), other.m_length);
		*/
		append(other.characters(), other.m_length);
// FYMP end
    }

    void append(const WebCore::String& string, unsigned offset, unsigned length)
    {
        if (!string.length())
            return;

        if ((offset + length) > string.length())
            return;

// FYMP begin - integrating part of r152754 but keep old WTFString. Old WTFString seems to be UTF-16.
		append(string.characters() + offset, length);
/*
        if (string.is8Bit())
            append(string.characters8() + offset, length);
        else
            append(string.characters16() + offset, length);
*/
// FYMP end
    }

    void append(const char* characters)
    {
        if (characters)
            append(characters, strlen(characters));
    }

    void append(UChar c)
    {
        if (m_buffer && m_length < m_buffer->length() && m_string.isNull()) {
/* FYMP begin - keeping old WTFString.
			if (!m_is8Bit) {
                m_bufferCharacters16[m_length++] = c;
                return;
            }

            if (!(c & ~0xff)) {
                m_bufferCharacters8[m_length++] = static_cast<LChar>(c);
                return;
            }
FYMP end */

			m_bufferCharacters16[m_length++] = c;
			return;

        }
        append(&c, 1);
    }

    void append(LChar c)
    {
        if (m_buffer && m_length < m_buffer->length() && m_string.isNull()) {
/* FYMP begin
            if (m_is8Bit)
                m_bufferCharacters8[m_length++] = c;
            else
                m_bufferCharacters16[m_length++] = c;
				*/
			m_bufferCharacters16[m_length++];
			// FYMP end
        } else
            append(&c, 1);
    }

    void append(char c)
    {
        append(static_cast<LChar>(c));
    }

    void append(UChar32 c)
    {
        if (U_IS_BMP(c)) {
            append(static_cast<UChar>(c));
            return;
        }
        append(U16_LEAD(c));
        append(U16_TRAIL(c));
    }

    template<unsigned charactersCount>
    ALWAYS_INLINE void appendLiteral(const char (&characters)[charactersCount]) { append(characters, charactersCount - 1); }

    void appendNumber(int);
    void appendNumber(unsigned int);
    void appendNumber(long);
    void appendNumber(unsigned long);
    void appendNumber(long long);
    void appendNumber(unsigned long long);

    WebCore::String toString()
    {
        shrinkToFit();
        if (m_string.isNull())
            reifyString();
        return m_string;
    }

    const WebCore::String& toStringPreserveCapacity() const
    {
        if (m_string.isNull())
            reifyString();
        return m_string;
    }

    WebCore::AtomicString toAtomicString() const
    {
// FYMP begin - in a hurry
//        if (!m_length)
//            return emptyAtom;
// FYMP end

        // If the buffer is sufficiently over-allocated, make a new AtomicString from a copy so its buffer is not so large.
        if (canShrink()) {
/* FYMP begin
            if (is8Bit())
                return AtomicString(characters8(), length());
FYMP end */
            return WebCore::AtomicString(characters(), length());
        }

        if (!m_string.isNull())
            return WebCore::AtomicString(m_string);

        ASSERT(m_buffer);

//        return WebCore::AtomicString(m_buffer.get(), 0, m_length); FYMP
		return WebCore::AtomicString(m_buffer.get()->characters(), m_length); // FYMP
    }

    unsigned length() const
    {
        return m_length;
    }

    bool isEmpty() const { return !m_length; }

    void reserveCapacity(unsigned newCapacity);

    unsigned capacity() const
    {
        return m_buffer ? m_buffer->length() : m_length;
    }

    void resize(unsigned newSize);

    bool canShrink() const;

    void shrinkToFit();

    UChar operator[](unsigned i) const
    {
        ASSERT_WITH_SECURITY_IMPLICATION(i < m_length);
/* FYMP begin
        if (m_is8Bit)
            return characters8()[i];

        return characters16()[i];
*/
		return characters()[i];
		// FYMP end 
    }

/* FYMP
    const LChar* characters8() const
    {
        ASSERT(m_is8Bit);
        if (!m_length)
            return 0;
        if (!m_string.isNull())
            return m_string.characters8();
        ASSERT(m_buffer);
        return m_buffer->characters8();
    }
*/

    const UChar* characters16() const
    {
/* FYMP begin
        ASSERT(!m_is8Bit);
        if (!m_length)
            return 0;
        if (!m_string.isNull())
            return m_string.characters16();
        ASSERT(m_buffer);
    	return m_buffer->characters16();
*/
		return m_buffer->characters();
// FYMP end
    }
    
    const UChar* characters() const
    {
/* FYMP
        if (!m_length)
            return 0;
        if (!m_string.isNull())
            return m_string.characters();
        ASSERT(m_buffer);
        if (m_buffer->has16BitShadow() && m_valid16BitShadowLength < m_length)
            m_buffer->upconvertCharacters(m_valid16BitShadowLength, m_length);

        m_valid16BitShadowLength = m_length;
*/

        return m_buffer->characters();
    }
    
    bool is8Bit() const { return /*m_is8Bit*/ false; } // FYMP - keeping old WTFString which is always utf-16.

    void clear()
    {
        m_length = 0;
        m_string = WebCore::String();
        m_buffer = 0;
		m_bufferCharacters16 = 0;
//        m_bufferCharacters8 = 0; FYMP
//        m_is8Bit = true; FYMP
//        m_valid16BitShadowLength = 0; FYMP
    }

    void swap(StringBuilder2& stringBuilder)
    {
        std::swap(m_length, stringBuilder.m_length);
        m_string.swap(stringBuilder.m_string);
        m_buffer.swap(stringBuilder.m_buffer);
//        std::swap(m_is8Bit, stringBuilder.m_is8Bit);                                  // FYMP
//        std::swap(m_valid16BitShadowLength, stringBuilder.m_valid16BitShadowLength);  // FYMP
//        std::swap(m_bufferCharacters8, stringBuilder.m_bufferCharacters8);            // FYMP
		std::swap(m_bufferCharacters16, stringBuilder.m_bufferCharacters16); // FYMP
    }

private:
// FYMP begin - keeping old 16bit WTFString in the background. Thus, only UChar is of interest.
//    void allocateBuffer(const LChar* currentCharacters, unsigned requiredLength); FYMP - keeping old WTFString.
    void allocateBuffer(const UChar* currentCharacters, unsigned requiredLength);
//    void allocateBufferUpConvert(const LChar* currentCharacters, unsigned requiredLength); FYMP - keeping old WTFString.

//	template <typename CharType>
//    void reallocateBuffer(unsigned requiredLength);
	void reallocateBuffer(unsigned requiredLength);

//	template <typename CharType>
//    ALWAYS_INLINE CharType* appendUninitialized(unsigned length);
    ALWAYS_INLINE UChar* appendUninitialized(unsigned length);

//    template <typename CharType>
//    CharType* appendUninitializedSlow(unsigned length);
    UChar* appendUninitializedSlow(unsigned length);


//    template <typename CharType>
//    ALWAYS_INLINE CharType * getBufferCharacters();
	ALWAYS_INLINE UChar* getBufferCharacters();
// FYMP end
    void reifyString() const;

    unsigned m_length;
    mutable WebCore::String m_string;
    RefPtr<WebCore::StringImpl> m_buffer;
//    const bool m_is8Bit; // FYMP - keeping old WTFString which is always utf-16
//    mutable unsigned m_valid16BitShadowLength; // FYMP - dont need it. right?
/* FYMP begin - keeping old WTFString
	union {
        LChar* m_bufferCharacters8;
        UChar* m_bufferCharacters16;
    };
*/
	UChar* m_bufferCharacters16;
	// FYMP end	
};

/* FYMP begin
template <>
ALWAYS_INLINE LChar* StringBuilder2::getBufferCharacters<LChar>()
{
    ASSERT(m_is8Bit);
    return m_bufferCharacters8;
}
FYMP end */

//template <> FYMP
ALWAYS_INLINE UChar* StringBuilder2::getBufferCharacters/*<UChar> FYMP*/()
{
//    ASSERT(!m_is8Bit); FYMP
//    return m_bufferCharacters16; FYMP
	return m_bufferCharacters16;
}    

template <typename CharType>
bool equal(const StringBuilder2& s, const CharType* buffer, unsigned length)
{
    if (s.length() != length)
        return false;
/* FYMP begin
    if (s.is8Bit())
        return equal(s.characters8(), buffer, length);

    return equal(s.characters16(), buffer, length);
*/
	return equal(s.characters(), buffer, length);
	// FYMP end
}

template <typename StringType>
bool equal(const StringBuilder2& a, const StringType& b)
{
    if (a.length() != b.length())
        return false;

    if (!a.length())
        return true;
/* FYMP begin
    if (a.is8Bit()) {
        if (b.is8Bit())
            return equal(a.characters8(), b.characters8(), a.length());
        return equal(a.characters8(), b.characters16(), a.length());
    }

    if (b.is8Bit())
        return equal(a.characters16(), b.characters8(), a.length());
    return equal(a.characters16(), b.characters16(), a.length());
	*/
	return WebCore::equal(a.characters(), b.characters(), a.length());
	// FYMP end
}

inline bool operator==(const StringBuilder2& a, const StringBuilder2& b) { return equal(a, b); }
inline bool operator!=(const StringBuilder2& a, const StringBuilder2& b) { return !equal(a, b); }
inline bool operator==(const StringBuilder2& a, const WebCore::String& b) { return equal(a, b); }
inline bool operator!=(const StringBuilder2& a, const WebCore::String& b) { return !equal(a, b); }
inline bool operator==(const WebCore::String& a, const StringBuilder2& b) { return equal(b, a); }
inline bool operator!=(const WebCore::String& a, const StringBuilder2& b) { return !equal(b, a); }

} // namespace WTF

using WTF::StringBuilder2;

#endif // StringBuilder2_h
