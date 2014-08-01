

/* FYWEBKITMOD BEGIN custom extension. this file was not auto-generated. Added to support JSTextTrack::regions() */

#include "config.h"

#if ENABLE(VIDEO_TRACK) && ENABLE(WEBVTT_STYLES)

#include "JSTextTrackStyleList.h"

//#include "AtomicString.h"
//#include "ExceptionCode.h"
//#include "Event.h"
//#include "JSEvent.h"
//#include "JSNode.h"
//#include "Node.h"
#include "TextTrackStyleList.h"
#include "JSTextTrackStyle.h"
#include <runtime/Error.h>
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSTextTrackStyleList);

/* Hash table */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSTextTrackStyleListTableValues[3] =
{
    { "length",        DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackStyleListLength),      (intptr_t)0                               THUNK_GENERATOR(0) },
    { "constructor",   DontEnum | ReadOnly,   (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackStyleListConstructor), (intptr_t)0                               THUNK_GENERATOR(0) },
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSTextTrackStyleListTable = { 5, 3, JSTextTrackStyleListTableValues, 0 };
/* Hash table for constructor */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSTextTrackStyleListConstructorTableValues[1] =
{
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSTextTrackStyleListConstructorTable = { 1, 0, JSTextTrackStyleListConstructorTableValues, 0 };
class JSTextTrackStyleListConstructor : public DOMConstructorObject {
public:
    JSTextTrackStyleListConstructor(JSC::ExecState*, JSDOMGlobalObject*);

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

const ClassInfo JSTextTrackStyleListConstructor::s_info = { "TextTrackStyleListConstructor", 0, &JSTextTrackStyleListConstructorTable, 0 };

JSTextTrackStyleListConstructor::JSTextTrackStyleListConstructor(ExecState* exec, JSDOMGlobalObject* globalObject)
    : DOMConstructorObject(JSTextTrackStyleListConstructor::createStructure(globalObject->objectPrototype()), globalObject)
{
    putDirect(exec->propertyNames().prototype, JSTextTrackStyleListPrototype::self(exec, globalObject), DontDelete | ReadOnly);
}

bool JSTextTrackStyleListConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
	const char* szDebug = propertyName.ascii();
    return getStaticValueSlot<JSTextTrackStyleListConstructor, DOMObject>(exec, &JSTextTrackStyleListConstructorTable, this, propertyName, slot);
}

bool JSTextTrackStyleListConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
	const char* szDebug = propertyName.ascii();
    return getStaticValueDescriptor<JSTextTrackStyleListConstructor, DOMObject>(exec, &JSTextTrackStyleListConstructorTable, this, propertyName, descriptor);
}

/* Hash table for prototype */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSTextTrackStyleListPrototypeTableValues[2] =
{
    { "item",                DontDelete | Function, (intptr_t)static_cast<NativeFunction>(JSTextTrackStyleListPrototypeFunctionItem), (intptr_t)1 THUNK_GENERATOR(0) },
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSTextTrackStyleListPrototypeTable = { 2, 1, JSTextTrackStyleListPrototypeTableValues, 0 };
const ClassInfo JSTextTrackStyleListPrototype::s_info = { "TextTrackStyleListPrototype", 0, &JSTextTrackStyleListPrototypeTable, 0 };

JSObject* JSTextTrackStyleListPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSTextTrackStyleList>(exec, globalObject);
}

bool JSTextTrackStyleListPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
	const char* szDebug = propertyName.ascii();
    return getStaticFunctionSlot<JSObject>(exec, &JSTextTrackStyleListPrototypeTable, this, propertyName, slot);
}

bool JSTextTrackStyleListPrototype::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticFunctionDescriptor<JSObject>(exec, &JSTextTrackStyleListPrototypeTable, this, propertyName, descriptor);
}

const ClassInfo JSTextTrackStyleList::s_info = { "TextTrackStyleList", 0, &JSTextTrackStyleListTable, 0 };

JSTextTrackStyleList::JSTextTrackStyleList(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<TextTrackStyleList> impl)
    : DOMObjectWithGlobalPointer(structure, globalObject)
    , m_impl(impl)
{
}

JSTextTrackStyleList::~JSTextTrackStyleList()
{
    forgetDOMObject(this, impl());
}

JSObject* JSTextTrackStyleList::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSTextTrackStyleListPrototype(globalObject, JSTextTrackStyleListPrototype::createStructure(globalObject->objectPrototype()));
}

