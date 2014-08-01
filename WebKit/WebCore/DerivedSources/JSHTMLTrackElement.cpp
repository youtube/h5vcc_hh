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

#include "config.h"

#if ENABLE(VIDEO) && ENABLE(VIDEO_TRACK)

#include "JSHTMLTrackElement.h"

#include "JSTextTrack.h"
#include "HTMLNames.h"
#include "HTMLTrackElement.h"
#include "KURL.h"
#include <runtime/JSString.h>
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSHTMLTrackElement);

/* Hash table */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSHTMLTrackElementTableValues[9] =
{
	{ "kind",        DontDelete,            (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsHTMLTrackElementKind),    (intptr_t)setJSHTMLTrackElementKind    THUNK_GENERATOR(0) },
    { "src",         DontDelete,            (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsHTMLTrackElementSrc),     (intptr_t)setJSHTMLTrackElementSrc     THUNK_GENERATOR(0) },
    { "srclang",     DontDelete,            (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsHTMLTrackElementSrclang), (intptr_t)setJSHTMLTrackElementSrclang THUNK_GENERATOR(0) },
    { "label",       DontDelete,            (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsHTMLTrackElementLabel),   (intptr_t)setJSHTMLTrackElementLabel   THUNK_GENERATOR(0) },
	{ "default",     DontDelete,            (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsHTMLTrackElementDefault), (intptr_t)setJSHTMLTrackElementDefault THUNK_GENERATOR(0) },
	{ "readyState",  DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsHTMLTrackElementReadyState), (intptr_t)0 THUNK_GENERATOR(0) },
	{ "track",       DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsHTMLTrackElementTrack),      (intptr_t)0 THUNK_GENERATOR(0) },
	{ "constructor", DontEnum | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsHTMLTrackElementConstructor),  (intptr_t)0 THUNK_GENERATOR(0) },
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSHTMLTrackElementTable = { 18, 15, JSHTMLTrackElementTableValues, 0 };
/* Hash table for constructor */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSHTMLTrackElementConstructorTableValues[5] =
{
    { "NONE",    DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsHTMLTrackElementNONE),    (intptr_t)0 THUNK_GENERATOR(0) },
    { "LOADING", DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsHTMLTrackElementLOADING), (intptr_t)0 THUNK_GENERATOR(0) },
    { "LOADED",  DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsHTMLTrackElementLOADED),  (intptr_t)0 THUNK_GENERATOR(0) },
    { "ERROR",   DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsHTMLTrackElementERROR),   (intptr_t)0 THUNK_GENERATOR(0) },
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSHTMLTrackElementConstructorTable = { 8, 7, JSHTMLTrackElementConstructorTableValues, 0 };
class JSHTMLTrackElementConstructor : public DOMConstructorObject {
public:
    JSHTMLTrackElementConstructor(JSC::ExecState*, JSDOMGlobalObject*);

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

const ClassInfo JSHTMLTrackElementConstructor::s_info = { "HTMLTrackElementConstructor", 0, &JSHTMLTrackElementConstructorTable, 0 };

JSHTMLTrackElementConstructor::JSHTMLTrackElementConstructor(ExecState* exec, JSDOMGlobalObject* globalObject)
    : DOMConstructorObject(JSHTMLTrackElementConstructor::createStructure(globalObject->objectPrototype()), globalObject)
{
    putDirect(exec->propertyNames().prototype, JSHTMLTrackElementPrototype::self(exec, globalObject), DontDelete | ReadOnly);
}

bool JSHTMLTrackElementConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSHTMLTrackElementConstructor, DOMObject>(exec, &JSHTMLTrackElementConstructorTable, this, propertyName, slot);
}

bool JSHTMLTrackElementConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSHTMLTrackElementConstructor, DOMObject>(exec, &JSHTMLTrackElementConstructorTable, this, propertyName, descriptor);
}

/* Hash table for prototype */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSHTMLTrackElementPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSHTMLTrackElementPrototypeTable = { 1, 0, JSHTMLTrackElementPrototypeTableValues, 0 };
const ClassInfo JSHTMLTrackElementPrototype::s_info = { "HTMLTrackElementPrototype", 0, &JSHTMLTrackElementPrototypeTable, 0 };

JSObject* JSHTMLTrackElementPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSHTMLTrackElement>(exec, globalObject);
}

bool JSHTMLTrackElementPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
	const char* szDebug = propertyName.ascii();
    return getStaticPropertySlot<JSHTMLTrackElementPrototype, JSObject>(exec, &JSHTMLTrackElementPrototypeTable, this, propertyName, slot);
}

bool JSHTMLTrackElementPrototype::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
	const char* szDebug = propertyName.ascii();
    return getStaticPropertyDescriptor<JSHTMLTrackElementPrototype, JSObject>(exec, &JSHTMLTrackElementPrototypeTable, this, propertyName, descriptor);
}

const ClassInfo JSHTMLTrackElement::s_info = { "HTMLTrackElement", &JSHTMLElement::s_info, &JSHTMLTrackElementTable, 0 };

JSHTMLTrackElement::JSHTMLTrackElement(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<HTMLTrackElement> impl)
    : JSHTMLElement(structure, globalObject, impl)
{
}

JSObject* JSHTMLTrackElement::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSHTMLTrackElementPrototype(globalObject, JSHTMLTrackElementPrototype::createStructure(JSHTMLElementPrototype::self(exec, globalObject)));
}

bool JSHTMLTrackElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSHTMLTrackElement, Base>(exec, &JSHTMLTrackElementTable, this, propertyName, slot);
}

bool JSHTMLTrackElement::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSHTMLTrackElement, Base>(exec, &JSHTMLTrackElementTable, this, propertyName, descriptor);
}

