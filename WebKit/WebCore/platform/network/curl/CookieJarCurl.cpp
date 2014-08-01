/* 
 * ...
 * Copyright (C) 2014 FactorY Media Production GmbH
 * 
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "config.h"
#include "CookieJar.h"

#include "Cookie.h"
#include "Document.h"
#include "KURL.h"
#include "PlatformString.h"
#include "StringHash.h"
#include "ResourceHandleManager.h" // FYWEBKITMOD
#include "NotImplemented.h"        // FYWEBKITMOD

#include <wtf/HashMap.h>

namespace WebCore {

void setCookies(Document* /*document*/, const KURL& url, const String& value)
{
    ResourceHandleManager::sharedInstance()->setCookies(url, value); // FYWEBKITMOD using ResourceHandleManager instead of static HashMap<String,String>
}

String cookies(const Document* /*document*/, const KURL& url)
{
    return ResourceHandleManager::sharedInstance()->cookies(url); // FYWEBKITMOD using ResourceHandleManager instead of static HashMap<String,String>
}

String cookieRequestHeaderFieldValue(const Document* /*document*/, const KURL& url)
{
    // FIXME: include HttpOnly cookie.
    return ResourceHandleManager::sharedInstance()->cookies(url); // FYWEBKITMOD using ResourceHandleManager instead of static HashMap<String,String>
}

bool cookiesEnabled(const Document* /*document*/)
{
    return true;
}

bool getRawCookies(const Document*, const KURL&, Vector<Cookie>& rawCookies)
{
    // FIXME: Not yet implemented
    notImplemented(); // FYWEBKITMOD
    rawCookies.clear();
    return false; // return true when implemented
}

void deleteCookie(const Document*, const KURL&, const String&)
{
    // FIXME: Not yet implemented
    notImplemented(); // FYWEBKITMOD
}

}
