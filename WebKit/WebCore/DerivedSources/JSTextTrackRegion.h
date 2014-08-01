/*
    This file is part of the WebKit open source project.

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

// FYMP: This file was not auto-generated! Added to support JSTextTrack::regions() (while integrating parts of r152754)

#ifndef JSTextTrackRegion_h
#define JSTextTrackRegion_h

#if ENABLE(VIDEO_TRACK) && ENABLE(WEBVTT_REGIONS)

#include "JSDOMBinding.h"
#include <runtime/JSGlobalObject.h>
#include <runtime/JSObjectWithGlobalObject.h>
#include <runtime/Lookup.h>
#include <runtime/ObjectPrototype.h>
#include <wtf/AlwaysInline.h>

namespace WebCore {

class TextTrackRegion;

class JSTextTrackRegion : public DOMObjectWithGlobalPointer {
    typedef DOMObjectWithGlobalPointer Base;
public:
    JSTextTrackRegion(NonNullPassRefPtr<JSC::Structure>, JSDOMGlobalObject*, PassRefPtr<TextTrackRegion>);
    virtual ~JSTextTrackRegion();
    static JSC::JSObject* createPrototype(JSC::ExecState*, JSC::JSGlobalObject*);
    virtual bool getOwnPropertySlot(JSC::ExecState*, const JSC::Identifier& propertyName, JSC::PropertySlot&);
    virtual bool getOwnPropertyDescriptor(JSC::ExecState*, const JSC::Identifier& propertyName, JSC::PropertyDescriptor&);
    virtual void put(JSC::ExecState*, const JSC::Identifier& propertyName, JSC::JSValue, JSC::PutPropertySlot&);
    virtual const JSC::ClassInfo* classInfo() const { return &s_info; }
    static const JSC::ClassInfo s_info;

    static PassRefPtr<JSC::Structure> createStructure(JSC::JSValue prototype)
    {
        return JSC::Structure::create(prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), AnonymousSlotCount);
    }

    static JSC::JSValue getConstructor(JSC::ExecState*, JSC::JSGlobalObject*);
    TextTrackRegion* impl() const { return m_impl.get(); }

private:
    RefPtr<TextTrackRegion> m_impl;
protected:
    static const unsigned StructureFlags = JSC::OverridesMarkChildren | JSC::OverridesGetOwnPropertySlot | Base::StructureFlags;
};

JSC::JSValue toJS(JSC::ExecState*, JSDOMGlobalObject*, TextTrackRegion*);
TextTrackRegion* toTextTrackRegion(JSC::JSValue);
JSC::JSValue toJSNewlyCreated(JSC::ExecState*, JSDOMGlobalObject*, TextTrackRegion*);

class JSTextTrackRegionPrototype : public JSC::JSObjectWithGlobalObject {
    typedef JSC::JSObjectWithGlobalObject Base;
public:
    static JSC::JSObject* self(JSC::ExecState*, JSC::JSGlobalObject*);
    virtual const JSC::ClassInfo* classInfo() const { return &s_info; }
    static const JSC::ClassInfo s_info;
    virtual bool getOwnPropertySlot(JSC::ExecState*, const JSC::Identifier&, JSC::PropertySlot&);
    virtual bool getOwnPropertyDescriptor(JSC::ExecState*, const JSC::Identifier&, JSC::PropertyDescriptor&);
    static PassRefPtr<JSC::Structure> createStructure(JSC::JSValue prototype)
    {
        return JSC::Structure::create(prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), AnonymousSlotCount);
    }
    JSTextTrackRegionPrototype(JSC::JSGlobalObject* globalObject, NonNullPassRefPtr<JSC::Structure> structure) : JSC::JSObjectWithGlobalObject(globalObject, structure) { }
protected:
    static const unsigned StructureFlags = JSC::OverridesMarkChildren | JSC::OverridesGetOwnPropertySlot | Base::StructureFlags;
};

// Functions

// Attributes
JSC::JSValue jsTextTrackRegionId             (JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsTextTrackRegionWidth          (JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsTextTrackRegionHeight         (JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsTextTrackRegionRegionAnchorX  (JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsTextTrackRegionRegionAnchorY  (JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsTextTrackRegionViewportAnchorX(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsTextTrackRegionViewportAnchorY(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsTextTrackRegionScroll         (JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsTextTrackRegionConstructor    (JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);

// Constants

} // namespace WebCore

#endif // ENABLE(VIDEO_TRACK) && ENABLE(WEBVTT_REGIONS)
#endif
//#include "JSTextTrackRegionCustom.h"
