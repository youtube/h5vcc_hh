/*
 * Copyright (c) 2008, Google Inc. All rights reserved.
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

#include "config.h"

#include "AffineTransform.h"
#include "BitmapImage.h"
#include "BitmapImageSingleFrameSkia.h"
#if !PLATFORM(FYMP) // FYWEBKITMOD removing ChromiumBridge.h
#include "ChromiumBridge.h"
#endif
#include "FloatConversion.h"
#include "FloatRect.h"
#include "GraphicsContext.h"
#include "Logging.h"
#include "NativeImageSkia.h"
#include "PlatformContextSkia.h"
#include "PlatformString.h"
#include "SkiaUtils.h"
#include "SkRect.h"
#include "SkShader.h"
#include "CurrentTime.h" // FYWEBKITMOD

#include "skia/ext/image_operations.h"
#include "skia/ext/platform_canvas.h"

double gBitmapFadeInSeconds = 0.0; // FYWEBKITMOD

namespace WebCore {

#if 0 /* FYWEBKITMOD BEGIN disabled */
// Used by computeResamplingMode to tell how bitmaps should be resampled.
enum ResamplingMode {
    // Nearest neighbor resampling. Used when we detect that the page is
    // trying to make a pattern by stretching a small bitmap very large.
    RESAMPLE_NONE,

    // Default skia resampling. Used for large growing of images where high
    // quality resampling doesn't get us very much except a slowdown.
    RESAMPLE_LINEAR,

    // High quality resampling.
    RESAMPLE_AWESOME,
};

static ResamplingMode computeResamplingMode(PlatformContextSkia* platformContext, const NativeImageSkia& bitmap, int srcWidth, int srcHeight, float destWidth, float destHeight)
{
    if (platformContext->hasImageResamplingHint()) {
        IntSize srcSize;
        FloatSize dstSize;
        platformContext->getImageResamplingHint(&srcSize, &dstSize);
        srcWidth = srcSize.width();
        srcHeight = srcSize.height();
        destWidth = dstSize.width();
        destHeight = dstSize.height();
    }

    int destIWidth = static_cast<int>(destWidth);
    int destIHeight = static_cast<int>(destHeight);

    // The percent change below which we will not resample. This usually means
    // an off-by-one error on the web page, and just doing nearest neighbor
    // sampling is usually good enough.
    const float kFractionalChangeThreshold = 0.025f;

    // Images smaller than this in either direction are considered "small" and
    // are not resampled ever (see below).
    const int kSmallImageSizeThreshold = 8;

    // The amount an image can be stretched in a single direction before we
    // say that it is being stretched so much that it must be a line or
    // background that doesn't need resampling.
    const float kLargeStretch = 3.0f;

    // Figure out if we should resample this image. We try to prune out some
    // common cases where resampling won't give us anything, since it is much
    // slower than drawing stretched.
    if (srcWidth == destIWidth && srcHeight == destIHeight) {
        // We don't need to resample if the source and destination are the same.
        return RESAMPLE_NONE;
    }

    if (srcWidth <= kSmallImageSizeThreshold
        || srcHeight <= kSmallImageSizeThreshold
        || destWidth <= kSmallImageSizeThreshold
        || destHeight <= kSmallImageSizeThreshold) {
        // Never resample small images. These are often used for borders and
        // rules (think 1x1 images used to make lines).
        return RESAMPLE_NONE;
    }

    if (srcHeight * kLargeStretch <= destHeight || srcWidth * kLargeStretch <= destWidth) {
        // Large image detected.

        // Don't resample if it is being stretched a lot in only one direction.
        // This is trying to catch cases where somebody has created a border
        // (which might be large) and then is stretching it to fill some part
        // of the page.
        if (srcWidth == destWidth || srcHeight == destHeight)
            return RESAMPLE_NONE;

        // The image is growing a lot and in more than one direction. Resampling
        // is slow and doesn't give us very much when growing a lot.
        return RESAMPLE_LINEAR;
    }

    if ((fabs(destWidth - srcWidth) / srcWidth < kFractionalChangeThreshold)
        && (fabs(destHeight - srcHeight) / srcHeight < kFractionalChangeThreshold)) {
        // It is disappointingly common on the web for image sizes to be off by
        // one or two pixels. We don't bother resampling if the size difference
        // is a small fraction of the original size.
        return RESAMPLE_NONE;
    }

    // When the image is not yet done loading, use linear. We don't cache the
    // partially resampled images, and as they come in incrementally, it causes
    // us to have to resample the whole thing every time.
    if (!bitmap.isDataComplete())
        return RESAMPLE_LINEAR;

    // Everything else gets resampled.
    // If the platform context permits high quality interpolation, use it.
    if (platformContext->interpolationQuality() == InterpolationHigh)
        return RESAMPLE_AWESOME;

    return RESAMPLE_LINEAR;
}

