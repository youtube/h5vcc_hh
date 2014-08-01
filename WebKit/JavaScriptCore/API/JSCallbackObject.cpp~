/*
 * Copyright (C) 2006 Apple Computer, Inc.  All rights reserved.
 * Copyright (C) 2007 Eric Seidel <eric@webkit.org>
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

#include "config.h"
#include "JSCallbackObject.h"

#include "Collector.h"
#include <wtf/text/StringHash.h>

namespace JSC {

ASSERT_CLASS_FITS_IN_CELL(JSCallbackObject<JSObjectWithGlobalObject>);
ASSERT_CLASS_FITS_IN_CELL(JSCallbackObject<JSGlobalObject>);

// Define the two types of JSCallbackObjects we support.
/* FYWEBKITMOD BEGIN */
#if PLATFORM(FYMP) && FYMP_PLATFORM == FYMP_PLATFORM_WIIU
/*
	Workaround for an ugly GHS compiler bug (07/24/13 - 5.3.20):

	The definition of the static members below should work just fine. The GHS compiler's "name mangler"
	seems to have somewhat of a split personality, though!

	When defining this in C++ like in the original code this will result in the following behavior:

	a) if defined in a module in which the static members are used all use cases inside the module will be fine
	b) if defined elsewhere (like here) the exported symbols WILL NOT MATCH the symbols expected by the referencing
	   modules. Hence the build will fail during the compile!

	The reason is really a mismatch between the mangled symbol name REFERENCED by other modules and the one EXPORTED
	by this module!

	Exported:

	info__S__Q2_3JSC58JSCallbackObject__tm__34_Q2_3JSC24JSObjectWithGlobalObject
	info__S__Q2_3JSC48JSCallbackObject__tm__24_Q2_3JSC14JSGlobalObject

	Imported:

	info__Q2_3JSC58JSCallbackObject__tm__34_Q2_3JSC24JSObjectWithGlobalObject
	info__Q2_3JSC48JSCallbackObject__tm__24_Q2_3JSC14JSGlobalObject

	Hence: link fails!

	The assembly below constructs the very same C++ structure manually and specifies the names
	as expected by the referencing modules, hence fixing the issue.

	OF COURSE THIS WILL HORRIBLY BREAK IF THE ClassInfo STRUCTURE EVER IS TO BE CHANGED!

	The trigger?

	It seems the fact that a static member is defined inside a templated class derived from another class
	could be the trigger - this is pretty unique in this instance. But... not really THAT uncommon generally?!?


	UPDATE: 07/25/13

	SDSG forwarded this to GHS, which came back claiming that not the compiler, but the source is at fault. That
	seems a bit proposterous as basically ALL other compilers we compile this code with are just fine with how
	things are. Still: for the record this is what they suggest:

	Before being ready for use the static member needs to be defined. Visibly for EACH AND EVERY module using it.
	So... likely in a header file!

	E.g. like so:

	namespace JSC {
		template <> const ClassInfo JSCallbackObject<JSObjectWithGlobalObject>::info;
		template <> const ClassInfo JSCallbackObject<JSGlobalObject>::info;
	}

	Now... for me (Thomas) this looks like an explicit definition of the static instance in a header! Bad. Very bad!

	But, indeed: this seems to work!

	Key factor with at least the GHS compiler: they put the instance into a .rodata section flagged as "linkonce", so
	that (as any other "template stuff" the actual implementation indeed only exists once...

	But: this THAT how C++ wants it? I don't know... and tend to disagree.

	Note: their "fix" has only be shown to compile & link on GHS. I've not run the resoluting code.

	Due to the smaller impact of the first work around, it's still in place for now!

*/
__asm(
"	.rodata\n" \
"classNameJSObjectWithGlobalObject:\n" \
"	.asciz	\"CallbackGlobalObject\"\n" \
"classNameJSGlobalObject:\n" \
"	.asciz	\"CallbackObject\"\n" \
"\n" \
"	.global info__Q2_3JSC58JSCallbackObject__tm__34_Q2_3JSC24JSObjectWithGlobalObject\n" \
"	.global	info__Q2_3JSC48JSCallbackObject__tm__24_Q2_3JSC14JSGlobalObject\n" \
"\n" \
"	.align 2\n" \
"info__Q2_3JSC58JSCallbackObject__tm__34_Q2_3JSC24JSObjectWithGlobalObject:\n" \
"	.long classNameJSObjectWithGlobalObject, 0, 0, 0\n" \
"info__Q2_3JSC48JSCallbackObject__tm__24_Q2_3JSC14JSGlobalObject:\n" \
"	.long classNameJSGlobalObject, 0, 0, 0\n");

/* FYWEBKITMOD END */
#else
// the original definition
template <> const ClassInfo JSCallbackObject<JSObjectWithGlobalObject>::info = { "CallbackObject", 0, 0, 0 };
template <> const ClassInfo JSCallbackObject<JSGlobalObject>::info = { "CallbackGlobalObject", 0, 0, 0 };
#endif

} // namespace JSC

