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

#include "config.h"

#include "ExecutableAllocator.h"

#if ENABLE(ASSEMBLER) && PLATFORM(FYMP) // FYWEBKITMOD including platform Fymp

#include "f5memory_Std.h"

namespace JSC {

void ExecutableAllocator::intializePageSize()
	{
    ExecutableAllocator::pageSize = 1024;
	}

ExecutablePool::Allocation ExecutablePool::systemAlloc(size_t n)
	{
	void* allocation = STDmem::AllocWii(n, 16, STDmem::MEM_FLG_PHYSICAL1);
    ExecutablePool::Allocation alloc = {reinterpret_cast<char*>(allocation), n};
    return alloc;
	}

void ExecutablePool::systemRelease(const ExecutablePool::Allocation& alloc)
	{
	STDmem::Free(alloc.pages);
	}

bool ExecutableAllocator::isValid() const
	{
    return true;
	}

}

#endif // HAVE(ASSEMBLER) && PLATFORM(FYMP)

