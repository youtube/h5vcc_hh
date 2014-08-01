/*
 * Copyright (C) 2011 Apple Inc.  All rights reserved.
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

// FYMP integrated from r152754.

#include "config.h"

#if ENABLE(VIDEO_TRACK)

#include "TrackEvent.h"

#include "EventNames.h"

namespace WebCore {

/* FYWEBKITMOD BEGIN Concept of EventInit is not used in our WebKit. */
/*
TrackEventInit::TrackEventInit()
{
}
*/
/* FYWEBKITMOD END */

TrackEvent::TrackEvent()
{
}

/* FYWEBKITMOD BEGIN Concept of EventInit is not used in our WebKit.
TrackEvent::TrackEvent(const AtomicString& type, const TrackEventInit& initializer)
    : Event(type, initializer)
    , m_track(initializer.track)
{
}
FYWEBKITMOD END */

TrackEvent::~TrackEvent()
{
}

/* FYWEBKITMOD BEGIN Not used in our code-generation code.
const AtomicString& TrackEvent::interfaceName() const
{
    return eventNames().interfaceForTrackEvent;
}
FYWEBKITMOD END */

/* FYWEBKITMOD BEGIN this is how Event-creation is generally done in our WebKit version. */
TrackEvent::TrackEvent(const AtomicString& type, RefPtr<TrackBase> trackRef, bool bubbles, bool cancelable)
: Event(type, bubbles, cancelable), m_track(trackRef)
{
}
/* FYWEBKITMOD END */

} // namespace WebCore

#endif
