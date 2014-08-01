/*
 * Copyright (C) 2007, 2008, 2009, 2010 Apple Inc. All rights reserved.
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

#include "config.h"

// Enable here!
//#define DOES_THIS_FIX_CCPARSINGBUG_20131007


#if ENABLE(VIDEO)
#include "HTMLMediaElement.h"

#include "Attribute.h"
#include "CSSHelper.h"
#include "CSSPropertyNames.h"
#include "CSSValueKeywords.h"
#include "Chrome.h"
#include "ChromeClient.h"
#include "ClientRect.h"
#include "ClientRectList.h"
#include "ContentType.h"
#include "DocLoader.h"
#include "Event.h"
#include "EventNames.h"
#include "ExceptionCode.h"
#include "Frame.h"
#include "FrameLoader.h"
#include "FrameLoaderClient.h"
#include "FrameView.h"
#include "HTMLDocument.h"
#include "HTMLNames.h"
#include "HTMLSourceElement.h"
#include "HTMLVideoElement.h"
#include "MIMETypeRegistry.h"
#include "MediaDocument.h"
#include "MediaError.h"
#include "MediaList.h"
#include "MediaPlayer.h"
#include "MediaQueryEvaluator.h"
#include "Page.h"
#include "RenderVideo.h"
#include "RenderView.h"
#include "ScriptEventListener.h"
#include "Settings.h"
#include "TimeRanges.h"
#include <limits>
#include <wtf/CurrentTime.h>
#include <wtf/MathExtras.h>
// FYMP begin - integrating parts of r152754
#include <wtf/NonCopyingSort.h>
#include <dom/ScriptExecutionContext.h>
// FYMP end

#if USE(ACCELERATED_COMPOSITING)
#include "RenderView.h"
#include "RenderLayerCompositor.h"
#endif

#if ENABLE(PLUGIN_PROXY_FOR_VIDEO)
#include "RenderEmbeddedObject.h"
#include "Widget.h"
#endif

// FYMP begin - integrating parts of r152754
// #include "CaptionUserPreferences.h" // we dont support user preferences.
#include "HTMLTrackElement.h"
//#include "InbandTextTrack.h"         // up to now, we dont support in-band tracks
//#include "InbandTextTrackPrivate.h"  // up to now, we dont support in-band tracks
#include "TextTrackCueList.h"
#include "TextTrackList.h"
// FYMP end

using namespace std;

namespace WebCore {

// FYMP begin - integrating parts of r152754
static void setFlags(unsigned& value, unsigned flags)
{
    value |= flags;
}

static void clearFlags(unsigned& value, unsigned flags)
{
    value &= ~flags;
}
// FYMP end

using namespace HTMLNames;

// FYMP begin - integrating TextTracks from r152754
#if ENABLE(VIDEO_TRACK)
class TrackDisplayUpdateScope {
public:
    TrackDisplayUpdateScope(HTMLMediaElement* mediaElement)
    {
        m_mediaElement = mediaElement;
        m_mediaElement->beginIgnoringTrackDisplayUpdateRequests();
    }
    ~TrackDisplayUpdateScope()
    {
        ASSERT(m_mediaElement);
        m_mediaElement->endIgnoringTrackDisplayUpdateRequests();
    }
    
private:
    HTMLMediaElement* m_mediaElement;
};
#endif
// FYMP end

// FYMP: added parameter 'createdByParser' while integrating TextTrack from r152754.
HTMLMediaElement::HTMLMediaElement(const QualifiedName& tagName, Document* doc, bool createdByParser)
    : HTMLElement(tagName, doc)
	, ActiveDOMObject(doc, this) // FYMP - integrating TextTracks from r152754
    , m_loadTimer(this, &HTMLMediaElement::loadTimerFired)
    , m_asyncEventTimer(this, &HTMLMediaElement::asyncEventTimerFired)
    , m_progressEventTimer(this, &HTMLMediaElement::progressEventTimerFired)
    , m_playbackProgressTimer(this, &HTMLMediaElement::playbackProgressTimerFired)
    , m_playedTimeRanges()
    , m_playbackRate(1.0f)
    , m_defaultPlaybackRate(1.0f)
    , m_webkitPreservesPitch(true)
    , m_networkState(NETWORK_EMPTY)
    , m_readyState(HAVE_NOTHING)
    , m_readyStateMaximum(HAVE_NOTHING)
    , m_volume(1.0f)
    , m_lastSeekTime(0)
    , m_previousProgress(0)
    , m_previousProgressTime(numeric_limits<double>::max())
    , m_lastTimeUpdateEventWallTime(0)
    , m_lastTimeUpdateEventMovieTime(numeric_limits<float>::max())
    , m_loadState(WaitingForSource)
    , m_currentSourceNode(0)
    , m_player(0)
#if ENABLE(PLUGIN_PROXY_FOR_VIDEO)
    , m_proxyWidget(0)
#endif
    , m_restrictions(NoRestrictions)
    , m_preload(MediaPlayer::Auto)
    , m_playing(false)
    , m_processingMediaPlayerCallback(0)
    , m_pendingActionFlags(0) // FYMP - integrating TextTracks from r152754
    , m_isWaitingUntilMediaCanStart(false)
    , m_processingLoad(false)
    , m_delayingTheLoadEvent(false)
    , m_haveFiredLoadedData(false)
    , m_inActiveDocument(true)
    , m_autoplaying(true)
    , m_muted(false)
    , m_paused(true)
    , m_seeking(false)
    , m_sentStalledEvent(false)
    , m_sentEndEvent(false)
    , m_pausedInternal(false)
    , m_sendProgressEvents(true)
    , m_isFullscreen(false)
    , m_closedCaptionsVisible(false)
#if ENABLE(PLUGIN_PROXY_FOR_VIDEO)
    , m_needWidgetUpdate(false)
#endif
    , m_dispatchingCanPlayEvent(false)
    , m_loadInitiatedByUserGesture(false)
    , m_completelyLoaded(false)
	, m_parsingInProgress(createdByParser)// FYMP - integrating TextTracks from r152754
// FYMP begin: integrating parts of r152754
#if ENABLE(VIDEO_TRACK)
    , m_tracksAreReady(true)
    , m_haveVisibleTextTrack(false)
    , m_lastTextTrackUpdateTime(-1)
//    , m_captionDisplayMode(CaptionUserPreferences::Automatic) // rendering related.
    , m_textTracks(0)
    , m_ignoreTrackDisplayUpdate(0)
#endif
// FYMP end
{
    document()->registerForDocumentActivationCallbacks(this);
    document()->registerForMediaVolumeCallbacks(this);
}

HTMLMediaElement::~HTMLMediaElement()
{
    if (m_isWaitingUntilMediaCanStart)
        document()->removeMediaCanStartListener(this);
    document()->unregisterForDocumentActivationCallbacks(this);
    document()->unregisterForMediaVolumeCallbacks(this);

// FYMP begin - integrating parts of r152754
#if ENABLE(VIDEO_TRACK)
    if (m_textTracks)
        m_textTracks->clearElement();
    if (m_textTracks) {
        for (unsigned i = 0; i < m_textTracks->length(); ++i)
            m_textTracks->item(i)->clearClient();
    }
#endif
// FYMP end
}

void HTMLMediaElement::willMoveToNewOwnerDocument()
{
    if (m_isWaitingUntilMediaCanStart)
        document()->removeMediaCanStartListener(this);
    document()->unregisterForDocumentActivationCallbacks(this);
    document()->unregisterForMediaVolumeCallbacks(this);
    HTMLElement::willMoveToNewOwnerDocument();
}

void HTMLMediaElement::didMoveToNewOwnerDocument()
{
    if (m_isWaitingUntilMediaCanStart)
        document()->addMediaCanStartListener(this);
    document()->registerForDocumentActivationCallbacks(this);
    document()->registerForMediaVolumeCallbacks(this);
    HTMLElement::didMoveToNewOwnerDocument();
}


bool HTMLMediaElement::checkDTD(const Node* newChild)
{
    return 	newChild->hasTagName(sourceTag) || 
// FYMP begin - integrating parts of r152754
		#if ENABLE(VIDEO_TRACK)
			newChild->hasTagName(trackTag) ||
		#endif
// FYMP end
			HTMLElement::checkDTD(newChild);
}

void HTMLMediaElement::attributeChanged(Attribute* attr, bool preserveDecls)
{
    HTMLElement::attributeChanged(attr, preserveDecls);

    const QualifiedName& attrName = attr->name();
    if (attrName == srcAttr) {
        // Trigger a reload, as long as the 'src' attribute is present.
        if (!getAttribute(srcAttr).isEmpty())
			{
			clearMediaPlayer(LoadMediaResource); // FYMP - integrating parts of r152754
            scheduleLoad();
			}
    }
#if !ENABLE(PLUGIN_PROXY_FOR_VIDEO)
    else if (attrName == controlsAttr) {
        if (!isVideo() && attached() && (controls() != (renderer() != 0))) {
            detach();
            attach();
        }
        if (renderer())
            renderer()->updateFromElement();
    }
#endif
}

void HTMLMediaElement::parseMappedAttribute(Attribute* attr)
{
    const QualifiedName& attrName = attr->name();

    if (attrName == preloadAttr) {
        String value = attr->value();

        if (equalIgnoringCase(value, "none"))
            m_preload = MediaPlayer::None;
        else if (equalIgnoringCase(value, "metadata"))
            m_preload = MediaPlayer::MetaData;
        else {
            // The spec does not define an "invalid value default" but "auto" is suggested as the
            // "missing value default", so use it for everything except "none" and "metadata"
            m_preload = MediaPlayer::Auto;
        }

        // The attribute must be ignored if the autoplay attribute is present
        if (!autoplay() && m_player)
            m_player->setPreload(m_preload);

    } else if (attrName == onabortAttr)
        setAttributeEventListener(eventNames().abortEvent, createAttributeEventListener(this, attr));
    else if (attrName == onbeforeloadAttr)
        setAttributeEventListener(eventNames().beforeloadEvent, createAttributeEventListener(this, attr));
    else if (attrName == oncanplayAttr)
        setAttributeEventListener(eventNames().canplayEvent, createAttributeEventListener(this, attr));
    else if (attrName == oncanplaythroughAttr)
        setAttributeEventListener(eventNames().canplaythroughEvent, createAttributeEventListener(this, attr));
    else if (attrName == ondurationchangeAttr)
        setAttributeEventListener(eventNames().durationchangeEvent, createAttributeEventListener(this, attr));
    else if (attrName == onemptiedAttr)
        setAttributeEventListener(eventNames().emptiedEvent, createAttributeEventListener(this, attr));
    else if (attrName == onendedAttr)
        setAttributeEventListener(eventNames().endedEvent, createAttributeEventListener(this, attr));
    else if (attrName == onerrorAttr)
        setAttributeEventListener(eventNames().errorEvent, createAttributeEventListener(this, attr));
    else if (attrName == onloadeddataAttr)
        setAttributeEventListener(eventNames().loadeddataEvent, createAttributeEventListener(this, attr));
    else if (attrName == onloadedmetadataAttr)
        setAttributeEventListener(eventNames().loadedmetadataEvent, createAttributeEventListener(this, attr));
    else if (attrName == onloadstartAttr)
        setAttributeEventListener(eventNames().loadstartEvent, createAttributeEventListener(this, attr));
    else if (attrName == onpauseAttr)
        setAttributeEventListener(eventNames().pauseEvent, createAttributeEventListener(this, attr));
    else if (attrName == onplayAttr)
        setAttributeEventListener(eventNames().playEvent, createAttributeEventListener(this, attr));
    else if (attrName == onplayingAttr)
        setAttributeEventListener(eventNames().playingEvent, createAttributeEventListener(this, attr));
    else if (attrName == onprogressAttr)
        setAttributeEventListener(eventNames().progressEvent, createAttributeEventListener(this, attr));
    else if (attrName == onratechangeAttr)
        setAttributeEventListener(eventNames().ratechangeEvent, createAttributeEventListener(this, attr));
    else if (attrName == onseekedAttr)
        setAttributeEventListener(eventNames().seekedEvent, createAttributeEventListener(this, attr));
    else if (attrName == onseekingAttr)
        setAttributeEventListener(eventNames().seekingEvent, createAttributeEventListener(this, attr));
    else if (attrName == onstalledAttr)
        setAttributeEventListener(eventNames().stalledEvent, createAttributeEventListener(this, attr));
    else if (attrName == onsuspendAttr)
        setAttributeEventListener(eventNames().suspendEvent, createAttributeEventListener(this, attr));
    else if (attrName == ontimeupdateAttr)
        setAttributeEventListener(eventNames().timeupdateEvent, createAttributeEventListener(this, attr));
    else if (attrName == onvolumechangeAttr)
        setAttributeEventListener(eventNames().volumechangeEvent, createAttributeEventListener(this, attr));
    else if (attrName == onwaitingAttr)
        setAttributeEventListener(eventNames().waitingEvent, createAttributeEventListener(this, attr));
    else if (attrName == onwebkitbeginfullscreenAttr)
        setAttributeEventListener(eventNames().webkitbeginfullscreenEvent, createAttributeEventListener(this, attr));
    else if (attrName == onwebkitendfullscreenAttr)
        setAttributeEventListener(eventNames().webkitendfullscreenEvent, createAttributeEventListener(this, attr));
    else
        HTMLElement::parseMappedAttribute(attr);
}

bool HTMLMediaElement::rendererIsNeeded(RenderStyle* style)
{
#if ENABLE(PLUGIN_PROXY_FOR_VIDEO)
    UNUSED_PARAM(style);
    Frame* frame = document()->frame();
    if (!frame)
        return false;

    return true;
#else
    return controls() ? HTMLElement::rendererIsNeeded(style) : false;
#endif
}

RenderObject* HTMLMediaElement::createRenderer(RenderArena* arena, RenderStyle*)
{
#if ENABLE(PLUGIN_PROXY_FOR_VIDEO)
    // Setup the renderer if we already have a proxy widget.
    RenderEmbeddedObject* mediaRenderer = new (arena) RenderEmbeddedObject(this);
    if (m_proxyWidget)
        mediaRenderer->setWidget(m_proxyWidget);
    return mediaRenderer;
#else
    return new (arena) RenderMedia(this);
#endif
}

void HTMLMediaElement::insertedIntoDocument()
{
    HTMLElement::insertedIntoDocument();
    if (!src().isEmpty() && m_networkState == NETWORK_EMPTY)
        scheduleLoad();
}

void HTMLMediaElement::removedFromDocument()
{
    if (m_networkState > NETWORK_EMPTY)
        pause(processingUserGesture());
    if (m_isFullscreen)
        exitFullscreen();
    HTMLElement::removedFromDocument();
}

void HTMLMediaElement::attach()
{
    ASSERT(!attached());

#if ENABLE(PLUGIN_PROXY_FOR_VIDEO)
    m_needWidgetUpdate = true;
#endif

    HTMLElement::attach();

    if (renderer())
        renderer()->updateFromElement();
}

void HTMLMediaElement::recalcStyle(StyleChange change)
{
    HTMLElement::recalcStyle(change);

    if (renderer())
        renderer()->updateFromElement();
}

void HTMLMediaElement::scheduleLoad()
{ 
	scheduleDelayedAction(LoadMediaResource); // FYMP: integrating parts of r152754. Kept old scheduleLoad to minimize changes.
}


// FYMP begin - integrating parts of r152754
void HTMLMediaElement::scheduleDelayedAction(DelayedActionType actionType)
{
    if ((actionType & LoadMediaResource) && !(m_pendingActionFlags & LoadMediaResource)) {
#if ENABLE(PLUGIN_PROXY_FOR_VIDEO)
        createMediaPlayerProxy();
#endif
        if (m_loadTimer.isActive())
            return;
        prepareForLoad();
        setFlags(m_pendingActionFlags, LoadMediaResource);
    }

#if ENABLE(VIDEO_TRACK)
    if (actionType & ConfigureTextTracks)
        setFlags(m_pendingActionFlags, ConfigureTextTracks);
#endif

#if USE(PLATFORM_TEXT_TRACK_MENU)
    if (actionType & TextTrackChangesNotification)
        setFlags(m_pendingActionFlags, TextTrackChangesNotification);
#endif

    m_loadTimer.startOneShot(0);
}
// FYMP end

void HTMLMediaElement::scheduleNextSourceChild()
{
    // Schedule the timer to try the next <source> element WITHOUT resetting state ala prepareForLoad.
    m_loadTimer.startOneShot(0);
}

void HTMLMediaElement::scheduleEvent(const AtomicString& eventName)
{
	//printf("scheduleEvent(%p: %s)\n", this, eventName.string().utf8().data());
    //NN_LOG("*** scheduleEvent(%p: %s)\n", this, eventName.string().utf8().data());
 	/*   
    if(strcmp("canplay", eventName.string().utf8().data()) == 0)
        {
        NN_LOG("***+++ FOUND event\n");
        }
 	*/   

	m_pendingEvents.append(Event::create(eventName, false, true));
    if (!m_asyncEventTimer.isActive())
        m_asyncEventTimer.startOneShot(0);
}

