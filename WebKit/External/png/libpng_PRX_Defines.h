/**************************************************************************/
/*    File: libpng_PRX_Defines.h                                          */
/*                                                                        */
/* Purpose: Platform specific declarations to export/import symbols to    */
/*          PRX (DLL) modules.                                            */
/**************************************************************************/
#ifndef _LIBPNG_PRX_DEFINES_H_
#define _LIBPNG_PRX_DEFINES_H_

//
// PS4 / VITA
//
#if FYMP_PLATFORM == FYMP_PLATFORM_PS4 || FYMP_PLATFORM == FYMP_PLATFORM_VITA
#ifdef FYMP_PNG_INTERNAL_PRX
# define PNG_BUILD_DLL		1
# define PNG_NO_MODULEDEF	1
# define PNGAPI
#else
# define PNG_USE_DLL		1
# define PNGAPI
#endif



//
// Other platforms
//
#else


#endif



#endif

