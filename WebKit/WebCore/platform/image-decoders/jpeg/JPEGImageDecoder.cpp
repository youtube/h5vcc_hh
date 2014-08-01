/*
 * Copyright (C) 2006 Apple Computer, Inc.
 *
 * Portions are Copyright (C) 2001-6 mozilla.org
 *
 * Other contributors:
 *   Stuart Parmenter <stuart@mozilla.com>
 *
 * Copyright (C) 2007-2009 Torch Mobile, Inc.
 * Copyright (C) 2014 FactorY Media Production GmbH
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Alternatively, the contents of this file may be used under the terms
 * of either the Mozilla Public License Version 1.1, found at
 * http://www.mozilla.org/MPL/ (the "MPL") or the GNU General Public
 * License Version 2.0, found at http://www.fsf.org/copyleft/gpl.html
 * (the "GPL"), in which case the provisions of the MPL or the GPL are
 * applicable instead of those above.  If you wish to allow use of your
 * version of this file only under the terms of one of those two
 * licenses (the MPL or the GPL) and not to allow others to use your
 * version of this file under the LGPL, indicate your decision by
 * deletingthe provisions above and replace them with the notice and
 * other provisions required by the MPL or the GPL, as the case may be.
 * If you do not delete the provisions above, a recipient may use your
 * version of this file under any of the LGPL, the MPL or the GPL.
 */

/* FYWEBKITMOD BEGIN file was more or less completely re-implemented */

#include "config.h"
#include "JPEGImageDecoder.h"

#if OS(WINCE) || PLATFORM(BREWMP_SIMULATOR)
// Remove warning: 'FAR' macro redefinition
#undef FAR

// jmorecfg.h in libjpeg checks for XMD_H with the comment: "X11/xmd.h correctly defines INT32"
// fix INT32 redefinition error by pretending we are X11/xmd.h
#define XMD_H
#endif

#include "ImageObserver.h"
#include <fyImageDecoderInterface.h>

namespace WebCore {

class JPEGImageReader : public FYimageDecoderClient
{
public:
    JPEGImageReader(JPEGImageDecoder* decoder)
        : m_decoder(decoder)
		, m_bIsDecoding(false)
    {
    }

    ~JPEGImageReader()
    {
    }

    bool decode(const Vector<char>& data, bool onlySize)
    {
		u32 w, h;

		// No image decoder? Get one!
		if (!m_imageDecoder)
		{
			m_imageDecoder = FYimageDecoderInterface::Create(FYimageDecoderInterface::eDecoder_JPeg);
			// Ok? If not: bail!
			if (!m_imageDecoder)
				return false;
		}

		// We are already decoding? Pretent all is well and do nothing (more)...
		if (m_bIsDecoding)
			return true;

		// Get the size...
		if (!m_imageDecoder->GetSize(&data[0], data.size(), w, h))
			return false;
		// ...and tell it to the owner
		if (!m_decoder->setSize(w, h))
			return false;

		// If we're only hunting for the size we're done...
		if (onlySize)
			return true;

		// More to do! Note it down as we MAY be doing this async...
		m_bIsDecoding = true;
	
		// Start/Do decode...
		// (we use a local, additional reference to the decoder to ensure that,
		//  in case we decode synchonously, we do not loose the instance before
		//  returning)
		shared_ptr<FYimageDecoderInterface> holdImageDecoder(m_imageDecoder);
		bool bOk = m_imageDecoder->Decode(&data[0], data.size(), this);
		holdImageDecoder.reset();
		return bOk;
    }

	virtual void DecodeDone()
		{
		if (!m_decoder->outputScanlines())
			{
			m_decoder->setFailed();
			// when we get here this instance has been deleted by it's owner! Whatever needs cleaning up will have been cleaned up in the destructor -> we MUST exit
			return;
			}

		// We're done. Let go of our reference to the image decoder
		// (so we can reclaim any and all resources it still may claim)
		m_imageDecoder.reset();
	
		m_bIsDecoding = false;
		}

	virtual void DecodeFailed()
		{
		m_decoder->setFailed();
		// when we get here this instance has been deleted by it's owner! Whatever needs cleaning up will have been cleaned up in the destructor -> we MUST exit
		}

