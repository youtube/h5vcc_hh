/*
 * Copyright (C) 2009 Apple Inc. All rights reserved.
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

#ifndef ArrayBuffer_h
#define ArrayBuffer_h

#include <wtf/PassRefPtr.h>
#include <wtf/RefCounted.h>

#include <wtf/RefPtr.h> // FYWEBKITMOD enabling binary response of XMLHttpRequest

namespace WebCore {

class ArrayBuffer : public RefCounted<ArrayBuffer> {
  public:
    static PassRefPtr<ArrayBuffer> create(unsigned numElements, unsigned elementByteSize);
    static PassRefPtr<ArrayBuffer> create(ArrayBuffer*);
/* FYWEBKITMOD BEGIN enabling binary response of XMLHttpRequest */
	static inline PassRefPtr<ArrayBuffer> create(const void* source, unsigned byteLength);
/* FYWEBKITMOD BEGIN */

    void* data();
    const void* data() const;
    unsigned byteLength() const;

    ~ArrayBuffer();

  private:
    ArrayBuffer(void* data, unsigned sizeInBytes);
    ArrayBuffer(unsigned numElements, unsigned elementByteSize);
    static void* tryAllocate(unsigned numElements, unsigned elementByteSize);
    unsigned m_sizeInBytes;
    void* m_data;
};

/* FYWEBKITMOD BEGIN enabling binary response of XMLHttpRequest */
PassRefPtr<ArrayBuffer> ArrayBuffer::create(const void* source, unsigned byteLength)
{
	void* data = tryAllocate(byteLength, byteLength);
	RefPtr<ArrayBuffer> buf = adoptRef(new ArrayBuffer(data, byteLength));
	memcpy(buf->data(), source, byteLength);

	return buf.release();
}
/* FYWEBKITMOD END */

} // namespace WebCore

#endif // ArrayBuffer_h
