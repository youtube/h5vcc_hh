/*
 Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies)
 Copyright (C) 2014 FactorY Media Production GmbH

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

/* FYWEBKITMOD BEGIN integrated from https://gitorious.org/webkit/noamrs-webkit/source/cb48ff9f4067b8ebcbb8a54e9dfef2d6fda0b82f:WebCore/platform/graphics/texmap/TextureMapper.h */

#ifndef TextureMapper_h
#define TextureMapper_h

#if USE(ACCELERATED_COMPOSITING)

#if (defined(QT_OPENGL_LIB) && !defined(AGC_OPENGL))
    #define AGC_OPENGL
    #ifdef QT_OPENGL_ES_2
        #define AGC_OPENGL_ES_2
    #endif
#endif

#include "GraphicsContext.h"
#include "IntRect.h"
#include "IntSize.h"
#include "TransformationMatrix.h"

/*
    TextureMapper (AGC) is a mechanism that enables hardware acceleration of CSS animations (accelerated compositing) without
    a need for a scene-graph library like CoreAnimations or QGraphicsView.
*/

namespace WebCore {

class TextureMapper;

// Platform managed animations allow composited layers to animate transform/opacity without relayouting.
class PlatformAnimationClient {
public:
    virtual void setAnimationStarted() = 0;
    virtual void setAnimationStopped() = 0;
    virtual void processFrame(float timeSecs) = 0;
};

class PlatformAnimation {
public:
    virtual ~PlatformAnimation() {}
    virtual void startAnimation() = 0;
    virtual void stopAnimation() = 0;

    // -1: infinite.
    virtual void setAnimationIterationCount(int) = 0;
    virtual void resumeAnimation() = 0;
    virtual void pauseAnimation() = 0;
    virtual float animationCurrentLoopTime() = 0;
    virtual int animationCurrentLoop() = 0;
    virtual float animationDuration() = 0;
    virtual void setAnimationDuration(float secs) = 0;
    virtual void setAnimationCurrentTime(float secs) = 0;

    static PlatformAnimation* create(PlatformAnimationClient*);
    static bool isSupported();
};

class BitmapTexture  : public RefCounted<BitmapTexture> {
public:
    BitmapTexture() : m_lockCount(0) {}
    virtual ~BitmapTexture() { }

    virtual bool allowOfflineTextureUpload() const { return false; }
    virtual void destroy() = 0;
    virtual IntSize size() const = 0;
    virtual bool isValid() const = 0;
    virtual void reset(const IntSize& size, bool opaque = false)
    {
        m_isOpaque = opaque;
        m_contentSize = size;
    }

    virtual PlatformGraphicsContext* beginPaint(const IntRect& dirtyRect) = 0;
    virtual void endPaint() = 0;
    virtual PlatformGraphicsContext* beginPaintMedia()
    {
        return beginPaint(IntRect(0, 0, size().width(), size().height()));
    }
    virtual void setContentsToImage(Image*) = 0;
    virtual bool save(const String &) { return false; }

    inline void lock() { ++m_lockCount; }
    inline void unlock() { --m_lockCount; }
    inline bool isLocked() { return m_lockCount; }
    inline IntSize contentSize() const { return m_contentSize; }
    inline void setOffset(const IntPoint& o) { m_offset = o; }
    inline IntPoint offset() const { return m_offset; }
private:
    int m_lockCount;
    IntSize m_contentSize;
    bool m_isOpaque;
    IntPoint m_offset;
};

class TextureMapper : public RefCounted<TextureMapper> {
    friend class BitmapTexture;

public:
    static PassRefPtr<TextureMapper> create(GraphicsContext*);
    virtual ~TextureMapper() { }

    virtual void drawTexture(const BitmapTexture& texture, const IntRect& target, const TransformationMatrix& matrix = TransformationMatrix(), float opacity = 1.0f, const BitmapTexture* maskTexture = 0) = 0;
    virtual void bindSurface(BitmapTexture* surface) = 0;
    virtual void paintToTarget(const BitmapTexture& texture, const IntSize&, const TransformationMatrix& matrix, float opacity, const IntRect& visibleRect)
    {
        drawTexture(texture, IntRect(0, 0, texture.contentSize().width(), texture.contentSize().height()), matrix, opacity, 0);
    }

    virtual void setClip(const IntRect&) = 0;
    virtual bool allowSurfaceForRoot() const = 0;
    virtual PassRefPtr<BitmapTexture> createTexture() = 0;
    virtual const char* type() const = 0;
    virtual void cleanup() {}

    GraphicsContext* graphicsContext() const { return m_gc; }

protected:
    TextureMapper(GraphicsContext* gc) : m_gc(gc) {}
    GraphicsContext* m_gc;
};

};

#endif

#endif

/* FYWEBKITMOD END */
