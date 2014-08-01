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

// FYMP: this file was not auto-generated. Added to support JSTextTrack::regions() (while integrating parts of r152754)

#include "config.h"

#if ENABLE(VIDEO_TRACK) && ENABLE(WEBVTT_REGIONS)

#include "JSTextTrackRegionList.h"

#include "AtomicString.h"
#include "ExceptionCode.h"
#include "Event.h"
#include "JSEvent.h"
#include "JSNode.h"
#include "Node.h"
#include "TextTrackRegionList.h"
#include "JSTextTrackRegion.h"
#include <runtime/Error.h>
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSTextTrackRegionList);

/* Hash table */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSTextTrackRegionListTableValues[3] =
{
    { "length",        DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackRegionListLength),      (intptr_t)0                               THUNK_GENERATOR(0) },
    { "constructor",   DontEnum | ReadOnly,   (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTextTrackRegionListConstructor), (intptr_t)0                               THUNK_GENERATOR(0) },
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSTextTrackRegionListTable = { 5, 3, JSTextTrackRegionListTableValues, 0 };
/* Hash table for constructor */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSTextTrackRegionListConstructorTableValues[1] =
{
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSTextTrackRegionListConstructorTable = { 1, 0, JSTextTrackRegionListConstructorTableValues, 0 };
class JSTextTrackRegionListConstructor : public DOMConstructorObject {
public:
    JSTextTrackRegionListConstructor(JSC::ExecState*, JSDOMGlobalObject*);

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

const ClassInfo JSTextTrackRegionListConstructor::s_info = { "TextTrackRegionListConstructor", 0, &JSTextTrackRegionListConstructorTable, 0 };

JSTextTrackRegionListConstructor::JSTextTrackRegionListConstructor(ExecState* exec, JSDOMGlobalObject* globalObject)
    : DOMConstructorObject(JSTextTrackRegionListConstructor::createStructure(globalObject->objectPrototype()), globalObject)
{
    putDirect(exec->propertyNames().prototype, JSTextTrackRegionListPrototype::self(exec, globalObject), DontDelete | ReadOnly);
}

bool JSTextTrackRegionListConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
	const char* szDebug = propertyName.ascii();
    return getStaticValueSlot<JSTextTrackRegionListConstructor, DOMObject>(exec, &JSTextTrackRegionListConstructorTable, this, propertyName, slot);
}

bool JSTextTrackRegionListConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
	const char* szDebug = propertyName.ascii();
    return getStaticValueDescriptor<JSTextTrackRegionListConstructor, DOMObject>(exec, &JSTextTrackRegionListConstructorTable, this, propertyName, descriptor);
}

/* Hash table for prototype */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSTextTrackRegionListPrototypeTableValues[2] =
{
    { "item",                DontDelete | Function, (intptr_t)static_cast<NativeFunction>(JSTextTrackRegionListPrototypeFunctionItem), (intptr_t)1 THUNK_GENERATOR(0) },
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSTextTrackRegionListPrototypeTable = { 2, 1, JSTextTrackRegionListPrototypeTableValues, 0 };
const ClassInfo JSTextTrackRegionListPrototype::s_info = { "TextTrackRegionListPrototype", 0, &JSTextTrackRegionListPrototypeTable, 0 };

JSObject* JSTextTrackRegionListPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSTextTrackRegionList>(exec, globalObject);
}

bool JSTextTrackRegionListPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
	const char* szDebug = propertyName.ascii();
    return getStaticFunctionSlot<JSObject>(exec, &JSTextTrackRegionListPrototypeTable, this, propertyName, slot);
}

bool JSTextTrackRegionListPrototype::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticFunctionDescriptor<JSObject>(exec, &JSTextTrackRegionListPrototypeTable, this, propertyName, descriptor);
}

const ClassInfo JSTextTrackRegionList::s_info = { "TextTrackRegionList", 0, &JSTextTrackRegionListTable, 0 };

JSTextTrackRegionList::JSTextTrackRegionList(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<TextTrackRegionList> impl)
    : DOMObjectWithGlobalPointer(structure, globalObject)
    , m_impl(impl)
{
}

JSTextTrackRegionList::~JSTextTrackRegionList()
{
    forgetDOMObject(this, impl());
}

JSObject* JSTextTrackRegionList::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSTextTrackRegionListPrototype(globalObject, JSTextTrackRegionListPrototype::createStructure(globalObject->objectPrototype()));
}

