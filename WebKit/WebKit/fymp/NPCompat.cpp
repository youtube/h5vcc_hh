#include "config.h"
#include "npruntime.h"
#include "npruntime_impl.h"

bool NPN_IdentifierIsString(NPIdentifier identifier)
{
    return _NPN_IdentifierIsString(identifier);
}

NPIdentifier NPN_GetStringIdentifier(const NPUTF8 *name)
{
    return _NPN_GetStringIdentifier(name);
}

NPUTF8 *NPN_UTF8FromIdentifier(NPIdentifier identifier)
{
    return _NPN_UTF8FromIdentifier(identifier);
}

NPIdentifier NPN_GetIntIdentifier(int32_t intid)
{
    return _NPN_GetIntIdentifier(intid);
}

int32_t NPN_IntFromIdentifier(NPIdentifier identifier)
{
    return _NPN_IntFromIdentifier(identifier);
}

NPObject *NPN_CreateObject(NPP npp, NPClass *aClass)
{
    return _NPN_CreateObject(npp, aClass);
}

NPObject *NPN_RetainObject(NPObject *obj)
{
    return _NPN_RetainObject(obj);
}
void NPN_ReleaseObject(NPObject *obj)
{
    _NPN_ReleaseObject(obj);
}

void NPN_ReleaseVariantValue(NPVariant *variant)
{
    _NPN_ReleaseVariantValue(variant);
}

bool NPN_InvokeDefault(NPP npp, NPObject *o, const NPVariant* args, uint32_t argCount, NPVariant* result)
{
    return _NPN_InvokeDefault(npp, o, args, argCount, result);
}

bool NPN_GetProperty(NPP npp, NPObject *o, NPIdentifier propertyName, NPVariant *variant)
{
    return _NPN_GetProperty(npp, o, propertyName, variant);
}

bool NPN_Enumerate(NPP npp, NPObject *npobj, NPIdentifier **identifier, uint32_t *count)
{
    return _NPN_Enumerate(npp, npobj, identifier, count);
}
