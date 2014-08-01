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

#include "config.h"

#if ENABLE(VIDEO_TRACK) && ENABLE(WEBVTT_REGIONS)

#include "JSNode.h"
#include "Document.h"
#include "Element.h"
#include "Event.h"
#include "JSDocument.h"
#include "JSElement.h"
#include "JSEvent.h"
#include "JSEventListener.h"
#include "KURL.h"
#include "RegisteredEventListener.h"
#include <runtime/Error.h>
#include <runtime/JSNumberCell.h>
#include <wtf/GetPtr.h>

#include "JSTextTrackRegion.h"
#include "TextTrackRegion.h"


using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSTextTrackRegion);

/* Hash table */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSTextTrackRegionTableValues[10] =
{
    { "id",              DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackRegionId),              (intptr_t)0 THUNK_GENERATOR(0) },
    { "width",           DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackRegionWidth),           (intptr_t)0 THUNK_GENERATOR(0) },
    { "height",          DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackRegionHeight),          (intptr_t)0 THUNK_GENERATOR(0) },
    { "regionAnchorX",   DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackRegionRegionAnchorX),   (intptr_t)0 THUNK_GENERATOR(0) },
    { "regionAnchorY",   DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackRegionRegionAnchorY),   (intptr_t)0 THUNK_GENERATOR(0) },
    { "viewportAnchorX", DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackRegionViewportAnchorX), (intptr_t)0 THUNK_GENERATOR(0) },
    { "viewportAnchorY", DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackRegionViewportAnchorY), (intptr_t)0 THUNK_GENERATOR(0) },
    { "scroll",          DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackRegionScroll),          (intptr_t)0 THUNK_GENERATOR(0) },
	{ "constructor",     DontEnum | ReadOnly,   (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackRegionConstructor), (intptr_t)0 THUNK_GENERATOR(0) },
	{ 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSTextTrackRegionTable = { 33, 31, JSTextTrackRegionTableValues, 0 };
/* Hash table for constructor */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSTextTrackRegionConstructorTableValues[1] =
{
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSTextTrackRegionConstructorTable = { 1, 0, JSTextTrackRegionConstructorTableValues, 0 };
class JSTextTrackRegionConstructor : public DOMConstructorObject {
public:
    JSTextTrackRegionConstructor(JSC::ExecState*, JSDOMGlobalObject*);

    virtual bool getOwnPropertySlot(JSC::ExecState*, const JSC::Identifier&, JSC::PropertySlot&);
    virtual bool getOwnPropertyDescriptor(JSC::ExecState*, const JSC::Identifier&, JSC::PropertyDescriptor&);
    virtual const JSC::ClassInfo* classInfo() const { return &s_info; }
    static const JSC::ClassInfo s_info;
    static PassRefPtr<JSC::Structure> createStructure(JSC::JSValue prototype)
    {
        return JSC::Structure::create(prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), AnonymousSlotCount);
    }
protected:
    static const unsigned StructureFlags = JSC::OverridesGetOwnPropertySlot | JSC::ImplementsHasInstance | DOMConstructorObject::StructureFlags;
};

const ClassInfo JSTextTrackRegionConstructor::s_info = { "TextTrackRegionConstructor", 0, &JSTextTrackRegionConstructorTable, 0 };

JSTextTrackRegionConstructor::JSTextTrackRegionConstructor(ExecState* exec, JSDOMGlobalObject* globalObject)
    : DOMConstructorObject(JSTextTrackRegionConstructor::createStructure(globalObject->objectPrototype()), globalObject)
{
    putDirect(exec->propertyNames().prototype, JSTextTrackRegionPrototype::self(exec, globalObject), DontDelete | ReadOnly);
}

bool JSTextTrackRegionConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSTextTrackRegionConstructor, DOMObject>(exec, &JSTextTrackRegionConstructorTable, this, propertyName, slot);
}

bool JSTextTrackRegionConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSTextTrackRegionConstructor, DOMObject>(exec, &JSTextTrackRegionConstructorTable, this, propertyName, descriptor);
}

/* Hash table for prototype */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSTextTrackRegionPrototypeTableValues[1] = {
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSTextTrackRegionPrototypeTable = { 1, 0, JSTextTrackRegionPrototypeTableValues, 0 };
const ClassInfo JSTextTrackRegionPrototype::s_info = { "TextTrackRegionPrototype", 0, &JSTextTrackRegionPrototypeTable, 0 };

JSObject* JSTextTrackRegionPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSTextTrackRegion>(exec, globalObject);
}

bool JSTextTrackRegionPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticPropertySlot<JSTextTrackRegionPrototype, JSObject>(exec, &JSTextTrackRegionPrototypeTable, this, propertyName, slot);
}

bool JSTextTrackRegionPrototype::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticPropertyDescriptor<JSTextTrackRegionPrototype, JSObject>(exec, &JSTextTrackRegionPrototypeTable, this, propertyName, descriptor);
}

const ClassInfo JSTextTrackRegion::s_info = { "TextTrackRegion", 0, &JSTextTrackRegionTable, 0 };

