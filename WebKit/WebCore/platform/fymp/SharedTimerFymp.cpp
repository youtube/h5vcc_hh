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

#include "SharedTimer.h"
#include "CurrentTime.h"
#include "Assertions.h"

#include "WebKit_PRX_Defines.h"

#include <stdio.h>

/*

	Note:

	This does not really implement the timer-logic itself. That is all dealt
	with in WebCore/Webkit's platform independent code.
	We just implement service functions. Mainly they focus on us being able
	to provide a true "sleep" service to webkit to not need to spin the CPU
	to wait for things.

	We do this, but the actual wait is implemented in the WKF application so
	that other systems can partake in the "webkit thread loop".

*/

namespace WebCore {

// ------------------------------------------------------------------------

static void (*_SharedTimerFiredFunction)();

static bool _bTimerSet = false;
static double _fireTime = 0.0;

// ------------------------------------------------------------------------

void setSharedTimerFiredFunction(void (*f)())
	{
    _SharedTimerFiredFunction = f;
	}

// ------------------------------------------------------------------------

void setSharedTimerFireTime(double time)
	{
    ASSERT(_SharedTimerFiredFunction);

    _bTimerSet = true;
    _fireTime = time;
	}

// ------------------------------------------------------------------------

void stopSharedTimer()
	{
    _bTimerSet = false;
    _fireTime = 0.0;
	}

// ------------------------------------------------------------------------

FYMP_PRXSYM_WEBKIT long getTimeUntilNextSharedTimer()
	{
	if (!_bTimerSet)
		return(-1);
	// return ms until next fire time
	return((long)((_fireTime - currentTime()) * 1000.0));
	}

// ------------------------------------------------------------------------

// Even though we are in WebCore here the prototype of this function is in WebKit, so we need to use the PRX define for Webkit
FYMP_PRXSYM_WEBKIT void checkSharedTimer()
	{
	if (_bTimerSet)
		_SharedTimerFiredFunction();
	}

}

/* FYWEBKITMOD END */