// FYMP begin - convenience function
void HTMLMediaElement::scheduleEvent(PassRefPtr<Event> e)
{
    m_pendingEvents.append(e);
    if (!m_asyncEventTimer.isActive())
        m_asyncEventTimer.startOneShot(0);
}
// FYMP end

void HTMLMediaElement::asyncEventTimerFired(Timer<HTMLMediaElement>*)
{
    Vector<RefPtr<Event> > pendingEvents;
    ExceptionCode ec = 0;

    m_pendingEvents.swap(pendingEvents);
    unsigned count = pendingEvents.size();
    for (unsigned ndx = 0; ndx < count; ++ndx) {
		EventTarget* pTarget = (pendingEvents[ndx]->target()) ? pendingEvents[ndx]->target() : this; // FYMP
        if (pendingEvents[ndx]->type() == eventNames().canplayEvent) {
            m_dispatchingCanPlayEvent = true;
			pTarget->dispatchEvent(pendingEvents[ndx].release(), ec); // FYMP - using member of pTarget. Integrating parts of r152754.
            m_dispatchingCanPlayEvent = false;
        } else
			{
			pTarget->dispatchEvent(pendingEvents[ndx].release(), ec); // FYMP - using member of pTarget. Integrating parts of r152754
		}
    }
}

void HTMLMediaElement::loadTimerFired(Timer<HTMLMediaElement>*)
{
// FYMP begin - integrating parts of r152754
    RefPtr<HTMLMediaElement> protect(this); // loadNextSourceChild may fire 'beforeload', which can make arbitrary DOM mutations.

#if ENABLE(VIDEO_TRACK)
    if (m_pendingActionFlags & ConfigureTextTracks)
        configureTextTracks();
#endif
// FYMP end

    if (m_loadState == LoadingFromSourceElement)
        loadNextSourceChild();
    else
        loadInternal();
}

static String serializeTimeOffset(float time)
{
    String timeString = String::number(time);
    // FIXME serialize time offset values properly (format not specified yet)
    timeString.append("s");
    return timeString;
}

static float parseTimeOffset(const String& timeString, bool* ok = 0)
{
    const UChar* characters = timeString.characters();
    unsigned length = timeString.length();

    if (length && characters[length - 1] == 's')
        length--;

    // FIXME parse time offset values (format not specified yet)
    float val = charactersToFloat(characters, length, ok);
    return val;
}

float HTMLMediaElement::getTimeOffsetAttribute(const QualifiedName& name, float valueOnError) const
{
    bool ok;
    String timeString = getAttribute(name);
    float result = parseTimeOffset(timeString, &ok);
    if (ok)
        return result;
    return valueOnError;
}

void HTMLMediaElement::setTimeOffsetAttribute(const QualifiedName& name, float value)
{
    setAttribute(name, serializeTimeOffset(value));
}

PassRefPtr<MediaError> HTMLMediaElement::error() const
{
    return m_error;
}

KURL HTMLMediaElement::src() const
{
    return getNonEmptyURLAttribute(srcAttr);
}

void HTMLMediaElement::setSrc(const String& url)
{
    setAttribute(srcAttr, url);
}

String HTMLMediaElement::currentSrc() const
{
    return m_currentSrc;
}

HTMLMediaElement::NetworkState HTMLMediaElement::networkState() const
{
    return m_networkState;
}

String HTMLMediaElement::canPlayType(const String& mimeType) const
{
    MediaPlayer::SupportsType support = MediaPlayer::supportsType(ContentType(mimeType));
    String canPlay;

    // 4.8.10.3
    switch (support)
    {
        case MediaPlayer::IsNotSupported:
            canPlay = "";
            break;
        case MediaPlayer::MayBeSupported:
            canPlay = "maybe";
            break;
        case MediaPlayer::IsSupported:
            canPlay = "probably";
            break;
    }

    return canPlay;
}

void HTMLMediaElement::load(bool isUserGesture, ExceptionCode& ec)
{
    if (m_restrictions & RequireUserGestureForLoadRestriction && !isUserGesture)
        ec = INVALID_STATE_ERR;
    else {
        m_loadInitiatedByUserGesture = isUserGesture;
        prepareForLoad();
        loadInternal();
    }
}

void HTMLMediaElement::prepareForLoad()
{
    // Perform the cleanup required for the resource load algorithm to run.
    stopPeriodicTimers();
    m_loadTimer.stop();
    m_sentEndEvent = false;			// FYMP: this must be reset as well. Newer versions of this file do this, so I've integrated this fix.
    m_sentStalledEvent = false;
    m_haveFiredLoadedData = false;
    m_completelyLoaded = false;

    // 1 - Abort any already-running instance of the resource selection algorithm for this element.
    m_currentSourceNode = 0;

    // 2 - If there are any tasks from the media element's media element event task source in
    // one of the task queues, then remove those tasks.
    cancelPendingEventsAndCallbacks();

    // 3 - If the media element's networkState is set to NETWORK_LOADING or NETWORK_IDLE, queue
    // a task to fire a simple event named abort at the media element.
    if (m_networkState == NETWORK_LOADING || m_networkState == NETWORK_IDLE)
        scheduleEvent(eventNames().abortEvent);

#if !ENABLE(PLUGIN_PROXY_FOR_VIDEO)
    m_player = MediaPlayer::create(this);
#else
    createMediaPlayerProxy();
#endif

    // 4 - If the media element's networkState is not set to NETWORK_EMPTY, then run these substeps
    if (m_networkState != NETWORK_EMPTY) {
        m_networkState = NETWORK_EMPTY;
        m_readyState = HAVE_NOTHING;
        m_readyStateMaximum = HAVE_NOTHING;
        m_paused = true;
        m_seeking = false;
        scheduleEvent(eventNames().emptiedEvent);

#if ENABLE(VIDEO_TRACK) // FYMP begin - integrated parts of r152754
        updateActiveTextTrackCues(0);
#endif
    }

    // 5 - Set the playbackRate attribute to the value of the defaultPlaybackRate attribute.
    setPlaybackRate(defaultPlaybackRate());

    // 6 - Set the error attribute to null and the autoplaying flag to true.
    m_error = 0;
    m_autoplaying = true;

    m_playedTimeRanges = TimeRanges::create();
    m_lastSeekTime = 0;
    m_closedCaptionsVisible = false;

}

void HTMLMediaElement::loadInternal()
{
    // If we can't start a load right away, start it later.
    Page* page = document()->page();
    if (page && !page->canStartMedia()) {
        if (m_isWaitingUntilMediaCanStart)
            return;
        document()->addMediaCanStartListener(this);
        m_isWaitingUntilMediaCanStart = true;
        return;
    }

    // Steps 1 - 6 were done in prepareForLoad


    // 7 - Invoke the media element's resource selection algorithm.

// FYMP begin - integrating part of r152754
#if ENABLE(VIDEO_TRACK)
//    if (hasMediaControls())
//        mediaControls()->changedClosedCaptionsVisibility();

    // HTMLMediaElement::textTracksAreReady will need "... the text tracks whose mode was not in the
    // disabled state when the element's resource selection algorithm last started".

	m_textTracksWhenResourceSelectionBegan.clear();
	if (m_textTracks) {
		for (unsigned i = 0; i < m_textTracks->length(); ++i) {
			TextTrack* track = m_textTracks->item(i);
			if (track->mode() != TextTrack::disabledKeyword())
				m_textTracksWhenResourceSelectionBegan.append(track);
		}
	}
#endif
// FYMP end

    selectMediaResource();
    m_processingLoad = false;
}

void HTMLMediaElement::selectMediaResource()
{
    enum Mode { attribute, children };
    Mode mode = attribute;

    // 1 - Set the networkState to NETWORK_NO_SOURCE
    m_networkState = NETWORK_NO_SOURCE;

    // 2 - Asynchronously await a stable state.

    // 3 - ... the media element has neither a src attribute ...
    if (!hasAttribute(srcAttr)) {
        // ... nor a source element child: ...
        Node* node;
        for (node = firstChild(); node; node = node->nextSibling()) {
            if (node->hasTagName(sourceTag))
                break;
        }

        if (!node) {
            m_loadState = WaitingForSource;

            // ... set the networkState to NETWORK_EMPTY, and abort these steps
            m_networkState = NETWORK_EMPTY;
//            ASSERT(!m_delayingTheLoadEvent); // FYWEBKITMOD I dont understand purpose of that variable (which is only set but never read) nor of this Assert.
            return;
        }

        mode = children;
    }

    // 4
    m_delayingTheLoadEvent = true;
    m_networkState = NETWORK_LOADING;

    // 5
    scheduleEvent(eventNames().loadstartEvent);

    // 6 - If mode is attribute, then run these substeps
    if (mode == attribute) {
        // If the src attribute's value is the empty string ... jump down to the failed step below
        KURL mediaURL = getNonEmptyURLAttribute(srcAttr);
        if (mediaURL.isEmpty()) {
            noneSupported();
            return;
        }

        if (isSafeToLoadURL(mediaURL, Complain) && dispatchBeforeLoadEvent(mediaURL.string())) {
            ContentType contentType("");
            m_loadState = LoadingFromSrcAttr;
            loadResource(mediaURL, contentType);
        } else
            noneSupported();

        return;
    }

    // Otherwise, the source elements will be used
    m_currentSourceNode = 0;
    loadNextSourceChild();
}

void HTMLMediaElement::loadNextSourceChild()
{
    ContentType contentType("");
    KURL mediaURL = selectNextSourceChild(&contentType, Complain);
    if (!mediaURL.isValid()) {
        waitForSourceChange();
        return;
    }

#if !ENABLE(PLUGIN_PROXY_FOR_VIDEO)
    // Recreate the media player for the new url
    m_player = MediaPlayer::create(this);
#endif

    m_loadState = LoadingFromSourceElement;
    loadResource(mediaURL, contentType);
}

void HTMLMediaElement::loadResource(const KURL& initialURL, ContentType& contentType)
{
    ASSERT(isSafeToLoadURL(initialURL, Complain));

    Frame* frame = document()->frame();
    if (!frame)
        return;
    FrameLoader* loader = frame->loader();
    if (!loader)
        return;

    KURL url(initialURL);
    if (!loader->willLoadMediaElementURL(url))
        return;

    // The resource fetch algorithm
    m_networkState = NETWORK_LOADING;

    m_currentSrc = url;

    if (m_sendProgressEvents)
        startProgressEventTimer();

    if (!autoplay())
        m_player->setPreload(m_preload);
    m_player->setPreservesPitch(m_webkitPreservesPitch);
    updateVolume();

    m_player->load(m_currentSrc, contentType);

    if (isVideo() && m_player->canLoadPoster()) {
        KURL posterUrl = poster();
        if (!posterUrl.isEmpty())
            m_player->setPoster(posterUrl);
    }

    if (renderer())
        renderer()->updateFromElement();
}

// FYMP begin - integrating parts of r152754
#if ENABLE(VIDEO_TRACK)
static bool trackIndexCompare(TextTrack* a,
                              TextTrack* b)
{
    return a->trackIndex() - b->trackIndex() < 0;
}

static bool eventTimeCueCompare(const std::pair<double, TextTrackCue*>& a,
                                const std::pair<double, TextTrackCue*>& b)
{
    // 12 - Sort the tasks in events in ascending time order (tasks with earlier
    // times first).
    if (a.first != b.first)
        return a.first - b.first < 0;

    // If the cues belong to different text tracks, it doesn't make sense to
    // compare the two tracks by the relative cue order, so return the relative
    // track order.
    if (a.second->track() != b.second->track())
        return trackIndexCompare(a.second->track(), b.second->track());

    // 12 - Further sort tasks in events that have the same time by the
    // relative text track cue order of the text track cues associated
    // with these tasks.
    return a.second->cueIndex() - b.second->cueIndex() < 0;
}