JSTextTrackRegion::JSTextTrackRegion(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<TextTrackRegion> impl)
    : DOMObjectWithGlobalPointer(structure, globalObject)
    , m_impl(impl)
{
}

JSTextTrackRegion::~JSTextTrackRegion()
{
	forgetDOMObject(this, impl());
}

JSObject* JSTextTrackRegion::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSTextTrackRegionPrototype(globalObject, JSTextTrackRegionPrototype::createStructure(globalObject->objectPrototype()));
}

bool JSTextTrackRegion::getOwnPropertySlot(JSC::ExecState* exec, const JSC::Identifier& propertyName, JSC::PropertySlot& slot)
{
    return JSC::getStaticValueSlot<JSTextTrackRegion, Base>(exec, s_info.staticPropHashTable, this, propertyName, slot);
}

bool JSTextTrackRegion::getOwnPropertyDescriptor(JSC::ExecState* exec, const JSC::Identifier& propertyName, JSC::PropertyDescriptor& descriptor)
{
    return JSC::getStaticValueDescriptor<JSTextTrackRegion, Base>(exec, s_info.staticPropHashTable, this, propertyName, descriptor);
}

void JSTextTrackRegion::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    lookupPut<JSTextTrackRegion, Base>(exec, propertyName, value, &JSTextTrackRegionTable, this, slot);
}

JSValue jsTextTrackRegionId(ExecState* exec, JSValue slotBase, const Identifier&)
	{
    JSTextTrackRegion* castedThis = static_cast<JSTextTrackRegion*>(asObject(slotBase));
    TextTrackRegion* imp = static_cast<TextTrackRegion*>(castedThis->impl());
	JSDOMGlobalObject*   pGlob = castedThis->globalObject();
    JSValue result = jsStringOrNull(exec, imp->id());
    return result;
	}

JSValue jsTextTrackRegionWidth(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrackRegion* castedThis = static_cast<JSTextTrackRegion*>(asObject(slotBase));
    TextTrackRegion* imp = static_cast<TextTrackRegion*>(castedThis->impl());
    JSValue result = jsNumber(exec, imp->width());
    return result;
}

JSValue jsTextTrackRegionHeight(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrackRegion* castedThis = static_cast<JSTextTrackRegion*>(asObject(slotBase));
    TextTrackRegion* imp = static_cast<TextTrackRegion*>(castedThis->impl());
    JSValue result = jsNumber(exec, imp->height());
    return result;
}

JSValue jsTextTrackRegionRegionAnchorX(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrackRegion* castedThis = static_cast<JSTextTrackRegion*>(asObject(slotBase));
    TextTrackRegion* imp = static_cast<TextTrackRegion*>(castedThis->impl());
    JSValue result = jsNumber(exec, imp->regionAnchorX());
    return result;
}

JSValue jsTextTrackRegionRegionAnchorY(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrackRegion* castedThis = static_cast<JSTextTrackRegion*>(asObject(slotBase));
    TextTrackRegion* imp = static_cast<TextTrackRegion*>(castedThis->impl());
    JSValue result = jsNumber(exec, imp->regionAnchorY());
    return result;
}

JSValue jsTextTrackRegionViewportAnchorX(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrackRegion* castedThis = static_cast<JSTextTrackRegion*>(asObject(slotBase));
    TextTrackRegion* imp = static_cast<TextTrackRegion*>(castedThis->impl());
    JSValue result = jsNumber(exec, imp->viewportAnchorX());
    return result;
}

JSC::JSValue jsTextTrackRegionViewportAnchorY(JSC::ExecState* exec, JSC::JSValue slotBase, const Identifier&)
{
	JSTextTrackRegion* castedThis = static_cast<JSTextTrackRegion*>(asObject(slotBase));
    TextTrackRegion* imp = static_cast<TextTrackRegion*>(castedThis->impl());
    JSValue result = jsNumber(exec, imp->viewportAnchorY());
    return result;

}

JSC::JSValue jsTextTrackRegionScroll(JSC::ExecState* exec, JSC::JSValue slotBase, const Identifier&)
{
	JSTextTrackRegion* castedThis = static_cast<JSTextTrackRegion*>(asObject(slotBase));
	TextTrackRegion* imp = static_cast<TextTrackRegion*>(castedThis->impl());
	JSValue result = jsStringOrNull(exec, imp->scroll());
	return result;
}

// Functions
JSValue jsTextTrackRegionConstructor(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrackRegion* domObject = static_cast<JSTextTrackRegion*>(asObject(slotBase));
    return JSTextTrackRegion::getConstructor(exec, domObject->globalObject());
}

JSValue JSTextTrackRegion::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTextTrackRegionConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}

JSC::JSValue toJS(JSC::ExecState* exec, JSDOMGlobalObject* globalObject, TextTrackRegion* textTrack)
{
	return getDOMObjectWrapper<JSTextTrackRegion>(exec, globalObject, textTrack);
}

TextTrackRegion* toTextTrackRegion(JSC::JSValue value)
{
    return value.inherits(&JSTextTrackRegion::s_info) ? static_cast<JSTextTrackRegion*>(asObject(value))->impl() : 0;
}

}

#endif // ENABLE(VIDEO_TRACK) && ENABLE(WEBVTT_REGIONS)

