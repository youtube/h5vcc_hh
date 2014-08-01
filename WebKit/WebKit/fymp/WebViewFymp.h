#ifndef WebViewFymp_H
#define WebViewFymp_H
// FYMP begin
#include "WebKit_PRX_Defines.h"
// FYMP end

#include <config.h>
#include <IntRect.h>

#include "PassRefPtr.h"

#include <vector>
#include <string>

typedef class PlatformContextSkia PlatformGraphicsContext;
#include "skia/ext/platform_canvas.h"
#include "SkView.h"

#include "ChromeClient.h"

extern "C" {
typedef struct NPObject NPObject;
typedef struct _NPVariant NPVariant;
}

#if PLATFORM(FYMP_VS)
#include "fytypes.h" // maybe better as forced header?
#endif

namespace WebCore {
    FYMP_PRXSYM_WEBKIT void checkSharedTimer();
	FYMP_PRXSYM_WEBKIT long getTimeUntilNextSharedTimer();

    class Frame;
    class Page;
    class GraphicsContext;
    class TextureMapperContentLayer;
	class IntSize;
	class IntPoint;
}

namespace WebKit {

struct WkLoadFailDataFymp
	{
	int			mErrorCode;
	std::string	mFailingURL;
	std::string	mDescription;
	};

struct WkContentSizeChangeFymp
	{
	WebCore::Frame *			mpFrame;
	const WebCore::IntSize *	mpSize;
	};

struct WkProgressInfoFymp
	{
	WebCore::Frame *			mpFrame;
	int							mPercentage;
	};

struct WkSetScrollPositionFymp
	{
	WebCore::Frame *			mpFrame;
	const WebCore::IntPoint *	mpPoint;
	};

struct WkTextInputFymp
	{
	WebCore::Frame *			mpFrame;
	const wchar_t *				mpText;
	const wchar_t *				mpTitle;
	};

struct WkPopUpStateChangeFymp
	{
	WebCore::Frame *					mpFrame;
	WebCore::ChromeClient::PopUpState	mState;
	WebCore::PopupMenuClient*			mpPopUpClient;
	const WebCore::IntRect *			mpRect;
	s32									mIndex;
	};

enum WkEvent {
    LoadFail,						/* data: WkLoadFailDataFymp * */
    WindowClose,
    WindowClear,
    FrameCreate,            		/* data: WebCore::Frame * created */
    ResourceDownloadStart,  		/* data: char * url string */
	ContentSizeChange,				/* data: WkContentSizeChangeFymp */
	SetInputGotFocus,				/* data: WkTextInputInfoFymp */
	SetPwdInputGotFocus,			/* data: WkTextInputInfoFymp */
	LoadCommitted,            		/* data: WebCore::Frame * comitted */
	ProgressStarted,				/* data: WkProgressInfoFymp* */
	ProgressUpdate,					/* data: WkProgressInfoFymp* */
	ProgressFinished,				/* data: WkProgressInfoFymp* */
	FirstLayout,            		/* data: WebCore::Frame * first layout */
	SetScrollPosition,				/* data: WkSetScrollPositionFymp * */
	PopUpMenuState,					/* data: WkPopUpStateChangeFymp * */
};

class WebViewFympListener
{
public:
    virtual ~WebViewFympListener() {}

    virtual void handleWebViewEvent(WkEvent, void* data) {}
    virtual void needRepaint(SkIRect &) {}
    virtual void javaScriptConsoleMessage(const char*, unsigned int, const char*) {}
};

class AccessFilter
{
public:
    virtual ~AccessFilter() {}

    virtual bool allowRequest(const char *url, const char *mimeType) = 0;
    virtual const char *mimeTypeForExt(const char *ext) = 0;
};

class ChromeClientFymp;
class FrameLoaderClientFymp;

struct HeapStatistics
	{
	HeapStatistics(size_t bUsed, size_t bFree, size_t cObjects) : bytesUsed(bUsed), bytesFree(bFree), countObjects(cObjects) {}

