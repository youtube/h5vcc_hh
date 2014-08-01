/* 
    Copyright (C) 2014 FactorY Media Production GmbH

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

#if ENABLE(VIDEO_TRACK)

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

#include "JSTextTrack.h"
#include "TextTrack.h"
#include "JSTextTrackCue.h"
#include "JSTextTrackCueList.h"

#if ENABLE(WEBVTT_REGIONS)
#include "TextTrackRegionList.h"
#include "JSTextTrackRegionList.h"
#endif

/* FYWEBKITMOD BEGIN custom extensions */
#if ENABLE(WEBVTT_STYLES)
#include "TextTrackStyleList.h"
#include "JSTextTrackStyleList.h"
#endif
/* FYWEBKITMOD END */


using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSTextTrack);

/* Hash table */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSTextTrackTableValues[11] =
{
/* FYWEBKITMOD BEGIN custom extensions */
#if ENABLE(WEBVTT_REGIONS)
    { "regions", DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackRegions), (intptr_t)0 THUNK_GENERATOR(0) },
#endif
#if ENABLE(WEBVTT_STYLES)
    { "styles", DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackStyles), (intptr_t)0 THUNK_GENERATOR(0) },
#endif
/* FYWEBKITMOD END */
    { "kind", DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackKind), (intptr_t)0 THUNK_GENERATOR(0) },
    { "label", DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackLabel), (intptr_t)0 THUNK_GENERATOR(0) },
    { "language", DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackLanguage), (intptr_t)0 THUNK_GENERATOR(0) },
// FYMP - 'id' is not easily possible due to our implementation. Latest WebKit also does not support this attribute.
//	{ "id", DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackId), (intptr_t)0 THUNK_GENERATOR(0) },
// FYMP - at the moment, we dont support in-band-texttracks. This attribute is also not supported by latest WebKit.
//    { "inBandMetadataTrackDispatchType", DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsNodeParentNode), (intptr_t)0 THUNK_GENERATOR(0) },
    { "mode",        DontDelete, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackMode), (intptr_t)jsSetTextTrackMode THUNK_GENERATOR(0) },
    { "cues",        DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackCues), (intptr_t)0 THUNK_GENERATOR(0) },
    { "activeCues",  DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackActiveCues),  (intptr_t)0 THUNK_GENERATOR(0) },
    { "oncuechange", DontDelete,            (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackOncuechange), (intptr_t)setJSTextTrackOncuechange THUNK_GENERATOR(0) },
	{ "constructor", DontEnum | ReadOnly,   (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackConstructor), (intptr_t)0 THUNK_GENERATOR(0) },
	{ 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSTextTrackTable = { 34, 31, JSTextTrackTableValues, 0 };
/* Hash table for constructor */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSTextTrackConstructorTableValues[1] =
{
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSTextTrackConstructorTable = { 1, 0, JSTextTrackConstructorTableValues, 0 };
class JSTextTrackConstructor : public DOMConstructorObject {
public:
    JSTextTrackConstructor(JSC::ExecState*, JSDOMGlobalObject*);

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

const ClassInfo JSTextTrackConstructor::s_info = { "TextTrackConstructor", 0, &JSTextTrackConstructorTable, 0 };

JSTextTrackConstructor::JSTextTrackConstructor(ExecState* exec, JSDOMGlobalObject* globalObject)
    : DOMConstructorObject(JSTextTrackConstructor::createStructure(globalObject->objectPrototype()), globalObject)
{
    putDirect(exec->propertyNames().prototype, JSTextTrackPrototype::self(exec, globalObject), DontDelete | ReadOnly);
}

bool JSTextTrackConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
	const char* szDebug = propertyName.ascii();
    return getStaticValueSlot<JSTextTrackConstructor, DOMObject>(exec, &JSTextTrackConstructorTable, this, propertyName, slot);
}

bool JSTextTrackConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
	const char* szDebug = propertyName.ascii();
    return getStaticValueDescriptor<JSTextTrackConstructor, DOMObject>(exec, &JSTextTrackConstructorTable, this, propertyName, descriptor);
}

/* Hash table for prototype */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSTextTrackPrototypeTableValues[6] = {
	{ "addCue",              DontDelete | Function, (intptr_t)static_cast<NativeFunction>(jsTextTrackPrototypeFunctionAddCue),              (intptr_t)1 THUNK_GENERATOR(0) },
    { "removeCue",           DontDelete | Function, (intptr_t)static_cast<NativeFunction>(jsTextTrackPrototypeFunctionRemoveCue),           (intptr_t)1 THUNK_GENERATOR(0) },
    { "addEventListener",    DontDelete | Function, (intptr_t)static_cast<NativeFunction>(jsTextTrackPrototypeFunctionAddEventListener),    (intptr_t)3 THUNK_GENERATOR(0) },
    { "removeEventListener", DontDelete | Function, (intptr_t)static_cast<NativeFunction>(jsTextTrackPrototypeFunctionRemoveEventListener), (intptr_t)3 THUNK_GENERATOR(0) },
    { "dispatchEvent",       DontDelete | Function, (intptr_t)static_cast<NativeFunction>(jsTextTrackPrototypeFunctionDispatchEvent),       (intptr_t)1 THUNK_GENERATOR(0) },
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSTextTrackPrototypeTable = { 16, 15, JSTextTrackPrototypeTableValues, 0 };
const ClassInfo JSTextTrackPrototype::s_info = { "TextTrackPrototype", 0, &JSTextTrackPrototypeTable, 0 };

JSObject* JSTextTrackPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSTextTrack>(exec, globalObject);
}

bool JSTextTrackPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticPropertySlot<JSTextTrackPrototype, JSObject>(exec, &JSTextTrackPrototypeTable, this, propertyName, slot);
}

