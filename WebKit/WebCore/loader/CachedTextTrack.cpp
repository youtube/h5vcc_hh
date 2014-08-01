/*
 * Copyright (C) 2011 Apple Inc. All rights reserved.
 * Copyright (C) 2014 FactorY Media Production GmbH
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

// FYMP - file integrated from r152754

#include "config.h"

#if ENABLE(VIDEO_TRACK)

#include "CachedTextTrack.h"

#include "CachedResourceClient.h"
#include "CachedResourceClientWalker.h"
/* FYWEBKITMOD BEGIN replacing Loader class */
// #include "CachedResourceLoader.h"
#include "DocLoader.h"
/* FYWEBKITMOD END */
// #include "ResourceBuffer.h" // FYWEBKITMOD not used
#include "SharedBuffer.h"
#include "TextResourceDecoder.h"
#include <wtf/Vector.h>

namespace WebCore {

/* FYWEBKITMOD BEGIN */
/*
CachedTextTrack::CachedTextTrack(const ResourceRequest& resourceRequest)
    : CachedResource(resourceRequest, TextTrackResource)
{
}*/
CachedTextTrack::CachedTextTrack(const String& url)
: CachedResource(url, TextTrackResource)
{
}
/* FYWEBKITMOD END */
 
CachedTextTrack::~CachedTextTrack()
{
}

/* FYWEBKITMOD BEGIN */ 
/*
void CachedTextTrack::addDataBuffer(ResourceBuffer* data)
{
    ASSERT(m_options.dataBufferingPolicy == BufferData);
    m_data = data;
    setEncodedSize(m_data.get() ? m_data->size() : 0);

    CachedResourceClientWalker<CachedResourceClient> walker(m_clients);
    while (CachedResourceClient *client = walker.next())
        client->deprecatedDidReceiveCachedResource(this);
}
*/  
void CachedTextTrack::data(PassRefPtr<SharedBuffer> data, bool allDataReceived)
{
    m_data = data; // already owned data seems to be always included in 'data'
    setEncodedSize(m_data.get() ? m_data->size() : 0);

    CachedResourceClientWalker walker(m_clients);
    while (CachedResourceClient *client = walker.next())
        client->didReceiveSomeData(this);

	CachedResource::data(data, allDataReceived); // will call 'notifyFinished' on the clients if 'allDataReceived'.

	if (allDataReceived)
		{
		setLoading(false);
		}
}
/* FYWEBKITMOD END */

/* FYWEBKITMOD BEGIN */
// implemented just as CachedScript does.
void CachedTextTrack::error()
{
    setLoading(false);
    setErrorOccurred(true);
    checkNotify();
}

// implemented just as CachedScript does.
void CachedTextTrack::checkNotify()
{
    if (isLoading())
        return;

    CachedResourceClientWalker w(m_clients);
    while (CachedResourceClient* c = w.next())
        c->notifyFinished(this);
}
/* FYWEBKITMOD END */

/* FYWEBKITMOD BEGIN
void CachedTextTrack::addDataBuffer(ResourceBuffer* data)
{
    ASSERT(m_options.dataBufferingPolicy == BufferData);
    m_data = data;
    setEncodedSize(m_data.get() ? m_data->size() : 0);

    CachedResourceClientWalker<CachedResourceClient> walker(m_clients);
    while (CachedResourceClient *client = walker.next())
        client->deprecatedDidReceiveCachedResource(this);
}
FYWEBKITMOD END */

/* FYWEBKITMOD BEGIN
void CachedTextTrack::finishLoading(SharedBuffer* data)
{
    addDataBuffer(data);
    CachedResource::finishLoading(data);
} 
FYWEBKITMOD END */ 

}

#endif
