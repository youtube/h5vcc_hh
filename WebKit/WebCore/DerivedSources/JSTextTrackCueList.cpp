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

#include "JSTextTrackCueList.h"
#include "AtomicString.h"
#include "ExceptionCode.h"
#include "JSNode.h"
#include "Node.h"
#include "TextTrackCueList.h"
#include "JSTextTrack.h"
#include "JSTextTrackCue.h"
#include <runtime/Error.h>
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSTextTrackCueList);

/* Hash table */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSTextTrackCueListTableValues[3] =
{
    { "length",    DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackCueListLength),      (intptr_t)0 THUNK_GENERATOR(0) },
    { "constructor", DontEnum | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackCueListConstructor), (intptr_t)0 THUNK_GENERATOR(0) },
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSTextTrackCueListTable = { 5, 3, JSTextTrackCueListTableValues, 0 };
/* Hash table for constructor */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSTextTrackCueListConstructorTableValues[1] =
{
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSTextTrackCueListConstructorTable = { 1, 0, JSTextTrackCueListConstructorTableValues, 0 };
class JSTextTrackCueListConstructor : public DOMConstructorObject {
public:
    JSTextTrackCueListConstructor(JSC::ExecState*, JSDOMGlobalObject*);

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

const ClassInfo JSTextTrackCueListConstructor::s_info = { "TextTrackCueListConstructor", 0, &JSTextTrackCueListConstructorTable, 0 };

JSTextTrackCueListConstructor::JSTextTrackCueListConstructor(ExecState* exec, JSDOMGlobalObject* globalObject)
    : DOMConstructorObject(JSTextTrackCueListConstructor::createStructure(globalObject->objectPrototype()), globalObject)
{
    putDirect(exec->propertyNames().prototype, JSTextTrackCueListPrototype::self(exec, globalObject), DontDelete | ReadOnly);
}

bool JSTextTrackCueListConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
	const char* szDebug = propertyName.ascii();
    return getStaticValueSlot<JSTextTrackCueListConstructor, DOMObject>(exec, &JSTextTrackCueListConstructorTable, this, propertyName, slot);
}

bool JSTextTrackCueListConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
	const char* szDebug = propertyName.ascii();
    return getStaticValueDescriptor<JSTextTrackCueListConstructor, DOMObject>(exec, &JSTextTrackCueListConstructorTable, this, propertyName, descriptor);
}

/* Hash table for prototype */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSTextTrackCueListPrototypeTableValues[3] =
{
    { "item",       DontDelete | Function, (intptr_t)static_cast<NativeFunction>(jsTextTrackCueListPrototypeFunctionItem),       (intptr_t)1 THUNK_GENERATOR(0) },
	{ "getCueById", DontDelete | Function, (intptr_t)static_cast<NativeFunction>(jsTextTrackCueListPrototypeFunctionGetCueById), (intptr_t)1 THUNK_GENERATOR(0) },
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSTextTrackCueListPrototypeTable = { 4, 3, JSTextTrackCueListPrototypeTableValues, 0 };
const ClassInfo JSTextTrackCueListPrototype::s_info = { "TextTrackCueListPrototype", 0, &JSTextTrackCueListPrototypeTable, 0 };

JSObject* JSTextTrackCueListPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSTextTrackCueList>(exec, globalObject);
}

bool JSTextTrackCueListPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
	const char* szDebug = propertyName.ascii();
    return getStaticFunctionSlot<JSObject>(exec, &JSTextTrackCueListPrototypeTable, this, propertyName, slot);
}

bool JSTextTrackCueListPrototype::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticFunctionDescriptor<JSObject>(exec, &JSTextTrackCueListPrototypeTable, this, propertyName, descriptor);
}

const ClassInfo JSTextTrackCueList::s_info = { "TextTrackCueList", 0, &JSTextTrackCueListTable, 0 };

JSTextTrackCueList::JSTextTrackCueList(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<TextTrackCueList> impl)
    : DOMObjectWithGlobalPointer(structure, globalObject)
    , m_impl(impl)
{
}

JSTextTrackCueList::~JSTextTrackCueList()
{
    forgetDOMObject(this, impl());
}

JSObject* JSTextTrackCueList::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSTextTrackCueListPrototype(globalObject, JSTextTrackCueListPrototype::createStructure(globalObject->objectPrototype()));
}

bool JSTextTrackCueList::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
	const char* szDebug = propertyName.ascii();

    const HashEntry* entry = JSTextTrackCueListTable.entry(exec, propertyName);
    if (entry) {
        slot.setCustom(this, entry->propertyGetter());
        return true;
    }

    bool ok;
    unsigned index = propertyName.toUInt32(&ok, false);
    if (ok && index < static_cast<TextTrackCueList*>(impl())->length()) {
        slot.setCustomIndex(this, index, indexGetter);
        return true;
    }

    return getStaticValueSlot<JSTextTrackCueList, Base>(exec, &JSTextTrackCueListTable, this, propertyName, slot);
}