static bool compareCueInterval(const CueInterval& one, const CueInterval& two)
{
    return one.data()->isOrderedBefore(two.data());
};


void HTMLMediaElement::updateActiveTextTrackCues(double movieTime)
{
    // 4.8.10.8 Playing the media resource

    //  If the current playback position changes while the steps are running,
    //  then the user agent must wait for the steps to complete, and then must
    //  immediately rerun the steps.

    if (ignoreTrackDisplayUpdateRequests())
        return;

    // 1 - Let current cues be a list of cues, initialized to contain all the
    // cues of all the hidden, showing, or showing by default text tracks of the
    // media element (not the disabled ones) whose start times are less than or
    // equal to the current playback position and whose end times are greater
    // than the current playback position.
    CueList currentCues;

    // The user agent must synchronously unset [the text track cue active] flag
    // whenever ... the media element's readyState is changed back to HAVE_NOTHING.
    if (m_readyState != HAVE_NOTHING && m_player) {
        currentCues = m_cueTree.allOverlaps(m_cueTree.createInterval(movieTime, movieTime));
        std::sort(currentCues.begin(), currentCues.end(), &compareCueInterval);
    }

    CueList previousCues;
    CueList missedCues;

    // 2 - Let other cues be a list of cues, initialized to contain all the cues
    // of hidden, showing, and showing by default text tracks of the media
    // element that are not present in current cues.
    previousCues = m_currentlyActiveCues;

    // 3 - Let last time be the current playback position at the time this
    // algorithm was last run for this media element, if this is not the first
    // time it has run.
    double lastTime = m_lastTextTrackUpdateTime;

    // 4 - If the current playback position has, since the last time this
    // algorithm was run, only changed through its usual monotonic increase
    // during normal playback, then let missed cues be the list of cues in other
    // cues whose start times are greater than or equal to last time and whose
    // end times are less than or equal to the current playback position.
    // Otherwise, let missed cues be an empty list.
    if (lastTime >= 0 && m_lastSeekTime < movieTime) {
        CueList potentiallySkippedCues =
            m_cueTree.allOverlaps(m_cueTree.createInterval(lastTime, movieTime));

        for (size_t i = 0; i < potentiallySkippedCues.size(); ++i) {
            double cueStartTime = potentiallySkippedCues[i].low();
            double cueEndTime = potentiallySkippedCues[i].high();

            // Consider cues that may have been missed since the last seek time.
            if (cueStartTime > max((double)m_lastSeekTime, lastTime) && cueEndTime < movieTime)
                missedCues.append(potentiallySkippedCues[i]);
        }
    }

    m_lastTextTrackUpdateTime = movieTime;

    // 5 - If the time was reached through the usual monotonic increase of the
    // current playback position during normal playback, and if the user agent
    // has not fired a timeupdate event at the element in the past 15 to 250ms
    // and is not still running event handlers for such an event, then the user
    // agent must queue a task to fire a simple event named timeupdate at the
    // element. (In the other cases, such as explicit seeks, relevant events get
    // fired as part of the overall process of changing the current playback
    // position.)
    if (m_lastSeekTime <= lastTime)
        scheduleTimeupdateEvent(false);

    // Explicitly cache vector sizes, as their content is constant from here.
    size_t currentCuesSize = currentCues.size();
    size_t missedCuesSize = missedCues.size();
    size_t previousCuesSize = previousCues.size();

    // 6 - If all of the cues in current cues have their text track cue active
    // flag set, none of the cues in other cues have their text track cue active
    // flag set, and missed cues is empty, then abort these steps.
    bool activeSetChanged = missedCuesSize;

    for (size_t i = 0; !activeSetChanged && i < previousCuesSize; ++i)
        if (!currentCues.contains(previousCues[i]) && previousCues[i].data()->isActive())
            activeSetChanged = true;

    for (size_t i = 0; i < currentCuesSize; ++i) {
#if ENABLE(ENABLE_TEXTTRACK_RENDERING) // FYWEBKITMOD marking render related stuff. Note, that ENABLE_TEXTTRACK_RENDERING is always DISABLED!
        currentCues[i].data()->updateDisplayTree(movieTime);
#endif

        if (!currentCues[i].data()->isActive())
            activeSetChanged = true;
    }

    if (!activeSetChanged) {
        // Even though the active set has not changed, it is possible that the
        // the mode of a track has changed from 'hidden' to 'showing' and the
        // cues have not yet been rendered.
        // Note: don't call updateTextTrackDisplay() unless we have controls because it will
        // create them.
#if ENABLE(ENABLE_TEXTTRACK_RENDERING) // FYWEBKITMOD marking render related stuff. Note, that ENABLE_TEXTTRACK_RENDERING is always DISABLED!
        if (hasMediaControls())
            updateTextTrackDisplay();
#endif
        return;
    }

    // 7 - If the time was reached through the usual monotonic increase of the
    // current playback position during normal playback, and there are cues in
    // other cues that have their text track cue pause-on-exi flag set and that
    // either have their text track cue active flag set or are also in missed
    // cues, then immediately pause the media element.
    for (size_t i = 0; !m_paused && i < previousCuesSize; ++i) {
        if (previousCues[i].data()->pauseOnExit()
            && previousCues[i].data()->isActive()
            && !currentCues.contains(previousCues[i]))
            pause();
    }

    for (size_t i = 0; !m_paused && i < missedCuesSize; ++i) {
        if (missedCues[i].data()->pauseOnExit())
            pause();
    }

    // 8 - Let events be a list of tasks, initially empty. Each task in this
    // list will be associated with a text track, a text track cue, and a time,
    // which are used to sort the list before the tasks are queued.
    Vector<std::pair<double, TextTrackCue*> > eventTasks;

    // 8 - Let affected tracks be a list of text tracks, initially empty.
    Vector<TextTrack*> affectedTracks;

    for (size_t i = 0; i < missedCuesSize; ++i) {
        // 9 - For each text track cue in missed cues, prepare an event named enter
        // for the TextTrackCue object with the text track cue start time.
        eventTasks.append(std::make_pair(missedCues[i].data()->startTime(),
                                         missedCues[i].data()));

        // 10 - For each text track [...] in missed cues, prepare an event
        // named exit for the TextTrackCue object with the  with the later of
        // the text track cue end time and the text track cue start time.

        // Note: An explicit task is added only if the cue is NOT a zero or
        // negative length cue. Otherwise, the need for an exit event is
        // checked when these tasks are actually queued below. This doesn't
        // affect sorting events before dispatch either, because the exit
        // event has the same time as the enter event.
        if (missedCues[i].data()->startTime() < missedCues[i].data()->endTime())
            eventTasks.append(std::make_pair(missedCues[i].data()->endTime(),
                                             missedCues[i].data()));
    }

    for (size_t i = 0; i < previousCuesSize; ++i) {
        // 10 - For each text track cue in other cues that has its text
        // track cue active flag set prepare an event named exit for the
        // TextTrackCue object with the text track cue end time.
        if (!currentCues.contains(previousCues[i]))
            eventTasks.append(std::make_pair(previousCues[i].data()->endTime(),
                                             previousCues[i].data()));
    }

    for (size_t i = 0; i < currentCuesSize; ++i) {
        // 11 - For each text track cue in current cues that does not have its
        // text track cue active flag set, prepare an event named enter for the
        // TextTrackCue object with the text track cue start time.
        if (!previousCues.contains(currentCues[i]))
            eventTasks.append(std::make_pair(currentCues[i].data()->startTime(),
                                             currentCues[i].data()));
    }

    // 12 - Sort the tasks in events in ascending time order (tasks with earlier
    // times first).
    nonCopyingSort(eventTasks.begin(), eventTasks.end(), eventTimeCueCompare);

    for (size_t i = 0; i < eventTasks.size(); ++i) {
        if (!affectedTracks.contains(eventTasks[i].second->track()))
            affectedTracks.append(eventTasks[i].second->track());

        // 13 - Queue each task in events, in list order.
        RefPtr<Event> event;

        // Each event in eventTasks may be either an enterEvent or an exitEvent,
        // depending on the time that is associated with the event. This
        // correctly identifies the type of the event, if the startTime is
        // less than the endTime in the cue.
        if (eventTasks[i].second->startTime() >= eventTasks[i].second->endTime()) {
            event = Event::create(eventNames().enterEvent, false, false);
            event->setTarget(eventTasks[i].second);
            scheduleEvent(event.release()); // FYMP: latest webkit uses 'EventQueue'.

            event = Event::create(eventNames().exitEvent, false, false);
            event->setTarget(eventTasks[i].second);
            scheduleEvent(event.release()); // FYMP: latest webkit uses 'EventQueue'.
        } else {
            if (eventTasks[i].first == eventTasks[i].second->startTime())
                event = Event::create(eventNames().enterEvent, false, false);
            else
                event = Event::create(eventNames().exitEvent, false, false);

            event->setTarget(eventTasks[i].second);
            scheduleEvent(event.release()); // FYMP: latest webkit uses 'EventQueue'.
        }
    }

    // 14 - Sort affected tracks in the same order as the text tracks appear in
    // the media element's list of text tracks, and remove duplicates.
    nonCopyingSort(affectedTracks.begin(), affectedTracks.end(), trackIndexCompare);

    // 15 - For each text track in affected tracks, in the list order, queue a
    // task to fire a simple event named cuechange at the TextTrack object, and, ...
    for (size_t i = 0; i < affectedTracks.size(); ++i) {
        RefPtr<Event> event = Event::create(eventNames().cuechangeEvent, false, false);
        event->setTarget(affectedTracks[i]);

        scheduleEvent(event.release()); // FYMP: latest webkit uses 'EventQueue'.

        // ... if the text track has a corresponding track element, to then fire a
        // simple event named cuechange at the track element as well.
        if (affectedTracks[i]->trackType() == TextTrack::TrackElement) {
            RefPtr<Event> event = Event::create(eventNames().cuechangeEvent, false, false);

            HTMLTrackElement* trackElement = static_cast<LoadableTextTrack*>(affectedTracks[i])->trackElement();
            ASSERT(trackElement);
            event->setTarget(trackElement);
            
            scheduleEvent(event.release()); // FYMP: latest webkit uses 'EventQueue'.
        }
    }

    // 16 - Set the text track cue active flag of all the cues in the current
    // cues, and unset the text track cue active flag of all the cues in the
    // other cues.
    for (size_t i = 0; i < currentCuesSize; ++i)
        currentCues[i].data()->setIsActive(true);

    for (size_t i = 0; i < previousCuesSize; ++i)
        if (!currentCues.contains(previousCues[i]))
            previousCues[i].data()->setIsActive(false);

    // Update the current active cues.
    m_currentlyActiveCues = currentCues;

#if ENABLE(ENABLE_TEXTTRACK_RENDERING) // FYWEBKITMOD marking render related stuff. Note, that ENABLE_TEXTTRACK_RENDERING is always DISABLED!
    if (activeSetChanged)
        updateTextTrackDisplay();
#endif
}

bool HTMLMediaElement::textTracksAreReady() const
{
    // 4.8.10.12.1 Text track model
    // ...
    // The text tracks of a media element are ready if all the text tracks whose mode was not 
    // in the disabled state when the element's resource selection algorithm last started now
    // have a text track readiness state of loaded or failed to load.
    for (unsigned i = 0; i < m_textTracksWhenResourceSelectionBegan.size(); ++i) {
        if (m_textTracksWhenResourceSelectionBegan[i]->readinessState() == TextTrack::Loading
            || m_textTracksWhenResourceSelectionBegan[i]->readinessState() == TextTrack::NotLoaded)
            return false;
    }

    return true;
}

void HTMLMediaElement::textTrackReadyStateChanged(TextTrack* track)
{
    if (m_player && m_textTracksWhenResourceSelectionBegan.contains(track)) {
        if (track->readinessState() != TextTrack::Loading)
            setReadyState(m_player->readyState());
    } else {
        // The track readiness state might have changed as a result of the user
        // clicking the captions button. In this case, a check whether all the
        // resources have failed loading should be done in order to hide the CC button.
#if ENABLE(ENABLE_TEXTTRACK_RENDERING) // FYWEBKITMOD marking render related stuff. Note, that ENABLE_TEXTTRACK_RENDERING is always DISABLED!
        if (hasMediaControls() && track->readinessState() == TextTrack::FailedToLoad)
            mediaControls()->refreshClosedCaptionsButtonVisibility();
#endif
    }
}

void HTMLMediaElement::textTrackModeChanged(TextTrack* track)
{
    bool trackIsLoaded = true;
    if (track->trackType() == TextTrack::TrackElement) {
        trackIsLoaded = false;
        for (Node* node = firstChild(); node; node = node->nextSibling()) {
            if (!node->hasTagName(trackTag))
                continue;

            HTMLTrackElement* trackElement = static_cast<HTMLTrackElement*>(node);
            if (trackElement->track() == track) {
                if (trackElement->readyState() == HTMLTrackElement::LOADING || trackElement->readyState() == HTMLTrackElement::LOADED)
                    trackIsLoaded = true;
                break;
            }
        }
    }

    // If this is the first added track, create the list of text tracks.
//    if (!m_textTracks) 
//        m_textTracks = TextTrackList::create(this, ActiveDOMObject::scriptExecutionContext());
    if (!m_textTracks) 
		m_textTracks = TextTrackList::create(this, ActiveDOMObject::scriptExecutionContext());
    
    // Mark this track as "configured" so configureTextTracks won't change the mode again.
    track->setHasBeenConfigured(true);
    
    if (track->mode() != TextTrack::disabledKeyword() && trackIsLoaded)
        textTrackAddCues(track, track->cues());

#if USE(PLATFORM_TEXT_TRACK_MENU)
    if (platformTextTrackMenu())
        platformTextTrackMenu()->trackWasSelected(track->platformTextTrack());
#endif
    
#if ENABLE(ENABLE_TEXTTRACK_RENDERING) // FYWEBKITMOD marking render related stuff. Note, that ENABLE_TEXTTRACK_RENDERING is always DISABLED!
    configureTextTrackDisplay();
#endif
    updateActiveTextTrackCues(currentTime());
}

