/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

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

#include "config.h"
#include "JSWebKitPoint.h"

#include "WebKitPoint.h"
#include <runtime/JSNumberCell.h>
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSWebKitPoint);

/* Hash table */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSWebKitPointTableValues[4] =
{
    { "x", DontDelete, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsWebKitPointX), (intptr_t)setJSWebKitPointX THUNK_GENERATOR(0) },
    { "y", DontDelete, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsWebKitPointY), (intptr_t)setJSWebKitPointY THUNK_GENERATOR(0) },
    { "constructor", DontEnum | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsWebKitPointConstructor), (intptr_t)0 THUNK_GENERATOR(0) },
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSWebKitPointTable = { 9, 7, JSWebKitPointTableValues, 0 };
/* Hash table for constructor */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSWebKitPointConstructorTableValues[1] =
{
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSWebKitPointConstructorTable = { 1, 0, JSWebKitPointConstructorTableValues, 0 };
const ClassInfo JSWebKitPointConstructor::s_info = { "WebKitPointConstructor", 0, &JSWebKitPointConstructorTable, 0 };

JSWebKitPointConstructor::JSWebKitPointConstructor(ExecState* exec, JSDOMGlobalObject* globalObject)
    : DOMConstructorObject(JSWebKitPointConstructor::createStructure(globalObject->objectPrototype()), globalObject)
{
    putDirect(exec->propertyNames().prototype, JSWebKitPointPrototype::self(exec, globalObject), DontDelete | ReadOnly);
    putDirect(exec->propertyNames().length, jsNumber(exec, 2), ReadOnly | DontDelete | DontEnum);
}

bool JSWebKitPointConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSWebKitPointConstructor, DOMObject>(exec, &JSWebKitPointConstructorTable, this, propertyName, slot);
}

bool JSWebKitPointConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSWebKitPointConstructor, DOMObject>(exec, &JSWebKitPointConstructorTable, this, propertyName, descriptor);
}

ConstructType JSWebKitPointConstructor::getConstructData(ConstructData& constructData)
{
    constructData.native.function = constructJSWebKitPoint;
    return ConstructTypeHost;
}

/* Hash table for prototype */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSWebKitPointPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSWebKitPointPrototypeTable = { 1, 0, JSWebKitPointPrototypeTableValues, 0 };
const ClassInfo JSWebKitPointPrototype::s_info = { "WebKitPointPrototype", 0, &JSWebKitPointPrototypeTable, 0 };

JSObject* JSWebKitPointPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSWebKitPoint>(exec, globalObject);
}

const ClassInfo JSWebKitPoint::s_info = { "WebKitPoint", 0, &JSWebKitPointTable, 0 };

JSWebKitPoint::JSWebKitPoint(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<WebKitPoint> impl)
    : DOMObjectWithGlobalPointer(structure, globalObject)
    , m_impl(impl)
{
}

JSWebKitPoint::~JSWebKitPoint()
{
    forgetDOMObject(this, impl());
}

JSObject* JSWebKitPoint::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSWebKitPointPrototype(globalObject, JSWebKitPointPrototype::createStructure(globalObject->objectPrototype()));
}

bool JSWebKitPoint::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSWebKitPoint, Base>(exec, &JSWebKitPointTable, this, propertyName, slot);
}

bool JSWebKitPoint::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSWebKitPoint, Base>(exec, &JSWebKitPointTable, this, propertyName, descriptor);
}

JSValue jsWebKitPointX(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSWebKitPoint* castedThis = static_cast<JSWebKitPoint*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    WebKitPoint* imp = static_cast<WebKitPoint*>(castedThis->impl());
    JSValue result = jsNumber(exec, imp->x());
    return result;
}

JSValue jsWebKitPointY(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSWebKitPoint* castedThis = static_cast<JSWebKitPoint*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    WebKitPoint* imp = static_cast<WebKitPoint*>(castedThis->impl());
    JSValue result = jsNumber(exec, imp->y());
    return result;
}

JSValue jsWebKitPointConstructor(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSWebKitPoint* domObject = static_cast<JSWebKitPoint*>(asObject(slotBase));
    return JSWebKitPoint::getConstructor(exec, domObject->globalObject());
}
void JSWebKitPoint::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    lookupPut<JSWebKitPoint, Base>(exec, propertyName, value, &JSWebKitPointTable, this, slot);
}

void setJSWebKitPointX(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSWebKitPoint* castedThis = static_cast<JSWebKitPoint*>(thisObject);
    WebKitPoint* imp = static_cast<WebKitPoint*>(castedThis->impl());
    imp->setX(value.toFloat(exec));
}

void setJSWebKitPointY(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSWebKitPoint* castedThis = static_cast<JSWebKitPoint*>(thisObject);
    WebKitPoint* imp = static_cast<WebKitPoint*>(castedThis->impl());
    imp->setY(value.toFloat(exec));
}

JSValue JSWebKitPoint::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSWebKitPointConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}

JSC::JSValue toJS(JSC::ExecState* exec, JSDOMGlobalObject* globalObject, WebKitPoint* object)
{
    return getDOMObjectWrapper<JSWebKitPoint>(exec, globalObject, object);
}
WebKitPoint* toWebKitPoint(JSC::JSValue value)
{
    return value.inherits(&JSWebKitPoint::s_info) ? static_cast<JSWebKitPoint*>(asObject(value))->impl() : 0;
}

}