void JSHTMLTrackElement::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    lookupPut<JSHTMLTrackElement, Base>(exec, propertyName, value, &JSHTMLTrackElementTable, this, slot);
}

// Attribute setters

JSValue jsHTMLTrackElementKind(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSHTMLTrackElement* castedThis = static_cast<JSHTMLTrackElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    HTMLTrackElement* imp = static_cast<HTMLTrackElement*>(castedThis->impl());
    JSValue result = jsString(exec, imp->kind());
    return result;
}

JSValue jsHTMLTrackElementSrc(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSHTMLTrackElement* castedThis = static_cast<JSHTMLTrackElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    HTMLTrackElement* imp = static_cast<HTMLTrackElement*>(castedThis->impl());
    JSValue result = jsString(exec, imp->getNonEmptyURLAttribute(WebCore::HTMLNames::srcAttr));
    return result;
}

JSValue jsHTMLTrackElementSrclang(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSHTMLTrackElement* castedThis = static_cast<JSHTMLTrackElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    HTMLTrackElement* imp = static_cast<HTMLTrackElement*>(castedThis->impl());
    JSValue result = jsString(exec, imp->srclang());
    return result;
}

JSValue jsHTMLTrackElementLabel(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSHTMLTrackElement* castedThis = static_cast<JSHTMLTrackElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    HTMLTrackElement* imp = static_cast<HTMLTrackElement*>(castedThis->impl());
    JSValue result = jsString(exec, imp->label());
    return result;
}

JSValue jsHTMLTrackElementDefault(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSHTMLTrackElement* castedThis = static_cast<JSHTMLTrackElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    HTMLTrackElement* imp = static_cast<HTMLTrackElement*>(castedThis->impl());
    JSValue result = jsBoolean(imp->hasAttribute(WebCore::HTMLNames::defaultAttr)); // FYMP - specified by .idl as '[Reflect] attribute boolean' did not find a role-model for this, thus did it like that.
    return result;
}

JSC::JSValue jsHTMLTrackElementReadyState(JSC::ExecState* exec, JSC::JSValue slotBase, const JSC::Identifier&)
{
    JSHTMLTrackElement* castedThis = static_cast<JSHTMLTrackElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    HTMLTrackElement* imp = static_cast<HTMLTrackElement*>(castedThis->impl());
    JSValue result = jsNumber(exec, imp->readyState());
    return result;
}

JSC::JSValue jsHTMLTrackElementTrack(JSC::ExecState* exec, JSC::JSValue slotBase, const JSC::Identifier&)
{
    JSHTMLTrackElement* castedThis = static_cast<JSHTMLTrackElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    HTMLTrackElement* imp = static_cast<HTMLTrackElement*>(castedThis->impl());
    JSValue result = toJS(exec, castedThis->globalObject(), imp->track());
    return result;
}

JSValue jsHTMLTrackElementConstructor(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSHTMLTrackElement* domObject = static_cast<JSHTMLTrackElement*>(asObject(slotBase));
    return JSHTMLTrackElement::getConstructor(exec, domObject->globalObject());
}

// Attribute getters

void setJSHTMLTrackElementKind(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSHTMLTrackElement* castedThis = static_cast<JSHTMLTrackElement*>(thisObject);
    HTMLTrackElement* imp = static_cast<HTMLTrackElement*>(castedThis->impl());
    imp->setKind(ustringToString(value.toString(exec)));
}

void setJSHTMLTrackElementSrc(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSHTMLTrackElement* castedThis = static_cast<JSHTMLTrackElement*>(thisObject);
    HTMLTrackElement* imp = static_cast<HTMLTrackElement*>(castedThis->impl());
    imp->setAttribute(WebCore::HTMLNames::srcAttr, valueToStringWithNullCheck(exec, value));
}

void setJSHTMLTrackElementSrclang(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSHTMLTrackElement* castedThis = static_cast<JSHTMLTrackElement*>(thisObject);
    HTMLTrackElement* imp = static_cast<HTMLTrackElement*>(castedThis->impl());
    imp->setSrclang(ustringToString(value.toString(exec)));
}

void setJSHTMLTrackElementLabel(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSHTMLTrackElement* castedThis = static_cast<JSHTMLTrackElement*>(thisObject);
    HTMLTrackElement* imp = static_cast<HTMLTrackElement*>(castedThis->impl());
    imp->setLabel(ustringToString(value.toString(exec)));
}

void setJSHTMLTrackElementDefault(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSHTMLTrackElement* castedThis = static_cast<JSHTMLTrackElement*>(thisObject);
    HTMLTrackElement* imp = static_cast<HTMLTrackElement*>(castedThis->impl());	
	imp->setBooleanAttribute(WebCore::HTMLNames::defaultAttr, value.toBoolean(exec)); // FYMP - specified by .idl as '[Reflect] attribute boolean' did not find a role-model for this, thus did it like that.
}

JSValue JSHTMLTrackElement::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSHTMLTrackElementConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}

// Constants
JSValue jsHTMLTrackElementNONE(ExecState* exec, JSValue, const Identifier&)
{
    return jsNumber(exec, static_cast<int>(0));
}
JSValue jsHTMLTrackElementLOADING(ExecState* exec, JSValue, const Identifier&)
{
    return jsNumber(exec, static_cast<int>(1));
}
JSValue jsHTMLTrackElementLOADED(ExecState* exec, JSValue, const Identifier&)
{
    return jsNumber(exec, static_cast<int>(2));
}
JSValue jsHTMLTrackElementERROR(ExecState* exec, JSValue, const Identifier&)
{
    return jsNumber(exec, static_cast<int>(3));
}

}

#endif // ENABLE(VIDEO) && ENABLE(VIDEO_TRACK)