	size_t bytesUsed;
	size_t bytesFree;
	size_t countObjects;
	};

struct FYMP_PRXSYM_WEBKIT WebViewConfig
{
	WebViewConfig();

	unsigned		m_cacheMinDeadBytes;
	unsigned		m_cacheMaxDeadBytes;
	unsigned		m_cacheTotalBytes;
	unsigned		m_pageCacheCapacity;
    AccessFilter *	m_requestFilter;
	const wchar_t *	m_pUserAgent;
};

class FYMP_PRXSYM_WEBKIT WebViewFymp : public SkView
{
public:
	static void setConfig(const WebViewConfig & config)		{ s_config = config; }
	static const WebViewConfig & getConfig()				{ return(s_config); }

    static WebViewFymp *create(int screenIndex, int screenWidth, int screenHeight, int viewReferenceWidth, int viewReferenceHeight);
    ~WebViewFymp();

    void addListener(WebViewFympListener *);
    void removeListener(WebViewFympListener *);

    void loadUri(char const *);
    void loadHtml(char const *);
    std::string currentUrl() const;
	void reload(bool bEndToEndReload=false);

    void setOpener(WebViewFymp *pView);
    WebViewFymp* getOpener();

    void setBaseBgColor(SkColor color);
    void repaint(skia::PlatformCanvas*, const SkIRect&);

    void keyDown(char const *, int);
	void keyPress(char const *, int);
    void keyUp(char const *, int);
	void inputString(const wchar_t* text, u32 numChars, bool bDefocus);
    void mouseMove(float, float);
    void mousePress(float, float);
    void mouseRelease(float, float);
    void wheelScroll(float, float, bool up);
	void invalidateClick();

    void syncCompositingState();

    void setCookieJarFileName(const char* cookieJarFileName);
    void setSslCtx(void *sslCtxFunction, void *sslCtxData = NULL);

    void addToJavaScriptWindowObject(WebCore::Frame*, const char *, NPObject*);
    NPVariant evaluateJavaScript(WebCore::Frame*, const char *);

    static AccessFilter *getRequestFilter() { return s_config.m_requestFilter; }
    void disableWebSecurity();

    void collectJavascriptGarbageNow();
    void collectJavascriptGarbageSoon();

	HeapStatistics getHeapStatistics() const;

	WebCore::Page * page() { return m_page; }

	// FYMP: extensions

	void getScreenDimensions(int & w, int & h) const;
    u8 getScreenIndex() const;
	WebCore::IntRect getViewReferenceSize() const;

	void ensureLayout();

protected:
    virtual void onDraw(SkCanvas*);

private:
    friend class ChromeClientFymp;
    friend class EditorClientFymp;
    friend class PlatformLayerFymp;
    friend class FrameLoaderClientFymp;

    void notify(WkEvent, void* data = NULL);
    void notifyRepaint(SkIRect);
    void javaScriptConsoleMessage(const char*, unsigned int, const char*);
    bool canHandleRequest(const char *pUrl, const char *pProtocol, const char *pPath) const;

    SkColor m_baseBgColor;
    WTF::PassRefPtr<WebCore::Frame> m_frame;
	int		m_screenIndex;									//!< screen index
	int		m_screenWidth, m_screenHeight;					//!< Screen size (note: this may not be the actual, physical size! - depends on settings)
	int		m_viewReferenceWidth, m_viewReferenceHeight;	//!< View reference size for layout purposes

    // stuff below is really private; friends, please don't use it.

    WebViewFymp(int screenIndex, int screenWidth, int screenHeight, int viewReferenceWidth, int viewReferenceHeight);

    SkIPoint mousePoint(float x, float y);

    WebViewFymp *m_Opener;

    WebCore::Page *m_page;
    WebCore::GraphicsContext *m_gc;
    PlatformGraphicsContext *m_pgc;
#if USE(ACCELERATED_COMPOSITING)
    WebCore::TextureMapperContentLayer* rootGraphicsLayer;
#endif

    std::vector<WebViewFympListener*>	m_listeners;

	static WebViewConfig				s_config;
};

}

#endif
