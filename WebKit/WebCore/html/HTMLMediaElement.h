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

#ifndef HTMLMediaElement_h
#define HTMLMediaElement_h

#include "WebKit_PRX_Defines.h" // FYWEBKITMOD

#if ENABLE(VIDEO)

#include "HTMLElement.h"
#include "MediaCanStartListener.h"
#include "MediaPlayer.h"

#if ENABLE(PLUGIN_PROXY_FOR_VIDEO)
#include "MediaPlayerProxy.h"
#endif

// FYMP begin - integrating parts of r152754
#if ENABLE(VIDEO_TRACK)
#include "PODIntervalTree.h"
#include "track\TextTrack.h"
#include "track\TextTrackList.h"
#include "track\TextTrackCue.h"
#endif

#include <dom\ActiveDOMObject.h> // FYWEBKITMOD
// FYMP end

namespace WebCore {

class Event;
class HTMLSourceElement;
class HTMLTrackElement; // FYMP - integrating parts of r152754
class MediaError;
class KURL;
class TimeRanges;
#if ENABLE(PLUGIN_PROXY_FOR_VIDEO)
class Widget;
#endif

// FYMP begin - integrating parts of r152754
#if ENABLE(VIDEO_TRACK)
class TextTrackList;

typedef PODIntervalTree<double, TextTrackCue*> CueIntervalTree;
typedef CueIntervalTree::IntervalType CueInterval;
typedef Vector<CueInterval> CueList;
#endif
// FYMP end

// FIXME: The inheritance from MediaPlayerClient here should be private inheritance.
// But it can't be until the Chromium WebMediaPlayerClientImpl class is fixed so it
// no longer depends on typecasting a MediaPlayerClient to an HTMLMediaElement.

class HTMLMediaElement : public HTMLElement, public MediaPlayerClient, private MediaCanStartListener,
// FYMP begin - integrating parts of r152754
	#if ENABLE(VIDEO_TRACK)
	private TextTrackClient,
	#endif
// FYMP end
	public ActiveDOMObject // FYWEBKITMOD neccessary when integrating parts of r152754
{
public:
    MediaPlayer* player() const { return m_player.get(); }

    virtual bool isVideo() const = 0;
    virtual bool hasVideo() const { return false; }
    virtual bool hasAudio() const;

    void rewind(float timeDelta);
    void returnToRealtime();

    // Eventually overloaded in HTMLVideoElement
    virtual bool supportsFullscreen() const { return false; };
    virtual const KURL poster() const { return KURL(); }

    virtual bool supportsSave() const;

    PlatformMedia platformMedia() const;
#if USE(ACCELERATED_COMPOSITING)
    PlatformLayer* platformLayer() const;
#endif

    void scheduleLoad();

// FYMP begin - integrating parts of r152754
    enum DelayedActionType {
        LoadMediaResource = 1 << 0,
        ConfigureTextTracks = 1 << 1,
        TextTrackChangesNotification = 1 << 2,
        ConfigureTextTrackDisplay = 1 << 3,
    };
    void scheduleDelayedAction(DelayedActionType);
// FYMP end

    MediaPlayer::MovieLoadType movieLoadType() const;

    bool inActiveDocument() const { return m_inActiveDocument; }

// DOM API
// error state
    PassRefPtr<MediaError> error() const;

// network state
    KURL src() const;
    void setSrc(const String&);
    String currentSrc() const;

    enum NetworkState { NETWORK_EMPTY, NETWORK_IDLE, NETWORK_LOADING, NETWORK_NO_SOURCE };
    NetworkState networkState() const;

    String preload() const;
    void setPreload(const String&);

    PassRefPtr<TimeRanges> buffered() const;
    void load(bool isUserGesture, ExceptionCode&);
    String canPlayType(const String& mimeType) const;

// ready state
    enum ReadyState { HAVE_NOTHING, HAVE_METADATA, HAVE_CURRENT_DATA, HAVE_FUTURE_DATA, HAVE_ENOUGH_DATA };
    ReadyState readyState() const;
    bool seeking() const;

// playback state
    float currentTime() const;
    void setCurrentTime(float, ExceptionCode&);
    float startTime() const;
    float duration() const;
    bool paused() const;
    float defaultPlaybackRate() const;
    void setDefaultPlaybackRate(float);
    float playbackRate() const;
    void setPlaybackRate(float);
    bool webkitPreservesPitch() const;
    void setWebkitPreservesPitch(bool);
    PassRefPtr<TimeRanges> played();
    PassRefPtr<TimeRanges> seekable() const;
    bool ended() const;
    bool autoplay() const;
    void setAutoplay(bool b);
    bool loop() const;
    void setLoop(bool b);
/* FYWEBKITMOD BEGIN - exporting symbols */
    FYMP_PRXSYM_WEBKIT void play(bool isUserGesture);
    FYMP_PRXSYM_WEBKIT void pause(bool isUserGesture=false); // FYMP - added default value (integrating parts of r152754)
/* FYWEBKITMOD END */

// captions
    bool webkitHasClosedCaptions() const;
    bool webkitClosedCaptionsVisible() const;
    void setWebkitClosedCaptionsVisible(bool);

// controls
    bool controls() const;
    void setControls(bool);
    float volume() const;
    void setVolume(float, ExceptionCode&);
    bool muted() const;
    void setMuted(bool);
    void togglePlayState();
    void beginScrubbing();
    void endScrubbing();

    IntRect screenRect();

    bool canPlay() const;

    float percentLoaded() const;

// FYMP begin - integrating parts of r152754
#if ENABLE(VIDEO_TRACK)
    PassRefPtr<TextTrack> addTextTrack(const String& kind, const String& label, const String& language, ExceptionCode&);
    PassRefPtr<TextTrack> addTextTrack(const String& kind, const String& label, ExceptionCode& ec)
	{
		return addTextTrack(kind, label, emptyString(), ec);
	}
    PassRefPtr<TextTrack> addTextTrack(const String& kind, ExceptionCode& ec)
	{
		return addTextTrack(kind, emptyString(), emptyString(), ec);
	}

	TextTrackList* textTracks();

	CueList currentlyActiveCues() const { return m_currentlyActiveCues; }

	void addTextTrack(PassRefPtr<TextTrack>);
	void removeTextTrack(TextTrack*);
//	void removeAllInbandTracks();              // FYWEBKITMOD we dont use inband-tracks
	void closeCaptionTracksChanged();
    void notifyMediaPlayerOfTextTrackChanges();

    virtual void didAddTextTrack(HTMLTrackElement*);
    virtual void didRemoveTextTrack(HTMLTrackElement*);

//	virtual void mediaPlayerDidAddTextTrack(PassRefPtr<InbandTextTrackPrivate>);    // FYWEBKITMOD we dont use inband-tracks
//	virtual void mediaPlayerDidRemoveTextTrack(PassRefPtr<InbandTextTrackPrivate>); // FYWEBKITMOD we dont use inband-tracks

    struct TrackGroup {
        enum GroupKind { CaptionsAndSubtitles, Description, Chapter, Metadata, Other };

        TrackGroup(GroupKind kind)
            : visibleTrack(0)
            , defaultTrack(0)
            , kind(kind)
            , hasSrcLang(false)
        {
        }

        Vector<RefPtr<TextTrack> > tracks;
        RefPtr<TextTrack> visibleTrack;
        RefPtr<TextTrack> defaultTrack;
        GroupKind kind;
        bool hasSrcLang;
    };

    void configureTextTrackGroupForLanguage(const TrackGroup&) const;
    void configureTextTracks();
    void configureTextTrackGroup(const TrackGroup&);

    void setSelectedTextTrack(TextTrack*);

    bool textTracksAreReady() const;
#if ENABLE(ENABLE_TEXTTRACK_RENDERING) // FYWEBKITMOD marking render related stuff. Note, that ENABLE_TEXTTRACK_RENDERING is always DISABLED!
    void configureTextTrackDisplay();
    void updateTextTrackDisplay();
#endif

    // TextTrackClient (TextTrack instances hold a pointer to their client)
    virtual void textTrackReadyStateChanged(TextTrack*);
    virtual void textTrackKindChanged(TextTrack*);
    virtual void textTrackModeChanged(TextTrack*);
    virtual void textTrackAddCues(TextTrack*, const TextTrackCueList*);
    virtual void textTrackRemoveCues(TextTrack*, const TextTrackCueList*);
    virtual void textTrackAddCue(TextTrack*, PassRefPtr<TextTrackCue>);
    virtual void textTrackRemoveCue(TextTrack*, PassRefPtr<TextTrackCue>);

#if ENABLE(ENABLE_TEXTTRACK_RENDERING) // FYWEBKITMOD marking render related stuff. Note, that ENABLE_TEXTTRACK_RENDERING is always DISABLED!
    bool requiresTextTrackRepresentation() const;
    void setTextTrackRepresentation(TextTrackRepresentation*);
#endif

#endif // #if ENABLE(VIDEO_TRACK)
// FYMP end

#if ENABLE(PLUGIN_PROXY_FOR_VIDEO)
    void allocateMediaPlayerIfNecessary();
    void setNeedWidgetUpdate(bool needWidgetUpdate) { m_needWidgetUpdate = needWidgetUpdate; }
    void deliverNotification(MediaPlayerProxyNotificationType notification);
    void setMediaPlayerProxy(WebMediaPlayerProxy* proxy);
    void getPluginProxyParams(KURL& url, Vector<String>& names, Vector<String>& values);
    virtual void finishParsingChildren();
    void createMediaPlayerProxy();
#endif

	virtual void finishParsingChildren(); // FYMP - integrating parts of r152754

    bool hasSingleSecurityOrigin() const { return !m_player || m_player->hasSingleSecurityOrigin(); }

    bool isFullscreen() const { return m_isFullscreen; }
    void enterFullscreen();
    void exitFullscreen();

    bool hasClosedCaptions() const;
    bool closedCaptionsVisible() const;
    void setClosedCaptionsVisible(bool);

    bool processingUserGesture() const;

protected:	
    HTMLMediaElement(const QualifiedName&, Document*, bool createdByParser); // FYMP: added parameter 'createdByParser' while integrating parts of r152754.
    virtual ~HTMLMediaElement();

    virtual void parseMappedAttribute(Attribute*);
    virtual bool isURLAttribute(Attribute*) const;
    virtual void attach();

    virtual void willMoveToNewOwnerDocument();
    virtual void didMoveToNewOwnerDocument();

// FYMP begin: integrating TextTracks from r152754
#if ENABLE(VIDEO_TRACK)
    bool ignoreTrackDisplayUpdateRequests() const { return m_ignoreTrackDisplayUpdate > 0 || !m_textTracks || !m_cueTree.size(); }
    void beginIgnoringTrackDisplayUpdateRequests();
    void endIgnoringTrackDisplayUpdateRequests();
#endif
// FYMP end

private:
    virtual bool checkDTD(const Node* newChild);
    virtual void attributeChanged(Attribute*, bool preserveDecls);
    virtual bool rendererIsNeeded(RenderStyle*);
    virtual RenderObject* createRenderer(RenderArena*, RenderStyle*);
    virtual void insertedIntoDocument();
    virtual void removedFromDocument();
    virtual void recalcStyle(StyleChange);

    virtual void defaultEventHandler(Event*);

    float getTimeOffsetAttribute(const QualifiedName&, float valueOnError) const;
    void setTimeOffsetAttribute(const QualifiedName&, float value);

    virtual void documentWillBecomeInactive();
    virtual void documentDidBecomeActive();
    virtual void mediaVolumeDidChange();
    virtual void updatePosterImage() { }

    void setReadyState(MediaPlayer::ReadyState);
    void setNetworkState(MediaPlayer::NetworkState);

    virtual Document* mediaPlayerOwningDocument();
    virtual void mediaPlayerNetworkStateChanged(MediaPlayer*);
    virtual void mediaPlayerReadyStateChanged(MediaPlayer*);
    virtual void mediaPlayerTimeChanged(MediaPlayer*);
    virtual void mediaPlayerVolumeChanged(MediaPlayer*);
    virtual void mediaPlayerMuteChanged(MediaPlayer*);
    virtual void mediaPlayerDurationChanged(MediaPlayer*);
    virtual void mediaPlayerRateChanged(MediaPlayer*);
    virtual void mediaPlayerSawUnsupportedTracks(MediaPlayer*);
    virtual void mediaPlayerRepaint(MediaPlayer*);
    virtual void mediaPlayerSizeChanged(MediaPlayer*);
#if USE(ACCELERATED_COMPOSITING)
    virtual bool mediaPlayerRenderingCanBeAccelerated(MediaPlayer*);
    virtual void mediaPlayerRenderingModeChanged(MediaPlayer*);
#endif

    void loadTimerFired(Timer<HTMLMediaElement>*);
    void asyncEventTimerFired(Timer<HTMLMediaElement>*);
    void progressEventTimerFired(Timer<HTMLMediaElement>*);
    void playbackProgressTimerFired(Timer<HTMLMediaElement>*);
    void startPlaybackProgressTimer();
    void startProgressEventTimer();
    void stopPeriodicTimers();

    void seek(float time, ExceptionCode&);
    void finishSeek();
    void checkIfSeekNeeded();
    void addPlayedRange(float start, float end);

    void scheduleTimeupdateEvent(bool periodicEvent);
    void scheduleEvent(const AtomicString& eventName);
	void scheduleEvent(PassRefPtr<Event> e); // FYMP - integrating parts of r152754

    // loading
    void selectMediaResource();
    void loadResource(const KURL&, ContentType&);
    void scheduleNextSourceChild();
    void loadNextSourceChild();
    void userCancelledLoad();
	void clearMediaPlayer(int flags); // FYMP - integrating parts of r152754
    bool havePotentialSourceChild();
    void noneSupported();
    void mediaEngineError(PassRefPtr<MediaError> err);
    void cancelPendingEventsAndCallbacks();
    void waitForSourceChange();

    enum InvalidSourceAction { DoNothing, Complain };
    bool isSafeToLoadURL(const KURL&, InvalidSourceAction);
    KURL selectNextSourceChild(ContentType*, InvalidSourceAction);

// FYMP begin - integrating parts of r152754
    void updateActiveTextTrackCues(double);
    HTMLTrackElement* showingTrackWithSameKind(HTMLTrackElement*) const;

    enum ReconfigureMode {
        Immediately,
        AfterDelay,
    };
    void markCaptionAndSubtitleTracksAsUnconfigured(ReconfigureMode);
// FYMP end

    // These "internal" functions do not check user gesture restrictions.
    void loadInternal();
    void playInternal();
    void pauseInternal();

    void prepareForLoad();

    bool processingMediaPlayerCallback() const { return m_processingMediaPlayerCallback > 0; }
    void beginProcessingMediaPlayerCallback() { ++m_processingMediaPlayerCallback; }
    void endProcessingMediaPlayerCallback() { ASSERT(m_processingMediaPlayerCallback); --m_processingMediaPlayerCallback; }

    void updateVolume();
    void updatePlayState();
    bool potentiallyPlaying() const;
    bool endedPlayback() const;
    bool stoppedDueToErrors() const;
    bool pausedForUserInteraction() const;
    bool couldPlayIfEnoughData() const;

    float minTimeSeekable() const;
    float maxTimeSeekable() const;

    // Pauses playback without changing any states or generating events
    void setPausedInternal(bool);

    virtual void mediaCanStart();

    // Restrictions to change default behaviors. This is effectively a compile time choice at the moment
    // because there are no accessor functions.
    enum BehaviorRestrictions {
        NoRestrictions = 0,
        RequireUserGestureForLoadRestriction = 1 << 0,
        RequireUserGestureForRateChangeRestriction = 1 << 1,
    };

    Timer<HTMLMediaElement> m_loadTimer;
    Timer<HTMLMediaElement> m_asyncEventTimer;
    Timer<HTMLMediaElement> m_progressEventTimer;
    Timer<HTMLMediaElement> m_playbackProgressTimer;
    Vector<RefPtr<Event> > m_pendingEvents;
    RefPtr<TimeRanges> m_playedTimeRanges;

    float m_playbackRate;
    float m_defaultPlaybackRate;
    bool m_webkitPreservesPitch;
    NetworkState m_networkState;
    ReadyState m_readyState;
    ReadyState m_readyStateMaximum;
    String m_currentSrc;

    RefPtr<MediaError> m_error;

    float m_volume;
    float m_lastSeekTime;

    unsigned m_previousProgress;
    double m_previousProgressTime;

    // the last time a timeupdate event was sent (wall clock)
    double m_lastTimeUpdateEventWallTime;

    // the last time a timeupdate event was sent in movie time
    float m_lastTimeUpdateEventMovieTime;

    // loading state
    enum LoadState { WaitingForSource, LoadingFromSrcAttr, LoadingFromSourceElement };
    LoadState m_loadState;
    HTMLSourceElement* m_currentSourceNode;

    OwnPtr<MediaPlayer> m_player;
#if ENABLE(PLUGIN_PROXY_FOR_VIDEO)
    RefPtr<Widget> m_proxyWidget;
#endif

    BehaviorRestrictions m_restrictions;

    MediaPlayer::Preload m_preload;

    bool m_playing;

    // Counter incremented while processing a callback from the media player, so we can avoid
    // calling the media engine recursively.
    int m_processingMediaPlayerCallback;

// FYMP begin - integrating parts of r152754
    typedef unsigned PendingActionFlags;
    PendingActionFlags m_pendingActionFlags;
// FYMP end

    bool m_isWaitingUntilMediaCanStart;

    bool m_processingLoad : 1;
    bool m_delayingTheLoadEvent : 1;
    bool m_haveFiredLoadedData : 1;
    bool m_inActiveDocument : 1;
    bool m_autoplaying : 1;
    bool m_muted : 1;
    bool m_paused : 1;
    bool m_seeking : 1;

    // data has not been loaded since sending a "stalled" event
    bool m_sentStalledEvent : 1;

    // time has not changed since sending an "ended" event
    bool m_sentEndEvent : 1;

    bool m_pausedInternal : 1;

    // Not all media engines provide enough information about a file to be able to
    // support progress events so setting m_sendProgressEvents disables them
    bool m_sendProgressEvents : 1;

    bool m_isFullscreen : 1;
    bool m_closedCaptionsVisible : 1;

#if ENABLE(PLUGIN_PROXY_FOR_VIDEO)
    bool m_needWidgetUpdate : 1;
#endif

    bool m_dispatchingCanPlayEvent : 1;
    bool m_loadInitiatedByUserGesture : 1;
    bool m_completelyLoaded : 1;

// FYMP - integrating parts of r152754
	bool m_parsingInProgress : 1;
#if ENABLE(VIDEO_TRACK)
    bool m_tracksAreReady : 1;
    bool m_haveVisibleTextTrack : 1;
    bool m_processingPreferenceChange : 1;

    String m_forcedOrAutomaticSubtitleTrackLanguage;
    float m_lastTextTrackUpdateTime;

    RefPtr<TextTrackList> m_textTracks;
    Vector<RefPtr<TextTrack> > m_textTracksWhenResourceSelectionBegan;

    CueIntervalTree m_cueTree;

    CueList m_currentlyActiveCues;
    int m_ignoreTrackDisplayUpdate;
#endif

    friend class TrackDisplayUpdateScope;

// FYMP end
};

} //namespace

#endif
#endif
