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

// FYMP: This file was not auto-generated! (while integrating parts of r152754)

#ifndef JSTextTrackCue_h
#define JSTextTrackCue_h

#if ENABLE(VIDEO_TRACK)

#include "JSDOMBinding.h"
#include <runtime/JSGlobalObject.h>
#include <runtime/JSObjectWithGlobalObject.h>
#include <runtime/Lookup.h>
#include <runtime/ObjectPrototype.h>
#include <wtf/AlwaysInline.h>

namespace WebCore {

class TextTrackCue;

class JSTextTrackCue : public DOMObjectWithGlobalPointer {
    typedef DOMObjectWithGlobalPointer Base;
public:
    JSTextTrackCue(NonNullPassRefPtr<JSC::Structure>, JSDOMGlobalObject*, PassRefPtr<TextTrackCue>);
    virtual ~JSTextTrackCue();
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

//	virtual void getOwnPropertyNames(JSC::ExecState*, JSC::PropertyNameArray&, JSC::EnumerationMode mode = JSC::ExcludeDontEnumProperties);
    static JSC::JSValue getConstructor(JSC::ExecState*, JSC::JSGlobalObject*);
    TextTrackCue* impl() const { return m_impl.get(); }

private:
    RefPtr<TextTrackCue> m_impl;
protected:
    static const unsigned StructureFlags = JSC::OverridesMarkChildren | JSC::OverridesGetOwnPropertySlot | Base::StructureFlags;
};

JSC::JSValue toJS(JSC::ExecState*, JSDOMGlobalObject*, TextTrackCue*);
TextTrackCue* toTextTrackCue(JSC::JSValue);
JSC::JSValue toJSNewlyCreated(JSC::ExecState*, JSDOMGlobalObject*, TextTrackCue*);

class JSTextTrackCuePrototype : public JSC::JSObjectWithGlobalObject {
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
    JSTextTrackCuePrototype(JSC::JSGlobalObject* globalObject, NonNullPassRefPtr<JSC::Structure> structure) : JSC::JSObjectWithGlobalObject(globalObject, structure) { }
protected:
    static const unsigned StructureFlags = JSC::OverridesMarkChildren | JSC::OverridesGetOwnPropertySlot | Base::StructureFlags;
};

// Functions
JSC::EncodedJSValue JSC_HOST_CALL jsTextTrackCuePrototypeFunctionAddEventListener(JSC::ExecState*);
JSC::EncodedJSValue JSC_HOST_CALL jsTextTrackCuePrototypeFunctionRemoveEventListener(JSC::ExecState*);
JSC::EncodedJSValue JSC_HOST_CALL jsTextTrackCuePrototypeFunctionDispatchEvent(JSC::ExecState*);

// Attributes
// Track track
JSC::JSValue jsTextTrackCueTrack(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
// String id
JSC::JSValue jsTextTrackCueId(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void jsSetTextTrackCueId(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
// double startTime
JSC::JSValue jsTextTrackCueStartTime(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void jsSetTextTrackCueStartTime(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
// double endTime
JSC::JSValue jsTextTrackCueEndTime(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void jsSetTextTrackCueEndTime(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
// bool pauseOnExit
JSC::JSValue jsTextTrackCuePauseOnExit(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void jsSetTextTrackCuePauseOnExit(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
// String vertical
JSC::JSValue jsTextTrackCueVertical(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void jsSetTextTrackCueVertical(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
// boolean snapToLines
JSC::JSValue jsTextTrackCueSnapToLines(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void jsSetTextTrackCueSnapToLines(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
// long line
JSC::JSValue jsTextTrackCueLine(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void jsSetTextTrackCueLine(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
// long position
JSC::JSValue jsTextTrackCuePosition(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void jsSetTextTrackCuePosition(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
// long size
JSC::JSValue jsTextTrackCueSize(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void jsSetTextTrackCueSize(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
// String align
JSC::JSValue jsTextTrackCueAlign(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void jsSetTextTrackCueAlign(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
// String text
JSC::JSValue jsTextTrackCueText(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void jsSetTextTrackCueText(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
// String region // FYMP: adding region-attribute on cue's but without enabling the whole WEBVTT_REGIONS which controls WebKit's rendering of Cues.
JSC::JSValue jsTextTrackCueRegion(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void jsSetTextTrackCueRegion(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
// callback onenter
JSC::JSValue jsTextTrackCueOnenter(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void setJSTextTrackCueOnenter(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
// callback onexit
JSC::JSValue jsTextTrackCueOnexit(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void setJSTextTrackCueOnexit(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);


JSC::JSValue jsTextTrackCueConstructor(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);

// Constants

} // namespace WebCore

#endif // ENABLE(VIDEO_TRACK)

#endif
//#include "JSTextTrackCueCustom.h"
