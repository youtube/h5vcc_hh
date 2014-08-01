

#ifndef SKIA_EXT_FYMP_PLATFORM_CANVAS_H_
#define SKIA_EXT_FYMP_PLATFORM_CANVAS_H_

#include "skia/ext/fymp_platform_device.h"
#include "SkCanvas.h"

namespace skia
{

class FYMPPlatformCanvas : public SkCanvas
    {
public:
    FYMPPlatformCanvas();
    FYMPPlatformCanvas(int width, int height);

    virtual ~FYMPPlatformCanvas();

    // For two-part init, call if you use the no-argument constructor above
    bool initialize(int width, int height, bool isOpaque, uint8_t* data = NULL);

    //void Begin(CGXPlatformRecorderClient *pClient, u32 clientID);
    //void End(void);
    //static void Flush(void);
	//static void ProcessRendering(void);

    //void Draw(CGXtargetGroupObj *pRenderTargetGroup, const SkIRect & renderRect, shared_ptr<DrawList> pDrawList, CGXpixelFmt layerPixFmt, CGXpixelFmt transLayerPixFmt);

protected:
    // Creates a device store for use by the canvas. We override this so that
    // the device is always our own so we know that we can use platform
    // operations on it.
    virtual SkDevice* createDevice(SkBitmap::Config,
                                int width,
                                int height,
                                bool is_opaque,
                                bool isForLayer,
                                bool isForImageBuffer);

private:
    // Disallow copy and assign.
    //FYMPPlatformCanvas(const CGXPlatformCanvas&);
    //FYMPPlatformCanvas& operator=(const CGXPlatformCanvas&);


    SkIPoint 			 		mViewportSize;			//!< Current size of the viewport
	bool						mbIsImageBuffer;		//!< True if this canvas is part of an ImageBuffer

    bool setViewport(int width, int height);

    int internalSave(SaveFlags flags);

	// All canvas instance known ------------------------------------
    //static STDvectorObj<CGXPlatformCanvas*>	mCanvases;
    };
};

#endif  // SKIA_EXT_CGX_PLATFORM_CANVAS_H_


