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

/**************************************************************************/
/*    File: WebKit_PRX_Defines.h                                          */
/*                                                                        */
/* Purpose: Platform specific declarations to export/import symbols to    */
/*          PRX (DLL) modules.                                            */
/**************************************************************************/
#ifndef _WEBKIT_PRX_DEFINES_H_
#define _WEBKIT_PRX_DEFINES_H_

//
// PS4
//
#if FYMP_PLATFORM == FYMP_PLATFORM_PS4 || FYMP_PLATFORM == FYMP_PLATFORM_VITA

#ifdef FYMP_WEBKIT_INTERNAL_PRX
# define FYMP_PRXSYM_WEBKIT		__declspec(dllexport)
#else
# define FYMP_PRXSYM_WEBKIT		__declspec(dllimport)
#endif



//
// Other platforms
//
#else

#define FYMP_PRXSYM_WEBKIT

#endif



#endif

