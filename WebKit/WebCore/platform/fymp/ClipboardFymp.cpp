/*
 * Copyright 2009, The Android Open Source Project
 * Copyright (C) 2006, 2007 Apple Inc.  All rights reserved.
 * Copyright (C) 2014 FactorY Media Production GmbH
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
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* FYWEBKITMOD BEGIN copied over from android/ClipboardAndroid.cpp */

#include "config.h"
#include "ClipboardFymp.h"

#include "CachedImage.h"
#include "Element.h"
#include "FileList.h"
#include "Frame.h"
#include "Range.h"

namespace WebCore {

ClipboardFymp::ClipboardFymp(ClipboardAccessPolicy policy, bool isForDragging)
    : Clipboard(policy, isForDragging)
{
}

ClipboardFymp::~ClipboardFymp()
{
}

void ClipboardFymp::clearData(const String&)
{
    ASSERT(isForDragging());
}

void ClipboardFymp::clearAllData()
{
    ASSERT(isForDragging());
}

String ClipboardFymp::getData(const String&, bool& success) const
{
    success = false;
    return "";
}

bool ClipboardFymp::setData(const String&, const String&)
{
    ASSERT(isForDragging());
    return false;
}

// extensions beyond IE's API
HashSet<String> ClipboardFymp::types() const
{
    return HashSet<String>();
}

PassRefPtr<FileList> ClipboardFymp::files() const
{
    return 0;
}

void ClipboardFymp::setDragImage(CachedImage*, const IntPoint&)
{
}

void ClipboardFymp::setDragImageElement(Node*, const IntPoint&)
{
}

DragImageRef ClipboardFymp::createDragImage(IntPoint&) const
{
    return 0;
}

void ClipboardFymp::declareAndWriteDragImage(Element*, const KURL&, const String&, Frame*)
{
}

void ClipboardFymp::writeURL(const KURL&, const String&, Frame*)
{
}

void ClipboardFymp::writeRange(Range* selectedRange, Frame*)
{
    ASSERT(selectedRange);
}

void ClipboardFymp::writePlainText(const String&)
{
}

bool ClipboardFymp::hasData()
{
    return false;
}

} // namespace WebCore

/* FYWEBKITMOD END */
