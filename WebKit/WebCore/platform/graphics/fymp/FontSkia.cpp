/*
 * Copyright (c) 2007, 2008, Google Inc. All rights reserved.
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

/* FYWEBKITMOD BEGIN copy of chromium/FontLinux.cpp */

#include "config.h"
#include "Font.h"

#include "FloatRect.h"
#include "GlyphBuffer.h"
#include "GraphicsContext.h"
#include "NotImplemented.h"
#include "PlatformContextSkia.h"

#include "SkCanvas.h"
#include "SkPaint.h"
#include "SkTemplates.h"

namespace WebCore {

bool Font::canReturnFallbackFontsForComplexText()
{
    return false;
}

static bool isCanvasMultiLayered(SkCanvas* canvas)
{
//SLOW?


/* FYWEBKITMOD begin */
#if PLATFORM(FYMP_VS)
    SkCanvas::LayerIter layerIterator(canvas, false); // VisualStudio build falls back on original code
#else
    SkCanvas_LayerIter layerIterator(canvas, false);
#endif
/* FYWEBKITMOD end */
    layerIterator.next();
    return !layerIterator.done();
}

static void adjustTextRenderMode(SkPaint* paint, bool isCanvasMultiLayered)
{
    // Our layers only have a single alpha channel. This means that subpixel
    // rendered text cannot be compositied correctly when the layer is
    // collapsed. Therefore, subpixel text is disabled when we are drawing
    // onto a layer.
    if (isCanvasMultiLayered)
        paint->setLCDRenderText(false);
}

void Font::drawGlyphs(GraphicsContext* gc, const SimpleFontData* font,
                      const GlyphBuffer& glyphBuffer,  int from, int numGlyphs,
                      const FloatPoint& point) const {
    SkASSERT(sizeof(GlyphBufferGlyph) == sizeof(uint16_t)); // compile-time assert

    int textMode = gc->platformContext()->getTextDrawingMode();

    // Only support fill style.
	// (as in: "clip" and "stroke" are not supported!)
    if (textMode & cTextFill) {
		SkCanvas* canvas = gc->platformContext()->canvas();

		const GlyphBufferGlyph* glyphs = glyphBuffer.glyphs(from);
		SkScalar x = SkFloatToScalar(point.x());
		SkScalar y = SkFloatToScalar(point.y());

		bool haveMultipleLayers = isCanvasMultiLayered(canvas);

        SkPaint paint;
        gc->platformContext()->setupPaintForFilling(&paint);
        font->platformData().setupPaint(&paint);
        adjustTextRenderMode(&paint, haveMultipleLayers);
        paint.setTextEncoding(SkPaint::kGlyphID_TextEncoding);
        paint.setColor(gc->fillColor().rgb());

//FYWEBKITMOD begin
#if !PLATFORM(FYMP_VS) // VisualStudio build falls back on original code
		// note: paint is passed in as we need to be able to do multi-pass rendering (shadows) etc.
        canvas->drawText_FYMP(glyphs, numGlyphs << 1, x, y, paint, font->platformData().font());
#else
		// original
        canvas->drawText(glyphs, numGlyphs << 1, x, y, paint);
#endif
//FYWEBKITMOD end
    }
}

void Font::drawComplexText(GraphicsContext* gc, const TextRun& run,
                           const FloatPoint& point, int from, int to) const
{
    notImplemented();
}

float Font::floatWidthForComplexText(const TextRun& run, HashSet<const SimpleFontData*>* /* fallbackFonts */, GlyphOverflow* /* glyphOverflow */) const
{
    notImplemented();
    return 0.0f;
}

// Return the code point index for the given |x| offset into the text run.
int Font::offsetForPositionForComplexText(const TextRun& run, float xFloat,
                                          bool includePartialGlyphs) const
{
    notImplemented();
    return 0;
}

// Return the rectangle for selecting the given range of code-points in the TextRun.
FloatRect Font::selectionRectForComplexText(const TextRun& run,
                                            const FloatPoint& point, int height,
                                            int from, int to) const
{
    notImplemented();
    return FloatRect();
}

} // namespace WebCore

/* FYWEBKITMOD END */