// Draws the given bitmap to the given canvas. The subset of the source bitmap
// identified by src_rect is drawn to the given destination rect. The bitmap
// will be resampled to resample_width * resample_height (this is the size of
// the whole image, not the subset). See shouldResampleBitmap for more.
//
// This does a lot of computation to resample only the portion of the bitmap
// that will only be drawn. This is critical for performance since when we are
// scrolling, for example, we are only drawing a small strip of the image.
// Resampling the whole image every time is very slow, so this speeds up things
// dramatically.
static void drawResampledBitmap(SkCanvas& canvas, SkPaint& paint, const NativeImageSkia& bitmap, const SkIRect& srcIRect, const SkRect& destRect)
{
    // First get the subset we need. This is efficient and does not copy pixels.
    SkBitmap subset;
    bitmap.extractSubset(&subset, srcIRect);
    SkRect srcRect;
    srcRect.set(srcIRect);

    // Whether we're doing a subset or using the full source image.
    bool srcIsFull = srcIRect.fLeft == 0 && srcIRect.fTop == 0
        && srcIRect.width() == bitmap.width()
        && srcIRect.height() == bitmap.height();

    // We will always draw in integer sizes, so round the destination rect.
    SkIRect destRectRounded;
    destRect.round(&destRectRounded);
    SkIRect resizedImageRect =  // Represents the size of the resized image.
        { 0, 0, destRectRounded.width(), destRectRounded.height() };

    if (srcIsFull && bitmap.hasResizedBitmap(destRectRounded.width(), destRectRounded.height())) {
        // Yay, this bitmap frame already has a resized version.
        SkBitmap resampled = bitmap.resizedBitmap(destRectRounded.width(), destRectRounded.height());
        canvas.drawBitmapRect(resampled, 0, destRect, &paint);
        return;
    }

    // Compute the visible portion of our rect.
    SkRect destBitmapSubsetSk;
    ClipRectToCanvas(canvas, destRect, &destBitmapSubsetSk);
    destBitmapSubsetSk.offset(-destRect.fLeft, -destRect.fTop);

    // The matrix inverting, etc. could have introduced rounding error which
    // causes the bounds to be outside of the resized bitmap. We round outward
    // so we always lean toward it being larger rather than smaller than we
    // need, and then clamp to the bitmap bounds so we don't get any invalid
    // data.
    SkIRect destBitmapSubsetSkI;
    destBitmapSubsetSk.roundOut(&destBitmapSubsetSkI);
    if (!destBitmapSubsetSkI.intersect(resizedImageRect))
        return;  // Resized image does not intersect.

/* FYWEBKITMOD BEGIN */
#if PLATFORM(FYMP)
	/*
		Skia will try to safe on rendering complexity by scaling images ahead of time - and possibly caching them.
		As we render with HW support we can scale with "zero" extra cost! Hence we implement a version of things,
		which does simply... not scale!
	*/
	if (srcIsFull) {
		// All of the source is to be drawn... just do it!
        canvas.drawBitmapRect(bitmap, 0, destRect, &paint);
	} else {
		// Just a subsection is needed! Extract it...
		// (this will generate a new bitmap instance pointing to the same Skia data -> but we will later on make a special native version -> wasteful, but Skia's way!)
		SkBitmap subBitmap;
		if (!bitmap.extractSubset(&subBitmap, srcIRect))
			return;
        canvas.drawBitmapRect(subBitmap, 0, destRect, &paint);
	}
#else
/* FYWEBKITMOD END */
    if (srcIsFull && bitmap.shouldCacheResampling(
            resizedImageRect.width(),
            resizedImageRect.height(),
            destBitmapSubsetSkI.width(),
            destBitmapSubsetSkI.height())) {
        // We're supposed to resize the entire image and cache it, even though
        // we don't need all of it.
        SkBitmap resampled = bitmap.resizedBitmap(destRectRounded.width(),
                                                  destRectRounded.height());
        canvas.drawBitmapRect(resampled, 0, destRect, &paint);
    } else {
        // We should only resize the exposed part of the bitmap to do the
        // minimal possible work.

        // Resample the needed part of the image.
        SkBitmap resampled = skia::ImageOperations::Resize(subset,
            skia::ImageOperations::RESIZE_LANCZOS3,
            destRectRounded.width(), destRectRounded.height(),
            destBitmapSubsetSkI);

        // Compute where the new bitmap should be drawn. Since our new bitmap
        // may be smaller than the original, we have to shift it over by the
        // same amount that we cut off the top and left.
        destBitmapSubsetSkI.offset(destRect.fLeft, destRect.fTop);
        SkRect offsetDestRect;
        offsetDestRect.set(destBitmapSubsetSkI);

        canvas.drawBitmapRect(resampled, 0, offsetDestRect, &paint);
    }
#endif
}
#endif /* FYWEBKITMOD END */

