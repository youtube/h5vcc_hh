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

#ifndef _FYMP_WEBKIT_GLUE_MEMORY_H_
#define _FYMP_WEBKIT_GLUE_MEMORY_H_


//
// PS4 / Vita
//
#if FYMP_PLATFORM == FYMP_PLATFORM_PS4 || FYMP_PLATFORM == FYMP_PLATFORM_VITA
# ifdef FYMP_WEBKITGLUE_INTERNAL_PRX
#  define FYMP_PRXSYM_WEBKITGLUE		__declspec(dllexport)
# else
#  define FYMP_PRXSYM_WEBKITGLUE		__declspec(dllimport)
# endif

//
// Other platforms
//
#else

#define FYMP_PRXSYM_WEBKITGLUE

#endif


namespace FYMPwebkitGlue
{

/*********************************/
/*** Called from Collector.cpp ***/
/*********************************/
FYMP_PRXSYM_WEBKITGLUE void *RTmalloc(unsigned int numBytes, unsigned int alignment);
FYMP_PRXSYM_WEBKITGLUE void  RTfree(void *pAddress);


/*****************************/
/*** Called from npapi.cpp ***/
/*****************************/
FYMP_PRXSYM_WEBKITGLUE void *NPNmalloc(unsigned int numBytes);
FYMP_PRXSYM_WEBKITGLUE void  NPNfree(void *pAddress);

/*********************************/
/*** Called from npruntime.cpp ***/
/*********************************/
FYMP_PRXSYM_WEBKITGLUE char *NPNstrdup(const char *pString);
//void *NPNSmalloc(unsigned int numBytes);
//void  NPNSfree(void *pAddress);
//void *NPNOmalloc(unsigned int numBytes);
//void  NPNOfree(void *pAddress);


/***********************************/
/*** Called from RenderArena.cpp ***/
/***********************************/
FYMP_PRXSYM_WEBKITGLUE void *RAmalloc(unsigned int numBytes);
FYMP_PRXSYM_WEBKITGLUE void  RAfree(void *pAddress);


/**********************************/
/*** Called from FastMalloc.cpp ***/
/**********************************/
FYMP_PRXSYM_WEBKITGLUE void *WTFmalloc(unsigned int numBytes);
FYMP_PRXSYM_WEBKITGLUE void *WTFmalloc(unsigned int numBytes, unsigned int alignment);
FYMP_PRXSYM_WEBKITGLUE void *WTFcalloc(unsigned int numElements, unsigned int elementSize);
FYMP_PRXSYM_WEBKITGLUE void *WTFrealloc(void *pAddress, unsigned int numBytes);
FYMP_PRXSYM_WEBKITGLUE void  WTFfree(void *pAddress);


/************************************/
/*** Called from TextIterator.cpp ***/
/************************************/
FYMP_PRXSYM_WEBKITGLUE void *WKmalloc(unsigned int numBytes);
FYMP_PRXSYM_WEBKITGLUE void  WKfree(void *pAddress);


//
// Misc
//
FYMP_PRXSYM_WEBKITGLUE void CollectGarbage();

} // namespace FYMPwebkitGlue
#endif