bool JSTextTrackPrototype::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticPropertyDescriptor<JSTextTrackPrototype, JSObject>(exec, &JSTextTrackPrototypeTable, this, propertyName, descriptor);
}

const ClassInfo JSTextTrack::s_info = { "TextTrack", 0, &JSTextTrackTable, 0 };

JSTextTrack::JSTextTrack(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<TextTrack> impl)
    : DOMObjectWithGlobalPointer(structure, globalObject)
    , m_impl(impl)
{
}

JSTextTrack::~JSTextTrack()
{
    impl()->invalidateJSEventListeners(this);
	forgetDOMObject(this, impl());
}

JSObject* JSTextTrack::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSTextTrackPrototype(globalObject, JSTextTrackPrototype::createStructure(globalObject->objectPrototype()));
}

bool JSTextTrack::getOwnPropertySlot(JSC::ExecState* exec, const JSC::Identifier& propertyName, JSC::PropertySlot& slot)
{
	const char* szDebug = propertyName.ascii();
    return JSC::getStaticValueSlot<JSTextTrack, Base>(exec, s_info.staticPropHashTable, this, propertyName, slot);
}

bool JSTextTrack::getOwnPropertyDescriptor(JSC::ExecState* exec, const JSC::Identifier& propertyName, JSC::PropertyDescriptor& descriptor)
{
	const char* szDebug = propertyName.ascii();
    return JSC::getStaticValueDescriptor<JSTextTrack, Base>(exec, s_info.staticPropHashTable, this, propertyName, descriptor);
}

void JSTextTrack::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    lookupPut<JSTextTrack, Base>(exec, propertyName, value, &JSTextTrackTable, this, slot);
}

#if ENABLE(WEBVTT_REGIONS)
JSValue jsTextTrackRegions(ExecState* exec, JSValue slotBase, const Identifier&)
	{
    JSTextTrack* castedThis = static_cast<JSTextTrack*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TextTrack* imp = static_cast<TextTrack*>(castedThis->impl());
	JSDOMGlobalObject*   pGlob = castedThis->globalObject();
	TextTrackRegionList* pList = WTF::getPtr(imp->regions());
    JSValue result             = toJS(exec, pGlob, pList);
    return result;
	}
#endif

/* FYWEBKITMOD BEGIN custom extensions */
#if ENABLE(WEBVTT_STYLES)
JSValue jsTextTrackStyles(ExecState* exec, JSValue slotBase, const Identifier&)
	{
    JSTextTrack* castedThis = static_cast<JSTextTrack*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TextTrack* imp = static_cast<TextTrack*>(castedThis->impl());
	JSDOMGlobalObject*   pGlob = castedThis->globalObject();
	TextTrackStyleList*  pList = WTF::getPtr(imp->styles());
    JSValue result             = toJS(exec, pGlob, pList);
    return result;
	}
