/*
 * Copyright (c) 2008, 2009, Google Inc. All rights reserved. 
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

/* FYWEBKITMOD BEGIN basis was chromium/SimpleFontDataLinux.cpp */

#include "config.h"
#include "SimpleFontData.h"

#include "Font.h"
#include "FontCache.h"
#include "FloatRect.h"
#include "FontDescription.h"
#include "Logging.h"

#include "SkFontHost.h"
//#if !PLATFORM(FYMP_VS) // FYWEBKITMOD excluded VisualStudio build
#include "SkFontHost_Fy.h"
//#endif
#include "SkPaint.h"
#include "SkTime.h"
#include "SkTypeface.h"
#include "SkTypes.h"
#include "SkiaUtils.h"

namespace WebCore {

// Smallcaps versions of fonts are 70% the size of the normal font.
static const float smallCapsFraction = 0.7f;

void SimpleFontData::platformInit()
{
    SkFontHostFy::FontMetrics  metrics;
    SkFontHostFy::GetMetrics(m_platformData.font(), &metrics);

//FYMP
//OLD:
//    SkScalar height = -metrics.fAscent + metrics.fDescent + metrics.fLeading;
//    m_ascent = SkScalarRound(-metrics.fAscent);
//    m_descent = SkScalarRound(height) - m_ascent;
//NEW:
/*
	We route the ascent and descent values from FT through to here, BUT:
	- freetype docs state they are the "recommended values".
	- there are also these top/bottom values with are including "everything"
	- that seems to be what Webkit expects! Not an estimate what usually fits, but the worst case
	===> hence we use these to inform our line spacing during layout!!!
*/
    SkScalar height = -metrics.fTop + metrics.fBottom + metrics.fLeading;
    m_ascent = SkScalarRound(-metrics.fTop);
    m_descent = SkScalarRound(height) - m_ascent;

    if (metrics.fXHeight)
        m_xHeight = metrics.fXHeight;
    else
    {
        // hack taken from the Windows port
        m_xHeight = m_ascent * 0.56f;
    }

    m_lineGap = SkScalarRound(metrics.fLeading);
    m_lineSpacing = m_ascent + m_descent + m_lineGap;

	GlyphPage* glyphPageZero = GlyphPageTreeNode::getRootChild(this, 0)->page();
	ASSERT(glyphPageZero);

    if (metrics.fAvgCharWidth > 0.0f)
        m_avgCharWidth = metrics.fAvgCharWidth;
    else
    {
    	const Glyph zeroGlyph = glyphPageZero->glyphDataForCharacter(L'0').glyph;
    	m_avgCharWidth = zeroGlyph ? widthForGlyph(zeroGlyph) : 0.0f;
    }

	const Glyph wGlyph = glyphPageZero->glyphDataForCharacter(L'W').glyph;
	if (wGlyph)
		m_maxCharWidth = widthForGlyph(wGlyph);
	Glyph m_spaceGlyph = glyphPageZero->glyphDataForCharacter(L' ').glyph;

	if (m_spaceGlyph)
		{
		m_spaceWidth = widthForGlyph(m_spaceGlyph);
		m_adjustedSpaceWidth = roundf(m_spaceWidth);
		}

	m_zeroWidthSpaceGlyph = glyphPageZero->glyphDataForCharacter(0).glyph;
}

void SimpleFontData::platformCharWidthInit()
{
    // charwidths are set in platformInit.
}

void SimpleFontData::platformDestroy()
{
    delete m_smallCapsFontData;
    m_smallCapsFontData = 0;
}

SimpleFontData* SimpleFontData::smallCapsFontData(const FontDescription& fontDescription) const
{
    if (!m_smallCapsFontData) {
        const float smallCapsSize = lroundf(fontDescription.computedSize() * smallCapsFraction);
        m_smallCapsFontData = new SimpleFontData(FontPlatformData(m_platformData, smallCapsSize));
    }

    return m_smallCapsFontData;
}

bool SimpleFontData::containsCharacters(const UChar* characters, int length) const
{
    FYASSERT(sizeof(UChar) == sizeof(STDwchar));
    return SkFontHostFy::HasCharacters(m_platformData.font(), (const STDwchar*)characters, length);
}

void SimpleFontData::determinePitch()
{
    m_treatAsFixedPitch = platformData().isFixedPitch();
}

FloatRect SimpleFontData::platformBoundsForGlyph(Glyph glyph) const
{
	SkRect rect;
	SkFontHostFy::GetGlyphBounds(m_platformData.font(), glyph, rect);
    return FloatRect(rect);
}
    
float SimpleFontData::platformWidthForGlyph(Glyph glyph) const
{
    return SkFontHostFy::GetGlyphWidth(m_platformData.font(), glyph);
}

float SimpleFontData::platformKerningPair(Glyph left, Glyph right) const
{
    return SkFontHostFy::GetKerningPair(m_platformData.font(), left, right);
}

}  // namespace WebCore

/* FYWEBKITMOD END */

