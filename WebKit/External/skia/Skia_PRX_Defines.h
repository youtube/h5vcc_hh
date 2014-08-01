/**************************************************************************/
/*    File: Skia_PRX_Defines.h                                            */
/*                                                                        */
/* Purpose: Platform specific declarations to export/import symbols to    */
/*          PRX (DLL) modules.                                            */
/**************************************************************************/
#ifndef _SKIA_PRX_DEFINES_H_
#define _SKIA_PRX_DEFINES_H_

//
// VITA
//
#if FYMP_PLATFORM == FYMP_PLATFORM_VITA

// This is different on VITA:
// - Both WebKit and skia belong to the same prx
// - This means that if a Skia HEADER gets included while webkit is compiled we also need to dllexport 
// - This means we are using  dllexport if either compilation of Webkit or compilation of Skia is running
 
#if defined(FYMP_WEBKIT_INTERNAL_PRX) || defined(FYMP_SKIA_INTERNAL_PRX)
# define FYMP_PRXSYM_SKIA		__declspec(dllexport)
#else
# define FYMP_PRXSYM_SKIA		__declspec(dllimport)
#endif

//
// PS4
//
#elif FYMP_PLATFORM == FYMP_PLATFORM_PS4

#ifdef FYMP_SKIA_INTERNAL_PRX
# define FYMP_PRXSYM_SKIA		__declspec(dllexport)
#else
# define FYMP_PRXSYM_SKIA		__declspec(dllimport)
#endif



//
// Other platforms
//
#else

#define FYMP_PRXSYM_SKIA

#endif



#endif

