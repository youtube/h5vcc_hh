/*
 * Copyright (C) 2009 Company 100, Inc. All rights reserved.
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

/* FYWEBKITMOD BEGIN copied over from brew/WidgetBrew.cpp then implemented Widget::paint() */

#include "config.h"
#include "Widget.h"
#include "FrameView.h"

#include "Cursor.h"
#include "GraphicsContext.h"
#include "IntRect.h"
#include "NotImplemented.h"

namespace WebCore {

/*

	A Widget is the base class for

	Scrollbar
	PluginView
	ScrollView

*/

Widget::Widget(PlatformWidget widget)
{
    init(widget);
}

Widget::~Widget()
{
}

IntRect Widget::frameRect() const
{
    return m_frame;
}

void Widget::setFrameRect(const IntRect& rect)
{
    m_frame = rect;
}

void Widget::setFocus(bool)
{
}

void Widget::setCursor(const Cursor& cursor)
{
}

void Widget::show()
{
}

void Widget::hide()
{
}

void Widget::paint(GraphicsContext* context, IntRect const& dirtyRect)
{
/* FYWEBKITMOD BEGIN */
    if (context->paintingDisabled() && !context->updatingControlTints())
        return;

	if (!isFrameView())
		return;

	FrameView *pFrameView = static_cast<FrameView*>(this);

	context->save();

	IntRect dr(dirtyRect);

	// dirty rectangle into local space & context in position on screen
	context->translate(x(), y());
	dr.move(-x(), -y());

	// note: since we don't use Webkit's scrolling feature, we don't do anything to support it here!
	//    context->translate(-scrollX(), -scrollY());
	//    dr.move(scrollX(), scrollY());

	pFrameView->paintContents(context, dr);
    context->restore();
/* FYWEBKITMOD END */
}

void Widget::setIsSelected(bool)
{
    notImplemented();
}

} // namespace WebCore

/* FYWEBKITMOD END */
