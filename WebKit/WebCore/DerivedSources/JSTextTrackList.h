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

// FYMP: this file is not auto-generated. It was done by hand. Thus, if you remove it, then you really remove it! (while integrating parts of r152754)

#ifndef JSTextTrackList_h
#define JSTextTrackList_h

#if ENABLE(VIDEO_TRACK)

#include "JSDOMBinding.h"
#include <runtime/CallData.h>
#include <runtime/JSGlobalObject.h>
#include <runtime/JSObjectWithGlobalObject.h>
#include <runtime/ObjectPrototype.h>

namespace WebCore {

class TextTrackList;

class JSTextTrackList : public DOMObjectWithGlobalPointer {
    typedef DOMObjectWithGlobalPointer Base;
public:
    JSTextTrackList(NonNullPassRefPtr<JSC::Structure>, JSDOMGlobalObject*, PassRefPtr<TextTrackList>);
    virtual ~JSTextTrackList();
    static JSC::JSObject* createPrototype(JSC::ExecState*, JSC::JSGlobalObject*);
    virtual bool getOwnPropertySlot(JSC::ExecState*, const JSC::Identifier& propertyName, JSC::PropertySlot&);
    virtual bool getOwnPropertyDescriptor(JSC::ExecState*, const JSC::Identifier& propertyName, JSC::PropertyDescriptor&);
    virtual bool getOwnPropertySlot(JSC::ExecState*, unsigned propertyName, JSC::PropertySlot&);
    virtual const JSC::ClassInfo* classInfo() const { return &s_info; }
    static const JSC::ClassInfo s_info;

    static PassRefPtr<JSC::Structure> createStructure(JSC::JSValue prototype)
    {
        return JSC::Structure::create(prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), AnonymousSlotCount);
    }

    virtual void getOwnPropertyNames(JSC::ExecState*, JSC::PropertyNameArray&, JSC::EnumerationMode mode = JSC::ExcludeDontEnumProperties);
    static JSC::JSValue getConstructor(JSC::ExecState*, JSC::JSGlobalObject*);
    TextTrackList* impl() const { return m_impl.get(); }

private:
    RefPtr<TextTrackList> m_impl;
protected:
    static const unsigned StructureFlags = JSC::OverridesGetPropertyNames | JSC::OverridesGetOwnPropertySlot | Base::StructureFlags;
    static JSC::JSValue indexGetter(JSC::ExecState*, JSC::JSValue, unsigned);
};

JSC::JSValue toJS(JSC::ExecState*, JSDOMGlobalObject*, TextTrackList*);
TextTrackList* toTextTrackList(JSC::JSValue);

class JSTextTrackListPrototype : public JSC::JSObjectWithGlobalObject {
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
    JSTextTrackListPrototype(JSC::JSGlobalObject* globalObject, NonNullPassRefPtr<JSC::Structure> structure) : JSC::JSObjectWithGlobalObject(globalObject, structure) { }
protected:
    static const unsigned StructureFlags = JSC::OverridesGetOwnPropertySlot | Base::StructureFlags;
};

// Functions
JSC::EncodedJSValue JSC_HOST_CALL jsTextTrackListPrototypeFunctionItem(JSC::ExecState*);
JSC::EncodedJSValue JSC_HOST_CALL jsTextTrackListPrototypeFunctionAddEventListener(JSC::ExecState*);
JSC::EncodedJSValue JSC_HOST_CALL jsTextTrackListPrototypeFunctionRemoveEventListener(JSC::ExecState*);
JSC::EncodedJSValue JSC_HOST_CALL jsTextTrackListPrototypeFunctionDispatchEvent(JSC::ExecState*);

// Attributes
JSC::JSValue jsTextTrackListLength(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsTextTrackListOnchange(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void setJSTextTrackListOnchange(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
JSC::JSValue jsTextTrackListOnaddtrack(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void setJSTextTrackListOnaddtrack(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
JSC::JSValue jsTextTrackListOnremovetrack(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void setJSTextTrackListOnremovetrack(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
JSC::JSValue jsTextTrackListConstructor(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);

} // namespace WebCore

#endif // ENABLE(VIDEO_TRACK)
#endif

