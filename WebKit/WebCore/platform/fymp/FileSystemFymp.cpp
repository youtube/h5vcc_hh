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

#include <wtf/Platform.h>
#include "FileSystem.h"

#include "NotImplemented.h"
#include "PlatformString.h"
#include "CString.h"

#if FYMP_PLATFORM == FYMP_PLATFORM_WII
#include <wii/virtualFilesystem_Wii.h>
#elif FYMP_PLATFORM == FYMP_PLATFORM_WIIU
#include <wiiu/virtualFilesystem_WiiU.h>
#elif FYMP_PLATFORM == FYMP_PLATFORM_CTR
#include <ctr/virtualFilesystem_CTR.h>
#elif FYMP_PLATFORM == FYMP_PLATFORM_PS3
#include <ps3/virtualFilesystem_PS3.h>
#elif FYMP_PLATFORM == FYMP_PLATFORM_PS4
#include <ps4/virtualFilesystem_PS4.h>
#elif FYMP_PLATFORM == FYMP_PLATFORM_X360
#include <x360/virtualFilesystem_X360.h>
#elif FYMP_PLATFORM == FYMP_PLATFORM_VITA
#include "saveFilesystem.h"
#endif

#include <std_DebugIO.h>

namespace WebCore
{

bool fileExists(const String &path)
	{
#if FYMP_PLATFORM == FYMP_PLATFORM_VITA
	return(SaveFilesystem::FileExists(std::string(path.ascii().data())));
#else
	return(VirtualFilesystem::FileExists(std::string(path.ascii().data())));
#endif
	}

bool deleteFile(const String &path)
	{
#if FYMP_PLATFORM == FYMP_PLATFORM_VITA
	return(SaveFilesystem::DeleteFile(std::string(path.ascii().data())));
#else
	return(VirtualFilesystem::DeleteFile(std::string(path.ascii().data())));
#endif
	}

bool deleteEmptyDirectory(const String &path)
	{
	notImplemented();
	return(true);
	}

bool getFileSize(const String &path, long long &resultSize)
	{
#if FYMP_PLATFORM == FYMP_PLATFORM_VITA
	SaveFilesystem::FileStats stats;
	SaveFilesystem::ErrorCode err;
	err = SaveFilesystem::GetFileStats(stats, std::string(path.ascii().data()));
	resultSize = (long long)stats.mSize;
	return(err == 0);
#else
	VirtualFilesystem::FileStats stats;
	VirtualFilesystem::ErrorCode err;
	err = VirtualFilesystem::GetFileStats(stats, std::string(path.ascii().data()));
	resultSize = (long long)stats.mSize;
	return(err == 0);
#endif
	}

bool getFileModificationTime(const String& path, time_t& modifiedTime)
	{
#if FYMP_PLATFORM == FYMP_PLATFORM_VITA
	SaveFilesystem::FileStats stats;
	SaveFilesystem::ErrorCode err;
	err = SaveFilesystem::GetFileStats(stats, std::string(path.ascii().data()));
	modifiedTime = time_t(stats.mTimestamp);
	return(err == 0);
#else
	VirtualFilesystem::FileStats stats;
	VirtualFilesystem::ErrorCode err;
	err = VirtualFilesystem::GetFileStats(stats, std::string(path.ascii().data()));
	modifiedTime = time_t(stats.mTimestamp);
	return(err == 0);
#endif
	}

String pathByAppendingComponent(const String& path, const String& component)
	{
	if (path.isEmpty() || path.endsWith(String("/")))
		return(path + component);
	return(path + "/" + component);
	}

bool makeAllDirectories(const String &path)
	{
	// We do not create directories. Every filepath/filename will eventually be mangled into a checksum and stored as a file by that name in the root.
	return(true);
	}

String homeDirectoryPath()
	{
	// this function is not called by code, so we do not need to implement it.
	notImplemented();
	return(String());
	}

String pathGetFileName(const String& pathName)
	{
	// this function is not called by code, so we do not need to implement it.
	notImplemented();
	return(String());
	}

String directoryName(const String& path)
	{
	// this function is not called by code, so we do not need to implement it.
	notImplemented();
	return(String());
	}


CString openTemporaryFile(const char* prefix, PlatformFileHandle& handle)
	{
	// this function is not called by code, so we do not need to implement it.
	notImplemented();
	handle = invalidPlatformFileHandle;
	return(CString());
	}

void closeFile(PlatformFileHandle& handle)
	{
	// this function is not called by code, so we do not need to implement it.
	notImplemented();
	}

int writeToFile(PlatformFileHandle handle, const char* data, int length)
	{
	// this function is not called by code, so we do not need to implement it.
	notImplemented();
	return(0);
	}



Vector<String> listDirectory(const String& path, const String& filter)
	{
	// this function is not called by code, so we do not need to implement it.
	Vector<String> entries;
	notImplemented();
	return(entries);
	}

bool unloadModule(PlatformModule module)
	{
	// this function is not called by code, so we do not need to implement it.
	notImplemented();
	return(true);
	}

CString fileSystemRepresentation(const String& path)
	{
	// this function is not called by code, so we do not need to implement it.
	notImplemented();
	return(path.utf8());
	}
}

/* FYWEBKITMOD END */
