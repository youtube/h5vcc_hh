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
#include "PlatformKeyboardEvent.h"

namespace WebCore {

PlatformKeyboardEvent::PlatformKeyboardEvent(Type type, String text, String keyIdentifier, int keyCode, unsigned modifier) :
	m_type(type),
	m_text(text),
	m_unmodifiedText(text), // FIX
	m_keyIdentifier(keyIdentifier),
	m_autoRepeat(false),
	m_windowsVirtualKeyCode(keyCode),
	m_nativeVirtualKeyCode(keyCode),
	m_isKeypad(false),
	m_shiftKey((modifier & ShiftKey) ? true : false),
	m_ctrlKey((modifier & CtrlKey) ? true : false),
	m_altKey((modifier & AltKey) ? true : false),
	m_metaKey((modifier & MetaKey) ? true : false)
{
}

void PlatformKeyboardEvent::disambiguateKeyDownEvent(Type type, bool backwardCompatibilityMode)
{
    ASSERT(m_type == KeyDown);
    ASSERT(type == RawKeyDown || type == Char);
    m_type = type;
    if (backwardCompatibilityMode)
        return;

    if (type == RawKeyDown) {
        m_text = String();
        m_unmodifiedText = String();
    } else {
        m_keyIdentifier = String();
        m_windowsVirtualKeyCode = 0;
    }
}

bool PlatformKeyboardEvent::currentCapsLockState()
{
    return false;
}

void PlatformKeyboardEvent::getCurrentModifierState(bool& shiftKey, bool& ctrlKey, bool& altKey, bool& metaKey)
{
    shiftKey = false;
    ctrlKey = false;
    altKey = false;
    metaKey = false;
}

}

/* FYWEBKITMOD END */
