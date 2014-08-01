/*
 * Copyright 2009, The Android Open Source Project
 * Copyright (C) 2014 FactorY Media Production GmbH
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
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

/* FYWEBKITMOD BEGIN copied over from android/TemporaryLinkStubs.cpp */

#include "config.h"
#include "ScrollbarTheme.h"

namespace WebCore {

// ScrollbarTheme::nativeTheme() is called by RenderTextControl::calcPrefWidths()
// like this: scrollbarSize = ScrollbarTheme::nativeTheme()->scrollbarThickness();
// with this comment:
// // FIXME: We should get the size of the scrollbar from the RenderTheme instead.
// since our text control doesn't have scrollbars, the default size of 0 width should be
// ok. notImplemented() is commented out below so that we can find other unresolved
// unimplemented functions.
ScrollbarTheme* ScrollbarTheme::nativeTheme()
{
    /* notImplemented(); */
    static ScrollbarTheme theme;
    return &theme;
}

}  // namespace WebCore

/* FYWEBKITMOD END */
