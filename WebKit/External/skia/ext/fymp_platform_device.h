

#ifndef SKIA_EXT_FYMP_PLATFORM_DEVICE_H_
#define SKIA_EXT_FYMP_PLATFORM_DEVICE_H_

#include <SkPathEffect.h>
#include <SkDevice.h>
#include <SkShader.h>
#include <skPixelRef.h>

namespace skia
{

// ---------------------------------------------------------------------------------------------------------------------------

class FYMPPlatformDevice : public SkDevice
	{
public:
	//static void Startup(NOThub *pNotHub);
	//static void Shutdown(void);

    FYMPPlatformDevice(const SkBitmap& bitmap, bool bIsLayer = false, bool bIsForImageBuffer = false, FYMPPlatformDevice *pParentDevice = NULL);
    virtual ~FYMPPlatformDevice();

    // rendering

    virtual void gainFocus(SkCanvas*);

    virtual void lockPixels();
    virtual void unlockPixels();
	virtual void onAccessBitmap(SkBitmap* pBitmap);

    virtual void setMatrixClip(const SkMatrix& matrix, const SkRegion& clip);

    virtual void drawPaint(const SkDraw&, const SkPaint& paint);
    virtual void drawPoints(const SkDraw&, SkCanvas::PointMode mode, size_t count,
                            const SkPoint[], const SkPaint& paint);
    virtual void drawRect(const SkDraw&, const SkRect& r,
                          const SkPaint& paint);
    virtual void drawPath(const SkDraw&, const SkPath& path,
                          const SkPaint& paint);
    virtual void drawBitmap(const SkDraw&, const SkBitmap& bitmap,
                            const SkMatrix& matrix, const SkPaint& paint);
    virtual void drawSprite(const SkDraw&, const SkBitmap& bitmap,
                            int x, int y, const SkPaint& paint);
    virtual void drawText(const SkDraw&, const void* text, size_t len,
                          SkScalar x, SkScalar y, const SkPaint& paint);
    virtual void drawPosText(const SkDraw&, const void* text, size_t len,
                             const SkScalar pos[], SkScalar constY,
                             int scalarsPerPos, const SkPaint& paint);
    virtual void drawTextOnPath(const SkDraw&, const void* text, size_t len,
                                const SkPath& path, const SkMatrix* matrix,
                                const SkPaint& paint);
    virtual void drawVertices(const SkDraw&, SkCanvas::VertexMode, int vertexCount,
                              const SkPoint verts[], const SkPoint texs[],
                              const SkColor colors[], SkXfermode* xmode,
                              const uint16_t indices[], int indexCount,
                              const SkPaint& paint);
    virtual void drawDevice(const SkDraw&, SkDevice*, int x, int y,
                            const SkPaint&);

	//void Begin(CGXPlatformRecorderClient *pClient, u32 clientID);
	//void End(void);
	//bool Flush(void);

	//static void ProcessRendering(void);

	//void Draw(CGXtargetGroupObj *pRenderTargetGroup, const SkIRect & renderRect, shared_ptr<DrawList> pDrawList, CGXpixelFmt layerPixFmt, CGXpixelFmt transLayerPixFmt);

	int GetLayerID() const { return(mLayerID); }

	bool IsRecording() const { return(mbRecording); }
	bool IsImageBuffer() const { return(mbIsImageBuffer); }

	//void NotifyLayerDisused(u32 layerID);

	//CGXPlatformCanvas *GetActiveCanvas() const;

	//static void AdjustSizeForPatternUse(u32 & w, u32 & h, bool bRepeatableW, bool bRepeatableH);

protected:

    /** Return the current matrix, from a previous call to setMatrixClip */
    const SkMatrix& matrix() const { return mMatrix; }

    /** Return the current clip, from a previous call to setMatrixClip */
    const SkRegion& clip() const { return mClip; }

private:

	friend class ClipIter;
	friend class SkCGXRecorder;


	bool					mbIsImageBuffer;	//!< True if this has been created to work on an ImageBuffer
	bool					mbIsLayer;			//!< True if this has been created as layer
	bool					mbHaveLayerRenderTarget;	//!< True once a layer's render target creation command has been recorded
	int 					mLayerID;			//!< ID of layer rendering resources created for this device (if layer & if created - used to reference them when layer is rendered to the "screen" during render processing)

	//
	// Logical render state
	//
	
    SkMatrix    			mMatrix;			//!< Current affine transform
    SkRegion    			mClip;				//!< Current clipping information

	bool        			mbDirty;			//!< True if clipping has changed, but not set, yet

	bool					mbRecording;		//!< True when inside Begin() / End() pairs



    typedef SkDevice INHERITED;
	};

// -------------------------------------------------------------------------------------------------------

typedef FYMPPlatformDevice PlatformDevice;


}; // namespace skia

#endif  // SKIA_EXT_CGX_PLATFORM_DEVICE_H_


