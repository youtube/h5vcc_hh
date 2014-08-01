/*
 * Copyright (C) 2011 Google Inc.  All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

// FYMP - file integrated from r152754

#include "config.h"

#if ENABLE(VIDEO_TRACK)

#include "TextTrackLoader.h"

/* FYWEBKITMOD BEGIN replaced */
//#include "CachedResourceLoader.h"
#include <DocLoader.h>
/* FYWEBKITMOD END */
//#include "CachedResourceRequest.h" // FYWEBKITMOD not used.
#include "CachedTextTrack.h"
#include "CrossOriginAccessControl.h"
#include "Document.h"
#include "Logging.h"
/* FYWEBKITMOD BEGIN replaced */
// #include "ResourceBuffer.h"
#include "SharedBuffer.h"
/* FYWEBKITMOD END */
#include "ScriptCallStack.h"
#include "SecurityOrigin.h"
#include "TextTrackCue.h"
#include "WebVTTParser.h"

namespace WebCore {
    
TextTrackLoader::TextTrackLoader(TextTrackLoaderClient* client, ScriptExecutionContext* context)
    : m_client(client)
    , m_scriptExecutionContext(context)
    , m_cueLoadTimer(this, &TextTrackLoader::cueLoadTimerFired)
    , m_state(Idle)
    , m_parseOffset(0)
    , m_newCuesAvailable(false)
{
}

TextTrackLoader::~TextTrackLoader()
{
    if (m_cachedCueData)
        m_cachedCueData->removeClient(this);
}

void TextTrackLoader::cueLoadTimerFired(Timer<TextTrackLoader>* timer)
{
    ASSERT_UNUSED(timer, timer == &m_cueLoadTimer);
    
    if (m_newCuesAvailable) {
        m_newCuesAvailable = false;
        m_client->newCuesAvailable(this); 
    }
    
    if (m_state >= Finished)
        m_client->cueLoadingCompleted(this, m_state == Failed);
}

void TextTrackLoader::cancelLoad()
{
    if (m_cachedCueData) {
        m_cachedCueData->removeClient(this);
        m_cachedCueData = 0;
    }
}

void TextTrackLoader::processNewCueData(CachedResource* resource)
{
    ASSERT(m_cachedCueData == resource);
    
    if (m_state == Failed || !resource->data()) // FYWEBKITMOD using old webkit resource interface.
        return;
    
    SharedBuffer* buffer = resource->data(); // FYWEBKITMOD using old webkit resource interface.
    if (m_parseOffset == buffer->size())
        return;

    if (!m_cueParser)
        m_cueParser = WebVTTParser::create(this, m_scriptExecutionContext);

    const char* data;
    unsigned length;

    while ((length = buffer->getSomeData(data, m_parseOffset))) {
        m_cueParser->parseBytes(data, length);
        m_parseOffset += length;
    }
}

/* FYWEBKITMOD BEGIN replaced */
/*
// FIXME: This is a very unusual pattern, no other CachedResourceClient does this. Refactor to use notifyFinished() instead.
void TextTrackLoader::deprecatedDidReceiveCachedResource(CachedResource* resource)
{
    ASSERT(m_cachedCueData == resource);
    
    if (!resource->resourceBuffer())
        return;
    
    processNewCueData(resource);
}
*/
void TextTrackLoader::didReceiveSomeData(CachedResource* resource)
{
    if (!resource->data())
        return;
    
    processNewCueData(resource);
}
/* FYWEBKITMOD END */

void TextTrackLoader::corsPolicyPreventedLoad()
{
/* FYWEBKITMOD begin - myTODO: would be nice to have some logging here... */
//    DEFINE_STATIC_LOCAL(String, consoleMessage, (ASCIILiteral("Cross-origin text track load denied by Cross-Origin Resource Sharing policy.")));
//    Document* document = toDocument(m_scriptExecutionContext);
//    document->addConsoleMessage(SecurityMessageSource, ErrorMessageLevel, consoleMessage); // FYMP: not implemented
/* FYWEBKITMOD END */

    m_state = Failed;
}

void TextTrackLoader::notifyFinished(CachedResource* resource)
{
    ASSERT(m_cachedCueData == resource);

    Document* document = toDocument(m_scriptExecutionContext);
    if (!m_crossOriginMode.isNull()
        && !document->securityOrigin()->canRequest(resource->response().url())
        /* && !resource->passesAccessControlCheck(document->securityOrigin()) FYWEBKITMOD - access controll check should be done by 'CrossOriginAccessControl'. */) {

        corsPolicyPreventedLoad();
    }

    if (m_state != Failed) {
        processNewCueData(resource);
        if (m_state != Failed)
            m_state = resource->errorOccurred() ? Failed : Finished;
    }

    if (!m_cueLoadTimer.isActive())
        m_cueLoadTimer.startOneShot(0);
    
    cancelLoad();
}

bool TextTrackLoader::load(const KURL& url, const String& crossOriginMode)
{
    cancelLoad();

    if (!m_client->shouldLoadCues(this))
        return false;

    ASSERT(m_scriptExecutionContext->isDocument());
    Document* document = toDocument(m_scriptExecutionContext);
//    CachedResourceRequest cueRequest(ResourceRequest(document->completeURL(url))); // FYWEBKITMOD removed

    if (!crossOriginMode.isNull()) {
        m_crossOriginMode = crossOriginMode;
//        StoredCredentials allowCredentials = equalIgnoringCase(crossOriginMode, "use-credentials") ? AllowStoredCredentials : DoNotAllowStoredCredentials; // FYWEBKITMOD removed
//        updateRequestForAccessControl(cueRequest.mutableResourceRequest(), document->securityOrigin(), allowCredentials);                                  // FYWEBKITMOD removed
    } else {
        // Cross-origin resources that are not suitably CORS-enabled may not load.
        if (!document->securityOrigin()->canRequest(url)) {
            corsPolicyPreventedLoad();
            return false;
        }
    }

	DocLoader* docLoader = document->docLoader(); // FYWEBKITMOD using docLoader instead of cachedResourceLoader.
    m_cachedCueData = docLoader->requestTextTrack(/*cueRequest FYWEBKITMOD */document->completeURL(url));
    if (m_cachedCueData)
        m_cachedCueData->addClient(this);
    
    m_client->cueLoadingStarted(this);
    
    return true;
}

void TextTrackLoader::newCuesParsed()
{
    if (m_cueLoadTimer.isActive())
        return;

    m_newCuesAvailable = true;
    m_cueLoadTimer.startOneShot(0);
}

#if ENABLE(WEBVTT_REGIONS)
void TextTrackLoader::newRegionsParsed()
{
    m_client->newRegionsAvailable(this); 
}
#endif

/* FYWEBKITMOD BEGIN custom extension. */
#if ENABLE(WEBVTT_STYLES)
void TextTrackLoader::newStylesParsed()
{
    m_client->newStylesAvailable(this); 
}
#endif
/* FYWEBKITMOD END */

void TextTrackLoader::fileFailedToParse()
{
    LOG(Media, "TextTrackLoader::fileFailedToParse");

    m_state = Failed;

    if (!m_cueLoadTimer.isActive())
        m_cueLoadTimer.startOneShot(0);

    cancelLoad();
}

void TextTrackLoader::getNewCues(Vector<RefPtr<TextTrackCue> >& outputCues)
{
    ASSERT(m_cueParser);
    if (m_cueParser) {
        Vector<RefPtr<WebVTTCueData> > newCues;
        m_cueParser->getNewCues(newCues);
        for (size_t i = 0; i < newCues.size(); ++i) {
            RefPtr<WebVTTCueData> data = newCues[i];
            RefPtr<TextTrackCue> cue = TextTrackCue::create(m_scriptExecutionContext, data->startTime(), data->endTime(), data->content());
            cue->setId(data->id());
            cue->setCueSettings(data->settings());
            outputCues.append(cue);
        }
    }
}

#if ENABLE(WEBVTT_REGIONS)
void TextTrackLoader::getNewRegions(Vector<RefPtr<TextTrackRegion> >& outputRegions)
{
    ASSERT(m_cueParser);
    if (m_cueParser)
        m_cueParser->getNewRegions(outputRegions);
}
#endif

/* FYWEBKITMOD BEGIN custom extension. */
#if ENABLE(WEBVTT_STYLES)
void TextTrackLoader::getNewStyles(Vector<RefPtr<TextTrackStyle> >& outputStyles)
{
    ASSERT(m_cueParser);
    if (m_cueParser)
        m_cueParser->getNewStyles(outputStyles);
}
#endif
/* FYWEBKITMOD END */

}

#endif
