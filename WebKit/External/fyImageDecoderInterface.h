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

/*

	FactorY Image Decoder Interface

*/

#ifndef _FYIMAGEDECODER_INTERFACE_H_
#define _FYIMAGEDECODER_INTERFACE_H_

#include <fytypes.h>
#if FYMP_PLATFORM == FYMP_PLATFORM_VS
using namespace std;
#else
#include <std_tr1.h>
#endif

#if FYMP_PLATFORM == FYMP_PLATFORM_PS4 || FYMP_PLATFORM == FYMP_PLATFORM_VITA
#error
#ifdef FY_BUILDING_FYIMAGEDECODER
# define FY_EXPORT_DLL		__declspec(dllexport)
# define FY_EXPORT_DLL_VAR	__declspec(dllexport) extern
#else
# define FY_EXPORT_DLL		__declspec(dllimport)
# define FY_EXPORT_DLL_VAR	__declspec(dllimport) extern
#endif
#else
# define FY_EXPORT_DLL
# define FY_EXPORT_DLL_VAR
#endif

class FYimageDecoderClient
	{
public:
	virtual void DecodeDone() = 0;
	virtual void DecodeFailed() = 0;
	};
	
class FYimageDecoderInterface
	{
public:
	enum Decoder
		{
		eDecoder_JPeg = 0,
		};

	enum OutputFormat
		{
		eOutputFormat_None = 0,
		eOutputFormat_RGBA,
		eOutputFormat_RGB,
		};

	enum CopyFormat
		{
		eCopyFormat_Skia = 0,
		};

	FY_EXPORT_DLL static shared_ptr<FYimageDecoderInterface>	Create(Decoder decoderType);

	FY_EXPORT_DLL static void CopyImageData(u32f width, u32f height, OutputFormat outFmt, const u8 *pSrc, u32f srcPitch, CopyFormat cpyFmt, u8 *pDst, u32f dstPitch, bool bForceSolidAlpha);
	FY_EXPORT_DLL static void CopyImageDataScaled(const int * pRows, u32f width, const int *pColumns, u32f height, OutputFormat outFmt, const u8 *pSrc, u32f srcPitch, CopyFormat cpyFmt, u8 *pDst, u32f dstPitch);

	FY_EXPORT_DLL static bool DecodeIsFullyAsync();
	FY_EXPORT_DLL static bool DecodeIsEarlySync();

	virtual bool GetSize(const void *pInput, size_t inputSize, u32 & width, u32 & height) = 0;
	virtual bool Decode(const void *pSource, size_t inputSize, FYimageDecoderClient *pClient = NULL) = 0;
	virtual const void *GetPixels() const = 0;
	virtual void GetOutputSize(u32 & width, u32 & height) const = 0;
	virtual u32 GetPitch() const = 0;
	virtual OutputFormat GetOutputFormat() const = 0;

	virtual ~FYimageDecoderInterface() {}
	};
	
#endif // _FYIMAGEDECODER_INTERFACE_H_