void HTMLMediaElement::textTrackKindChanged(TextTrack* track)
{
    if (track->kind() != TextTrack::captionsKeyword() && track->kind() != TextTrack::subtitlesKeyword() && track->mode() == TextTrack::showingKeyword())
        track->setMode(TextTrack::hiddenKeyword());
}

void HTMLMediaElement::beginIgnoringTrackDisplayUpdateRequests()
{
    ++m_ignoreTrackDisplayUpdate;
}

void HTMLMediaElement::endIgnoringTrackDisplayUpdateRequests()
{
    ASSERT(m_ignoreTrackDisplayUpdate);
    --m_ignoreTrackDisplayUpdate;
    if (!m_ignoreTrackDisplayUpdate && m_inActiveDocument)
        updateActiveTextTrackCues(currentTime());
}

void HTMLMediaElement::textTrackAddCues(TextTrack* track, const TextTrackCueList* cues) 
{
    if (track->mode() == TextTrack::disabledKeyword())
        return;

    TrackDisplayUpdateScope scope(this);
    for (size_t i = 0; i < cues->length(); ++i)
        textTrackAddCue(track, cues->item(i));
}

void HTMLMediaElement::textTrackRemoveCues(TextTrack*, const TextTrackCueList* cues) 
{
    TrackDisplayUpdateScope scope(this);
    for (size_t i = 0; i < cues->length(); ++i)
        textTrackRemoveCue(cues->item(i)->track(), cues->item(i));
}

void HTMLMediaElement::textTrackAddCue(TextTrack* track, PassRefPtr<TextTrackCue> cue)
{
    if (track->mode() == TextTrack::disabledKeyword())
        return;

    // Negative duration cues need be treated in the interval tree as
    // zero-length cues.
    double endTime = max(cue->startTime(), cue->endTime());

    CueInterval interval = m_cueTree.createInterval(cue->startTime(), endTime, cue.get());
    if (!m_cueTree.contains(interval))
        m_cueTree.add(interval);
    updateActiveTextTrackCues(currentTime());
}

void HTMLMediaElement::textTrackRemoveCue(TextTrack*, PassRefPtr<TextTrackCue> cue)
{
    // Negative duration cues need to be treated in the interval tree as
    // zero-length cues.
    double endTime = max(cue->startTime(), cue->endTime());

    CueInterval interval = m_cueTree.createInterval(cue->startTime(), endTime, cue.get());
    m_cueTree.remove(interval);

    size_t index = m_currentlyActiveCues.find(interval);
    if (index != notFound) {
        cue->setIsActive(false);
        m_currentlyActiveCues.remove(index);
    }

#if ENABLE(ENABLE_TEXTTRACK_RENDERING) // FYWEBKITMOD marking render related stuff. Note, that ENABLE_TEXTTRACK_RENDERING is always DISABLED!
    cue->removeDisplayTree();
#endif
    updateActiveTextTrackCues(currentTime());
}

#endif
// FYMP end

bool HTMLMediaElement::isSafeToLoadURL(const KURL& url, InvalidSourceAction actionIfInvalid)
{
    if (!url.isValid())
        return false;

    Frame* frame = document()->frame();
    FrameLoader* loader = frame ? frame->loader() : 0;

    // don't allow remote to local urls, and check with the frame loader client.
    if (!loader || !SecurityOrigin::canLoad(url, String(), document())) {
        if (actionIfInvalid == Complain)
            FrameLoader::reportLocalLoadFailed(frame, url.string());
        return false;
    }

    return true;
}

void HTMLMediaElement::startProgressEventTimer()
{
    if (m_progressEventTimer.isActive())
        return;

    m_previousProgressTime = WTF::currentTime();
    m_previousProgress = 0;
    // 350ms is not magic, it is in the spec!
    m_progressEventTimer.startRepeating(0.350);
}

void HTMLMediaElement::waitForSourceChange()
{
    stopPeriodicTimers();
    m_loadState = WaitingForSource;

    // 6.17 - Waiting: Set the element's networkState attribute to the NETWORK_NO_SOURCE value
    m_networkState = NETWORK_NO_SOURCE;

    // 6.18 - Set the element's delaying-the-load-event flag to false. This stops delaying the load event.
    m_delayingTheLoadEvent = false;
}

void HTMLMediaElement::noneSupported()
{
    stopPeriodicTimers();
    m_loadState = WaitingForSource;
    m_currentSourceNode = 0;

    // 5 - Reaching this step indicates that either the URL failed to resolve, or the media
    // resource failed to load. Set the error attribute to a new MediaError object whose
    // code attribute is set to MEDIA_ERR_SRC_NOT_SUPPORTED.
    m_error = MediaError::create(MediaError::MEDIA_ERR_SRC_NOT_SUPPORTED);

    // 6 - Set the element's networkState attribute to the NETWORK_NO_SOURCE value.
    m_networkState = NETWORK_NO_SOURCE;

    // 7 - Queue a task to fire a progress event called error at the media element, in
    // the context of the fetching process that was used to try to obtain the media
    // resource in the resource fetch algorithm.
    scheduleEvent(eventNames().errorEvent);

    // 8 - Set the element's delaying-the-load-event flag to false. This stops delaying the load event.
    m_delayingTheLoadEvent = false;

    // 9 -Abort these steps. Until the load() method is invoked, the element won't attempt to load another resource.

    updatePosterImage();

    if (renderer())
        renderer()->updateFromElement();
}

void HTMLMediaElement::mediaEngineError(PassRefPtr<MediaError> err)
{
    // 1 - The user agent should cancel the fetching process.
    stopPeriodicTimers();
    m_loadState = WaitingForSource;

    // 2 - Set the error attribute to a new MediaError object whose code attribute is
    // set to MEDIA_ERR_NETWORK/MEDIA_ERR_DECODE.
    m_error = err;

    // 3 - Queue a task to fire a progress event called error at the media element, in
    // the context of the fetching process started by this instance of this algorithm.
    scheduleEvent(eventNames().errorEvent);

    // 4 - Set the element's networkState attribute to the NETWORK_EMPTY value and queue a
    // task to fire a simple event called emptied at the element.
    m_networkState = NETWORK_EMPTY;
    scheduleEvent(eventNames().emptiedEvent);

    // 5 - Set the element's delaying-the-load-event flag to false. This stops delaying the load event.
    m_delayingTheLoadEvent = false;

    // 6 - Abort the overall resource selection algorithm.
    m_currentSourceNode = 0;
}

void HTMLMediaElement::cancelPendingEventsAndCallbacks()
{
    m_pendingEvents.clear();

    for (Node* node = firstChild(); node; node = node->nextSibling()) {
        if (node->hasTagName(sourceTag))
            static_cast<HTMLSourceElement*>(node)->cancelPendingErrorEvent();
    }
}

Document* HTMLMediaElement::mediaPlayerOwningDocument()
{
    Document* d = document();

    if (!d)
        d = ownerDocument();

    return d;
}

void HTMLMediaElement::mediaPlayerNetworkStateChanged(MediaPlayer*)
{
    beginProcessingMediaPlayerCallback();
    setNetworkState(m_player->networkState());
    endProcessingMediaPlayerCallback();
}

void HTMLMediaElement::setNetworkState(MediaPlayer::NetworkState state)
{
    if (state == MediaPlayer::Empty) {
        // just update the cached state and leave, we can't do anything
        m_networkState = NETWORK_EMPTY;
        return;
    }

    if (state == MediaPlayer::FormatError || state == MediaPlayer::NetworkError || state == MediaPlayer::DecodeError) {
        stopPeriodicTimers();

        // If we failed while trying to load a <source> element, the movie was never parsed, and there are more
        // <source> children, schedule the next one
        if (m_readyState < HAVE_METADATA && m_loadState == LoadingFromSourceElement) {
            m_currentSourceNode->scheduleErrorEvent();
            if (havePotentialSourceChild())
                scheduleNextSourceChild();
            else
                waitForSourceChange();

            return;
        }

        if (state == MediaPlayer::NetworkError)
            mediaEngineError(MediaError::create(MediaError::MEDIA_ERR_NETWORK));
        else if (state == MediaPlayer::DecodeError)
            mediaEngineError(MediaError::create(MediaError::MEDIA_ERR_DECODE));
        else if (state == MediaPlayer::FormatError && m_loadState == LoadingFromSrcAttr)
            noneSupported();

        updatePosterImage();
        return;
    }

    if (state == MediaPlayer::Idle) {
        if (m_networkState > NETWORK_IDLE) {
            m_progressEventTimer.stop();
            scheduleEvent(eventNames().suspendEvent);
        }
        m_networkState = NETWORK_IDLE;
    }

    if (state == MediaPlayer::Loading) {
        if (m_networkState < NETWORK_LOADING || m_networkState == NETWORK_NO_SOURCE)
            startProgressEventTimer();
        m_networkState = NETWORK_LOADING;
    }

    if (state == MediaPlayer::Loaded) {
        if (m_networkState != NETWORK_IDLE) {
            m_progressEventTimer.stop();

            // Schedule one last progress event so we guarantee that at least one is fired
            // for files that load very quickly.
            scheduleEvent(eventNames().progressEvent);
        }
        m_networkState = NETWORK_IDLE;
        m_completelyLoaded = true;
    }
}

void HTMLMediaElement::mediaPlayerReadyStateChanged(MediaPlayer*)
{
    beginProcessingMediaPlayerCallback();

    setReadyState(m_player->readyState());

    endProcessingMediaPlayerCallback();
}

void HTMLMediaElement::setReadyState(MediaPlayer::ReadyState state)
{
    // Set "wasPotentiallyPlaying" BEFORE updating m_readyState, potentiallyPlaying() uses it
    bool wasPotentiallyPlaying = potentiallyPlaying();

    ReadyState oldState = m_readyState;

// FYMP begin - integrating parts of r152754

/*
    m_readyState = static_cast<ReadyState>(state);
    if (m_readyState == oldState)
        return; 
*/

	ReadyState newState = static_cast<ReadyState>(state);

#if ENABLE(VIDEO_TRACK)
    bool bNoTracksUsed = m_textTracksWhenResourceSelectionBegan.size() == 0;
    bool tracksAreReady = textTracksAreReady();

    if (newState == oldState && m_tracksAreReady == tracksAreReady)
        return;
 
    m_tracksAreReady = tracksAreReady;
	
	#ifdef DOES_THIS_FIX_CCPARSINGBUG_20131007
	
	// If tracks are not needed, we have default behaviour any all is good
	if(bNoTracksUsed)
		{
        m_readyState = newState;
		}
	else
		{
		// If tracks are ready, we are also fine
		if(tracksAreReady)
			{
			m_readyState = newState;
			}
		else
			{
			
			// No tracks ready here, but we HAVE tracks!			

			// If a media file has text tracks the readyState may not progress beyond HAVE_META_DATA until
			// the text tracks are ready, regardless of the state of the media file.
			if(newState > HAVE_METADATA)
				{
				NN_LOG("*** HTMLMediaElement::setReadyState clamped to HAVE_METADATA (wanted: %d)\n", (int)newState);

				// New state would trigger a "canplay", but text tracks are not valid. CLAMP to max allowed state
				newState = HAVE_METADATA;
				}
				
			// Did we already see this new 
			if(newState == oldState)
				{
				return;
				}
				
			// Proceedee with the new state
			m_readyState = newState;
			}
		}
	
	#else	
	
    if (tracksAreReady)
        m_readyState = newState;
    else {
        // If a media file has text tracks the readyState may not progress beyond HAVE_FUTURE_DATA until
        // the text tracks are ready, regardless of the state of the media file.
        if (newState <= HAVE_METADATA)
            m_readyState = newState;
        else
            m_readyState = HAVE_CURRENT_DATA;
		}
	#endif

#else
    if (newState == oldState)
        return;
		
    m_readyState = newState;
#endif

// FYMP end

    if (oldState > m_readyStateMaximum)
        m_readyStateMaximum = oldState;

    if (m_networkState == NETWORK_EMPTY)
        return;

    if (m_seeking) {
        // 4.8.10.10, step 8
        if (wasPotentiallyPlaying && m_readyState < HAVE_FUTURE_DATA)
            scheduleEvent(eventNames().waitingEvent);

        // 4.8.10.10, step 9
        if (m_readyState < HAVE_CURRENT_DATA) {
            if (oldState >= HAVE_CURRENT_DATA)
                scheduleEvent(eventNames().seekingEvent);
        } else {
            // 4.8.10.10 step 12 & 13.
            finishSeek();
        }

    } else {
        if (wasPotentiallyPlaying && m_readyState < HAVE_FUTURE_DATA) {
            // 4.8.10.9
            scheduleTimeupdateEvent(false);
            scheduleEvent(eventNames().waitingEvent);
        }
    }

    if (m_readyState >= HAVE_METADATA && oldState < HAVE_METADATA) {
        scheduleEvent(eventNames().durationchangeEvent);
        scheduleEvent(eventNames().loadedmetadataEvent);

#if !ENABLE(PLUGIN_PROXY_FOR_VIDEO)
        if (renderer() && renderer()->isVideo()) {
            toRenderVideo(renderer())->videoSizeChanged();
        }
#endif
        m_delayingTheLoadEvent = false;
        m_player->seek(0);
    }

    bool shouldUpdatePosterImage = false;

    // 4.8.10.7 says loadeddata is sent only when the new state *is* HAVE_CURRENT_DATA: "If the
    // previous ready state was HAVE_METADATA and the new ready state is HAVE_CURRENT_DATA",
    // but the event table at the end of the spec says it is sent when: "readyState newly
    // increased to HAVE_CURRENT_DATA  or greater for the first time"
    // We go with the later because it seems useful to count on getting this event
    if (m_readyState >= HAVE_CURRENT_DATA && oldState < HAVE_CURRENT_DATA && !m_haveFiredLoadedData) {
        m_haveFiredLoadedData = true;
        shouldUpdatePosterImage = true;
        scheduleEvent(eventNames().loadeddataEvent);
    }

    bool isPotentiallyPlaying = potentiallyPlaying();
    if (m_readyState == HAVE_FUTURE_DATA && oldState <= HAVE_CURRENT_DATA) {
        scheduleEvent(eventNames().canplayEvent);
        if (isPotentiallyPlaying)
            scheduleEvent(eventNames().playingEvent);
        shouldUpdatePosterImage = true;
    }

    if (m_readyState == HAVE_ENOUGH_DATA && oldState < HAVE_ENOUGH_DATA) {
        if (oldState <= HAVE_CURRENT_DATA)
            scheduleEvent(eventNames().canplayEvent);

        scheduleEvent(eventNames().canplaythroughEvent);

        if (isPotentiallyPlaying && oldState <= HAVE_CURRENT_DATA)
            scheduleEvent(eventNames().playingEvent);

        if (m_autoplaying && m_paused && autoplay()) {
            m_paused = false;
            scheduleEvent(eventNames().playEvent);
            scheduleEvent(eventNames().playingEvent);
        }

        shouldUpdatePosterImage = true;
    }

    if (shouldUpdatePosterImage)
        updatePosterImage();

    updatePlayState();
// FYMP begin - integrating parts of r152754
#if ENABLE(VIDEO_TRACK)
	updateActiveTextTrackCues(currentTime());
#endif
// FYMP end
}

