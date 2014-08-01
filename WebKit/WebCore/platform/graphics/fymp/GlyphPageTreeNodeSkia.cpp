/*
 * Copyright (c) 2008, 2009 Google Inc. All rights reserved. 
 * Copyright (C) 2014 FactorY Media Production GmbH 
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* FYWEBKITMOD BEGIN basis was chromium/GlyphPageTreeNodeLinux.cpp */

#include "config.h"
#include "GlyphPageTreeNode.h"

#include "Font.h"
#include "SimpleFontData.h"

#include "SkTemplates.h"
#include "SkPaint.h"
#include "SkUtils.h"
#include "SkFontHost_Fy.h"

#if !PLATFORM(FYMP_VS) // FYWEBKITMOD excluded VisualStudio build
#include <std_VectorObj.h>
#endif

namespace WebCore {

class Allocator
	{
public:
	static uint16_t *Allocate(u32f numElements)
		{
		return new uint16_t[numElements];
		}
	static void Deallocate(uint16_t *pAddress)
		{
		delete [] pAddress;
		}
	};

bool GlyphPage::fill(unsigned offset, unsigned length, UChar* buffer, unsigned bufferLength, const SimpleFontData* fontData)
{
    if (SkUTF16_IsHighSurrogate(buffer[bufferLength-1])) {
        SkDebugf("%s last char is high-surrogate", __FUNCTION__);
        return false;
    }
	FYASSERT(sizeof(UChar) == sizeof(STDwchar));

	// note: we always establish a mapping to the very font inside SimpleFontData. BUT: the data present to Webkit
	// allows for fallback fonts as a pointer to the font is present for each mapping!
#if !PLATFORM(FYMP_VS) // FYWEBKITMOD VisualStudio build will use new-operator to gain the buffer
	STDvectorObjJit<uint16_t, 1024, Allocator>	glyphBuffer;
	glyphBuffer.Reserve(bufferLength);
	glyphBuffer.SetSize(bufferLength);
	uint16_t *glyphs = &glyphBuffer[0];
#else
	uint16_t* glyphs = new uint16_t[bufferLength];
#endif
	bool bAnyGood = SkFontHostFy::CharactersToGlyphs(fontData->platformData().font(), (const STDwchar*)buffer, bufferLength, glyphs);
	for (unsigned i = 0; i < length; ++i)
		setGlyphDataForIndex(offset + i, glyphs[i], glyphs[i] ? fontData : NULL);

#if PLATFORM(FYMP_VS)
	delete[] glyphs;
#endif

	return bAnyGood;
}

}  // namespace WebCore

/* FYWEBKITMOD END */