bool JSTextTrackRegionList::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
	const char* szDebug = propertyName.ascii();

    const HashEntry* entry = JSTextTrackRegionListTable.entry(exec, propertyName);
    if (entry) {
        slot.setCustom(this, entry->propertyGetter());
        return true;
    }

    bool ok;
    unsigned index = propertyName.toUInt32(&ok, false);
    if (ok && index < static_cast<TextTrackRegionList*>(impl())->length()) {
        slot.setCustomIndex(this, index, indexGetter);
        return true;
    }

    return getStaticValueSlot<JSTextTrackRegionList, Base>(exec, &JSTextTrackRegionListTable, this, propertyName, slot);
}

bool JSTextTrackRegionList::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    bool ok;
    unsigned index = propertyName.toUInt32(&ok, false);
    if (ok && index < static_cast<TextTrackRegionList*>(impl())->length()) {
        PropertySlot slot;
        slot.setCustomIndex(this, index, indexGetter);
        descriptor.setDescriptor(slot.getValue(exec, propertyName), DontDelete | ReadOnly);
        return true;
    }

    return getStaticValueDescriptor<JSTextTrackRegionList, Base>(exec, &JSTextTrackRegionListTable, this, propertyName, descriptor);
}

bool JSTextTrackRegionList::getOwnPropertySlot(ExecState* exec, unsigned propertyName, PropertySlot& slot)
{
    if (propertyName < static_cast<TextTrackRegionList*>(impl())->length()) {
        slot.setCustomIndex(this, propertyName, indexGetter);
        return true;
    }
    return getOwnPropertySlot(exec, Identifier::from(exec, propertyName), slot);
}

// Attributes
JSValue jsTextTrackRegionListLength(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrackRegionList* castedThis = static_cast<JSTextTrackRegionList*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TextTrackRegionList* imp = static_cast<TextTrackRegionList*>(castedThis->impl());
    JSValue result = jsNumber(exec, imp->length());
    return result;
}

JSValue jsTextTrackRegionListConstructor(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTextTrackRegionList* domObject = static_cast<JSTextTrackRegionList*>(asObject(slotBase));
    return JSTextTrackRegionList::getConstructor(exec, domObject->globalObject());
}
void JSTextTrackRegionList::getOwnPropertyNames(ExecState* exec, PropertyNameArray& propertyNames, EnumerationMode mode)
{
    for (unsigned i = 0; i < static_cast<TextTrackRegionList*>(impl())->length(); ++i)
        propertyNames.add(Identifier::from(exec, i));
     Base::getOwnPropertyNames(exec, propertyNames, mode);
}

JSValue JSTextTrackRegionList::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTextTrackRegionListConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}

EncodedJSValue JSC_HOST_CALL JSTextTrackRegionListPrototypeFunctionItem(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(&JSTextTrackRegionList::s_info))
        return throwVMTypeError(exec);
    JSTextTrackRegionList* castedThis = static_cast<JSTextTrackRegionList*>(asObject(thisValue));
    TextTrackRegionList* imp = static_cast<TextTrackRegionList*>(castedThis->impl());
    int index = exec->argument(0).toInt32(exec);
    if (index < 0) {
        setDOMException(exec, INDEX_SIZE_ERR);
        return JSValue::encode(jsUndefined());
    }

    JSC::JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(imp->item(index)));
    return JSValue::encode(result);
}

JSValue JSTextTrackRegionList::indexGetter(ExecState* exec, JSValue slotBase, unsigned index)
{
    JSTextTrackRegionList* thisObj = static_cast<JSTextTrackRegionList*>(asObject(slotBase));
    return toJS(exec, thisObj->globalObject(), static_cast<TextTrackRegionList*>(thisObj->impl())->item(index));
}
JSC::JSValue toJS(JSC::ExecState* exec, JSDOMGlobalObject* globalObject, TextTrackRegionList* object)
{
    return getDOMObjectWrapper<JSTextTrackRegionList>(exec, globalObject, object);
}
TextTrackRegionList* toTextTrackRegionList(JSC::JSValue value)
{
    return value.inherits(&JSTextTrackRegionList::s_info) ? static_cast<JSTextTrackRegionList*>(asObject(value))->impl() : 0;
}

} // WebCore

#endif // ENABLE(VIDEO_TRACK)