#endif
/* FYWEBKITMOD END */

JSValue jsTextTrackKind(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrack* castedThis = static_cast<JSTextTrack*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TextTrack* imp = static_cast<TextTrack*>(castedThis->impl());
    JSValue result = jsStringOrNull(exec, imp->kind()); // myTODO: must return 'TextTrackKind'
    return result;
}

JSValue jsTextTrackLabel(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrack* castedThis = static_cast<JSTextTrack*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TextTrack* imp = static_cast<TextTrack*>(castedThis->impl());
    JSValue result = jsStringOrNull(exec, imp->label());
    return result;
}

JSValue jsTextTrackLanguage(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrack* castedThis = static_cast<JSTextTrack*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TextTrack* imp = static_cast<TextTrack*>(castedThis->impl());
    JSValue result = jsStringOrNull(exec, imp->language());
    return result;
}

/*
JSValue jsTextTrackId(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrack* castedThis = static_cast<JSTextTrack*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TextTrack* imp = static_cast<TextTrack*>(castedThis->impl());
    JSValue result = jsStringOrNull(exec, 0));
    return result;
}
*/
JSC::JSValue jsTextTrackMode(JSC::ExecState* exec, JSC::JSValue slotBase, const Identifier&)
{
	JSTextTrack* castedThis = static_cast<JSTextTrack*>(asObject(slotBase));
	UNUSED_PARAM(exec);
    TextTrack* imp = static_cast<TextTrack*>(castedThis->impl());
    JSValue result = jsStringOrNull(exec, imp->mode());
    return result;

}

void jsSetTextTrackMode(JSC::ExecState* exec, JSC::JSObject* slotBase, JSC::JSValue value)
{
	JSTextTrack* castedThis = static_cast<JSTextTrack*>(asObject(slotBase));
	TextTrack* imp = static_cast<TextTrack*>(castedThis->impl());
//	ExceptionCode ec = 0;
	imp->setMode(valueToStringWithNullCheck(exec, value));

//	setDOMException(exec, ec);
}

JSValue jsTextTrackCues(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrack* castedThis = static_cast<JSTextTrack*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TextTrack* imp = static_cast<TextTrack*>(castedThis->impl());
    JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(imp->cues()));
    return result;
}

JSValue jsTextTrackActiveCues(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrack* castedThis = static_cast<JSTextTrack*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TextTrack* imp = static_cast<TextTrack*>(castedThis->impl());
    JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(imp->activeCues()));
    return result;
}

JSValue jsTextTrackOncuechange(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrack* castedThis = static_cast<JSTextTrack*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TextTrack* imp = static_cast<TextTrack*>(castedThis->impl());
    if (EventListener* listener = imp->oncuechange()) {
        if (const JSEventListener* jsListener = JSEventListener::cast(listener)) {
            if (JSObject* jsFunction = jsListener->jsFunction(imp->scriptExecutionContext()))
                return jsFunction;
        }
    }
    return jsNull();
}
void setJSTextTrackOncuechange(ExecState* exec, JSObject* thisObject, JSValue value)
{
    UNUSED_PARAM(exec);
    TextTrack* imp = static_cast<TextTrack*>(static_cast<JSTextTrack*>(thisObject)->impl());
    imp->setOncuechange(createJSAttributeEventListener(exec, value, thisObject));
}

// Functions

EncodedJSValue JSC_HOST_CALL jsTextTrackPrototypeFunctionAddCue(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(&JSTextTrack::s_info))
        return throwVMTypeError(exec);
    JSTextTrack* castedThis = static_cast<JSTextTrack*>(asObject(thisValue));

	TextTrack* thisTextTrack = castedThis->impl();

	JSC::JSValue argFirst = exec->argument(0);
	TextTrackCue* argTextTrackCue = argFirst.inherits(&JSTextTrackCue::s_info) ? static_cast<JSTextTrackCue*>(asObject(argFirst))->impl() : 0;

	if (argTextTrackCue)
		{
		thisTextTrack->addCue(argTextTrackCue);
		}

	return JSValue::encode(jsUndefined());
}

