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

/* FYWEBKITMOD BEGIN */

#include "config.h"
#include "CString.h"
#include "NativeImageSkia.h"
#include "PlatformContextSkia.h"
#include "texmap/TextureMapper.h"

#include "SkBitmap.h"
#include "SkImageEncoder.h"
#include "skia/ext/platform_canvas.h"

namespace WebCore {

class BitmapTextureSkia : public BitmapTexture {
    friend class TextureMapperSkia;
public:
    BitmapTextureSkia() : m_context(0), m_device(0), m_gc(0) { }
    ~BitmapTextureSkia() { destroy(); }
    virtual void destroy();
    virtual IntSize size() const { return IntSize(m_bitmap.width(), m_bitmap.height()); }
    virtual void reset(const IntSize&, bool opaque);
    virtual PlatformGraphicsContext* beginPaint(const IntRect& dirtyRect);
    virtual void endPaint();
    virtual void setContentsToImage(Image*);
    virtual bool save(const String &);
    virtual bool isValid() const { return !m_bitmap.empty(); }
    virtual bool allowOfflineTextureUpload() const { return true; }
    IntRect sourceRect() const { return IntRect(0, 0, contentSize().width(), contentSize().height()); }
private:
    void clearBitmap(const IntRect *rect=0);
    SkBitmap               m_bitmap;
    skia::PlatformCanvas   m_canvas;
    PlatformContextSkia    m_context;
    skia::PlatformDevice  *m_device;
    GraphicsContext       *m_gc;
};

class TextureMapperSkia : public TextureMapper {
public:
    virtual void drawTexture(const BitmapTexture& texture, const IntRect& targetRect,
                             const TransformationMatrix& matrix, float opacity, const BitmapTexture* maskTexture);
    virtual void bindSurface(BitmapTexture* surface);
    virtual void setClip(const IntRect&);
    virtual bool allowSurfaceForRoot() const { return false; }
    TextureMapperSkia(GraphicsContext* gc);
    virtual const char* type() const { return "Skia"; }
    virtual PassRefPtr<BitmapTexture> createTexture();

private:
    PlatformContextSkia       *m_context;
    SkRect                     m_clipRect;
    RefPtr<BitmapTextureSkia>  m_currentSurface;
};

void BitmapTextureSkia::destroy()
{
    m_context.setCanvas(0);
    m_canvas.setDevice(0);
#if 0
    fprintf(stderr, "Destroy[%p/%p]!\n", this, m_device); fflush(stderr);
    if(m_device)
        m_device->unref();
#endif
    m_device = 0;
    m_bitmap = SkBitmap();
}

void BitmapTextureSkia::reset(const IntSize& size, bool isOpaque)
{
    BitmapTexture::reset(size, isOpaque);
    if (size.width() > m_bitmap.width() || size.height() > m_bitmap.height() || m_bitmap.empty()) {
        m_bitmap.setConfig(SkBitmap::kARGB_8888_Config, size.width(), size.height());
        m_bitmap.allocPixels();
#if 0
        fprintf(stderr, "Reset1[%p/%p]!\n", this, m_device); fflush(stderr);
        if(m_device)
            m_device->unref();
#endif
        m_device = new skia::PlatformDevice(m_bitmap);
        //fprintf(stderr, "Reset2[%p/%p]!\n", this, m_device); fflush(stderr);
        m_canvas.setDevice(m_device);
    }
    m_bitmap.setIsOpaque(isOpaque);
    clearBitmap();
}

void BitmapTextureSkia::clearBitmap(const IntRect *rect)
{
    SkPaint paint;
    paint.setXfermodeMode(SkXfermode::kClear_Mode);
    paint.setColor(0);
    m_canvas.drawRect(rect ? *rect : IntRect(0, 0, m_bitmap.width(), m_bitmap.height()), paint);
}

PlatformGraphicsContext* BitmapTextureSkia::beginPaint(const IntRect& dirtyRect)
{
    clearBitmap(&dirtyRect);
    m_context.setCanvas(&m_canvas);
    return &m_context;
}

void BitmapTextureSkia::endPaint()
{
    m_context.setCanvas(0);
}

bool BitmapTextureSkia::save(const String &path)
{
#if PLATFORM(FYMP)
    return false;
#else
    return SkImageEncoder::EncodeFile(path.ascii().data(), m_bitmap, SkImageEncoder::kPNG_Type, 100);
#endif
}

void BitmapTextureSkia::setContentsToImage(Image* image)
{
    if (!image)
        return;
    const SkBitmap* bitmap = image->nativeImageForCurrentFrame();
    if (!bitmap)
        return;
    BitmapTexture::reset(IntSize(bitmap->width(), bitmap->height()), bitmap->isOpaque());
    destroy();
    m_bitmap = SkBitmap(*bitmap);
}

void TextureMapperSkia::setClip(const IntRect& rect)
{
    m_clipRect = rect;
}

TextureMapperSkia::TextureMapperSkia(GraphicsContext* gc) : TextureMapper(gc),
                                                            m_currentSurface(0),
                                                            m_context(gc->platformContext())
{
}

void TextureMapperSkia::bindSurface(BitmapTexture* aSurface)
{
    if (m_currentSurface == aSurface)
        return;
    if (m_currentSurface)
        m_currentSurface->m_context.setCanvas(0);
    if (!aSurface) {
        m_currentSurface = 0;
        return;
    }
    BitmapTextureSkia* surface = static_cast<BitmapTextureSkia*>(aSurface);
    if (!surface->m_context.canvas())
        surface->m_context.setCanvas(&surface->m_canvas);
    m_currentSurface = surface;
}

void TextureMapperSkia::drawTexture(const BitmapTexture& aTexture, const IntRect& targetRect,
                                    const TransformationMatrix& aMatrix, float opacity, const BitmapTexture* maskTexture)
{
    const BitmapTextureSkia& texture = static_cast<const BitmapTextureSkia&>(aTexture);

    SkBitmap tmpBitmap;
    PlatformContextSkia *context = m_context;
    const SkBitmap *bitmap = &texture.m_bitmap;
    if (m_currentSurface)
        context = &m_currentSurface->m_context;

    if (maskTexture && maskTexture->isValid()) {
        const BitmapTextureSkia* maskSkia = static_cast<const BitmapTextureSkia*>(maskTexture);
        tmpBitmap.setConfig(SkBitmap::kARGB_8888_Config, bitmap->width(), bitmap->height());
        tmpBitmap.allocPixels();
        tmpBitmap.setIsOpaque(false);
        {
            skia::PlatformDevice tmpDevice(tmpBitmap);
            skia::PlatformCanvas tmpCanvas;
            tmpCanvas.setDevice(&tmpDevice);
            SkPaint paint;
            //copy it down
            paint.setXfermodeMode(SkXfermode::kSrc_Mode);
            tmpCanvas.drawBitmap(*bitmap, 0, 0, &paint);
            //mask it
            paint.setXfermodeMode(SkXfermode::kDstIn_Mode);
            SkRect srect = maskSkia->sourceRect(), drect = SkRect::MakeXYWH(0, 0, bitmap->width(), bitmap->height());
            SkIRect sirect;
            srect.round(&sirect);
            tmpCanvas.drawBitmapRect(maskSkia->m_bitmap, &sirect, drect, &paint);
        }
        bitmap = &tmpBitmap;
    }

    if( skia::PlatformCanvas *canvas = context->canvas() ) {
        canvas->save();
        {
            SkPaint paint;
            int alpha = opacity*255;
            if (alpha > 255)
                alpha = 255;
            else if (alpha < 0)
                alpha = 0;
            paint.setAlpha(alpha);
            paint.setXfermodeMode(SkXfermode::kSrcOver_Mode);
            SkRect srect = texture.sourceRect(), drect = targetRect;

            context->canvas()->clipRect(m_clipRect, SkRegion::kReplace_Op);
            canvas->setMatrix(aMatrix);
            context->canvas()->clipRect(drect, SkRegion::kIntersect_Op);

            SkIRect sirect;
            srect.round(&sirect);
            canvas->drawBitmapRect(*bitmap, &sirect, drect, &paint);
        }
        canvas->restore();
    }
}

PassRefPtr<TextureMapper> TextureMapper::create(GraphicsContext* gc)
{
    return adoptRef(new TextureMapperSkia(gc));
}

PassRefPtr<BitmapTexture> TextureMapperSkia::createTexture()
{
    return adoptRef(new BitmapTextureSkia());
}

PlatformAnimation *PlatformAnimation::create(PlatformAnimationClient*)
{
    return 0;
}

bool PlatformAnimation::isSupported()
{
    return false;
}

};


/* FYWEBKITMOD END */
