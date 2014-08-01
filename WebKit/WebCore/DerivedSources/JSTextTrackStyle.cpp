

/* FYWEBKITMOD BEGIN custom extension. This file was not auto-generated! Added to support JSTextTrack::regions() */

#include "config.h"

#if ENABLE(VIDEO_TRACK) && ENABLE(WEBVTT_STYLES)

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

#include "JSTextTrackStyle.h"
#include "TextTrackStyle.h"


using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSTextTrackStyle);

/* Hash table */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSTextTrackStyleTableValues[5] =
{
    { "selector",    DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackStyleSelector),    (intptr_t)0 THUNK_GENERATOR(0) },
    { "style",       DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackStyleStyle),       (intptr_t)0 THUNK_GENERATOR(0) },
    { "styleJSON",   DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackStyleStyleJSON),   (intptr_t)0 THUNK_GENERATOR(0) },
	{ "constructor", DontEnum   | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackStyleConstructor), (intptr_t)0 THUNK_GENERATOR(0) },
	{ 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSTextTrackStyleTable = { 9, 7, JSTextTrackStyleTableValues, 0 };
/* Hash table for constructor */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSTextTrackStyleConstructorTableValues[1] =
{
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSTextTrackStyleConstructorTable = { 1, 0, JSTextTrackStyleConstructorTableValues, 0 };
class JSTextTrackStyleConstructor : public DOMConstructorObject {
public:
    JSTextTrackStyleConstructor(JSC::ExecState*, JSDOMGlobalObject*);

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

const ClassInfo JSTextTrackStyleConstructor::s_info = { "TextTrackStyleConstructor", 0, &JSTextTrackStyleConstructorTable, 0 };

JSTextTrackStyleConstructor::JSTextTrackStyleConstructor(ExecState* exec, JSDOMGlobalObject* globalObject)
    : DOMConstructorObject(JSTextTrackStyleConstructor::createStructure(globalObject->objectPrototype()), globalObject)
{
    putDirect(exec->propertyNames().prototype, JSTextTrackStylePrototype::self(exec, globalObject), DontDelete | ReadOnly);
}

bool JSTextTrackStyleConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
	const char* szDebug = propertyName.ascii();
    return getStaticValueSlot<JSTextTrackStyleConstructor, DOMObject>(exec, &JSTextTrackStyleConstructorTable, this, propertyName, slot);
}

bool JSTextTrackStyleConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
	const char* szDebug = propertyName.ascii();
    return getStaticValueDescriptor<JSTextTrackStyleConstructor, DOMObject>(exec, &JSTextTrackStyleConstructorTable, this, propertyName, descriptor);
}

/* Hash table for prototype */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSTextTrackStylePrototypeTableValues[1] = {
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSTextTrackStylePrototypeTable = { 1, 0, JSTextTrackStylePrototypeTableValues, 0 };
const ClassInfo JSTextTrackStylePrototype::s_info = { "TextTrackStylePrototype", 0, &JSTextTrackStylePrototypeTable, 0 };

JSObject* JSTextTrackStylePrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSTextTrackStyle>(exec, globalObject);
}

bool JSTextTrackStylePrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticPropertySlot<JSTextTrackStylePrototype, JSObject>(exec, &JSTextTrackStylePrototypeTable, this, propertyName, slot);
}

bool JSTextTrackStylePrototype::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticPropertyDescriptor<JSTextTrackStylePrototype, JSObject>(exec, &JSTextTrackStylePrototypeTable, this, propertyName, descriptor);
}

const ClassInfo JSTextTrackStyle::s_info = { "TextTrackStyle", 0, &JSTextTrackStyleTable, 0 };

JSTextTrackStyle::JSTextTrackStyle(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<TextTrackStyle> impl)
    : DOMObjectWithGlobalPointer(structure, globalObject)
    , m_impl(impl)
{
}

JSTextTrackStyle::~JSTextTrackStyle()
{
	forgetDOMObject(this, impl());
}

JSObject* JSTextTrackStyle::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSTextTrackStylePrototype(globalObject, JSTextTrackStylePrototype::createStructure(globalObject->objectPrototype()));
}

bool JSTextTrackStyle::getOwnPropertySlot(JSC::ExecState* exec, const JSC::Identifier& propertyName, JSC::PropertySlot& slot)
{
    return JSC::getStaticValueSlot<JSTextTrackStyle, Base>(exec, s_info.staticPropHashTable, this, propertyName, slot);
}

bool JSTextTrackStyle::getOwnPropertyDescriptor(JSC::ExecState* exec, const JSC::Identifier& propertyName, JSC::PropertyDescriptor& descriptor)
{
    return JSC::getStaticValueDescriptor<JSTextTrackStyle, Base>(exec, s_info.staticPropHashTable, this, propertyName, descriptor);
}

void JSTextTrackStyle::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    lookupPut<JSTextTrackStyle, Base>(exec, propertyName, value, &JSTextTrackStyleTable, this, slot);
}

JSC::JSValue jsTextTrackStyleSelector(JSC::ExecState* exec, JSC::JSValue slotBase, const Identifier&)
{
	JSTextTrackStyle* castedThis = static_cast<JSTextTrackStyle*>(asObject(slotBase));
    TextTrackStyle* imp = static_cast<TextTrackStyle*>(castedThis->impl());
    JSValue result = jsStringOrNull(exec, imp->selector());
    return result;

}

JSC::JSValue jsTextTrackStyleStyle(JSC::ExecState* exec, JSC::JSValue slotBase, const Identifier&)
{
	JSTextTrackStyle* castedThis = static_cast<JSTextTrackStyle*>(asObject(slotBase));
	TextTrackStyle* imp = static_cast<TextTrackStyle*>(castedThis->impl());
	JSValue result = jsStringOrNull(exec, imp->style());
	return result;
}

JSC::JSValue jsTextTrackStyleStyleJSON(JSC::ExecState* exec, JSC::JSValue slotBase, const Identifier&)
{
	JSTextTrackStyle* castedThis = static_cast<JSTextTrackStyle*>(asObject(slotBase));
	TextTrackStyle* imp = static_cast<TextTrackStyle*>(castedThis->impl());
	JSValue result = jsStringOrNull(exec, imp->styleJSON());
	return result;
}

JSValue jsTextTrackStyleConstructor(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrackStyle* domObject = static_cast<JSTextTrackStyle*>(asObject(slotBase));
    return JSTextTrackStyle::getConstructor(exec, domObject->globalObject());
}

JSValue JSTextTrackStyle::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTextTrackStyleConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}

JSC::JSValue toJS(JSC::ExecState* exec, JSDOMGlobalObject* globalObject, TextTrackStyle* textTrack)
{
	return getDOMObjectWrapper<JSTextTrackStyle>(exec, globalObject, textTrack);
}

TextTrackStyle* toTextTrackStyle(JSC::JSValue value)
{
    return value.inherits(&JSTextTrackStyle::s_info) ? static_cast<JSTextTrackStyle*>(asObject(value))->impl() : 0;
}

}

#endif // ENABLE(VIDEO_TRACK) && ENABLE(WEBVTT_STYLES)

/* FYWEBKITMOD END */
