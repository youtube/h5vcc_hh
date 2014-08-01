

/* FYWEBKITMOD BEGIN custom extension. This file was not auto-generated! Added to support JSTextTrack::regions() */

#ifndef JSTextTrackStyle_h
#define JSTextTrackStyle_h

#if ENABLE(VIDEO_TRACK) && ENABLE(WEBVTT_STYLES)

#include "JSDOMBinding.h"
#include <runtime/JSGlobalObject.h>
#include <runtime/JSObjectWithGlobalObject.h>
#include <runtime/Lookup.h>
#include <runtime/ObjectPrototype.h>
#include <wtf/AlwaysInline.h>

namespace WebCore {

class TextTrackStyle;

class JSTextTrackStyle : public DOMObjectWithGlobalPointer {
    typedef DOMObjectWithGlobalPointer Base;
public:
    JSTextTrackStyle(NonNullPassRefPtr<JSC::Structure>, JSDOMGlobalObject*, PassRefPtr<TextTrackStyle>);
    virtual ~JSTextTrackStyle();
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
    TextTrackStyle* impl() const { return m_impl.get(); }

private:
    RefPtr<TextTrackStyle> m_impl;
protected:
    static const unsigned StructureFlags = JSC::OverridesMarkChildren | JSC::OverridesGetOwnPropertySlot | Base::StructureFlags;
};

JSC::JSValue toJS(JSC::ExecState*, JSDOMGlobalObject*, TextTrackStyle*);
TextTrackStyle* toTextTrackStyle(JSC::JSValue);
JSC::JSValue toJSNewlyCreated(JSC::ExecState*, JSDOMGlobalObject*, TextTrackStyle*);

class JSTextTrackStylePrototype : public JSC::JSObjectWithGlobalObject {
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
    JSTextTrackStylePrototype(JSC::JSGlobalObject* globalObject, NonNullPassRefPtr<JSC::Structure> structure) : JSC::JSObjectWithGlobalObject(globalObject, structure) { }
protected:
    static const unsigned StructureFlags = JSC::OverridesMarkChildren | JSC::OverridesGetOwnPropertySlot | Base::StructureFlags;
};

// Functions

// Attributes
JSC::JSValue jsTextTrackStyleSelector   (JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsTextTrackStyleStyle      (JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsTextTrackStyleStyleJSON  (JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsTextTrackStyleConstructor(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);

// Constants

} // namespace WebCore

#endif // ENABLE(VIDEO_TRACK) && ENABLE(WEBVTT_STYLES)
#endif
//#include "JSTextTrackStyleCustom.h"

/* FYWEBKITMOD END */
