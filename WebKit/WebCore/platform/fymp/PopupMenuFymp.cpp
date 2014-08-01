/*
 * This file is part of the popup menu implementation for <select> elements in WebCore.
 *
 * Copyright 2009, The Android Open Source Project
 * Copyright (C) 2006 Apple Computer, Inc.
 * Copyright (C) 2006 Michael Emmel mike.emmel@gmail.com
 * Copyright (C) 2014 FactorY Media Production GmbH
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */

/* FYWEBKITMOD BEGIN initially copied over from android/PopupMenuAndroid.cpp which had only empty implementation. Then added own implementation. */

#include "config.h"
#include "PopupMenu.h"

#include "Chrome.h"
#include "ChromeClient.h"

namespace WebCore {

PopupMenu::PopupMenu(PopupMenuClient* menuList)
    : m_popupClient(menuList)
{
	if (m_popupClient)
		static_cast<Chrome*>(m_popupClient->hostWindow())->client()->notify_PopUpState(ChromeClient::ePopUpState_Create, m_popupClient, NULL, NULL, -1);
}

PopupMenu::~PopupMenu()
{
	// We usually will see a NULL here. The code has been left here to catch any edge cases (if they exist)
	if (m_popupClient)
		static_cast<Chrome*>(m_popupClient->hostWindow())->client()->notify_PopUpState(ChromeClient::ePopUpState_Destroy, m_popupClient, NULL, NULL, -1);
}

void PopupMenu::disconnectClient()
{
	// Disconnect from client. We take this as a "destroy" trigger
	// (usually should get a NULL as m_popupClient during the destructor call as webkit code will reset it prior to tearing things down - hence we do things here)
	if (m_popupClient)
		static_cast<Chrome*>(m_popupClient->hostWindow())->client()->notify_PopUpState(ChromeClient::ePopUpState_Destroy, m_popupClient, NULL, NULL, -1);
}

void PopupMenu::show(const IntRect& rect, FrameView* pFrameView, int index)
{
	// Visually present the popup
	if (m_popupClient)
		static_cast<Chrome*>(m_popupClient->hostWindow())->client()->notify_PopUpState(ChromeClient::ePopUpState_Show, m_popupClient, &rect, pFrameView, index);
}

void PopupMenu::hide()
{
	// Visually hide the popup (it might be shown again)
	if (m_popupClient)
	{
		// Tell out system about the need to hide things...
		static_cast<Chrome*>(m_popupClient->hostWindow())->client()->notify_PopUpState(ChromeClient::ePopUpState_Hide, m_popupClient, NULL, NULL, -1);
		// ...and tell Webkit that we're hiding things
		// (otherwise we will not receive a "show" anymore)
		m_popupClient->popupDidHide();
	}
}

void PopupMenu::updateFromElement() 
{
	if (m_popupClient)
	{
		// We need to pass on the logical updates as visual updates once the popup is visible
		// (otherwise webkit handles it internally & doesn't even call us)
		m_popupClient->setTextFromItem(m_popupClient->selectedIndex());
		// For good measure: also tell our system that an update has been made...
		static_cast<Chrome*>(m_popupClient->hostWindow())->client()->notify_PopUpState(ChromeClient::ePopUpState_Update, m_popupClient, NULL, NULL, -1);
	}
}

bool PopupMenu::itemWritingDirectionIsNatural()
{
    return false;
}

} // namespace WebCore

/* FYWEBKITMOD END */
