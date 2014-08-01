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
#include "JSTextTrackCue.h"
#include "TextTrackCue.h"


using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSTextTrackCue);

/* Hash table */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSTextTrackCueTableValues[17] =
{
    { "track",       DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackCueTrack),       (intptr_t)0                            THUNK_GENERATOR(0) },
    { "id",          DontDelete,            (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackCueId),          (intptr_t)jsTextTrackCueId             THUNK_GENERATOR(0) },
    { "startTime",   DontDelete,            (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackCueStartTime),   (intptr_t)jsSetTextTrackCueStartTime   THUNK_GENERATOR(0) },
	{ "endTime",     DontDelete,            (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackCueEndTime),     (intptr_t)jsSetTextTrackCueEndTime     THUNK_GENERATOR(0) },
	{ "pauseOnExit", DontDelete,            (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackCuePauseOnExit), (intptr_t)jsSetTextTrackCuePauseOnExit THUNK_GENERATOR(0) },
    { "vertical",    DontDelete,            (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackCueVertical),    (intptr_t)jsSetTextTrackCueVertical    THUNK_GENERATOR(0) },
    { "snapToLines", DontDelete,            (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackCueSnapToLines), (intptr_t)jsSetTextTrackCueSnapToLines THUNK_GENERATOR(0) },
    { "line",        DontDelete,            (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackCueLine),        (intptr_t)jsSetTextTrackCueLine        THUNK_GENERATOR(0) },
    { "position",    DontDelete,            (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackCuePosition),    (intptr_t)jsSetTextTrackCuePosition    THUNK_GENERATOR(0) },
	{ "size",        DontDelete,            (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackCueSize),        (intptr_t)jsSetTextTrackCueSize        THUNK_GENERATOR(0) },
	{ "align",       DontDelete,            (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackCueAlign),       (intptr_t)jsSetTextTrackCueAlign       THUNK_GENERATOR(0) },
	{ "text",        DontDelete,            (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackCueText),        (intptr_t)jsSetTextTrackCueText        THUNK_GENERATOR(0) },
// FYMP begin - adding region-attribute on cue's but without enabling the whole WEBVTT_REGIONS which controls WebKit's rendering of Cues.
	{ "region",      DontDelete,            (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackCueRegion),        (intptr_t)jsSetTextTrackCueRegion    THUNK_GENERATOR(0) },
// FYMP end
	{ "onenter",     DontDelete,            (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackCueOnenter),     (intptr_t)setJSTextTrackCueOnenter     THUNK_GENERATOR(0) },
    { "onexit",      DontDelete,            (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackCueOnexit),      (intptr_t)setJSTextTrackCueOnexit      THUNK_GENERATOR(0) },
	{ "constructor", DontEnum | ReadOnly,   (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackCueConstructor), (intptr_t)0                            THUNK_GENERATOR(0) },
	{ 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSTextTrackCueTable = { 36, 31, JSTextTrackCueTableValues, 0 };
/* Hash table for constructor */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSTextTrackCueConstructorTableValues[1] =
{
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSTextTrackCueConstructorTable = { 1, 0, JSTextTrackCueConstructorTableValues, 0 };
class JSTextTrackCueConstructor : public DOMConstructorObject {
public:
    JSTextTrackCueConstructor(JSC::ExecState*, JSDOMGlobalObject*);

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
	static JSC::EncodedJSValue JSC_HOST_CALL constructJSTextTrackCue(JSC::ExecState*);
	virtual JSC::ConstructType getConstructData(JSC::ConstructData&);
};

const ClassInfo JSTextTrackCueConstructor::s_info = { "TextTrackCueConstructor", 0, &JSTextTrackCueConstructorTable, 0 };

JSTextTrackCueConstructor::JSTextTrackCueConstructor(ExecState* exec, JSDOMGlobalObject* globalObject)
    : DOMConstructorObject(JSTextTrackCueConstructor::createStructure(globalObject->objectPrototype()), globalObject)
{
    putDirect(exec->propertyNames().prototype, JSTextTrackCuePrototype::self(exec, globalObject), DontDelete | ReadOnly);
}

bool JSTextTrackCueConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
	const char* szDebug = propertyName.ascii();
    return getStaticValueSlot<JSTextTrackCueConstructor, DOMObject>(exec, &JSTextTrackCueConstructorTable, this, propertyName, slot);
}

bool JSTextTrackCueConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
	const char* szDebug = propertyName.ascii();
    return getStaticValueDescriptor<JSTextTrackCueConstructor, DOMObject>(exec, &JSTextTrackCueConstructorTable, this, propertyName, descriptor);
}