static void paintSkBitmap(PlatformContextSkia* platformContext, const NativeImageSkia& nativeImage, const SkIRect& srcRect, const SkRect& destRect, const SkXfermode::Mode& compOp, double nativeImageAge) // FYWEBKITMOD adding parameter 'nativeImageAge'
{
    SkPaint paint;
    paint.setXfermodeMode(compOp);
    paint.setFilterBitmap(true);
    int alpha = roundf(platformContext->getAlpha() * 256);
    if (alpha > 255)
        alpha = 255;
    else if (alpha < 0)
        alpha = 0;
/* FYWEBKITMOD BEGIN */
    if(gBitmapFadeInSeconds > 0.0) {
        if(nativeImageAge < gBitmapFadeInSeconds) {
            alpha = (int)(alpha * (nativeImageAge / gBitmapFadeInSeconds));
        }
    }
/* FYWEBKITMOD END */
    paint.setAlpha(alpha);

    skia::PlatformCanvas* canvas = platformContext->canvas();

/* FYWEBKITMOD BEGIN commented out
    ResamplingMode resampling = platformContext->isPrinting() ? RESAMPLE_NONE :
        computeResamplingMode(platformContext, nativeImage, srcRect.width(), srcRect.height(),
                              SkScalarToFloat(destRect.width()),
                              SkScalarToFloat(destRect.height()));
    if (resampling == RESAMPLE_AWESOME) {
        drawResampledBitmap(*canvas, paint, nativeImage, srcRect, destRect);
    } else {
FYWEBKITMOD END */        
        // No resampling necessary, we can just draw the nativeImage. We want to
        // filter it if we decided to do linear interpolation above, or if there
        // is something interesting going on with the matrix (like a rotation).
        // Note: for serialization, we will want to subset the nativeImage first so
        // we don't send extra pixels.
        canvas->drawBitmapRect(nativeImage, &srcRect, destRect, &paint);
//    }
}

// Transforms the given dimensions with the given matrix. Used to see how big
// images will be once transformed.
static void TransformDimensions(const SkMatrix& matrix, float srcWidth, float srcHeight, float* destWidth, float* destHeight) {
    // Transform 3 points to see how long each side of the bitmap will be.
    SkPoint src_points[3];  // (0, 0), (width, 0), (0, height).
    src_points[0].set(0, 0);
    src_points[1].set(SkFloatToScalar(srcWidth), 0);
    src_points[2].set(0, SkFloatToScalar(srcHeight));

    // Now measure the length of the two transformed vectors relative to the
    // transformed origin to see how big the bitmap will be. Note: for skews,
    // this isn't the best thing, but we don't have skews.
    SkPoint dest_points[3];
    matrix.mapPoints(dest_points, src_points, 3);
    *destWidth = SkScalarToFloat((dest_points[1] - dest_points[0]).length());
    *destHeight = SkScalarToFloat((dest_points[2] - dest_points[0]).length());
}

