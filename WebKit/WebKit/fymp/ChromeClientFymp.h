#ifndef ChromeClientFymp_h__
#define ChromeClientFymp_h__

#include "ChromeClient.h"
#include "WebViewFymp.h"
#include "Timer.h"
#include "GraphicsLayer.h"
#include "NotImplemented.h"

namespace WebCore {
class FrameView;
};

namespace WebKit {

class PlatformLayerFymp;

class ChromeClientFymp : public WebCore::ChromeClient
{
public:
    ChromeClientFymp(WebViewFymp *);
    virtual ~ChromeClientFymp();

    virtual void chromeDestroyed();

    virtual void setWindowRect(const WebCore::FloatRect&);
    virtual WebCore::FloatRect windowRect();

    virtual WebCore::FloatRect pageRect();

    virtual float scaleFactor();

    virtual void focus() { breakpoint(); }
    virtual void unfocus() { breakpoint(); }

    virtual bool canTakeFocus(WebCore::FocusDirection);
    virtual void takeFocus(WebCore::FocusDirection);

        virtual void focusedNodeChanged(WebCore::Node*) { breakpoint(); }

    virtual WebCore::Page* createWindow(WebCore::Frame*, const WebCore::FrameLoadRequest&, const WebCore::WindowFeatures&) { breakpoint(); return 0; }
    virtual void show() { breakpoint(); }

    virtual bool canRunModal() { breakpoint(); return false; }
    virtual void runModal() { breakpoint(); }

    virtual void setToolbarsVisible(bool) { breakpoint(); }
    virtual bool toolbarsVisible() { breakpoint(); return false; }

    virtual void setStatusbarVisible(bool) { breakpoint(); }
    virtual bool statusbarVisible() { breakpoint(); return false; }

    virtual void setScrollbarsVisible(bool) { breakpoint(); }
    virtual bool scrollbarsVisible() { breakpoint(); return false; }

    virtual void setMenubarVisible(bool) { breakpoint(); }
    virtual bool menubarVisible() { breakpoint(); return false; }

    virtual void setResizable(bool) { breakpoint(); }

    virtual void addMessageToConsole(WebCore::MessageSource source, WebCore::MessageType type,
                                         WebCore::MessageLevel level, const WebCore::String& message,
                                         unsigned int lineNumber, const WebCore::String& sourceID);

    virtual bool canRunBeforeUnloadConfirmPanel();
    virtual bool runBeforeUnloadConfirmPanel(const WebCore::String&, WebCore::Frame*) { breakpoint(); return true; }

    virtual void closeWindowSoon();

    virtual void runJavaScriptAlert(WebCore::Frame*, const WebCore::String&);
    virtual bool runJavaScriptConfirm(WebCore::Frame*, const WebCore::String&) { breakpoint(); return true; }
    virtual bool runJavaScriptPrompt(WebCore::Frame*, const WebCore::String&, const WebCore::String&, WebCore::String&) { breakpoint(); return true; }
    virtual void setStatusbarText(const WebCore::String&);
    virtual bool shouldInterruptJavaScript();
    virtual bool tabsToLinks() const { breakpoint(); return false; }

    virtual WebCore::IntRect windowResizerRect() const { breakpoint(); return WebCore::IntRect(); }

        virtual void invalidateWindow(const WebCore::IntRect&, bool);
        virtual void invalidateContentsAndWindow(const WebCore::IntRect&, bool);
        virtual void invalidateContentsForSlowScroll(const WebCore::IntRect&, bool);
    virtual void scroll(const WebCore::IntSize&, const WebCore::IntRect&, const WebCore::IntRect&);
        virtual WebCore::IntPoint screenToWindow(const WebCore::IntPoint& p) const { breakpoint(); return p; }
    virtual WebCore::IntRect windowToScreen(const WebCore::IntRect& r) const { breakpoint(); return r; }
    virtual PlatformPageClient platformPageClient() const { breakpoint(); return 0; }
    virtual void scrollbarsModeDidChange() const { breakpoint(); }
    virtual void setCursor(const WebCore::Cursor&) { breakpoint(); }

        virtual void contentsSizeChanged(WebCore::Frame*, const WebCore::IntSize&) const;
    virtual void scrollRectIntoView(const WebCore::IntRect&, const WebCore::ScrollView*) const { breakpoint(); }

    virtual void mouseDidMoveOverElement(const WebCore::HitTestResult&, unsigned) { breakpoint(); }

    virtual void setToolTip(const WebCore::String&, WebCore::TextDirection) { breakpoint(); }

    virtual void print(WebCore::Frame*) { breakpoint(); }

    virtual void didReceiveViewportArguments(WebCore::Frame*, const WebCore::ViewportArguments&) const;

#if ENABLE(DATABASE)
    virtual void exceededDatabaseQuota(WebCore::Frame*, const WebCore::String&) { breakpoint(); }
#endif

#if ENABLE(OFFLINE_WEB_APPLICATIONS)
    virtual void reachedMaxAppCacheSize(int64_t) { breakpoint(); }
#endif

#if USE(ACCELERATED_COMPOSITING)
    virtual void attachRootGraphicsLayer(WebCore::Frame*, WebCore::GraphicsLayer*);
    virtual void setNeedsOneShotDrawingSynchronization();
    virtual void scheduleCompositingLayerSync();
    virtual bool allowsAcceleratedCompositing() const;
#endif

#if ENABLE(NOTIFICATIONS)
    virtual WebCore::NotificationPresenter* notificationPresenter() const { breakpoint(); return 0; }
#endif

    virtual void requestGeolocationPermissionForFrame(WebCore::Frame*, WebCore::Geolocation*) { breakpoint(); }
    virtual void cancelGeolocationPermissionRequestForFrame(WebCore::Frame*, WebCore::Geolocation*) { breakpoint(); }

    virtual void runOpenPanel(WebCore::Frame*, PassRefPtr<WebCore::FileChooser>) { breakpoint(); }
    virtual void chooseIconForFiles(const Vector<WebCore::String>&, WebCore::FileChooser*) { breakpoint(); }

    virtual void formStateDidChange(const WebCore::Node*) { }

    virtual PassOwnPtr<WebCore::HTMLParserQuirks> createHTMLParserQuirks() { return 0; }

	// FYMP: Custom extensions

	void getScreenDimensions(int & w, int & h) const;
	WebCore::IntRect getViewReferenceSize() const;

	void notifySetScrollPosition(WebCore::ScrollView *pScrollView, const WebCore::IntPoint& scrollPoint);

    void setWebView(WebViewFymp *pWebView);
	WebViewFymp *webview() { return m_webView; }

	virtual bool domWindow_fake_innerWidth(WebCore::Frame *pFrame, int & width) const;
	virtual bool domWindow_fake_innerHeight(WebCore::Frame *pFrame, int & height) const;

	virtual void notify_PopUpState(PopUpState state, WebCore::PopupMenuClient* pPopUpClient, const WebCore::IntRect * pRect, WebCore::FrameView* pFrameView, int index);

	virtual int getScreenIndex() const;

private:
    void breakpoint() const { }
    WebViewFymp *m_webView;

#if USE(ACCELERATED_COMPOSITING)
    friend class PlatformLayerFymp;
    void syncLayers(WebCore::Timer<ChromeClientFymp>*);
    PlatformLayerFymp *rootGraphicsLayer;
    WebCore::Timer<ChromeClientFymp> syncTimer;
#endif

};

}

#endif // ChromeClientFymp_h__