ConstructType JSTextTrackCueConstructor::getConstructData(ConstructData& constructData)
{
    constructData.native.function = constructJSTextTrackCue;
    return ConstructTypeHost;
}

EncodedJSValue JSC_HOST_CALL JSTextTrackCueConstructor::constructJSTextTrackCue(ExecState* exec)
{
    JSTextTrackCueConstructor* jsConstructor = static_cast<JSTextTrackCueConstructor*>(exec->callee());
    ScriptExecutionContext* context = jsConstructor->scriptExecutionContext();
    if (!context)
        return throwVMError(exec, createReferenceError(exec, "TextTrackCue constructor associated document is unavailable"));

	double start = exec->argument(0).toNumber(exec);
	double end   = exec->argument(1).toNumber(exec);
	const String& content = ustringToString(exec->argument(2).toString(exec));

    RefPtr<TextTrackCue> cue = TextTrackCue::create(context, start, end, content);

    return JSValue::encode(CREATE_DOM_OBJECT_WRAPPER(exec, jsConstructor->globalObject(), TextTrackCue, cue.get()));
}

/* Hash table for prototype */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSTextTrackCuePrototypeTableValues[4] = {
    { "addEventListener",    DontDelete | Function, (intptr_t)static_cast<NativeFunction>(jsTextTrackCuePrototypeFunctionAddEventListener),    (intptr_t)3 THUNK_GENERATOR(0) },
    { "removeEventListener", DontDelete | Function, (intptr_t)static_cast<NativeFunction>(jsTextTrackCuePrototypeFunctionRemoveEventListener), (intptr_t)3 THUNK_GENERATOR(0) },
    { "dispatchEvent",       DontDelete | Function, (intptr_t)static_cast<NativeFunction>(jsTextTrackCuePrototypeFunctionDispatchEvent),       (intptr_t)1 THUNK_GENERATOR(0) },
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSTextTrackCuePrototypeTable = { 8, 7, JSTextTrackCuePrototypeTableValues, 0 };
const ClassInfo JSTextTrackCuePrototype::s_info = { "TextTrackCuePrototype", 0, &JSTextTrackCuePrototypeTable, 0 };

JSObject* JSTextTrackCuePrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSTextTrackCue>(exec, globalObject);
}

bool JSTextTrackCuePrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticPropertySlot<JSTextTrackCuePrototype, JSObject>(exec, &JSTextTrackCuePrototypeTable, this, propertyName, slot);
}

bool JSTextTrackCuePrototype::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticPropertyDescriptor<JSTextTrackCuePrototype, JSObject>(exec, &JSTextTrackCuePrototypeTable, this, propertyName, descriptor);
}

const ClassInfo JSTextTrackCue::s_info = { "TextTrackCue", 0, &JSTextTrackCueTable, 0 };

JSTextTrackCue::JSTextTrackCue(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<TextTrackCue> impl)
    : DOMObjectWithGlobalPointer(structure, globalObject)
    , m_impl(impl)
{
}

JSTextTrackCue::~JSTextTrackCue()
{
    impl()->invalidateJSEventListeners(this);
	forgetDOMObject(this, impl());
}

JSObject* JSTextTrackCue::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSTextTrackCuePrototype(globalObject, JSTextTrackCuePrototype::createStructure(globalObject->objectPrototype()));
}

bool JSTextTrackCue::getOwnPropertySlot(JSC::ExecState* exec, const JSC::Identifier& propertyName, JSC::PropertySlot& slot)
{
	const char* szDebug = propertyName.ascii();
    return JSC::getStaticValueSlot<JSTextTrackCue, Base>(exec, s_info.staticPropHashTable, this, propertyName, slot);
}

bool JSTextTrackCue::getOwnPropertyDescriptor(JSC::ExecState* exec, const JSC::Identifier& propertyName, JSC::PropertyDescriptor& descriptor)
{
	const char* szDebug = propertyName.ascii();
    return JSC::getStaticValueDescriptor<JSTextTrackCue, Base>(exec, s_info.staticPropHashTable, this, propertyName, descriptor);
}

void JSTextTrackCue::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    lookupPut<JSTextTrackCue, Base>(exec, propertyName, value, &JSTextTrackCueTable, this, slot);
}

// Attributes