EncodedJSValue JSC_HOST_CALL jsTextTrackPrototypeFunctionRemoveCue(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(&JSTextTrack::s_info))
        return throwVMTypeError(exec);
    JSTextTrack* castedThis = static_cast<JSTextTrack*>(asObject(thisValue));
	TextTrack* thisTextTrack = castedThis->impl();

	JSC::JSValue argFirst = exec->argument(0);
	TextTrackCue* argTextTrackCue = argFirst.inherits(&JSTextTrackCue::s_info) ? static_cast<JSTextTrackCue*>(asObject(argFirst))->impl() : 0;

	if (argTextTrackCue)
		{
		ExceptionCode ec = 0;
		thisTextTrack->removeCue(argTextTrackCue, ec);
		setDOMException(exec, ec);
		}

	return JSValue::encode(jsUndefined());
}

EncodedJSValue JSC_HOST_CALL jsTextTrackPrototypeFunctionAddEventListener(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(&JSTextTrack::s_info))
        return throwVMTypeError(exec);
    JSTextTrack* castedThis = static_cast<JSTextTrack*>(asObject(thisValue));
    TextTrack* imp = static_cast<TextTrack*>(castedThis->impl());
    JSValue listener = exec->argument(1);
    if (!listener.isObject())
        return JSValue::encode(jsUndefined());
    imp->addEventListener(ustringToAtomicString(exec->argument(0).toString(exec)), JSEventListener::create(asObject(listener), castedThis, false, currentWorld(exec)), exec->argument(2).toBoolean(exec));
    return JSValue::encode(jsUndefined());
}

EncodedJSValue JSC_HOST_CALL jsTextTrackPrototypeFunctionRemoveEventListener(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(&JSTextTrack::s_info))
        return throwVMTypeError(exec);
    JSTextTrack* castedThis = static_cast<JSTextTrack*>(asObject(thisValue));
    TextTrack* imp = static_cast<TextTrack*>(castedThis->impl());
    JSValue listener = exec->argument(1);
    if (!listener.isObject())
        return JSValue::encode(jsUndefined());
    imp->removeEventListener(ustringToAtomicString(exec->argument(0).toString(exec)), JSEventListener::create(asObject(listener), castedThis, false, currentWorld(exec)).get(), exec->argument(2).toBoolean(exec));
    return JSValue::encode(jsUndefined());
}

EncodedJSValue JSC_HOST_CALL jsTextTrackPrototypeFunctionDispatchEvent(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(&JSTextTrack::s_info))
        return throwVMTypeError(exec);
    JSTextTrack* castedThis = static_cast<JSTextTrack*>(asObject(thisValue));
    TextTrack* imp = static_cast<TextTrack*>(castedThis->impl());
    ExceptionCode ec = 0;
    Event* event = toEvent(exec->argument(0));

    JSC::JSValue result = jsBoolean(imp->dispatchEvent(event, ec));
    setDOMException(exec, ec);
    return JSValue::encode(result);
}

JSValue jsTextTrackConstructor(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrack* domObject = static_cast<JSTextTrack*>(asObject(slotBase));
    return JSTextTrack::getConstructor(exec, domObject->globalObject());
}
/*
void JSTextTrack::getOwnPropertyNames(ExecState* exec, PropertyNameArray& propertyNames, EnumerationMode mode)
{
    for (unsigned i = 0; i < static_cast<TextTrack*>(impl())->length(); ++i)
        propertyNames.add(Identifier::from(exec, i));
     Base::getOwnPropertyNames(exec, propertyNames, mode);
}
*/
JSValue JSTextTrack::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTextTrackConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}

JSC::JSValue toJS(JSC::ExecState* exec, JSDOMGlobalObject* globalObject, TextTrack* textTrack)
{
	return getDOMObjectWrapper<JSTextTrack>(exec, globalObject, textTrack);
}

TextTrack* toTextTrack(JSC::JSValue value)
{
    return value.inherits(&JSTextTrack::s_info) ? static_cast<JSTextTrack*>(asObject(value))->impl() : 0;
}

}

#endif // ENABLE(VIDEO_TRACK)