void HTMLMediaElement::progressEventTimerFired(Timer<HTMLMediaElement>*)
{
    ASSERT(m_player);
    if (m_networkState != NETWORK_LOADING)
        return;

    unsigned progress = m_player->bytesLoaded();
    double time = WTF::currentTime();
    double timedelta = time - m_previousProgressTime;

    if (progress == m_previousProgress) {
        if (timedelta > 3.0 && !m_sentStalledEvent) {
            scheduleEvent(eventNames().stalledEvent);
            m_sentStalledEvent = true;
        }
    } else {
        scheduleEvent(eventNames().progressEvent);
        m_previousProgress = progress;
        m_previousProgressTime = time;
        m_sentStalledEvent = false;
        if (renderer())
            renderer()->updateFromElement();
    }
}

void HTMLMediaElement::rewind(float timeDelta)
{
    ExceptionCode e;
    setCurrentTime(max(currentTime() - timeDelta, minTimeSeekable()), e);
}

void HTMLMediaElement::returnToRealtime()
{
    ExceptionCode e;
    setCurrentTime(maxTimeSeekable(), e);
}

void HTMLMediaElement::addPlayedRange(float start, float end)
{
    if (!m_playedTimeRanges)
        m_playedTimeRanges = TimeRanges::create();
    m_playedTimeRanges->add(start, end);
}

bool HTMLMediaElement::supportsSave() const
{
    return m_player ? m_player->supportsSave() : false;
}

void HTMLMediaElement::seek(float time, ExceptionCode& ec)
{
    // 4.8.9.9 Seeking

    // 1 - If the media element's readyState is HAVE_NOTHING, then raise an INVALID_STATE_ERR exception.
    if (m_readyState == HAVE_NOTHING || !m_player) {
        ec = INVALID_STATE_ERR;
        return;
    }

    // Get the current time before setting m_seeking, m_lastSeekTime is returned once it is set.
    float now = currentTime();

    // 3 - Set the seeking IDL attribute to true.
    // The flag will be cleared when the engine tells is the time has actually changed
    m_seeking = true;

    // 4 - Queue a task to fire a simple event named timeupdate at the element.
    scheduleTimeupdateEvent(false);

    // 6 - If the new playback position is later than the end of the media resource, then let it be the end
    // of the media resource instead.
    time = min(time, duration());

    // 7 - If the new playback position is less than the earliest possible position, let it be that position instead.
    float earliestTime = m_player->startTime();
    time = max(time, earliestTime);

    // 8 - If the (possibly now changed) new playback position is not in one of the ranges given in the
    // seekable attribute, then let it be the position in one of the ranges given in the seekable attribute
    // that is the nearest to the new playback position. ... If there are no ranges given in the seekable
    // attribute then set the seeking IDL attribute to false and abort these steps.
    RefPtr<TimeRanges> seekableRanges = seekable();
    if (!seekableRanges->length() || time == now) {
        m_seeking = false;
        return;
    }
    time = seekableRanges->nearest(time);

    if (m_playing) {
        if (m_lastSeekTime < now)
            addPlayedRange(m_lastSeekTime, now);
    }
    m_lastSeekTime = time;
    m_sentEndEvent = false;

    // 9 - Set the current playback position to the given new playback position
    m_player->seek(time);

    // 10-15 are handled, if necessary, when the engine signals a readystate change.

}

void HTMLMediaElement::finishSeek()
{
    // 4.8.10.10 Seeking step 12
    m_seeking = false;

    // 4.8.10.10 Seeking step 13
    scheduleEvent(eventNames().seekedEvent);
}

HTMLMediaElement::ReadyState HTMLMediaElement::readyState() const
{
    return m_readyState;
}

MediaPlayer::MovieLoadType HTMLMediaElement::movieLoadType() const
{
    return m_player ? m_player->movieLoadType() : MediaPlayer::Unknown;
}

bool HTMLMediaElement::hasAudio() const
{
    return m_player ? m_player->hasAudio() : false;
}

bool HTMLMediaElement::seeking() const
{
    return m_seeking;
}

// playback state
float HTMLMediaElement::currentTime() const
{
    if (!m_player)
        return 0;
    if (m_seeking)
        return m_lastSeekTime;
    return m_player->currentTime();
}

void HTMLMediaElement::setCurrentTime(float time, ExceptionCode& ec)
{
    seek(time, ec);
}

float HTMLMediaElement::startTime() const
{
    if (!m_player)
        return 0;
    return m_player->startTime();
}

float HTMLMediaElement::duration() const
{
    if (m_player && m_readyState >= HAVE_METADATA)
        return m_player->duration();

    return numeric_limits<float>::quiet_NaN();
}

bool HTMLMediaElement::paused() const
{
    return m_paused;
}

float HTMLMediaElement::defaultPlaybackRate() const
{
    return m_defaultPlaybackRate;
}

void HTMLMediaElement::setDefaultPlaybackRate(float rate)
{
    if (m_defaultPlaybackRate != rate) {
        m_defaultPlaybackRate = rate;
        scheduleEvent(eventNames().ratechangeEvent);
    }
}

float HTMLMediaElement::playbackRate() const
{
    return m_player ? m_player->rate() : 0;
}

void HTMLMediaElement::setPlaybackRate(float rate)
{
    if (m_playbackRate != rate) {
        m_playbackRate = rate;
        scheduleEvent(eventNames().ratechangeEvent);
    }
    if (m_player && potentiallyPlaying() && m_player->rate() != rate)
        m_player->setRate(rate);
}

bool HTMLMediaElement::webkitPreservesPitch() const
{
    return m_webkitPreservesPitch;
}

void HTMLMediaElement::setWebkitPreservesPitch(bool preservesPitch)
{
    m_webkitPreservesPitch = preservesPitch;

    if (!m_player)
        return;

    m_player->setPreservesPitch(preservesPitch);
}

bool HTMLMediaElement::ended() const
{
    // 4.8.10.8 Playing the media resource
    // The ended attribute must return true if the media element has ended
    // playback and the direction of playback is forwards, and false otherwise.
    return endedPlayback() && m_playbackRate > 0;
}

bool HTMLMediaElement::autoplay() const
{
    return hasAttribute(autoplayAttr);
}

void HTMLMediaElement::setAutoplay(bool b)
{
    setBooleanAttribute(autoplayAttr, b);
}

String HTMLMediaElement::preload() const
{
    switch (m_preload) {
    case MediaPlayer::None:
        return "none";
        break;
    case MediaPlayer::MetaData:
        return "metadata";
        break;
    case MediaPlayer::Auto:
        return "auto";
        break;
    }

    ASSERT_NOT_REACHED();
    return String();
}

void HTMLMediaElement::setPreload(const String& preload)
{
    setAttribute(preloadAttr, preload);
}

void HTMLMediaElement::play(bool isUserGesture)
{
    if (m_restrictions & RequireUserGestureForRateChangeRestriction && !isUserGesture)
        return;

    Document* doc = document();
    Settings* settings = doc->settings();
    if (settings && settings->needsSiteSpecificQuirks() && m_dispatchingCanPlayEvent && !m_loadInitiatedByUserGesture) {
        // It should be impossible to be processing the canplay event while handling a user gesture
        // since it is dispatched asynchronously.
        ASSERT(!isUserGesture);
        String host = doc->baseURL().host();
        if (host.endsWith(".npr.org", false) || equalIgnoringCase(host, "npr.org"))
            return;
    }

    playInternal();
}

void HTMLMediaElement::playInternal()
{
    // 4.8.10.9. Playing the media resource
    if (!m_player || m_networkState == NETWORK_EMPTY)
        scheduleLoad();

    if (endedPlayback()) {
        ExceptionCode unused;
        seek(0, unused);
    }

    setPlaybackRate(defaultPlaybackRate());

    if (m_paused) {
        m_paused = false;
        scheduleEvent(eventNames().playEvent);

        if (m_readyState <= HAVE_CURRENT_DATA)
            scheduleEvent(eventNames().waitingEvent);
        else if (m_readyState >= HAVE_FUTURE_DATA)
            scheduleEvent(eventNames().playingEvent);
    }
    m_autoplaying = false;

    updatePlayState();
}

void HTMLMediaElement::pause(bool isUserGesture)
{
    if (m_restrictions & RequireUserGestureForRateChangeRestriction && !isUserGesture)
        return;

    pauseInternal();
}


void HTMLMediaElement::pauseInternal()
{
    // 4.8.10.9. Playing the media resource
    if (!m_player || m_networkState == NETWORK_EMPTY)
        scheduleLoad();

    m_autoplaying = false;

    if (!m_paused) {
        m_paused = true;
        scheduleTimeupdateEvent(false);
        scheduleEvent(eventNames().pauseEvent);
    }

    updatePlayState();
}

bool HTMLMediaElement::loop() const
{
    return hasAttribute(loopAttr);
}

void HTMLMediaElement::setLoop(bool b)
{
    setBooleanAttribute(loopAttr, b);
}

bool HTMLMediaElement::controls() const
{
    Frame* frame = document()->frame();

    // always show controls when scripting is disabled
    if (frame && !frame->script()->canExecuteScripts(NotAboutToExecuteScript))
        return true;

    return hasAttribute(controlsAttr);
}

void HTMLMediaElement::setControls(bool b)
{
    setBooleanAttribute(controlsAttr, b);
}

float HTMLMediaElement::volume() const
{
    return m_volume;
}

void HTMLMediaElement::setVolume(float vol, ExceptionCode& ec)
{
    if (vol < 0.0f || vol > 1.0f) {
        ec = INDEX_SIZE_ERR;
        return;
    }

    if (m_volume != vol) {
        m_volume = vol;
        updateVolume();
        scheduleEvent(eventNames().volumechangeEvent);
    }
}

bool HTMLMediaElement::muted() const
{
    return m_muted;
}

void HTMLMediaElement::setMuted(bool muted)
{
    if (m_muted != muted) {
        m_muted = muted;
        // Avoid recursion when the player reports volume changes.
        if (!processingMediaPlayerCallback()) {
            if (m_player) {
                m_player->setMuted(m_muted);
                if (renderer())
                    renderer()->updateFromElement();
            } else
                updateVolume();
        }
        scheduleEvent(eventNames().volumechangeEvent);
    }
}

void HTMLMediaElement::togglePlayState()
{
    // We can safely call the internal play/pause methods, which don't check restrictions, because
    // this method is only called from the built-in media controller
    if (canPlay())
        playInternal();
    else
        pauseInternal();
}

void HTMLMediaElement::beginScrubbing()
{
    if (!paused()) {
        if (ended()) {
            // Because a media element stays in non-paused state when it reaches end, playback resumes
            // when the slider is dragged from the end to another position unless we pause first. Do
            // a "hard pause" so an event is generated, since we want to stay paused after scrubbing finishes.
            pause(processingUserGesture());
        } else {
            // Not at the end but we still want to pause playback so the media engine doesn't try to
            // continue playing during scrubbing. Pause without generating an event as we will
            // unpause after scrubbing finishes.
            setPausedInternal(true);
        }
    }
}

void HTMLMediaElement::endScrubbing()
{
    if (m_pausedInternal)
        setPausedInternal(false);
}

// The spec says to fire periodic timeupdate events (those sent while playing) every
// "15 to 250ms", we choose the slowest frequency
static const double maxTimeupdateEventFrequency = 0.25;

void HTMLMediaElement::startPlaybackProgressTimer()
{
    if (m_playbackProgressTimer.isActive())
        return;

    m_previousProgressTime = WTF::currentTime();
    m_previousProgress = 0;
    m_playbackProgressTimer.startRepeating(maxTimeupdateEventFrequency);
}

void HTMLMediaElement::playbackProgressTimerFired(Timer<HTMLMediaElement>*)
{
    ASSERT(m_player);
    if (!m_playbackRate)
        return;

    scheduleTimeupdateEvent(true);

// FYMP begin - integrating parts of r152754
#if ENABLE(VIDEO_TRACK)
	updateActiveTextTrackCues(currentTime());
#endif
// FYMP end

}

void HTMLMediaElement::scheduleTimeupdateEvent(bool periodicEvent)
{
    double now = WTF::currentTime();
    double timedelta = now - m_lastTimeUpdateEventWallTime;

    // throttle the periodic events
    if (periodicEvent && timedelta < maxTimeupdateEventFrequency)
        return;

    // Some media engines make multiple "time changed" callbacks at the same time, but we only want one
    // event at a given time so filter here
    float movieTime = m_player ? m_player->currentTime() : 0;
    if (movieTime != m_lastTimeUpdateEventMovieTime) {
        scheduleEvent(eventNames().timeupdateEvent);
        m_lastTimeUpdateEventWallTime = now;
        m_lastTimeUpdateEventMovieTime = movieTime;
    }
}

bool HTMLMediaElement::canPlay() const
{
    return paused() || ended() || m_readyState < HAVE_METADATA;
}

float HTMLMediaElement::percentLoaded() const
{
    if (!m_player)
        return 0;
    float duration = m_player->duration();

    if (!duration || isinf(duration))
        return 0;

    float buffered = 0;
    RefPtr<TimeRanges> timeRanges = m_player->buffered();
    for (unsigned i = 0; i < timeRanges->length(); ++i) {
        ExceptionCode ignoredException;
        float start = timeRanges->start(i, ignoredException);
        float end = timeRanges->end(i, ignoredException);
        buffered += end - start;
    }
    return buffered / duration;
}