JSC::JSValue jsTextTrackCueTrack(JSC::ExecState* exec, JSC::JSValue slotBase, const JSC::Identifier&)
{
    JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());
    JSValue result = toJS(exec, castedThis->globalObject(), imp->track());
    return result;
}
JSValue jsTextTrackCueId(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());
    JSValue result = jsStringOrNull(exec, imp->id());
    return result;
}
void jsSetTextTrackCueId(JSC::ExecState* exec, JSC::JSObject* slotBase, JSC::JSValue value)
{
	JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(asObject(slotBase));
	TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());
	imp->setId(valueToStringWithNullCheck(exec, value));
}
JSValue jsTextTrackCueStartTime(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());
    JSValue result = jsNumber(exec, imp->startTime());
    return result;
}
void jsSetTextTrackCueStartTime(JSC::ExecState* exec, JSC::JSObject* slotBase, JSC::JSValue value)
{
	JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(asObject(slotBase));
	TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());
	if (value.isDouble())
		{
		ExceptionCode ec = 0;
		imp->setStartTime(value.asDouble(), ec);
		setDOMException(exec, ec);
		}
}
JSValue jsTextTrackCueEndTime(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());
    JSValue result = jsNumber(exec, imp->endTime());
    return result;
}
void jsSetTextTrackCueEndTime(JSC::ExecState* exec, JSC::JSObject* slotBase, JSC::JSValue value)
{
	JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(asObject(slotBase));
	TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());
	if (value.isDouble())
		{
		ExceptionCode ec = 0;
		imp->setEndTime(value.asDouble(), ec);
		setDOMException(exec, ec);
		}
}
JSValue jsTextTrackCuePauseOnExit(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());
    JSValue result = jsBoolean(imp->pauseOnExit());
    return result;
}
void jsSetTextTrackCuePauseOnExit(JSC::ExecState* exec, JSC::JSObject* slotBase, JSC::JSValue value)
{
	JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(asObject(slotBase));
	TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());
	if (value.isDouble())
		{
		imp->setPauseOnExit(value.toBoolean(exec));
		}
}
JSValue jsTextTrackCueVertical(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());
    JSValue result = jsStringOrNull(exec, imp->vertical());
    return result;
}
void jsSetTextTrackCueVertical(JSC::ExecState* exec, JSC::JSObject* slotBase, JSC::JSValue value)
{
	JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(asObject(slotBase));
	TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());

	ExceptionCode ec = 0;
	imp->setVertical(valueToStringWithNullCheck(exec, value), ec);
	setDOMException(exec, ec);
}
JSValue jsTextTrackCueSnapToLines(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());
    JSValue result = jsBoolean(imp->snapToLines());
    return result;
}
void jsSetTextTrackCueSnapToLines(JSC::ExecState* exec, JSC::JSObject* slotBase, JSC::JSValue value)
{
	JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(asObject(slotBase));
	TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());
	if (value.isDouble())
		{
		imp->setSnapToLines(value.toBoolean(exec));
		}
}
JSValue jsTextTrackCueLine(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());
    JSValue result = jsNumber(exec, imp->line());
    return result;
}
void jsSetTextTrackCueLine(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(thisObject);
    TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());
	ExceptionCode ec = 0;
    imp->setLine(value.toInt32(exec), ec);
	setDOMException(exec, ec);
}
JSValue jsTextTrackCuePosition(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());
    JSValue result = jsNumber(exec, imp->position());
    return result;
}
void jsSetTextTrackCuePosition(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(thisObject);
    TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());
	ExceptionCode ec = 0;
    imp->setPosition(value.toInt32(exec), ec);
	setDOMException(exec, ec);
}
JSValue jsTextTrackCueSize(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());
    JSValue result = jsNumber(exec, imp->size());
    return result;
}
void jsSetTextTrackCueSize(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(thisObject);
    TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());
	ExceptionCode ec = 0;
    imp->setSize(value.toInt32(exec), ec);
	setDOMException(exec, ec);
}
JSValue jsTextTrackCueAlign(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());
    JSValue result = jsStringOrNull(exec, imp->align());
    return result;
}
void jsSetTextTrackCueAlign(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(thisObject);
    TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());
	ExceptionCode ec = 0;
    imp->setAlign(valueToStringWithNullCheck(exec, value), ec);
	setDOMException(exec, ec);
}
JSValue jsTextTrackCueText(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());
    JSValue result = jsStringOrNull(exec, imp->text());
    return result;
}
void jsSetTextTrackCueText(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(thisObject);
    TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());
    imp->setText(valueToStringWithNullCheck(exec, value));
}
// FYMP begin - adding region-attribute on cue's but without enabling the whole WEBVTT_REGIONS which controls WebKit's rendering of Cues.
JSValue jsTextTrackCueRegion(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());
    JSValue result = jsStringOrNull(exec, imp->regionId());
    return result;
}
void jsSetTextTrackCueRegion(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(thisObject);
    TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());
    imp->setRegionId(valueToStringWithNullCheck(exec, value));
}
// FYMP end
JSValue jsTextTrackCueOnenter(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());
    if (EventListener* listener = imp->onenter()) {
        if (const JSEventListener* jsListener = JSEventListener::cast(listener)) {
            if (JSObject* jsFunction = jsListener->jsFunction(imp->scriptExecutionContext()))
                return jsFunction;
        }
    }
    return jsNull();
}
void setJSTextTrackCueOnenter(ExecState* exec, JSObject* thisObject, JSValue value)
{
    UNUSED_PARAM(exec);
    TextTrackCue* imp = static_cast<TextTrackCue*>(static_cast<JSTextTrackCue*>(thisObject)->impl());
    imp->setOnenter(createJSAttributeEventListener(exec, value, thisObject));
}
JSValue jsTextTrackCueOnexit(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());
    if (EventListener* listener = imp->onexit()) {
        if (const JSEventListener* jsListener = JSEventListener::cast(listener)) {
            if (JSObject* jsFunction = jsListener->jsFunction(imp->scriptExecutionContext()))
                return jsFunction;
        }
    }
    return jsNull();
}
void setJSTextTrackCueOnexit(ExecState* exec, JSObject* thisObject, JSValue value)
{
    UNUSED_PARAM(exec);
    TextTrackCue* imp = static_cast<TextTrackCue*>(static_cast<JSTextTrackCue*>(thisObject)->impl());
    imp->setOnexit(createJSAttributeEventListener(exec, value, thisObject));
}

