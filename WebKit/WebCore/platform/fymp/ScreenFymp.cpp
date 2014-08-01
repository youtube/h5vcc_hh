/*
 * Copyright (C) 2007 Apple Inc.  All rights reserved.
 * Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies)
 * Copyright (C) 2008 Holger Hans Peter Freyther
 * Copyright (C) 2008 INdT - Instituto Nokia de Tecnologia
 * Copyright (C) 2009-2010 ProFUSION embedded systems
 * Copyright (C) 2009-2010 Samsung Electronics
 * Copyright (C) 2014 FactorY Media Production GmbH
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of Apple Computer, Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* FYWEBKITMOD BEGIN copied over efl\PlatformScreenEfl.cpp and then implemented previous 'notImplemented()' methods resp. changed implementation */

#include "config.h"
#include "PlatformScreen.h"

#include "NotImplemented.h"
#include "PlatformString.h"
#include "Widget.h"
#include "FrameView.h"
#include "Frame.h"
#include "Page.h"
#include "Chrome.h"
#include <Webkit/fymp/ChromeClientFymp.h>
#include <wtf/text/CString.h>

namespace WebCore {

// ----------------------------------------------------------------------------------------
/**
*/
int screenDepth(Widget* widget)
	{
	// In reality we might have less then a true color display, but...
	return(3*8);
	}

int screenDepthPerComponent(Widget*)
	{
	// In reality we might have less then a true color display, but...
	return(8);
	}

// ----------------------------------------------------------------------------------------
/**
*/
bool screenIsMonochrome(Widget*)
	{
	// We always assume a color display!
	return(false);
	}

// ----------------------------------------------------------------------------------------
/**
*/
FloatRect screenRect(Widget* widget)
	{
	int x = 0, y = 0, w = 0, h = 0;
	
	FrameView *pFrameView = dynamic_cast<FrameView*>(widget);
	if (pFrameView)
		{
		// Get the chrome client... (we know it must be ours)
		WebKit::ChromeClientFymp *pChromeClient = static_cast<WebKit::ChromeClientFymp*>(pFrameView->frame()->page()->chrome()->client());
		pChromeClient->getScreenDimensions(w, h);
		}
	
	return(FloatRect(x, y, w, h));
	}

// ----------------------------------------------------------------------------------------
/**
*/
FloatRect screenAvailableRect(Widget* widget)
	{
	// we just return the same as the full screen - no "Windows Taskbar" here ;-)
	return(screenRect(widget));
	}

}

/* FYWEBKITMOD END */