// FYMP begin - integrated TextTracks from r152754
#if ENABLE(VIDEO_TRACK)

/* FYWEBKITMOD BEGIN we dont use inband tracks
void HTMLMediaElement::mediaPlayerDidAddTextTrack(PassRefPtr<InbandTextTrackPrivate> prpTrack)
{   
    // 4.8.10.12.2 Sourcing in-band text tracks
    // 1. Associate the relevant data with a new text track and its corresponding new TextTrack object.
    RefPtr<InbandTextTrack> textTrack = InbandTextTrack::create(ActiveDOMObject::scriptExecutionContext(), this, prpTrack);
    
    // 2. Set the new text track's kind, label, and language based on the semantics of the relevant data,
    // as defined by the relevant specification. If there is no label in that data, then the label must
    // be set to the empty string.
    // 3. Associate the text track list of cues with the rules for updating the text track rendering appropriate
    // for the format in question.
    // 4. If the new text track's kind is metadata, then set the text track in-band metadata track dispatch type
    // as follows, based on the type of the media resource:
    // 5. Populate the new text track's list of cues with the cues parsed so far, folllowing the guidelines for exposing
    // cues, and begin updating it dynamically as necessary.
    //   - Thess are all done by the media engine.
    
    // 6. Set the new text track's readiness state to loaded.
    textTrack->setReadinessState(TextTrack::Loaded);
    
    // 7. Set the new text track's mode to the mode consistent with the user's preferences and the requirements of
    // the relevant specification for the data.
    //  - This will happen in configureTextTracks()
    scheduleDelayedAction(ConfigureTextTracks);
    
    // 8. Add the new text track to the media element's list of text tracks.
    // 9. Fire an event with the name addtrack, that does not bubble and is not cancelable, and that uses the TrackEvent
    // interface, with the track attribute initialized to the text track's TextTrack object, at the media element's
    // textTracks attribute's TextTrackList object.
    addTextTrack(textTrack.release());
}

void HTMLMediaElement::mediaPlayerDidRemoveTextTrack(PassRefPtr<InbandTextTrackPrivate> prpTrack)
{
    prpTrack->willBeRemoved();
}
FYWEBKITMOD END */

#if USE(PLATFORM_TEXT_TRACK_MENU)
void HTMLMediaElement::setSelectedTextTrack(PassRefPtr<PlatformTextTrack> platformTrack)
{
    if (!m_textTracks)
        return;

    TrackDisplayUpdateScope scope(this);

    if (!platformTrack) {
        setSelectedTextTrack(TextTrack::captionMenuOffItem());
        return;
    }

    TextTrack* textTrack;
    if (platformTrack == PlatformTextTrack::captionMenuOffItem())
        textTrack = TextTrack::captionMenuOffItem();
    else if (platformTrack == PlatformTextTrack::captionMenuAutomaticItem())
        textTrack = TextTrack::captionMenuAutomaticItem();
    else {
        size_t i;
        for (i = 0; i < m_textTracks->length(); ++i) {
            textTrack = m_textTracks->item(i);
            
            if (textTrack->platformTextTrack() == platformTrack)
                break;
        }
        if (i == m_textTracks->length())
            return;
    }

    setSelectedTextTrack(textTrack);
}

Vector<RefPtr<PlatformTextTrack> > HTMLMediaElement::platformTextTracks()
{
    if (!m_textTracks || !m_textTracks->length())
        return Vector<RefPtr<PlatformTextTrack> >();
    
    Vector<RefPtr<PlatformTextTrack> > platformTracks;
    for (size_t i = 0; i < m_textTracks->length(); ++i)
        platformTracks.append(m_textTracks->item(i)->platformTextTrack());
    
    return platformTracks;
}

void HTMLMediaElement::notifyMediaPlayerOfTextTrackChanges()
{
    if (!m_textTracks || !m_textTracks->length() || !platformTextTrackMenu())
        return;
    
    m_platformMenu->tracksDidChange();
}

PlatformTextTrackMenuInterface* HTMLMediaElement::platformTextTrackMenu()
{
    if (m_platformMenu)
        return m_platformMenu.get();

    if (!m_player || !m_player->implementsTextTrackControls())
        return 0;

    m_platformMenu = m_player->textTrackMenu();
    if (!m_platformMenu)
        return 0;

    m_platformMenu->setClient(this);

    return m_platformMenu.get();
}
#endif // #if USE(PLATFORM_TEXT_TRACK_MENU)
    
void HTMLMediaElement::closeCaptionTracksChanged()
{
#if ENABLE(ENABLE_TEXTTRACK_RENDERING) // FYWEBKITMOD marking render related stuff. Note, that ENABLE_TEXTTRACK_RENDERING is always DISABLED!
    if (hasMediaControls())
        mediaControls()->closedCaptionTracksChanged();
#endif

#if USE(PLATFORM_TEXT_TRACK_MENU)
    if (m_player && m_player->implementsTextTrackControls())
        scheduleDelayedAction(TextTrackChangesNotification);
#endif
}


/* FYWEBKITMOD BEGIN not used
void HTMLMediaElement::closeCaptionTracksChanged()
{
    if (hasMediaControls())
        mediaControls()->closedCaptionTracksChanged();

#if USE(PLATFORM_TEXT_TRACK_MENU)
    if (m_player && m_player->implementsTextTrackControls())
        scheduleDelayedAction(TextTrackChangesNotification);
#endif
}
FYWEBKITMOD END */

void HTMLMediaElement::addTextTrack(PassRefPtr<TextTrack> track)
{
    textTracks()->append(track);

    closeCaptionTracksChanged();
}

void HTMLMediaElement::removeTextTrack(TextTrack* track)
{
    TrackDisplayUpdateScope scope(this);
    TextTrackCueList* cues = track->cues();
    if (cues)
        textTrackRemoveCues(track, cues);
    track->clearClient();
    m_textTracks->remove(track);

    closeCaptionTracksChanged();
}

/* FYWEBKITMOD BEGIN we dont use inband tracks
void HTMLMediaElement::removeAllInbandTracks()
{
    while (m_audioTracks &&  m_audioTracks->length())
        removeAudioTrack(m_audioTracks->lastItem());

    if (m_textTracks) {
        TrackDisplayUpdateScope scope(this);
        for (int i = m_textTracks->length() - 1; i >= 0; --i) {
            TextTrack* track = m_textTracks->item(i);

            if (track->trackType() == TextTrack::InBand)
                removeTextTrack(track);
        }
    }

    while (m_videoTracks &&  m_videoTracks->length())
        removeVideoTrack(m_videoTracks->lastItem());
}
FYWEBKITMOD END */

PassRefPtr<TextTrack> HTMLMediaElement::addTextTrack(const String& kind, const String& label, const String& language, ExceptionCode& ec)
{
    // 4.8.10.12.4 Text track API
    // The addTextTrack(kind, label, language) method of media elements, when invoked, must run the following steps:

    // 1. If kind is not one of the following strings, then throw a SyntaxError exception and abort these steps
    if (!TextTrack::isValidKindKeyword(kind)) {
        ec = SYNTAX_ERR;
        return 0;
    }

    // 2. If the label argument was omitted, let label be the empty string.
    // 3. If the language argument was omitted, let language be the empty string.
    // 4. Create a new TextTrack object.

    // 5. Create a new text track corresponding to the new object, and set its text track kind to kind, its text 
    // track label to label, its text track language to language...
    RefPtr<TextTrack> textTrack = TextTrack::create(ActiveDOMObject::scriptExecutionContext(), this, kind, label, language);

    // Note, due to side effects when changing track parameters, we have to
    // first append the track to the text track list.

    // 6. Add the new text track to the media element's list of text tracks.
    addTextTrack(textTrack);

    // ... its text track readiness state to the text track loaded state ...
    textTrack->setReadinessState(TextTrack::Loaded);

    // ... its text track mode to the text track hidden mode, and its text track list of cues to an empty list ...
    textTrack->setMode(TextTrack::hiddenKeyword());

    return textTrack.release();
}

TextTrackList* HTMLMediaElement::textTracks() 
{
    if (!m_textTracks)
        m_textTracks = TextTrackList::create(this, ActiveDOMObject::scriptExecutionContext());

    return m_textTracks.get();
}

void HTMLMediaElement::didAddTextTrack(HTMLTrackElement* trackElement)
{
    ASSERT(trackElement->hasTagName(trackTag));

    // 4.8.10.12.3 Sourcing out-of-band text tracks
    // When a track element's parent element changes and the new parent is a media element, 
    // then the user agent must add the track element's corresponding text track to the 
    // media element's list of text tracks ... [continues in TextTrackList::append]
    RefPtr<TextTrack> textTrack = trackElement->track();
    if (!textTrack)
        return;
    
    addTextTrack(textTrack.release());
    
    // Do not schedule the track loading until parsing finishes so we don't start before all tracks
    // in the markup have been added.
    if (!m_parsingInProgress)
        scheduleDelayedAction(ConfigureTextTracks);

#if ENABLE(ENABLE_TEXTTRACK_RENDERING) // FYWEBKITMOD marking render related stuff. Note, that ENABLE_TEXTTRACK_RENDERING is always DISABLED!
    if (hasMediaControls())
        mediaControls()->closedCaptionTracksChanged();
#endif
}

void HTMLMediaElement::didRemoveTextTrack(HTMLTrackElement* trackElement)
{
    ASSERT(trackElement->hasTagName(trackTag));

#if !LOG_DISABLED
    if (trackElement->hasTagName(trackTag)) {
        KURL url = trackElement->getNonEmptyURLAttribute(srcAttr);
    }
#endif

    RefPtr<TextTrack> textTrack = trackElement->track();
    if (!textTrack)
        return;
    
    textTrack->setHasBeenConfigured(false);

    if (!m_textTracks)
        return;
    
    // 4.8.10.12.3 Sourcing out-of-band text tracks
    // When a track element's parent element changes and the old parent was a media element, 
    // then the user agent must remove the track element's corresponding text track from the 
    // media element's list of text tracks.
    removeTextTrack(textTrack.get());

    size_t index = m_textTracksWhenResourceSelectionBegan.find(textTrack.get());
    if (index != notFound)
        m_textTracksWhenResourceSelectionBegan.remove(index);
}

void HTMLMediaElement::configureTextTrackGroup(const TrackGroup& group)
{
    ASSERT(group.tracks.size());

    Page* page = document()->page();
//    CaptionUserPreferences* captionPreferences = page? page->group().captionPreferences() : 0; FYMP

    // First, find the track in the group that should be enabled (if any).
    Vector<RefPtr<TextTrack> > currentlyEnabledTracks;
    RefPtr<TextTrack> trackToEnable;
    RefPtr<TextTrack> defaultTrack;
    RefPtr<TextTrack> fallbackTrack;
    RefPtr<TextTrack> forcedSubitleTrack;
    int highestTrackScore = 0;
    int highestForcedScore = 0;
    for (size_t i = 0; i < group.tracks.size(); ++i) {
        RefPtr<TextTrack> textTrack = group.tracks[i];

        if (m_processingPreferenceChange && textTrack->mode() == TextTrack::showingKeyword())
            currentlyEnabledTracks.append(textTrack);
/* FYWEBKITMOD BEGIN we dont have captionPreferences */
//        int trackScore = captionPreferences ? captionPreferences->textTrackSelectionScore(textTrack.get(), this) : 0; FYMP
		int trackScore = 0;
//        LOG(Media, "HTMLMediaElement::configureTextTrackGroup -  '%s' track with language '%s' has score %i", textTrack->kind().string().utf8().data(), textTrack->language().string().utf8().data(), trackScore);
/* FYWEBKITMOD END */

        if (trackScore) {

            // * If the text track kind is { [subtitles or captions] [descriptions] } and the user has indicated an interest in having a
            // track with this text track kind, text track language, and text track label enabled, and there is no
            // other text track in the media element's list of text tracks with a text track kind of either subtitles
            // or captions whose text track mode is showing
            // ...
            // * If the text track kind is chapters and the text track language is one that the user agent has reason
            // to believe is appropriate for the user, and there is no other text track in the media element's list of
            // text tracks with a text track kind of chapters whose text track mode is showing
            //    Let the text track mode be showing.
            if (trackScore > highestTrackScore) {
                highestTrackScore = trackScore;
                trackToEnable = textTrack;
            }

            if (!defaultTrack && textTrack->isDefault())
                defaultTrack = textTrack;
            if (!defaultTrack && !fallbackTrack)
                fallbackTrack = textTrack;
            if (textTrack->containsOnlyForcedSubtitles() && trackScore > highestForcedScore) {
                forcedSubitleTrack = textTrack;
                highestForcedScore = trackScore;
            }
        } else if (!group.visibleTrack && !defaultTrack && textTrack->isDefault()) {
            // * If the track element has a default attribute specified, and there is no other text track in the media
            // element's list of text tracks whose text track mode is showing or showing by default
            //    Let the text track mode be showing by default.
            defaultTrack = textTrack;
        }
    }

    if (!trackToEnable && defaultTrack)
        trackToEnable = defaultTrack;

    // If no track matches the user's preferred language, none was marked as 'default', and there is a forced subtitle track
    // in the same language as the language of the primary audio track, enable it.
    if (!trackToEnable && forcedSubitleTrack)
        trackToEnable = forcedSubitleTrack;

    // If no track matches the user's preferred language and non was marked 'default', enable the first track
    // because the user has explicitly stated a preference for this kind of track.
    if (!trackToEnable && fallbackTrack)
        trackToEnable = fallbackTrack;

    if (!defaultTrack && trackToEnable && trackToEnable != fallbackTrack /*&& m_captionDisplayMode != CaptionUserPreferences::AlwaysOn*/) // FYWEBKITMOD we dont have captionPreferences
        m_forcedOrAutomaticSubtitleTrackLanguage = trackToEnable->language();
    else
        m_forcedOrAutomaticSubtitleTrackLanguage = emptyString();
    
    if (currentlyEnabledTracks.size()) {
        for (size_t i = 0; i < currentlyEnabledTracks.size(); ++i) {
            RefPtr<TextTrack> textTrack = currentlyEnabledTracks[i];
            if (textTrack != trackToEnable)
                textTrack->setMode(TextTrack::disabledKeyword());
        }
    }

    if (trackToEnable)
        trackToEnable->setMode(TextTrack::showingKeyword());

    m_processingPreferenceChange = false;
}