	bool startGetSamples(FYimageDecoderInterface::OutputFormat & outFmt, unsigned & width, unsigned & height)
	{
		if (!m_imageDecoder)
			return false;

		u32 w, h;
		m_imageDecoder->GetOutputSize(w, h);
		width = w;
		height = h;
		outFmt = m_imageDecoder->GetOutputFormat();

		m_linesLeft = height;
		m_currentLineStep = m_imageDecoder->GetPitch();
		m_pCurrentRead = (const unsigned char *)m_imageDecoder->GetPixels();

		return true;
	}

	const unsigned char * getSamples() const
	{
		if (m_linesLeft == 0)
			return NULL;

		const unsigned char *pAddr = m_pCurrentRead;
		m_pCurrentRead += m_currentLineStep;
		--m_linesLeft;

		return pAddr;
	}

	unsigned getPitch() const
	{
		return m_imageDecoder->GetPitch();
	}

private:
	JPEGImageDecoder *					m_decoder;
	shared_ptr<FYimageDecoderInterface>	m_imageDecoder;

	bool								m_bIsDecoding;

	mutable const unsigned char *		m_pCurrentRead;
	mutable unsigned					m_currentLineStep;
	mutable unsigned					m_linesLeft;
};


// ---------------------------------------------------------------------------------

JPEGImageDecoder::JPEGImageDecoder()
	: m_imageObserver(0)
{
}

// ---------------------------------------------------------------------------------

JPEGImageDecoder::~JPEGImageDecoder()
{
}

// ---------------------------------------------------------------------------------

bool JPEGImageDecoder::isSizeAvailable()
{
    if (!ImageDecoder::isSizeAvailable())
         decode(true);

    return ImageDecoder::isSizeAvailable();
}

// ---------------------------------------------------------------------------------

bool JPEGImageDecoder::setSize(unsigned width, unsigned height)
{
    if (!ImageDecoder::setSize(width, height))
        return false;

    prepareScaleDataIfNecessary();
    return true;
}

// ---------------------------------------------------------------------------------

RGBA32Buffer* JPEGImageDecoder::frameBufferAtIndex(size_t index)
{
    if (index)
        return 0;

    if (m_frameBufferCache.isEmpty())
        m_frameBufferCache.resize(1);

    RGBA32Buffer& frame = m_frameBufferCache[0];
    if (isAllDataReceived() && (frame.status() != RGBA32Buffer::FrameComplete)) // FYWEBKITMOD added check on isAllDataReceived()
        decode(false);
    return &frame;
}

// ---------------------------------------------------------------------------------

bool JPEGImageDecoder::setFailed()
{
    m_reader.clear();
    return ImageDecoder::setFailed();
}

// ---------------------------------------------------------------------------------

bool JPEGImageDecoder::outputScanlines()
{
    if (m_frameBufferCache.isEmpty())
        return false;

    RGBA32Buffer& buffer = m_frameBufferCache[0];

	// If we are NOT in "early sync" mode we make the bitmap right now. This will let all rendering
	// up to this point (correctly) assume that we don't have any image data, yet. We now change that
	// over to actually HAVE some.
	// (in case of a complete synchronous setup we are of course still in the decode() call... quite simple)
	if (!FYimageDecoderInterface::DecodeIsEarlySync())
	{
		// Now get Skia's buffer object to the right size so we can later on deliver data into it...
		// (this will also make the SkBitmap in it "readyToDraw" as it allocates & clears pixel storage)
		if (buffer.status() == RGBA32Buffer::FrameEmpty) {
			if (!buffer.setSize(scaledSize().width(), scaledSize().height()))
				return false;
	
			buffer.setStatus(RGBA32Buffer::FramePartial);
			buffer.setHasAlpha(false);
		
			// For JPEGs, the frame always fills the entire image.
			buffer.setRect(IntRect(IntPoint(), size()));
		}
	}



	unsigned output_width, output_height;
	FYimageDecoderInterface::OutputFormat outFmt = FYimageDecoderInterface::eOutputFormat_None;	// init only to apeace the compiler
	if (!m_reader->startGetSamples(outFmt, output_width, output_height))
		return false;

	switch(outFmt)
	{
		case	FYimageDecoderInterface::eOutputFormat_RGB:
		case	FYimageDecoderInterface::eOutputFormat_RGBA:
		{
			SkBitmap & bm = buffer.GetSkiaBitmap();

			if (m_scaled)
				FYimageDecoderInterface::CopyImageDataScaled(&m_scaledColumns[0], m_scaledColumns.size(), &m_scaledRows[0], m_scaledRows.size(), outFmt, m_reader->getSamples(), m_reader->getPitch(), FYimageDecoderInterface::eCopyFormat_Skia, (unsigned char*)bm.getPixels(), bm.rowBytes());
			else
				FYimageDecoderInterface::CopyImageData(output_width, output_height, outFmt, m_reader->getSamples(), m_reader->getPitch(), FYimageDecoderInterface::eCopyFormat_Skia, (unsigned char*)bm.getPixels(), bm.rowBytes(), true);

			bm.notifyPixelsChanged();
			break;
		}
		default:
		{
			ASSERT_NOT_REACHED();
			return false;
		}
	}


	// That allows us to mark the frame as "complete"
	// (although the contents are far from it)
	m_frameBufferCache[0].setStatus(RGBA32Buffer::FrameComplete);

	// Only if we run 100% without sync we do need to notify observers that we finally got the data
	// (otherwise the data may never reach the screen as no paint is done!)
	if (FYimageDecoderInterface::DecodeIsFullyAsync() && m_imageObserver)
		m_imageObserver->changedInRect(m_image, m_frameBufferCache[0].rect());

    return true;
}

// ---------------------------------------------------------------------------------

void JPEGImageDecoder::setData(SharedBuffer* data, bool allDataReceived)
{
	ImageDecoder::setData(data, allDataReceived);
}

// ---------------------------------------------------------------------------------

void JPEGImageDecoder::decode(bool onlySize)
{
	// If we already failed, all is lost...
    if (failed())
        return;

	// No reader? Make one!
    if (!m_reader)
        m_reader.set(new JPEGImageReader(this));

	// This will all really need the full data
	if (!isAllDataReceived())
		return;

	// Yes! Decode the size first if we don't have it...
	if (!ImageDecoder::isSizeAvailable())
	{
		if (!m_reader->decode(m_data->buffer(), true))
		{
			// That went wrong...
			setFailed();
			return;
		}
	}

	// Bail if we just had been after the size!
	if (onlySize)
		return;

	// We are about to do a real decode!
	
	// We better don't get an empty frame buffer cache here!
	// (but we don't outright mark things as failed if we do)
	if (m_frameBufferCache.isEmpty())
		return;

	// If the decoder is in "early sync" mode it will deliver the data to the ultimate
	// HW representation "just in time" for the next render. We hence can setup the bitmap
	// now. This will tell all systems involved that we're "ready to render", but the actual
	// conversison of the (empty) bitmap will only happen once the decoder is done...
	if (FYimageDecoderInterface::DecodeIsEarlySync())
	{
		// Now get Skia's buffer object to the right size so we can later on deliver data into it...
		RGBA32Buffer& buffer = m_frameBufferCache[0];
		if (buffer.status() == RGBA32Buffer::FrameEmpty)
		{
			if (!buffer.setSize(scaledSize().width(), scaledSize().height()))
			{
				setFailed();
				return;
			}
	
			buffer.setStatus(RGBA32Buffer::FramePartial);
			buffer.setHasAlpha(false);
		
			// For JPEGs, the frame always fills the entire image.
			buffer.setRect(IntRect(IntPoint(), size()));
		}

		// That allows us to mark the frame as "complete"
		// (although the contents are far from it)
		m_frameBufferCache[0].setStatus(RGBA32Buffer::FrameComplete);
	}

	// Trigger / Do the decode...
    if (!m_reader->decode(m_data->buffer(), false))
		setFailed();
}

} // WebCore

/* FYWEBKITMOD END */