// A helper method for translating negative width and height values.
static FloatRect normalizeRect(const FloatRect& rect)
{
    FloatRect norm = rect;
    if (norm.width() < 0) {
        norm.setX(norm.x() + norm.width());
        norm.setWidth(-norm.width());
    }
    if (norm.height() < 0) {
        norm.setY(norm.y() + norm.height());
        norm.setHeight(-norm.height());
    }
    return norm;
}

bool FrameData::clear(bool clearMetadata)
{
    if (clearMetadata)
        m_haveMetadata = false;

    if (m_frame) {
        // ImageSource::createFrameAtIndex() allocated |m_frame| and passed
        // ownership to BitmapImage; we must delete it here.
        delete m_frame;
        m_frame = 0;
        return true;
    }
    return false;
}

PassRefPtr<Image> Image::loadPlatformResource(const char *name)
{
/* FYWEBKITMOD BEGIN */
#if PLATFORM(FYMP)
    ///TODO: Image::loadPlatformResource
    RefPtr<Image> img = Image::nullImage();
    return img.release();
#else
/* FYWEBKITMOD END */
    return ChromiumBridge::loadPlatformImageResource(name);
#endif
}

/* FYWEBKITMOD BEGIN method has thorrowly been revised for HW usage! */
void Image::drawPattern(GraphicsContext* context,
                        const FloatRect& floatSrcRect,
                        const AffineTransform& patternTransform,
                        const FloatPoint& phase,
                        ColorSpace styleColorSpace,
                        CompositeOperator compositeOp,
                        const FloatRect& destRect)
{
    FloatRect normSrcRect = normalizeRect(floatSrcRect);
    if (destRect.isEmpty() || normSrcRect.isEmpty())
        return;  // nothing to draw

    NativeImageSkia* bitmap = nativeImageForCurrentFrame();
    if (!bitmap)
        return;

	SkBitmap srcSubset;
	SkIRect srcRect = enclosingIntRect(normSrcRect);

/* FYWEBKITMOD BEGIN */
	// !! FYMP:
	//
	// - yes, for it this is a very cheap operation (just an offset & pitch is recomputed)
	// - no, for us this is NOT cheap. We cannot tell (at least any) GPU API a new pitch!
	// - so we need to copy(!) the data (with the GPU) as needed & of course also need memory for that!
	// --> One could imagine a straight forward pixel-shader solution that would remove the need for this, BUT: some platforms do not have pixel shaders
	// (yes, in the year 2014... sigh)
	//
#if !PLATFORM(FYMP_VS)  // FYWEBKITMOD using unmodified skia for VisualStudio build
    bitmap->extractSubset(&srcSubset, srcRect, true);
#else
	bitmap->extractSubset(&srcSubset, srcRect);
#endif

    SkShader* shader = SkShader::CreateBitmapShader(srcSubset, SkShader::kRepeat_TileMode, SkShader::kRepeat_TileMode);
	if (!shader)
		return;
/* FYWEBKITMOD END */

    // Load the transform WebKit requested.
    SkMatrix matrix(patternTransform);

    // We also need to translate it such that the origin of the pattern is the
    // origin of the destination rect, which is what WebKit expects. Skia uses
    // the coordinate system origin as the base for the patter. If WebKit wants
    // a shifted image, it will shift it from there using the patternTransform.
    float adjustedX = phase.x() + normSrcRect.x() *
                      narrowPrecisionToFloat(patternTransform.a());
    float adjustedY = phase.y() + normSrcRect.y() *
                      narrowPrecisionToFloat(patternTransform.d());
    matrix.postTranslate(SkFloatToScalar(adjustedX),
                         SkFloatToScalar(adjustedY));

/* FYWEBKITMOD BEGIN */
	// !! FYMP:
	// We possibly scaled the dimensions of the texture above to conform with HW limitations!
	// -> as Skia & Webkit render a texture pixel-by-pixel we need to make sure we apply a
	//    scale to "undo" this cheat visually!
	// (This is the inverse of the scale one trivially would expect as we end up using the inverse of the matrix
	//  we prepare here as (part of) the texture matrix!)
	//
	// -> Note: one more matrix is applied "after" this one to generate UVs. Skia will only ever feed it with a scale
	//    or the identity. Hence we should be safe to feed our scale into the pipeline at this point!
	//
	float subSetScaleX = (float)srcRect.width() / (float)srcSubset.width();
	float subSetScaleY = (float)srcRect.height() / (float)srcSubset.height();
	matrix.preScale(subSetScaleX, subSetScaleY);
/* FYWEBKITMOD END */

    shader->setLocalMatrix(matrix);

    SkPaint paint;
    paint.setShader(shader)->unref();
    paint.setXfermodeMode(WebCoreCompositeToSkiaComposite(compositeOp));
    paint.setFilterBitmap(true); // FYWEBKITMOD always true, not only when resampling == RESAMPLE_LINEAR

    context->platformContext()->paintSkPaint(destRect, paint);
}
/* FYWEBKITMOD END */