bool JSTextTrackCueList::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    bool ok;
    unsigned index = propertyName.toUInt32(&ok, false);
    if (ok && index < static_cast<TextTrackCueList*>(impl())->length()) {
        PropertySlot slot;
        slot.setCustomIndex(this, index, indexGetter);
        descriptor.setDescriptor(slot.getValue(exec, propertyName), DontDelete | ReadOnly);
        return true;
    }

    return getStaticValueDescriptor<JSTextTrackCueList, Base>(exec, &JSTextTrackCueListTable, this, propertyName, descriptor);
}

bool JSTextTrackCueList::getOwnPropertySlot(ExecState* exec, unsigned propertyName, PropertySlot& slot)
{
    if (propertyName < static_cast<TextTrackCueList*>(impl())->length()) {
        slot.setCustomIndex(this, propertyName, indexGetter);
        return true;
    }
    return getOwnPropertySlot(exec, Identifier::from(exec, propertyName), slot);
}

JSValue jsTextTrackCueListLength(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrackCueList* castedThis = static_cast<JSTextTrackCueList*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TextTrackCueList* imp = static_cast<TextTrackCueList*>(castedThis->impl());
    JSValue result = jsNumber(exec, imp->length());
    return result;
}

JSValue jsTextTrackCueListConstructor(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrackCueList* domObject = static_cast<JSTextTrackCueList*>(asObject(slotBase));
    return JSTextTrackCueList::getConstructor(exec, domObject->globalObject());
}
void JSTextTrackCueList::getOwnPropertyNames(ExecState* exec, PropertyNameArray& propertyNames, EnumerationMode mode)
{
    for (unsigned i = 0; i < static_cast<TextTrackCueList*>(impl())->length(); ++i)
        propertyNames.add(Identifier::from(exec, i));
     Base::getOwnPropertyNames(exec, propertyNames, mode);
}

JSValue JSTextTrackCueList::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTextTrackCueListConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}

EncodedJSValue JSC_HOST_CALL jsTextTrackCueListPrototypeFunctionItem(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(&JSTextTrackCueList::s_info))
        return throwVMTypeError(exec);
    JSTextTrackCueList* castedThis = static_cast<JSTextTrackCueList*>(asObject(thisValue));
    TextTrackCueList* imp = static_cast<TextTrackCueList*>(castedThis->impl());
    int index = exec->argument(0).toInt32(exec);
    if (index < 0) {
        setDOMException(exec, INDEX_SIZE_ERR);
        return JSValue::encode(jsUndefined());
    }

	JSDOMGlobalObject* pGlob = castedThis->globalObject();
	TextTrackCue*      pCue  = WTF::getPtr(imp->item(index));

    JSC::JSValue result = toJS(exec, pGlob, pCue);
    return JSValue::encode(result);
}

EncodedJSValue JSC_HOST_CALL jsTextTrackCueListPrototypeFunctionGetCueById(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(&JSTextTrackCueList::s_info))
        return throwVMTypeError(exec);
    JSTextTrackCueList* castedThis = static_cast<JSTextTrackCueList*>(asObject(thisValue));
    TextTrackCueList* imp = static_cast<TextTrackCueList*>(castedThis->impl());
    String id = valueToStringWithNullCheck(exec, exec->argument(0));

	JSDOMGlobalObject* pGlob = castedThis->globalObject();
	TextTrackCue*      pCue  = WTF::getPtr(imp->getCueById(id));

    JSC::JSValue result = toJS(exec, pGlob, pCue);
    return JSValue::encode(result);
}

JSValue JSTextTrackCueList::indexGetter(ExecState* exec, JSValue slotBase, unsigned index)
{
    JSTextTrackCueList* thisObj = static_cast<JSTextTrackCueList*>(asObject(slotBase));
    return toJS(exec, thisObj->globalObject(), static_cast<TextTrackCueList*>(thisObj->impl())->item(index));
}
JSC::JSValue toJS(JSC::ExecState* exec, JSDOMGlobalObject* globalObject, TextTrackCueList* object)
{
    return getDOMObjectWrapper<JSTextTrackCueList>(exec, globalObject, object);
}
TextTrackCueList* toTextTrackCueList(JSC::JSValue value)
{
    return value.inherits(&JSTextTrackCueList::s_info) ? static_cast<JSTextTrackCueList*>(asObject(value))->impl() : 0;
}

} // WebCore

#endif // ENABLE(VIDEO_TRACK)
