/*
 * Copyright (C) 2014 FactorY Media Production GmbH
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted.
 *
 * THIS SOFTWARE IS PROVIDED BY FACTORY MEDIA PRODUCTION GMBH AND ITS CONTRIBUTORS "AS IS" AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED.  IN NO EVENT SHALL FACTORY MEDIA PRODUCTION GMBH OR CONTRIBUTORS BE LIABLE FOR ANY 
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF 
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* FYWEBKITMOD BEGIN */

#ifndef MEDIAPLAYERPRIVATEFYMP_H
#define MEDIAPLAYERPRIVATEFYMP_H

#if ENABLE(VIDEO) && PLATFORM(FYMP)

#include "WebKit_PRX_Defines.h"

#include "MediaPlayerPrivate.h"
#include "Timer.h"


class FYwebkitMediaPlayerPrivateImpl;

namespace WebCore {

class GraphicsContext;
class IntSize;
class IntRect;
class String;

class FYMP_PRXSYM_WEBKIT MediaPlayerPrivateFymp : public MediaPlayerPrivateInterface
	{
public:
	static void registerMediaEngine(MediaEngineRegistrar);

	~MediaPlayerPrivateFymp();

    void load(const String& url);
    void cancelLoad();

    void prepareToPlay();

    PlatformMedia platformMedia() const;

#if USE(ACCELERATED_COMPOSITING)
    PlatformLayer* platformLayer() const;
#endif

    void play();
    void pause();

    bool supportsFullscreen() const
		{
		return false;
		}

    IntSize naturalSize() const;

    bool hasVideo() const;
    bool hasAudio() const;

    void setVisible(bool);

    float duration() const;

    float currentTime() const;
    void seek(float time);
    bool seeking() const;

    void setRate(float);
    //virtual void setPreservesPitch(bool) { }

    bool paused() const;
    void setVolume(float);

    bool hasClosedCaptions() const
		{
		return false;
		}
    void setClosedCaptionsVisible(bool)
		{
		}

    MediaPlayer::NetworkState networkState() const;
    MediaPlayer::ReadyState readyState() const;

    float maxTimeSeekable() const;
    PassRefPtr<TimeRanges> buffered() const;

    unsigned bytesLoaded() const;

    void setSize(const IntSize&);

    void paint(GraphicsContext*, const IntRect&);

    void setPreload(MediaPlayer::Preload);

    bool hasAvailableVideoFrame() const
		{
		return readyState() >= MediaPlayer::HaveCurrentData;
		}

#if ENABLE(PLUGIN_PROXY_FOR_VIDEO)
#error No Impl
    virtual void deliverNotification(MediaPlayerProxyNotificationType) = 0;
    virtual void setMediaPlayerProxy(WebMediaPlayerProxy*) = 0;
#endif

#if USE(ACCELERATED_COMPOSITING)
    // whether accelerated rendering is supported by the media engine for the current media.
    bool supportsAcceleratedRendering() const
		{
		return false;
		}
    // called when the rendering system flips the into or out of accelerated rendering mode.
    void acceleratedRenderingStateChanged()
		{
		}
#endif

    bool hasSingleSecurityOrigin() const;

    MediaPlayer::MovieLoadType movieLoadType() const;

#if 0 //USE(ACCELERATED_COMPOSITING)
    // GraphicsLayerClient methods
    virtual void paintContents(const GraphicsLayer*, GraphicsContext&, GraphicsLayerPaintingPhase, const IntRect& inClip);
    virtual void notifyAnimationStarted(const GraphicsLayer*, double time) { }
    virtual void notifySyncRequired(const GraphicsLayer*) { }
    virtual bool showDebugBorders() const { return false; }
    virtual bool showRepaintCounter() const { return false; }

#endif

	/*
		Simple interface to get the currently active media player for direct interaction with it from outside Webkit

		NOTE THAT THIS IS ASSUMING ONLY A SINGLE INSTANCE BEING ACTIVE, WHICH IS -=NOT=- A GIVEN IN GENERAL!
	*/
	static MediaPlayerPrivateFymp *getActivePlayer()	{ return(spActiveInstance); }
	MediaPlayer *getMediaPlayer()						{ return(m_player); }

//private:
public:	// because some compilers have restrictive access rules for inner classes
	MediaPlayerPrivateFymp(MediaPlayer*);
	void workerTimerFunction(WebCore::Timer<MediaPlayerPrivateFymp> *pTimer);

    // engine support
    static MediaPlayerPrivateInterface* create(MediaPlayer*);
    static void getSupportedTypes(HashSet<String>& types);
    static MediaPlayer::SupportsType supportsType(const String& type, const String& codecs);
    static bool isAvailable();

	void openStream();
	bool newReadyState(MediaPlayer::ReadyState newState);
	bool newNetworkState(MediaPlayer::NetworkState newState);

	void loadingFailed();

    void timeChanged();
    void durationChanged();


	friend class FYwebkitMediaPlayerPrivateImpl;

	FYwebkitMediaPlayerPrivateImpl			*mpImpl;
	WebCore::Timer<MediaPlayerPrivateFymp>	*mpWorkerTimer;
	bool									mbErrorOccurred;

	MediaPlayer* 							m_player;
	MediaPlayer::NetworkState				m_networkState;
	MediaPlayer::ReadyState					m_readyState;
	MediaPlayer::Preload					m_preLoadMode;
	float									m_seekTime;
	bool									m_seeking;
	bool									m_paused;
	bool									m_haveMetadata;
	bool									m_bEndReached;

	IntSize									m_size;
	String									m_url;

	// TODO.....
	/*
	Timer<MediaPlayerPrivate> m_seekTimer;
    unsigned m_enabledTrackCount;
    unsigned m_totalTrackCount;
    bool m_hasUnsupportedTracks;
    bool m_startedPlaying;
    bool m_isStreaming;
    bool m_visible;
    bool m_newFrameAvailable;
	*/

	static MediaPlayerPrivateFymp 			*spActiveInstance;
	};

};


#endif
#endif

/* FYWEBKITMOD END */
