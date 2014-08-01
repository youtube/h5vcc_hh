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

#include "config.h"

#if ENABLE(VIDEO) && PLATFORM(FYMP)

#include "WebKit_PRX_Defines.h"

#include "MediaPlayerPrivateFymp.h"
#include "TimeRanges.h"

#include "GraphicsContext.h"

#include <std_Printf.h>
#include <std_Interlocked.h>

using namespace std;

#include <string>
#include <WebkitMediaPlayerImpl.h>


WebCore::MediaPlayerPrivateFymp *	WebCore::MediaPlayerPrivateFymp::spActiveInstance = NULL;






namespace WebCore {


static HashSet<String> mimeTypeCache()
	{
	DEFINE_STATIC_LOCAL(HashSet<String>, cache, ());
	static bool gsbTypeListInitialized = false;

	if(!gsbTypeListInitialized)
		{
		cache.add(String("video/3gpp"));
		//cache.add(String("video/3gpp2"));
		cache.add(String("video/mp4"));
//		cache.add(String("audio/aac"));
		gsbTypeListInitialized = true;
		}
	return cache;
	}

// -------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------

MediaPlayerPrivateInterface* MediaPlayerPrivateFymp::create(MediaPlayer* player)
	{
    return new MediaPlayerPrivateFymp(player);
	}

void MediaPlayerPrivateFymp::getSupportedTypes(HashSet<String>& types)
	{
    types = mimeTypeCache();
	}

bool MediaPlayerPrivateFymp::isAvailable()
	{
	// In this context we assume always available player
	return true;
	}

MediaPlayer::SupportsType MediaPlayerPrivateFymp::supportsType(const String& type, const String& codecs)
	{
    if (type.isNull() || type.isEmpty())
        return MediaPlayer::IsNotSupported;
    // spec says we should not return "probably" if the codecs string is empty
    if (mimeTypeCache().contains(type))
        return codecs.isEmpty() ? MediaPlayer::MayBeSupported : MediaPlayer::IsSupported;
    return MediaPlayer::IsNotSupported;
	}

void MediaPlayerPrivateFymp::registerMediaEngine(MediaEngineRegistrar registrar)
	{
	if (isAvailable())
		registrar(create, getSupportedTypes, supportsType);
	}




void MediaPlayerPrivateFymp::workerTimerFunction(WebCore::Timer<MediaPlayerPrivateFymp> *pTimer)
	{
	if (mpImpl)
		mpImpl->workerTimerFunction();
	}

MediaPlayerPrivateFymp::MediaPlayerPrivateFymp(MediaPlayer *player)
    : m_player(player)
	, m_networkState(MediaPlayer::Empty)
    , m_readyState(MediaPlayer::HaveNothing)
	, m_seeking(false)
	, m_paused(true)		// not autoplaying!
	, m_haveMetadata(false)
	, m_size(IntSize())
	, mbErrorOccurred(false)
	{
	mpImpl = new FYwebkitMediaPlayerPrivateImpl(this);
	mpWorkerTimer = new WebCore::Timer<MediaPlayerPrivateFymp>(this, &MediaPlayerPrivateFymp::workerTimerFunction);
	spActiveInstance = this;
	STDprintf("MediaPlayerPrivateFymp::MediaPlayerPrivateFymp() @ %p (impl @ %p)\n", this, mpImpl);
	}

MediaPlayerPrivateFymp::~MediaPlayerPrivateFymp()
	{
	STDprintf("MediaPlayerPrivateFymp::~MediaPlayerPrivateFymp() @ %p (impl @ %p)\n", this, mpImpl);
	delete mpWorkerTimer;
	FYwebkitMediaPlayerPrivateImpl *pImpl = (FYwebkitMediaPlayerPrivateImpl *)STDinterlockedExchangePointer((void * volatile &)mpImpl, (void *)0);
	spActiveInstance = NULL;
	delete pImpl;
	}

bool MediaPlayerPrivateFymp::newReadyState(MediaPlayer::ReadyState newState)
	{
	bool bRet;
	if (m_readyState == newState)
		{
		bRet = false;
		}
	else
		{
		static const char* _dbgTextReadyState[] = { "HaveNothing", "HaveMetadata", "HaveCurrentData", "HaveFutureData", "HaveEnoughData" };
		STDprintf("MediaPlayerPrivateFymp::newReadyState(): Ready State Changed from %s to %s\n", _dbgTextReadyState[m_readyState], _dbgTextReadyState[newState]);

		m_readyState = newState;
		m_player->readyStateChanged();
		bRet = true;
		}
	return(bRet);
	}

bool MediaPlayerPrivateFymp::newNetworkState(MediaPlayer::NetworkState newState)
	{
	bool bRet;
	if (m_networkState == newState)
		{
		bRet = false;
		}
	else
		{
		static const char* _dbgTextNetworkState[] = { "Empty", "Idle", "Loading", "Loaded", "FormatError", "NetworkError", "DecodeError" };
		STDprintf("MediaPlayerPrivateFymp::newNetworkState(): Network State Changed from %s to %s\n", _dbgTextNetworkState[m_networkState], _dbgTextNetworkState[newState]);

		m_networkState = newState;
		m_player->networkStateChanged();
		bRet = true;
		}
	return(bRet);
	}


void MediaPlayerPrivateFymp::setPreload(MediaPlayer::Preload preLoad)
	{
	STDprintf("MediaPlayerPrivateFymp::setPreload(): Preload '%s'\n", preLoad == MediaPlayer::None ? "none" : preLoad == MediaPlayer::MetaData ? "metadata" : "auto");
	m_preLoadMode = preLoad;
	}

void MediaPlayerPrivateFymp::load(const String& url)
	{
	m_url = url;

    //LOG_VERBOSE(Media, "Load %s", url.utf8().data());
	STDprintf("MediaPlayerPrivateFymp::load(): Load %s\n", url.utf8().data());

	if (m_preLoadMode == MediaPlayer::Auto)
		openStream();
	}


void MediaPlayerPrivateFymp::openStream()
	{
	// Are we already loading or got an error?
	if (m_networkState >= MediaPlayer::Loading)
		return;	// -> Out!

	m_haveMetadata = false;
	m_seeking = false;
	m_bEndReached = false;
	if (mpImpl->Open(m_url.utf8().data()))
		{
		mpWorkerTimer->startRepeating(16.0 / 1000.0);
		newNetworkState(MediaPlayer::Loading);
		newReadyState(MediaPlayer::HaveNothing);
		}
	}


void MediaPlayerPrivateFymp::cancelLoad()
	{
	STDprintf("MediaPlayerPrivateFymp::cancelLoad():\n");
	if (m_networkState < MediaPlayer::Loading || m_networkState == MediaPlayer::Loaded)
		return;

	mpWorkerTimer->stop();
	mpImpl->CancelOpen();

//	lockDataMutex();

	m_haveMetadata = false;
	m_paused = true;
	m_seeking = false;
	m_bEndReached = false;

	newNetworkState(MediaPlayer::Empty);
	newReadyState(MediaPlayer::HaveNothing);

//	unlockDataMutex();
	}

void MediaPlayerPrivateFymp::prepareToPlay()
	{
	STDprintf("MediaPlayerPrivateFymp::prepareToPlay()\n");
	m_seeking = false;
	m_bEndReached = false;
	openStream();
	}

PlatformMedia MediaPlayerPrivateFymp::platformMedia() const
	{
	PlatformMedia p;
	p.type = PlatformMedia::None;
	p.media.gstreamerGWorld = NULL;
    return p;
	}

#if USE(ACCELERATED_COMPOSITING)
PlatformLayer* MediaPlayerPrivateFymp::platformLayer() const
	{
	// In the future we can do something here?
	return 0;
	}
#endif

void MediaPlayerPrivateFymp::play()
	{
	STDprintf("MediaPlayerPrivateFymp::play()\n");
	openStream();
	m_paused = false;
	m_bEndReached = false;
	}

void MediaPlayerPrivateFymp::pause()
	{
	STDprintf("MediaPlayerPrivateFymp::pause()\n");
	m_paused = true;
	}

IntSize MediaPlayerPrivateFymp::naturalSize() const
	{
	// We ignore the size of the video tag here
	// This means: NO paint events
	#if 0
    if (!hasVideo() || m_readyState < MediaPlayer::HaveMetadata)
        return IntSize();
    return IntSize(m_metaData.m_width, m_metaData.m_height);
	#else
       return IntSize();
	#endif
	}

bool MediaPlayerPrivateFymp::hasVideo() const
	{
//	return m_pPlayer && (m_pPlayer->HasVideo() == MEDIAinterface::eYes);
	return true;
	}

bool MediaPlayerPrivateFymp::hasAudio() const
	{
//	return m_pPlayer && (m_pPlayer->HasAudio() == MEDIAinterface::eYes);
	return true;
	}

void MediaPlayerPrivateFymp::setVisible(bool)
	{
	// we assume player is always visible
//	m_bVisible = bVisible;
	}

//-----------------------------------------------------------------------------
/**
 * Returns the total time of the media.
 *
 * @return
 */
float MediaPlayerPrivateFymp::duration() const
	{
	if (mbErrorOccurred)
		return(0.0f);

	f64 dur = mpImpl->Duration();
	return(dur > 0.0 ? dur : numeric_limits<float>::infinity());
	}



//-----------------------------------------------------------------------------
/**
 * Returns the current play time within the media.
 *
 * @return
 */
float MediaPlayerPrivateFymp::currentTime() const
	{
	if (mbErrorOccurred)
		return(0.0f);
	if (m_seeking)
		return(m_seekTime);
	if (m_bEndReached)
		return(duration());

	f64 pos = mpImpl->PlayPos();
	if (pos < 0.0)
		pos = 0.0;
	return(pos);
	}



//-----------------------------------------------------------------------------
/**
 * Seek within the media to a given time.
 *
 * @param _time
 */
void MediaPlayerPrivateFymp::seek(float _time)
	{
	if (mbErrorOccurred)
		return;

	// Can only seek when we have metadata which holds the necessary information.
	if (mpImpl->HaveMetadata())
		{
		f64 time = _time;
		f64 cur = currentTime();
		f64 dur = mpImpl->Duration();
		if (dur < 0.0)
			dur = 0.0;
		if (time < 0.0)
			time = 0.0;
		else if (time > dur)
			time = dur;
		// seek distance not big enough?
		if (abs(time - cur) < 1.0)
			return;

		// Don't issue seeks to the same position in succession.
		if (m_seeking && abs(time - m_seekTime) < 1.0)
			return;

		mpImpl->RequestSeekTo(time);
		m_seeking = true;
		m_seekTime = time;
		m_bEndReached = false;

		STDprintf("MediaPlayerPrivateFymp::seek(%#7.4f):\n", time);
		}
	}

bool MediaPlayerPrivateFymp::seeking() const
	{
    return m_seeking;
	}

void MediaPlayerPrivateFymp::setRate(float)
	{
	// Not supported
	}

bool MediaPlayerPrivateFymp::paused() const
	{
    return m_paused;
	}

void MediaPlayerPrivateFymp::setVolume(float)
	{
	}

MediaPlayer::NetworkState MediaPlayerPrivateFymp::networkState() const
	{
    return(m_networkState);
	}

MediaPlayer::ReadyState MediaPlayerPrivateFymp::readyState() const
	{
    return(m_readyState);
	}



//-----------------------------------------------------------------------------
/**
 * Returns how far into the stream can be seeked.
 *
 * @return
 */
float MediaPlayerPrivateFymp::maxTimeSeekable() const
	{
	if (mbErrorOccurred)
		return(0.0f);
	f64 dur = mpImpl->Duration();
	return(dur > 0.0 ? dur : 0.0f);
	}

PassRefPtr<TimeRanges> MediaPlayerPrivateFymp::buffered() const
	{
    RefPtr<TimeRanges> timeRanges = TimeRanges::create();
// We are not buffering anything, so we can't return any buffered ranges!
	/*
    float loaded = maxTimeLoaded();
	if (!m_errorOccured && !m_isStreaming && loaded > 0)
        timeRanges->add(0, loaded);
	*/
    return timeRanges.release();
	}

unsigned MediaPlayerPrivateFymp::bytesLoaded() const
	{
	return(mpImpl->BytesLoaded());
	}

void MediaPlayerPrivateFymp::setSize(const IntSize& size)
	{
    //if (m_hasUnsupportedTracks || !m_qtMovie || m_size == size)
    //    return;
    m_size = size;
    //m_qtGWorld->setSize(size.width(), size.height());
	}





void MediaPlayerPrivateFymp::loadingFailed()
	{
	mbErrorOccurred = true;
	}


void MediaPlayerPrivateFymp::timeChanged()
	{
	m_player->timeChanged();
	}

void MediaPlayerPrivateFymp::durationChanged()
	{
	m_player->durationChanged();
	}





#if 0
void MediaPlayerPrivateFymp::paintCompleted(GraphicsContext& context, const IntRect& rect)
	{
    m_newFrameAvailable = false;

#if DRAW_FRAME_RATE
    if (m_frameCountWhilePlaying > 10)
		{
        double interval =  m_startedPlaying ? WTF::currentTime() - m_timeStartedPlaying : m_timeStoppedPlaying - m_timeStartedPlaying;
        double frameRate = (m_frameCountWhilePlaying - 1) / interval;
        CGContextRef cgContext = context.platformContext();
        CGRect drawRect = rect;

        char text[8];
        _snprintf(text, sizeof(text), "%1.2f", frameRate);

        static const int fontSize = 25;
        static const int fontCharWidth = 12;
        static const int boxHeight = 25;
        static const int boxBorderWidth = 4;
        drawRect.size.width = boxBorderWidth * 2 + fontCharWidth * strlen(text);
        drawRect.size.height = boxHeight;

        CGContextSaveGState(cgContext);
#if USE(ACCELERATED_COMPOSITING)
        if (m_qtVideoLayer)
            CGContextScaleCTM(cgContext, 1, -1);
        CGContextTranslateCTM(cgContext, rect.width() - drawRect.size.width, m_qtVideoLayer ? -rect.height() : 0);
#else
        CGContextTranslateCTM(cgContext, rect.width() - drawRect.size.width, 0);
#endif
        static const CGFloat backgroundColor[4] = { 0.98, 0.98, 0.82, 0.8 };
        CGContextSetFillColor(cgContext, backgroundColor);
        CGContextFillRect(cgContext, drawRect);

        static const CGFloat textColor[4] = { 0, 0, 0, 1 };
        CGContextSetFillColor(cgContext, textColor);
        CGContextSetTextMatrix(cgContext, CGAffineTransformMakeScale(1, -1));
        CGContextSelectFont(cgContext, "Helvetica", fontSize, kCGEncodingMacRoman);

        CGContextShowTextAtPoint(cgContext, drawRect.origin.x + boxBorderWidth, drawRect.origin.y + boxHeight - boxBorderWidth, text, strlen(text));

        CGContextRestoreGState(cgContext);
		}
#endif
	}
#endif

void MediaPlayerPrivateFymp::paint(GraphicsContext* context, const IntRect& rect)
	{
	// Please see comment at method: MediaPlayerPrivateFymp::naturalSize()
	if (context->paintingDisabled())
        return;

	// SAMPLE FROM GSTREAMER
	#if 0
	if (context->paintingDisabled())
        return;

    if (!m_player->visible())
        return;
    if (!m_buffer)
        return;

    RefPtr<ImageGStreamer> gstImage = ImageGStreamer::createImage(m_buffer);
    if (!gstImage)
        return;

    context->drawImage(reinterpret_cast<Image*>(gstImage->image().get()), sRGBColorSpace,
                       rect, CompositeCopy, false);
	#endif

	// SAMPLE FROM WINDOWS
	#if 0
	#if USE(ACCELERATED_COMPOSITING)
		if (m_qtVideoLayer)
			return;
	#endif

    if (p->paintingDisabled() || !m_qtMovie || m_hasUnsupportedTracks)
        return;
    bool usingTempBitmap = false;
    OwnPtr<GraphicsContext::WindowsBitmap> bitmap;
    HDC hdc = p->getWindowsContext(r);
    if (!hdc) {
        // The graphics context doesn't have an associated HDC so create a temporary
        // bitmap where QTMovieGWorld can draw the frame and we can copy it.
        usingTempBitmap = true;
        bitmap.set(p->createWindowsBitmap(r.size()));
        hdc = bitmap->hdc();

        // FIXME: is this necessary??
        XFORM xform;
        xform.eM11 = 1.0f;
        xform.eM12 = 0.0f;
        xform.eM21 = 0.0f;
        xform.eM22 = 1.0f;
        xform.eDx = -r.x();
        xform.eDy = -r.y();
        SetWorldTransform(hdc, &xform);
    }

    m_qtGWorld->paint(hdc, r.x(), r.y());
    if (usingTempBitmap)
        p->drawWindowsBitmap(bitmap.get(), r.topLeft());
    else
        p->releaseWindowsContext(hdc, r);

    paintCompleted(*p, r);
	#endif
	}

bool MediaPlayerPrivateFymp::hasSingleSecurityOrigin() const
	{
    // We tell to disallow resources that come from different origins so we all media is single origin.
    return true;
	}


MediaPlayer::MovieLoadType MediaPlayerPrivateFymp::movieLoadType() const
	{
//    enum MovieLoadType { Unknown, Download, StoredStream, LiveStream };
	return MediaPlayer::Unknown;
	}

};


#endif

/* FYWEBKITMOD END */