bool JSTextTrackStyleList::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
	const char* szDebug = propertyName.ascii();

    const HashEntry* entry = JSTextTrackStyleListTable.entry(exec, propertyName);
    if (entry) {
        slot.setCustom(this, entry->propertyGetter());
        return true;
    }

    bool ok;
    unsigned index = propertyName.toUInt32(&ok, false);
    if (ok && index < static_cast<TextTrackStyleList*>(impl())->length()) {
        slot.setCustomIndex(this, index, indexGetter);
        return true;
    }

    return getStaticValueSlot<JSTextTrackStyleList, Base>(exec, &JSTextTrackStyleListTable, this, propertyName, slot);
}

bool JSTextTrackStyleList::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    bool ok;
    unsigned index = propertyName.toUInt32(&ok, false);
    if (ok && index < static_cast<TextTrackStyleList*>(impl())->length()) {
        PropertySlot slot;
        slot.setCustomIndex(this, index, indexGetter);
        descriptor.setDescriptor(slot.getValue(exec, propertyName), DontDelete | ReadOnly);
        return true;
    }

    return getStaticValueDescriptor<JSTextTrackStyleList, Base>(exec, &JSTextTrackStyleListTable, this, propertyName, descriptor);
}

bool JSTextTrackStyleList::getOwnPropertySlot(ExecState* exec, unsigned propertyName, PropertySlot& slot)
{
    if (propertyName < static_cast<TextTrackStyleList*>(impl())->length()) {
        slot.setCustomIndex(this, propertyName, indexGetter);
        return true;
    }
    return getOwnPropertySlot(exec, Identifier::from(exec, propertyName), slot);
}

// Attributes
JSValue jsTextTrackStyleListLength(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrackStyleList* castedThis = static_cast<JSTextTrackStyleList*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TextTrackStyleList* imp = static_cast<TextTrackStyleList*>(castedThis->impl());
    JSValue result = jsNumber(exec, imp->length());
    return result;
}

JSValue jsTextTrackStyleListConstructor(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrackStyleList* domObject = static_cast<JSTextTrackStyleList*>(asObject(slotBase));
    return JSTextTrackStyleList::getConstructor(exec, domObject->globalObject());
}
void JSTextTrackStyleList::getOwnPropertyNames(ExecState* exec, PropertyNameArray& propertyNames, EnumerationMode mode)
{
    for (unsigned i = 0; i < static_cast<TextTrackStyleList*>(impl())->length(); ++i)
        propertyNames.add(Identifier::from(exec, i));
     Base::getOwnPropertyNames(exec, propertyNames, mode);
}

JSValue JSTextTrackStyleList::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTextTrackStyleListConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}

EncodedJSValue JSC_HOST_CALL JSTextTrackStyleListPrototypeFunctionItem(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(&JSTextTrackStyleList::s_info))
        return throwVMTypeError(exec);
    JSTextTrackStyleList* castedThis = static_cast<JSTextTrackStyleList*>(asObject(thisValue));
    TextTrackStyleList* imp = static_cast<TextTrackStyleList*>(castedThis->impl());
    int index = exec->argument(0).toInt32(exec);
    if (index < 0) {
        setDOMException(exec, INDEX_SIZE_ERR);
        return JSValue::encode(jsUndefined());
    }

    JSC::JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(imp->item(index)));
    return JSValue::encode(result);
}

JSValue JSTextTrackStyleList::indexGetter(ExecState* exec, JSValue slotBase, unsigned index)
{
    JSTextTrackStyleList* thisObj = static_cast<JSTextTrackStyleList*>(asObject(slotBase));
    return toJS(exec, thisObj->globalObject(), static_cast<TextTrackStyleList*>(thisObj->impl())->item(index));
}
JSC::JSValue toJS(JSC::ExecState* exec, JSDOMGlobalObject* globalObject, TextTrackStyleList* object)
{
    return getDOMObjectWrapper<JSTextTrackStyleList>(exec, globalObject, object);
}
TextTrackStyleList* toTextTrackStyleList(JSC::JSValue value)
{
    return value.inherits(&JSTextTrackStyleList::s_info) ? static_cast<JSTextTrackStyleList*>(asObject(value))->impl() : 0;
}

} // WebCore

#endif // ENABLE(VIDEO_TRACK)

/* FYWEBKITMOD END */
