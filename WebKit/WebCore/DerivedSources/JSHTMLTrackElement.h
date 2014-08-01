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

#ifndef JSHTMLTrackElement_h
#define JSHTMLTrackElement_h

#if ENABLE(VIDEO) && ENABLE(VIDEO_TRACK)

#include "JSHTMLElement.h"
#include <runtime/JSObjectWithGlobalObject.h>

namespace WebCore {

class HTMLTrackElement;

class JSHTMLTrackElement : public JSHTMLElement {
    typedef JSHTMLElement Base;
public:
    JSHTMLTrackElement(NonNullPassRefPtr<JSC::Structure>, JSDOMGlobalObject*, PassRefPtr<HTMLTrackElement>);
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
protected:
    static const unsigned StructureFlags = JSC::OverridesGetOwnPropertySlot | Base::StructureFlags;
};


class JSHTMLTrackElementPrototype : public JSC::JSObjectWithGlobalObject {
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
    JSHTMLTrackElementPrototype(JSC::JSGlobalObject* globalObject, NonNullPassRefPtr<JSC::Structure> structure) : JSC::JSObjectWithGlobalObject(globalObject, structure) { }
protected:
    static const unsigned StructureFlags = JSC::OverridesGetOwnPropertySlot | Base::StructureFlags;
};

// Attributes
// kind
JSC::JSValue jsHTMLTrackElementKind(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void setJSHTMLTrackElementKind(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
// src
JSC::JSValue jsHTMLTrackElementSrc(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void setJSHTMLTrackElementSrc(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
// srclang
JSC::JSValue jsHTMLTrackElementSrclang(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void setJSHTMLTrackElementSrclang(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
// label
JSC::JSValue jsHTMLTrackElementLabel(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void setJSHTMLTrackElementLabel(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
// default
JSC::JSValue jsHTMLTrackElementDefault(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void setJSHTMLTrackElementDefault(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
// ready-state
JSC::JSValue jsHTMLTrackElementReadyState(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
// track
JSC::JSValue jsHTMLTrackElementTrack(JSC::ExecState* exec, JSC::JSValue slotBase, const JSC::Identifier&);
// constructor
JSC::JSValue jsHTMLTrackElementConstructor(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);

// Constants
JSC::JSValue jsHTMLTrackElementNONE   (JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsHTMLTrackElementLOADING(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsHTMLTrackElementLOADED (JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsHTMLTrackElementERROR  (JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);

} // namespace WebCore

#endif // ENABLE(VIDEO) && ENABLE(VIDEO_TRACK)

#endif