// Functions
EncodedJSValue JSC_HOST_CALL jsTextTrackCuePrototypeFunctionAddEventListener(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(&JSTextTrackCue::s_info))
        return throwVMTypeError(exec);
    JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(asObject(thisValue));
    TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());
    JSValue listener = exec->argument(1);
    if (!listener.isObject())
        return JSValue::encode(jsUndefined());
    imp->addEventListener(ustringToAtomicString(exec->argument(0).toString(exec)), JSEventListener::create(asObject(listener), castedThis, false, currentWorld(exec)), exec->argument(2).toBoolean(exec));
    return JSValue::encode(jsUndefined());
}
EncodedJSValue JSC_HOST_CALL jsTextTrackCuePrototypeFunctionRemoveEventListener(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(&JSTextTrackCue::s_info))
        return throwVMTypeError(exec);
    JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(asObject(thisValue));
    TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());
    JSValue listener = exec->argument(1);
    if (!listener.isObject())
        return JSValue::encode(jsUndefined());
    imp->removeEventListener(ustringToAtomicString(exec->argument(0).toString(exec)), JSEventListener::create(asObject(listener), castedThis, false, currentWorld(exec)).get(), exec->argument(2).toBoolean(exec));
    return JSValue::encode(jsUndefined());
}
EncodedJSValue JSC_HOST_CALL jsTextTrackCuePrototypeFunctionDispatchEvent(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(&JSTextTrackCue::s_info))
        return throwVMTypeError(exec);
    JSTextTrackCue* castedThis = static_cast<JSTextTrackCue*>(asObject(thisValue));
    TextTrackCue* imp = static_cast<TextTrackCue*>(castedThis->impl());
    ExceptionCode ec = 0;
    Event* event = toEvent(exec->argument(0));

    JSC::JSValue result = jsBoolean(imp->dispatchEvent(event, ec));
    setDOMException(exec, ec);
    return JSValue::encode(result);
}


JSValue jsTextTrackCueConstructor(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrackCue* domObject = static_cast<JSTextTrackCue*>(asObject(slotBase));
    return JSTextTrackCue::getConstructor(exec, domObject->globalObject());
}
/*
void JSTextTrackCue::getOwnPropertyNames(ExecState* exec, PropertyNameArray& propertyNames, EnumerationMode mode)
{
    for (unsigned i = 0; i < static_cast<TextTrackCue*>(impl())->length(); ++i)
        propertyNames.add(Identifier::from(exec, i));
     Base::getOwnPropertyNames(exec, propertyNames, mode);
}
*/
JSValue JSTextTrackCue::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTextTrackCueConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}

JSC::JSValue toJS(JSC::ExecState* exec, JSDOMGlobalObject* globalObject, TextTrackCue* textTrack)
{
	return getDOMObjectWrapper<JSTextTrackCue>(exec, globalObject, textTrack);
}

TextTrackCue* toTextTrackCue(JSC::JSValue value)
{
    return value.inherits(&JSTextTrackCue::s_info) ? static_cast<JSTextTrackCue*>(asObject(value))->impl() : 0;
}

}

#endif // ENABLE(VIDEO_TRACK)
