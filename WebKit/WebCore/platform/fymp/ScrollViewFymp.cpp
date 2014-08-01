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
/*

	Platform Specific Implementations for Scroll Views

*/

#include "config.h"

#if PLATFORM(FYMP)

#include "ScrollView.h"
#include "FrameView.h"

#include "GraphicsContext.h"
#include "HostWindow.h"
#include "PlatformMouseEvent.h"
#include "PlatformWheelEvent.h"
#include "Scrollbar.h"
#include "ScrollbarTheme.h"
#include <wtf/StdLibExtras.h>

#include "Chrome.h"
#include <Webkit/fymp/ChromeClientFymp.h>

namespace WebCore {

// -------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------
/**
*/
void ScrollView::platformInit()
{
	// fake widget, so we are called. We'll never use it as a pointer...
	setPlatformWidget((void*)0x01);
}

// -------------------------------------------------------------------------------------
/**
*/
void ScrollView::platformDestroy()
{
	// nothing to do
}

// -------------------------------------------------------------------------------------
/**
*/
void ScrollView::platformAddChild(Widget*)
{
	// nothing to do
}

// -------------------------------------------------------------------------------------
/**
*/
void ScrollView::platformRemoveChild(Widget*)
{
	// nothing to do
}

// -------------------------------------------------------------------------------------
/**
*/
void ScrollView::platformSetScrollbarsSuppressed(bool repaintOnUnsuppress)
{
	// we don't have scrollbars. So we don't do anything here...
}

// -------------------------------------------------------------------------------------
/**
*/
void ScrollView::platformSetScrollbarModes()
{
	// we don't have scrollbars. So we don't do anything here...
}

// -------------------------------------------------------------------------------------
/**
*/
void ScrollView::platformScrollbarModes(ScrollbarMode& horizontal, ScrollbarMode& vertical) const
{
	// Just do what the default implenentation does (not that we care)
    horizontal = m_horizontalScrollbarMode;
    vertical = m_verticalScrollbarMode;
}

// -------------------------------------------------------------------------------------
/**
*/
void ScrollView::platformSetCanBlitOnScroll(bool b)
{
	// Just do what the default implenentation does (not that we care)
	m_canBlitOnScroll = b;
}

// -------------------------------------------------------------------------------------
/**
*/
bool ScrollView::platformCanBlitOnScroll() const
{
	// Just do what the default implenentation does (not that we care)
    return m_canBlitOnScroll;
}

// -------------------------------------------------------------------------------------
/**
*/
IntRect ScrollView::platformVisibleContentRect(bool /*includeScrollbars*/) const
{
	// Is this a FrameView?
	if (isFrameView())
	{
		// Yes. Get is access...
		const FrameView *pFrameView = static_cast<const FrameView*>(this);

		// Is this the main frame?
		if (pFrameView->frame() == pFrameView->frame()->page()->mainFrame())
			{
			// Yes...

			/*
				Why this fakery with a "reference size"?

				We want the FrameView to be as big as the content size at all times as we consider
				"all in view" in respect to our tile rendered apporach of using Webkit.

				This collides badly with Webkit's layout engine: It uses the very same metric - the
				size of the FrameView - as guide to layout dynamically laid out content.

				So, if we grow the size of the frame view to keep everything visible as new content
				size change events happen, we also close the door on every shrinking the size down
				again! (Even on page loads!)

				Hence we added a check to tell us if we are called during layout. If so, we report
				a reference size of the view instead of the actual size.

				That actual size is returned at all times during normal use outside the layout...

				(we only do this for the main view - we assume any contained views to - in the end -
				 to be layed out following the main view or explicit sizes. Hence there is no need
				 to fake anything.)
			*/

			// Are we inside the layout code now? If so: return the "reference size" rather then the actual content size...
			if (pFrameView->isInLayout())
				return static_cast<WebKit::ChromeClientFymp*>(pFrameView->frame()->page()->chrome()->client())->getViewReferenceSize();
			}
	}

	// No scrollbars to look out for, just return the rect as is...
	// (note: this is in local space; hence no position! - we assume no scale)
	return IntRect(0, 0, width(), height());
}

// -------------------------------------------------------------------------------------
/**
*/
IntSize ScrollView::platformContentsSize() const
{
	// We don't manipulate the content size. Just give it to the caller...
    return m_contentsSize;
}

// -------------------------------------------------------------------------------------
/**
*/
void ScrollView::platformSetContentsSize()
{
	// content size is already set to m_contentsSize - this is to enable us to update scrollbars etc. -> we don't have any, so we don't do anything
}

// -------------------------------------------------------------------------------------
/**
*/
IntRect ScrollView::platformContentsToScreen(const IntRect& rect) const
{
	// note: we assume there is a "hostWindow" (linked up to Chrome & ChromeClientFymp in the end)
	FYASSERT(hostWindow());
    return hostWindow()->windowToScreen(contentsToWindow(rect));
}

// -------------------------------------------------------------------------------------
/**
*/
IntPoint ScrollView::platformScreenToContents(const IntPoint& point) const
{
	// note: we assume there is a "hostWindow" (linked up to Chrome & ChromeClientFymp in the end)
	FYASSERT(hostWindow());
    return windowToContents(hostWindow()->screenToWindow(point));
}

// -------------------------------------------------------------------------------------
/**
*/
void ScrollView::platformSetScrollPosition(const IntPoint& scrollPoint)
{
	// Send out a notification of this call to our chrome client
	FYASSERT(hostWindow());
	static_cast<WebKit::ChromeClientFymp*>(static_cast<Chrome*>(hostWindow())->client())->notifySetScrollPosition(this, scrollPoint);
}

// -------------------------------------------------------------------------------------
/**
*/
bool ScrollView::platformScroll(ScrollDirection, ScrollGranularity)
{
	// Seems to be used to update the scrollbar positions... we don't have any, so...
    return true;
}

// -------------------------------------------------------------------------------------
/**
*/
void ScrollView::platformRepaintContentRectangle(const IntRect& paintRect, bool bNow)
{
	// note: we assume there is a "hostWindow" (linked up to Chrome & ChromeClientFymp in the end)
	FYASSERT(hostWindow());
    hostWindow()->invalidateContentsAndWindow(contentsToWindow(paintRect), bNow);
}

// -------------------------------------------------------------------------------------
/**
*/
bool ScrollView::platformIsOffscreen() const
{
	// we always assume us to be on-screen!
    return false;
}


// -------------------------------------------------------------------------------------

} // namespace WebCore

#endif // PLATFORM(FYMP)

/* FYWEBKITMOD END */