// ================================================
// BitmapImage Class
// ================================================

// FIXME: These should go to BitmapImageSkia.cpp

void BitmapImage::initPlatformData()
{
    // This is not used. On Mac, the "platform" data is a cache of some OS
    // specific versions of the image that are created is some cases. These
    // aren't normally used, it is equivalent to getHBITMAP on Windows, and
    // the platform data is the cache.
}

void BitmapImage::invalidatePlatformData()
{
    // See initPlatformData above.
}

void BitmapImage::checkForSolidColor()
{
    m_checkedForSolidColor = true;
}

void BitmapImage::draw(GraphicsContext* ctxt, const FloatRect& dstRect,
                       const FloatRect& srcRect, ColorSpace, CompositeOperator compositeOp)
{
    if (!m_source.initialized())
        return;

    // Spin the animation to the correct frame before we try to draw it, so we
    // don't draw an old frame and then immediately need to draw a newer one,
    // causing flicker and wasting CPU.
    startAnimation();

    const NativeImageSkia* nativeImage = nativeImageForCurrentFrame();
    if (!nativeImage)
        return;  // It's too early and we don't have an image yet.

    FloatRect normDstRect = normalizeRect(dstRect);
    FloatRect normSrcRect = normalizeRect(srcRect);

    if (normSrcRect.isEmpty() || normDstRect.isEmpty())
        return;  // Nothing to draw.

    paintSkBitmap(ctxt->platformContext(),
                  *nativeImage,
                  enclosingIntRect(normSrcRect),
                  WebCoreFloatRectToSkRect(normDstRect),
                  WebCoreCompositeToSkiaComposite(compositeOp),
                  getNativeImageAge()); // FYWEBKITMOD adding last parameter
}

// FIXME: These should go into BitmapImageSingleFrameSkia.cpp

void BitmapImageSingleFrameSkia::draw(GraphicsContext* ctxt,
                                      const FloatRect& dstRect,
                                      const FloatRect& srcRect,
                                      ColorSpace styleColorSpace,
                                      CompositeOperator compositeOp)
{
    FloatRect normDstRect = normalizeRect(dstRect);
    FloatRect normSrcRect = normalizeRect(srcRect);

    if (normSrcRect.isEmpty() || normDstRect.isEmpty())
        return;  // Nothing to draw.

    paintSkBitmap(ctxt->platformContext(),
                  m_nativeImage,
                  enclosingIntRect(normSrcRect),
                  normDstRect,
                  WebCoreCompositeToSkiaComposite(compositeOp),
                  getNativeImageAge()); // FYWEBKITMOD adding last parameter
}

PassRefPtr<BitmapImageSingleFrameSkia> BitmapImageSingleFrameSkia::create(const SkBitmap& bitmap)
{
    RefPtr<BitmapImageSingleFrameSkia> image(adoptRef(new BitmapImageSingleFrameSkia()));
    bitmap.copyTo(&image->m_nativeImage, bitmap.config());
    return image.release();
}

}  // namespace WebCore
