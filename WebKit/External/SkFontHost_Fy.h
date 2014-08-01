/*
  * Copyright (C) 2014 FactorY Media Production GmbH
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted.
  *
  * THIS SOFTWARE IS PROVIDED BY FACTORY MEDIA PRODUCTION GMBH AND ITS CONTRIBUTORS "AS IS" AND ANY
  * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  * ARE DISCLAIMED.  IN NO EVENT SHALL FACTORY MEDIA PRODUCTION GMBH OR CONTRIBUTORS BE LIABLE FOR ANY
  * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
  * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
  * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  */

/**************************************************************************/
/*                                                                        */
/*    File: SkFontHost_fy.h                                               */
/* Purpose: class to encapsulate a font data set                          */
/*                                                                        */
/**************************************************************************/

#ifndef _SKFONTHOST_FY_H_
#define _SKFONTHOST_FY_H_

#include "fytypes.h"

//--------------------------------------------------------------------------

typedef wchar_t	STDwchar;

//#include <std_String.h>
class FONTfont;
class SkTypeface;
//class STDwchar;

//--------------------------------------------------------------------------

namespace SkFontHostFy {

struct FontMetrics {
	f32    fTop;       		//!< The greatest distance above the baseline for any glyph (will be <= 0)
	f32    fAscent;    		//!< The recommended distance above the baseline (will be <= 0)
	f32    fDescent;   		//!< The recommended distance below the baseline (will be >= 0)
	f32    fBottom;    		//!< The greatest distance below the baseline for any glyph (will be >= 0)
	f32    fLeading;   		//!< The recommended distance to add between lines of text (will be >= 0)
	f32    fAvgCharWidth;	//!< the average charactor width (>= 0)
	f32    fXMin;      		//!< The minimum bounding box x value for all glyphs
	f32    fXMax;      		//!< The maximum bounding box x value for all glyphs
	f32    fXHeight;   		//!< the height of an 'x' in px, or 0 if no 'x' in face
};

FONTfont* GetFont(SkTypeface *pTypeFace, f32 textSizeInPixels, u8 obliqueStyle);
void ReleaseFont(FONTfont *pFont);
void AddFontReference(FONTfont *pFont);

f32 GetKerningPair(FONTfont *pFont, u16 leftGlyph, u16 rightGlyph);
void GetMetrics(FONTfont *pFont, FontMetrics *pMetrics);
f32 GetGlyphWidth(FONTfont *pFont, u16 glyph);
void GetGlyphBounds(FONTfont *pFont, u16 glyph, SkRect & rect);

bool HasCharacters(FONTfont *pFont, const STDwchar *pCharacters, u32 numCharacters);
bool CharactersToGlyphs(FONTfont *pFont, const STDwchar *pCharacters, u32 numCharacters, u16 *pGlyphs);

} // SkFontHostFy

//--------------------------------------------------------------------------

#endif // _SKFONTHOST_FY_H_