void HTMLMediaElement::setSelectedTextTrack(TextTrack* trackToSelect)
{
    TextTrackList* trackList = textTracks();
    if (!trackList || !trackList->length())
        return;

    if (trackToSelect != TextTrack::captionMenuOffItem() && trackToSelect != TextTrack::captionMenuAutomaticItem()) {
        if (!trackList->contains(trackToSelect))
            return;
        
        for (int i = 0, length = trackList->length(); i < length; ++i) {
            TextTrack* track = trackList->item(i);
            if (!trackToSelect || track != trackToSelect)
                track->setMode(TextTrack::disabledKeyword());
            else
                track->setMode(TextTrack::showingKeyword());
        }
    }
/* FYWEBKITMOD BEGIN we dont have captionPreferences */
//    CaptionUserPreferences* captionPreferences = document()->page() ? document()->page()->group().captionPreferences() : 0;
//    if (!captionPreferences)
        return;
/*
    CaptionUserPreferences::CaptionDisplayMode displayMode = captionPreferences->captionDisplayMode();
    if (trackToSelect == TextTrack::captionMenuOffItem())
        displayMode = CaptionUserPreferences::ForcedOnly;
    else if (trackToSelect == TextTrack::captionMenuAutomaticItem())
        displayMode = CaptionUserPreferences::Automatic;
    else {
        displayMode = CaptionUserPreferences::AlwaysOn;
        if (trackToSelect->language().length())
            captionPreferences->setPreferredLanguage(trackToSelect->language());
        
        // Set m_captionDisplayMode here so we don't reconfigure again when the preference changed notification comes through.
        m_captionDisplayMode = displayMode;
    }

    captionPreferences->setCaptionDisplayMode(displayMode);
*/
/* FYWEBKITMOD END */
}

void HTMLMediaElement::configureTextTracks()
{
    TrackGroup captionAndSubtitleTracks(TrackGroup::CaptionsAndSubtitles);
    TrackGroup descriptionTracks(TrackGroup::Description);
    TrackGroup chapterTracks(TrackGroup::Chapter);
    TrackGroup metadataTracks(TrackGroup::Metadata);
    TrackGroup otherTracks(TrackGroup::Other);

    if (!m_textTracks)
        return;

    for (size_t i = 0; i < m_textTracks->length(); ++i) {
        RefPtr<TextTrack> textTrack = m_textTracks->item(i);
        if (!textTrack)
            continue;

        String kind = textTrack->kind();
        TrackGroup* currentGroup;
        if (kind == TextTrack::subtitlesKeyword() || kind == TextTrack::captionsKeyword() || kind == TextTrack::forcedKeyword())
            currentGroup = &captionAndSubtitleTracks;
        else if (kind == TextTrack::descriptionsKeyword())
            currentGroup = &descriptionTracks;
        else if (kind == TextTrack::chaptersKeyword())
            currentGroup = &chapterTracks;
        else if (kind == TextTrack::metadataKeyword())
            currentGroup = &metadataTracks;
        else
            currentGroup = &otherTracks;

        if (!currentGroup->visibleTrack && textTrack->mode() == TextTrack::showingKeyword())
            currentGroup->visibleTrack = textTrack;
        if (!currentGroup->defaultTrack && textTrack->isDefault())
            currentGroup->defaultTrack = textTrack;

        // Do not add this track to the group if it has already been automatically configured
        // as we only want to call configureTextTrack once per track so that adding another 
        // track after the initial configuration doesn't reconfigure every track - only those 
        // that should be changed by the new addition. For example all metadata tracks are 
        // disabled by default, and we don't want a track that has been enabled by script 
        // to be disabled automatically when a new metadata track is added later.
        if (textTrack->hasBeenConfigured())
            continue;
        
        if (textTrack->language().length())
            currentGroup->hasSrcLang = true;
        currentGroup->tracks.append(textTrack);
    }
    
    if (captionAndSubtitleTracks.tracks.size())
        configureTextTrackGroup(captionAndSubtitleTracks);
    if (descriptionTracks.tracks.size())
        configureTextTrackGroup(descriptionTracks);
    if (chapterTracks.tracks.size())
        configureTextTrackGroup(chapterTracks);
    if (metadataTracks.tracks.size())
        configureTextTrackGroup(metadataTracks);
    if (otherTracks.tracks.size())
        configureTextTrackGroup(otherTracks);

#if ENABLE(ENABLE_TEXTTRACK_RENDERING) // FYWEBKITMOD marking render related stuff. Note, that ENABLE_TEXTTRACK_RENDERING is always DISABLED!
    configureTextTrackDisplay();
    if (hasMediaControls())
        mediaControls()->closedCaptionTracksChanged();
#endif
}
#endif // ENABLE(VIDEO_TRACK)
// FYMP end

bool HTMLMediaElement::havePotentialSourceChild()
{
    // Stash the current <source> node so we can restore it after checking
    // to see there is another potential
    HTMLSourceElement* currentSourceNode = m_currentSourceNode;
    KURL nextURL = selectNextSourceChild(0, DoNothing);
    m_currentSourceNode = currentSourceNode;

    return nextURL.isValid();
}

KURL HTMLMediaElement::selectNextSourceChild(ContentType *contentType, InvalidSourceAction actionIfInvalid)
{
    KURL mediaURL;
    Node* node;
    bool lookingForPreviousNode = m_currentSourceNode;
    bool canUse = false;

    for (node = firstChild(); !canUse && node; node = node->nextSibling()) {
        if (!node->hasTagName(sourceTag))
            continue;

        if (lookingForPreviousNode) {
            if (m_currentSourceNode == static_cast<HTMLSourceElement*>(node))
                lookingForPreviousNode = false;
            continue;
        }

        HTMLSourceElement* source = static_cast<HTMLSourceElement*>(node);

        // If candidate does not have a src attribute, or if its src attribute's value is the empty string ... jump down to the failed step below
        mediaURL = source->getNonEmptyURLAttribute(srcAttr);
        if (mediaURL.isEmpty())
            goto check_again;

        if (source->hasAttribute(mediaAttr)) {
            MediaQueryEvaluator screenEval("screen", document()->frame(), renderer() ? renderer()->style() : 0);
            RefPtr<MediaList> media = MediaList::createAllowingDescriptionSyntax(source->media());
            if (!screenEval.eval(media.get()))
                goto check_again;
        }

        if (source->hasAttribute(typeAttr)) {
            if (!MediaPlayer::supportsType(ContentType(source->type())))
                goto check_again;
        }

        // Is it safe to load this url?
        if (!isSafeToLoadURL(mediaURL, actionIfInvalid) || !dispatchBeforeLoadEvent(mediaURL.string()))
            goto check_again;

        // Making it this far means the <source> looks reasonable
        canUse = true;
        if (contentType)
            *contentType = ContentType(source->type());

check_again:
        if (!canUse && actionIfInvalid == Complain)
            source->scheduleErrorEvent();
        m_currentSourceNode = static_cast<HTMLSourceElement*>(node);
    }

    if (!canUse)
        m_currentSourceNode = 0;
    return canUse ? mediaURL : KURL();
}

void HTMLMediaElement::mediaPlayerTimeChanged(MediaPlayer*)
{
// FYMP begin - integrating parts of r152754
#if ENABLE(VIDEO_TRACK)
	updateActiveTextTrackCues(currentTime());
#endif
// FYMP end

    beginProcessingMediaPlayerCallback();

    // Always call scheduleTimeupdateEvent when the media engine reports a time discontinuity,
    // it will only queue a 'timeupdate' event if we haven't already posted one at the current
    // movie time.
    scheduleTimeupdateEvent(false);

    // 4.8.10.10 step 12 & 13.  Needed if no ReadyState change is associated with the seek.
    if (m_readyState >= HAVE_CURRENT_DATA && m_seeking)
        finishSeek();

    float now = currentTime();
    float dur = duration();
    if (!isnan(dur) && dur && now >= dur) {
        if (loop()) {
            ExceptionCode ignoredException;
            m_sentEndEvent = false;
            seek(0, ignoredException);
        } else {
            if (!m_sentEndEvent) {
                m_sentEndEvent = true;
                scheduleEvent(eventNames().endedEvent);
            }
        }
    }
    else
        m_sentEndEvent = false;

    updatePlayState();
    endProcessingMediaPlayerCallback();
}

void HTMLMediaElement::mediaPlayerVolumeChanged(MediaPlayer*)
{
    beginProcessingMediaPlayerCallback();
    if (m_player)
        m_volume = m_player->volume();
    updateVolume();
    endProcessingMediaPlayerCallback();
}

void HTMLMediaElement::mediaPlayerMuteChanged(MediaPlayer*)
{
    beginProcessingMediaPlayerCallback();
    if (m_player)
        setMuted(m_player->muted());
    endProcessingMediaPlayerCallback();
}

void HTMLMediaElement::mediaPlayerDurationChanged(MediaPlayer*)
{
    beginProcessingMediaPlayerCallback();
    scheduleEvent(eventNames().durationchangeEvent);
#if !ENABLE(PLUGIN_PROXY_FOR_VIDEO)
    if (renderer()) {
        renderer()->updateFromElement();
        if (renderer()->isVideo())
            toRenderVideo(renderer())->videoSizeChanged();
    }
#endif
    endProcessingMediaPlayerCallback();
}

void HTMLMediaElement::mediaPlayerRateChanged(MediaPlayer*)
{
    beginProcessingMediaPlayerCallback();
    // Stash the rate in case the one we tried to set isn't what the engine is
    // using (eg. it can't handle the rate we set)
    m_playbackRate = m_player->rate();
    endProcessingMediaPlayerCallback();
}

void HTMLMediaElement::mediaPlayerSawUnsupportedTracks(MediaPlayer*)
{
    // The MediaPlayer came across content it cannot completely handle.
    // This is normally acceptable except when we are in a standalone
    // MediaDocument. If so, tell the document what has happened.
    if (ownerDocument()->isMediaDocument()) {
        MediaDocument* mediaDocument = static_cast<MediaDocument*>(ownerDocument());
        mediaDocument->mediaElementSawUnsupportedTracks();
    }
}

// MediaPlayerPresentation methods
void HTMLMediaElement::mediaPlayerRepaint(MediaPlayer*)
{
    beginProcessingMediaPlayerCallback();
    if (renderer())
        renderer()->repaint();

    updatePosterImage();
    endProcessingMediaPlayerCallback();
}

void HTMLMediaElement::mediaPlayerSizeChanged(MediaPlayer*)
{
    beginProcessingMediaPlayerCallback();
#if !ENABLE(PLUGIN_PROXY_FOR_VIDEO)
    if (renderer() && renderer()->isVideo())
        toRenderVideo(renderer())->videoSizeChanged();
#endif
    endProcessingMediaPlayerCallback();
}

#if USE(ACCELERATED_COMPOSITING)
bool HTMLMediaElement::mediaPlayerRenderingCanBeAccelerated(MediaPlayer*)
{
    if (renderer() && renderer()->isVideo()) {
        ASSERT(renderer()->view());
        return renderer()->view()->compositor()->canAccelerateVideoRendering(toRenderVideo(renderer()));
    }
    return false;
}

void HTMLMediaElement::mediaPlayerRenderingModeChanged(MediaPlayer*)
{
    // Kick off a fake recalcStyle that will update the compositing tree.
    setNeedsStyleRecalc(SyntheticStyleChange);
}
#endif

PassRefPtr<TimeRanges> HTMLMediaElement::buffered() const
{
    if (!m_player)
        return TimeRanges::create();
    return m_player->buffered();
}

PassRefPtr<TimeRanges> HTMLMediaElement::played()
{
    if (m_playing) {
        float time = currentTime();
        if (time > m_lastSeekTime)
            addPlayedRange(m_lastSeekTime, time);
    }

    if (!m_playedTimeRanges)
        m_playedTimeRanges = TimeRanges::create();

    return m_playedTimeRanges->copy();
}

PassRefPtr<TimeRanges> HTMLMediaElement::seekable() const
{
    // FIXME real ranges support
    if (!maxTimeSeekable())
        return TimeRanges::create();
    return TimeRanges::create(minTimeSeekable(), maxTimeSeekable());
}

bool HTMLMediaElement::potentiallyPlaying() const
{
    // "pausedToBuffer" means the media engine's rate is 0, but only because it had to stop playing
    // when it ran out of buffered data. A movie is this state is "potentially playing", modulo the
    // checks in couldPlayIfEnoughData().
    bool pausedToBuffer = m_readyStateMaximum >= HAVE_FUTURE_DATA && m_readyState < HAVE_FUTURE_DATA;
    return (pausedToBuffer || m_readyState >= HAVE_FUTURE_DATA) && couldPlayIfEnoughData();
}

bool HTMLMediaElement::couldPlayIfEnoughData() const
{
    return !paused() && !endedPlayback() && !stoppedDueToErrors() && !pausedForUserInteraction();
}

bool HTMLMediaElement::endedPlayback() const
{
    float dur = duration();
    if (!m_player || isnan(dur))
        return false;

    // 4.8.10.8 Playing the media resource

    // A media element is said to have ended playback when the element's
    // readyState attribute is HAVE_METADATA or greater,
    if (m_readyState < HAVE_METADATA)
        return false;

    // and the current playback position is the end of the media resource and the direction
    // of playback is forwards and the media element does not have a loop attribute specified,
    float now = currentTime();
    if (m_playbackRate > 0)
        return now >= dur && !loop();

    // or the current playback position is the earliest possible position and the direction
    // of playback is backwards
    if (m_playbackRate < 0)
        return now <= 0;

    return false;
}

bool HTMLMediaElement::stoppedDueToErrors() const
{
    if (m_readyState >= HAVE_METADATA && m_error) {
        RefPtr<TimeRanges> seekableRanges = seekable();
        if (!seekableRanges->contain(currentTime()))
            return true;
    }

    return false;
}

bool HTMLMediaElement::pausedForUserInteraction() const
{
//    return !paused() && m_readyState >= HAVE_FUTURE_DATA && [UA requires a decitions from the user]
    return false;
}

