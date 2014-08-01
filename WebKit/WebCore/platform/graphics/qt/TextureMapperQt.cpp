/*
 Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies)

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

#include "config.h"
#include "texmap/TextureMapper.h"

#include "QtCore/qdebug.h"
#include "QtGui/qpaintengine.h"
#include "QtGui/qpixmap.h"

#ifndef QT_NO_ANIMATIONS
# include "QtCore/qabstractanimation.h"
#endif

#ifdef QT_OPENGL_LIB
# include "opengl/TextureMapperGL.h"
#endif

namespace WebCore {

class BitmapTextureQt : public BitmapTexture {
    friend class TextureMapperQt;
public:
    BitmapTextureQt() : m_gc(0) {}
    virtual void destroy();
    virtual IntSize size() const { return IntSize(m_pixmap.width(), m_pixmap.height()); }
    virtual void reset(const IntSize&, bool opaque);
    virtual PlatformGraphicsContext* beginPaint(const IntRect& dirtyRect);
    virtual void endPaint();
    virtual void setContentsToImage(Image*);
    virtual bool save(const String &);
    virtual bool isValid() const { return !m_pixmap.isNull(); }
    virtual bool allowOfflineTextureUpload() const { return true; }
    IntRect sourceRect() const { return IntRect(0, 0, contentSize().width(), contentSize().height()); }
private:
    QPainter m_painter;
    GraphicsContext* m_gc;
    QPixmap m_pixmap;
};

class TextureMapperQt : public TextureMapper {
public:
    virtual void drawTexture(const BitmapTexture& texture, const IntRect& targetRect, const TransformationMatrix& matrix, float opacity, const BitmapTexture* maskTexture);
    virtual void bindSurface(BitmapTexture* surface);
    virtual void setClip(const IntRect&);
    virtual bool allowSurfaceForRoot() const { return false; }
    TextureMapperQt(GraphicsContext* gc);
    virtual const char* type() const { return "Qt"; }
    virtual PassRefPtr<BitmapTexture> createTexture();

    static void initialize(QPainter *painter)
    {
        painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform, false);
    }

private:
    QPainter* m_painter;
    RefPtr<BitmapTextureQt> m_currentSurface;
};

void BitmapTextureQt::destroy()
{
    if (m_pixmap.paintingActive())
        qFatal("Destroying an active pixmap");
    m_pixmap = QPixmap();
}

void BitmapTextureQt::reset(const IntSize& size, bool isOpaque)
{
    BitmapTexture::reset(size, isOpaque);

    if (size.width() > m_pixmap.size().width() || size.height() > m_pixmap.size().height() || m_pixmap.isNull())
        m_pixmap = QPixmap(size.width(), size.height());
    if (!isOpaque)
        m_pixmap.fill(Qt::transparent);
}

PlatformGraphicsContext* BitmapTextureQt::beginPaint(const IntRect& dirtyRect)
{
    m_painter.begin(&m_pixmap);
    TextureMapperQt::initialize(&m_painter);
    m_painter.setCompositionMode(QPainter::CompositionMode_Clear);
    m_painter.fillRect(QRect(dirtyRect), Qt::transparent);
    m_painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    return &m_painter;
}

void BitmapTextureQt::endPaint()
{
    m_painter.end();
}

bool BitmapTextureQt::save(const String &path)
{
    return m_pixmap.save(path, "PNG");
}

void BitmapTextureQt::setContentsToImage(Image* image)
{
    if (!image)
        return;
    const QPixmap* pixmap = image->nativeImageForCurrentFrame();
    if (!pixmap)
        return;
    BitmapTexture::reset(pixmap->size(), !pixmap->hasAlphaChannel());
    m_pixmap = *pixmap;
}

void TextureMapperQt::setClip(const IntRect& rect)
{
     QPainter* painter = m_currentSurface ? &m_currentSurface->m_painter : m_painter;
     painter->setClipRect(rect);
}

TextureMapperQt::TextureMapperQt(GraphicsContext* gc)
    : TextureMapper(gc)
    , m_painter(gc->platformContext())
    , m_currentSurface(0)
{
    TextureMapperQt::initialize(m_painter);
}

void TextureMapperQt::bindSurface(BitmapTexture* aSurface)
{
    if (m_currentSurface == aSurface)
        return;
    if (m_currentSurface)
        m_currentSurface->m_painter.end();
    if (!aSurface) {
        m_currentSurface = 0;
        return;
    }
    BitmapTextureQt* surface = static_cast<BitmapTextureQt*>(aSurface);
    if (!surface->m_painter.isActive())
        surface->m_painter.begin(&surface->m_pixmap);
    m_currentSurface = surface;
}


void TextureMapperQt::drawTexture(const BitmapTexture& aTexture, const IntRect& targetRect, const TransformationMatrix& matrix, float opacity, const BitmapTexture* maskTexture)
{
    const BitmapTextureQt& texture = static_cast<const BitmapTextureQt&>(aTexture);
    QPainter* painter = m_painter;
    QPixmap pixmap = texture.m_pixmap;
    if (m_currentSurface)
        painter = &m_currentSurface->m_painter;

    if (maskTexture && maskTexture->isValid()) {
        const BitmapTextureQt* maskQt = static_cast<const BitmapTextureQt*>(maskTexture);
        QPixmap intermediatePixmap(pixmap.size());
        intermediatePixmap.fill(Qt::transparent);
        QPainter maskPainter(&intermediatePixmap);
        maskPainter.setCompositionMode(QPainter::CompositionMode_Source);
        maskPainter.drawPixmap(0, 0, pixmap);
        maskPainter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
        maskPainter.drawPixmap(QRect(0, 0, pixmap.width(), pixmap.height()), maskQt->m_pixmap, maskQt->sourceRect());
        maskPainter.end();
        pixmap = intermediatePixmap;
    }

    const qreal prevOpacity = painter->opacity();
    const QTransform prevTransform = painter->transform();
    painter->setOpacity(opacity);
    painter->setTransform(matrix, true);
    painter->drawPixmap(targetRect, pixmap, texture.sourceRect());
    painter->setTransform(prevTransform);
    painter->setOpacity(prevOpacity);
}

PassRefPtr<TextureMapper> TextureMapper::create(GraphicsContext* gc)
{
#ifdef QT_OPENGL_LIB
    if (gc->platformContext()->paintEngine()->type() == QPaintEngine::OpenGL2)
        return adoptRef(new TextureMapperGL(gc));
#endif
    return adoptRef(new TextureMapperQt(gc));
}


PassRefPtr<BitmapTexture> TextureMapperQt::createTexture() { return adoptRef(new BitmapTextureQt()); }

#ifdef QT_OPENGL_LIB
class RGBA32PremultimpliedBufferQt : public RGBA32PremultimpliedBuffer {
public:
    virtual PlatformGraphicsContext* beginPaint(const IntRect& rect, bool opaque)
    {
        m_image = QImage(rect.size().width(), rect.size().height(), QImage::Format_ARGB32_Premultiplied);
        if (!opaque)
            m_image.fill(0);
        m_painter.begin(&m_image);
        TextureMapperQt::initialize(&m_painter);
        m_painter.translate(-rect.x(), -rect.y());
        return &m_painter;
    }

    virtual void endPaint() { m_painter.end(); }
    virtual const void* data() const { return m_image.constBits(); }

private:
    QPainter m_painter;
    QImage m_image;
};
PassRefPtr<RGBA32PremultimpliedBuffer> RGBA32PremultimpliedBuffer::create() { return adoptRef(new RGBA32PremultimpliedBufferQt()); }
#endif

#ifndef QT_NO_ANIMATIONS
class PlatformAnimationQt : public QAbstractAnimation, public virtual PlatformAnimation {
    Q_OBJECT

public:
    PlatformAnimationQt(PlatformAnimationClient* client) : m_client(client)
    { 
        QObject::connect(this, SIGNAL(setAnimationStartedAsync()), 
                         this, SLOT(setAnimationStarted()), Qt::QueuedConnection);
        QObject::connect(this, SIGNAL(setAnimationStoppedAsync()), 
                         this, SLOT(setAnimationStopped()), Qt::QueuedConnection);
    }
    virtual void startAnimation() { start(); }
    virtual void stopAnimation() { stop(); }
    virtual void setAnimationIterationCount(int count) { setLoopCount(count); }
    virtual void resumeAnimation() { resume(); }
    virtual void pauseAnimation() { pause(); }
    virtual void setAnimationCurrentTime(float secs) { setCurrentTime(secs / 1000); }
    virtual float animationCurrentLoopTime() { return float(currentLoopTime()) / 1000; }
    virtual int animationCurrentLoop() { return currentLoop(); }
    virtual float animationDuration() { return m_duration; }
    virtual void setAnimationDuration(float durationSecs) { m_duration = durationSecs; }
    virtual void updateState(QAbstractAnimation::State newState, QAbstractAnimation::State oldState)
    {
        QAbstractAnimation::updateState(newState, oldState);
        if (newState == Stopped)
            setAnimationStopped();
        else if (newState == Running)
            setAnimationStarted();
    }
    virtual int duration() const { return m_duration * 1000; }
    virtual void updateCurrentTime(int time) { m_client->processFrame(float(time) * 1000); }

public slots:
    void setAnimationStarted() { m_client->setAnimationStarted(); }
    void setAnimationStopped() { m_client->setAnimationStopped(); }

signals:
    void setAnimationStartedAsync();
    void setAnimationStoppedAsync();

private:
    PlatformAnimationClient* m_client;
    float m_duration;
};

PlatformAnimation* PlatformAnimation::create(PlatformAnimationClient* client) { return new PlatformAnimationQt(client); }

bool PlatformAnimation::isSupported()
{
    return true;
}

#else
PassRefPtr<PlatformAnimation> PlatformAnimation::create(PlatformAnimationClient*) { return 0; }
bool PlatformAnimation::isSupported() { return false; }
#endif

};

#include <TextureMapperQt.moc>
