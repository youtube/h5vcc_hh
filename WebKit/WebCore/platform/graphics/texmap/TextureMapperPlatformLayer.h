/*
    Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies)
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

/* FYWEBKITMOD BEGIN integrated from https://gitorious.org/webkit/noamrs-webkit/source/cb48ff9f4067b8ebcbb8a54e9dfef2d6fda0b82f:WebCore/platform/graphics/texmap/TextureMapperPlatformLayer.h */

#ifndef TextureMapperPlatformLayer_h
#define TextureMapperPlatformLayer_h

namespace WebCore {

class GraphicsContext;
class IntRect;
class IntSize;
class TransformationMatrix;

class TextureMapperLayerClient {
public:
    virtual ~TextureMapperLayerClient() {}
    virtual void setNeedsDisplay() = 0;
    virtual void setNeedsDisplayInRect(const IntRect& rect) = 0;
    virtual void setSizeChanged(const IntSize&) = 0;
};

class TextureMapperPlatformLayer {
public:
    enum Type {
        ContentLayer,
        VideoLayer
    };

    virtual Type layerType() const = 0;
    virtual ~TextureMapperPlatformLayer() {}
};

class TextureMapperContentLayer : public TextureMapperPlatformLayer {
public:
    virtual void setPlatformLayerClient(TextureMapperLayerClient*) = 0;
    virtual void paint(GraphicsContext*, const IntSize&, const IntRect& targetRect, const IntRect& exposedRect, const TransformationMatrix& transform, float opacity) {}
    virtual IntSize size() const = 0;
    virtual void cleanupTextureMapper() {}
    virtual Type layerType() const { return ContentLayer; }
};

class TextureMapperMediaLayer : public TextureMapperPlatformLayer {
public:
    virtual void paint(GraphicsContext*) = 0;
    virtual Type layerType() const { return VideoLayer; }
};

}

#endif // TextureMapperPlatformLayer_h

/* FYWEBKITMOD END */