float HTMLMediaElement::minTimeSeekable() const
{
    return 0;
}

float HTMLMediaElement::maxTimeSeekable() const
{
    return m_player ? m_player->maxTimeSeekable() : 0;
}

void HTMLMediaElement::updateVolume()
{
    if (!m_player)
        return;

    // Avoid recursion when the player reports volume changes.
    if (!processingMediaPlayerCallback()) {
        Page* page = document()->page();
        float volumeMultiplier = page ? page->mediaVolume() : 1;

        m_player->setMuted(m_muted);
        m_player->setVolume(m_volume * volumeMultiplier);
    }

    if (renderer())
        renderer()->updateFromElement();
}

void HTMLMediaElement::updatePlayState()
{
    if (!m_player)
        return;

    if (m_pausedInternal) {
        if (!m_player->paused())
            m_player->pause();
        m_playbackProgressTimer.stop();
        return;
    }

    bool shouldBePlaying = potentiallyPlaying();
    bool playerPaused = m_player->paused();
    if (shouldBePlaying && playerPaused) {
        // Set rate before calling play in case the rate was set before the media engine wasn't setup.
        // The media engine should just stash the rate since it isn't already playing.
        m_player->setRate(m_playbackRate);
        m_player->play();
        startPlaybackProgressTimer();
        m_playing = true;
    } else if (!shouldBePlaying && !playerPaused) {
        m_player->pause();
        m_playbackProgressTimer.stop();
        m_playing = false;
        float time = currentTime();
        if (time > m_lastSeekTime)
            addPlayedRange(m_lastSeekTime, time);
    } else if (couldPlayIfEnoughData() && playerPaused)
        m_player->prepareToPlay();

    if (renderer())
        renderer()->updateFromElement();
}

void HTMLMediaElement::setPausedInternal(bool b)
{
    m_pausedInternal = b;
    updatePlayState();
}

void HTMLMediaElement::stopPeriodicTimers()
{
    m_progressEventTimer.stop();
    m_playbackProgressTimer.stop();
}

void HTMLMediaElement::userCancelledLoad()
{
    if (m_networkState == NETWORK_EMPTY || m_completelyLoaded)
        return;

    // If the media data fetching process is aborted by the user:

    // 1 - The user agent should cancel the fetching process.
// FYMP begin - integrated from r152754
	clearMediaPlayer(-1);
/*
#if !ENABLE(PLUGIN_PROXY_FOR_VIDEO)
    m_player.clear();
#endif
    stopPeriodicTimers();
*/
// FYMP end

    // 2 - Set the error attribute to a new MediaError object whose code attribute is set to MEDIA_ERR_ABORTED.
    m_error = MediaError::create(MediaError::MEDIA_ERR_ABORTED);

    // 3 - Queue a task to fire a progress event called abort at the media element, in the context
    // of the fetching process started by this instance of this algorithm.
    scheduleEvent(eventNames().abortEvent);

    // 5 - If the media element's readyState attribute has a value equal to HAVE_NOTHING, set the
    // element's networkState attribute to the NETWORK_EMPTY value and queue a task to fire a
    // simple event called emptied at the element. Otherwise, set set the element's networkState
    // attribute to the NETWORK_IDLE value.
    if (m_readyState == HAVE_NOTHING) {
        m_networkState = NETWORK_EMPTY;
        scheduleEvent(eventNames().emptiedEvent);
    }
    else
        m_networkState = NETWORK_IDLE;

    // 6 - Set the element's delaying-the-load-event flag to false. This stops delaying the load event.
    m_delayingTheLoadEvent = false;

    // 7 - Abort the overall resource selection algorithm.
    m_currentSourceNode = 0;

    // Reset m_readyState since m_player is gone.
    m_readyState = HAVE_NOTHING;

// FYMP begin - integrated TextTracks from r152754
#if ENABLE(VIDEO_TRACK)
	updateActiveTextTrackCues(0);
#endif
}

void HTMLMediaElement::clearMediaPlayer(int flags)
{
#if USE(PLATFORM_TEXT_TRACK_MENU)
    if (platformTextTrackMenu()) {
        m_platformMenu->setClient(0);
        m_platformMenu = 0;
    }
#endif

#if ENABLE(VIDEO_TRACK)
//    removeAllInbandTracks(); // FYWEBKITMOD we dont use inband tracks
#endif

#if !ENABLE(PLUGIN_PROXY_FOR_VIDEO)

#if ENABLE(MEDIA_SOURCE)
    setSourceState(MediaSource::closedKeyword());
#endif

    m_player.clear();
#endif
    stopPeriodicTimers();
    m_loadTimer.stop();

    clearFlags(m_pendingActionFlags, flags);
    m_loadState = WaitingForSource;

#if ENABLE(VIDEO_TRACK)
#if ENABLE(ENABLE_TEXTTRACK_RENDERING) // FYWEBKITMOD marking render related stuff. Note, that ENABLE_TEXTTRACK_RENDERING is always DISABLED!
    if (m_textTracks)
        configureTextTrackDisplay();
#endif
#endif
// FYMP end
}

void HTMLMediaElement::documentWillBecomeInactive()
{
    if (m_isFullscreen)
        exitFullscreen();

    m_inActiveDocument = false;
    userCancelledLoad();

    // Stop the playback without generating events
    setPausedInternal(true);

    if (renderer())
        renderer()->updateFromElement();

    stopPeriodicTimers();
    cancelPendingEventsAndCallbacks();
}

void HTMLMediaElement::documentDidBecomeActive()
{
    m_inActiveDocument = true;
    setPausedInternal(false);

    if (m_error && m_error->code() == MediaError::MEDIA_ERR_ABORTED) {
        // Restart the load if it was aborted in the middle by moving the document to the page cache.
        // m_error is only left at MEDIA_ERR_ABORTED when the document becomes inactive (it is set to
        //  MEDIA_ERR_ABORTED while the abortEvent is being sent, but cleared immediately afterwards).
        // This behavior is not specified but it seems like a sensible thing to do.
        ExceptionCode ec;
        load(processingUserGesture(), ec);
    }

    if (renderer())
        renderer()->updateFromElement();
}

void HTMLMediaElement::mediaVolumeDidChange()
{
    updateVolume();
}

IntRect HTMLMediaElement::screenRect()
{
    if (!renderer())
        return IntRect();
    return renderer()->view()->frameView()->contentsToScreen(renderer()->absoluteBoundingBoxRect());
}

void HTMLMediaElement::defaultEventHandler(Event* event)
{
#if ENABLE(PLUGIN_PROXY_FOR_VIDEO)
    RenderObject* r = renderer();
    if (!r || !r->isWidget())
        return;

    Widget* widget = toRenderWidget(r)->widget();
    if (widget)
        widget->handleEvent(event);
#else
    if (renderer() && renderer()->isMedia())
        toRenderMedia(renderer())->forwardEvent(event);
    if (event->defaultHandled())
        return;
    HTMLElement::defaultEventHandler(event);
#endif
}

bool HTMLMediaElement::processingUserGesture() const
{
    Frame* frame = document()->frame();
    FrameLoader* loader = frame ? frame->loader() : 0;

    // return 'true' for safety if we don't know the answer
    return loader ? loader->isProcessingUserGesture() : true;
}

 // FYMP begin - integrating parts of r152754
#if ENABLE(VIDEO_TRACK)
#if ENABLE(ENABLE_TEXTTRACK_RENDERING) // FYWEBKITMOD marking render related stuff. Note, that ENABLE_TEXTTRACK_RENDERING is always DISABLED!
bool HTMLMediaElement::requiresTextTrackRepresentation() const
{
    return m_player ? m_player->requiresTextTrackRepresentation() : 0;
}

void HTMLMediaElement::setTextTrackRepresentation(TextTrackRepresentation* representation)
{
    if (m_player)
        m_player->setTextTrackRepresentation(representation);
}
#endif
#endif
// FYMP end

#if ENABLE(PLUGIN_PROXY_FOR_VIDEO)

void HTMLMediaElement::ensureMediaPlayer()
{
    if (!m_player)
        m_player = MediaPlayer::create(this);
}

void HTMLMediaElement::deliverNotification(MediaPlayerProxyNotificationType notification)
{
    if (notification == MediaPlayerNotificationPlayPauseButtonPressed) {
        togglePlayState();
        return;
    }

    if (m_player)
        m_player->deliverNotification(notification);
}

void HTMLMediaElement::setMediaPlayerProxy(WebMediaPlayerProxy* proxy)
{
    ensureMediaPlayer();
    m_player->setMediaPlayerProxy(proxy);
}

void HTMLMediaElement::getPluginProxyParams(KURL& url, Vector<String>& names, Vector<String>& values)
{
    Frame* frame = document()->frame();
    FrameLoader* loader = frame ? frame->loader() : 0;

    if (isVideo()) {
        String poster = poster();
        if (!poster.isEmpty() && loader) {
            KURL posterURL = loader->completeURL(poster);
            if (posterURL.isValid() && loader->willLoadMediaElementURL(posterURL)) {
                names.append("_media_element_poster_");
                values.append(posterURL.string());
            }
        }
    }

    if (controls()) {
        names.append("_media_element_controls_");
        values.append("true");
    }

    url = src();
    if (!isSafeToLoadURL(url, Complain))
        url = selectNextSourceChild(0, DoNothing);

    m_currentSrc = url.string();
    if (url.isValid() && loader && loader->willLoadMediaElementURL(url)) {
        names.append("_media_element_src_");
        values.append(m_currentSrc);
    }
}

void HTMLMediaElement::createMediaPlayerProxy()
{
    ensureMediaPlayer();

    if (!inDocument() && m_proxyWidget)
        return;
    if (inDocument() && !m_needWidgetUpdate)
        return;

    Frame* frame = document()->frame();
    FrameLoader* loader = frame ? frame->loader() : 0;
    if (!loader)
        return;

    KURL url;
    Vector<String> paramNames;
    Vector<String> paramValues;

    getPluginProxyParams(url, paramNames, paramValues);

    // Hang onto the proxy widget so it won't be destroyed if the plug-in is set to
    // display:none
    m_proxyWidget = loader->subframeLoader()->loadMediaPlayerProxyPlugin(this, url, paramNames, paramValues);
    if (m_proxyWidget)
        m_needWidgetUpdate = false;
}
#endif // ENABLE(PLUGIN_PROXY_FOR_VIDEO)

void HTMLMediaElement::finishParsingChildren()
{
    HTMLElement::finishParsingChildren();
	m_parsingInProgress = false; // FYMP - integrating parts of r152754

    document()->updateStyleIfNeeded();
#if ENABLE(PLUGIN_PROXY_FOR_VIDEO)
    createMediaPlayerProxy();
#endif

// FYMP begin - integrating parts of r152754.
#if ENABLE(VIDEO_TRACK) 
    for (Node* node = firstChild(); node; node = node->nextSibling()) {
        if (node->hasTagName(trackTag)) {
            scheduleDelayedAction(ConfigureTextTracks);
            break;
        }
    }
#endif
// FYMP end
}

void HTMLMediaElement::enterFullscreen()
{
    ASSERT(!m_isFullscreen);
    m_isFullscreen = true;
    if (document() && document()->page()) {
        document()->page()->chrome()->client()->enterFullscreenForNode(this);
        scheduleEvent(eventNames().webkitbeginfullscreenEvent);
    }
}

void HTMLMediaElement::exitFullscreen()
{
    ASSERT(m_isFullscreen);
    m_isFullscreen = false;
    if (document() && document()->page()) {
        document()->page()->chrome()->client()->exitFullscreenForNode(this);
        scheduleEvent(eventNames().webkitendfullscreenEvent);
    }
}

PlatformMedia HTMLMediaElement::platformMedia() const
{
    return m_player ? m_player->platformMedia() : NoPlatformMedia;
}

#if USE(ACCELERATED_COMPOSITING)
PlatformLayer* HTMLMediaElement::platformLayer() const
{
    return m_player ? m_player->platformLayer() : 0;
}
#endif

bool HTMLMediaElement::hasClosedCaptions() const
{
// FYMP begin - integrated parts of r152754
//    return m_player && m_player->hasClosedCaptions();
    if (m_player && m_player->hasClosedCaptions())
        return true;

#if ENABLE(VIDEO_TRACK)
    if (!m_textTracks)
        return false;

    for (unsigned i = 0; i < m_textTracks->length(); ++i) {
        if (m_textTracks->item(i)->readinessState() == TextTrack::FailedToLoad)
            continue;

        if (m_textTracks->item(i)->kind() == TextTrack::captionsKeyword()
            || m_textTracks->item(i)->kind() == TextTrack::subtitlesKeyword())
            return true;
    }
#endif

    return false;
// FYMP end
}

bool HTMLMediaElement::closedCaptionsVisible() const
{
    return m_closedCaptionsVisible;
}

void HTMLMediaElement::setClosedCaptionsVisible(bool closedCaptionVisible)
{
    if (!m_player ||!hasClosedCaptions())
        return;

    m_closedCaptionsVisible = closedCaptionVisible;
    m_player->setClosedCaptionsVisible(closedCaptionVisible);

// FYMP begin - integrated parts r152754
#if ENABLE(VIDEO_TRACK)

#if ENABLE(ENABLE_TEXTTRACK_RENDERING) // FYWEBKITMOD marking render related stuff. Note, that ENABLE_TEXTTRACK_RENDERING is always DISABLED!
		markCaptionAndSubtitleTracksAsUnconfigured(Immediately);
        updateTextTrackDisplay();
#endif
#endif
// FYMP end

    if (renderer())
        renderer()->updateFromElement();
}

void HTMLMediaElement::setWebkitClosedCaptionsVisible(bool visible)
{
    setClosedCaptionsVisible(visible);
}

bool HTMLMediaElement::webkitClosedCaptionsVisible() const
{
    return closedCaptionsVisible();
}


bool HTMLMediaElement::webkitHasClosedCaptions() const
{
    return hasClosedCaptions();
}

void HTMLMediaElement::mediaCanStart()
{
    ASSERT(m_isWaitingUntilMediaCanStart);
    m_isWaitingUntilMediaCanStart = false;
    loadInternal();
}

bool HTMLMediaElement::isURLAttribute(Attribute* attribute) const
{
    return attribute->name() == srcAttr;
}

}

#endif
