/*
 * Copyright (C) 2007 Apple Inc.
 * Copyright (C) 2007 Alp Toker <alp@atoker.com>
 * Copyright (C) 2008 Collabora Ltd.
 * Copyright (C) 2008, 2009 Google Inc.
 * Copyright (C) 2014 FactorY Media Production GmbH
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

/* FYWEBKITMOD BEGIN initially copied over from rendering/RenderThemeChromiumSkia.cpp */

#include "config.h"
#include "RenderThemeFymp.h"

#include "CSSValueKeywords.h"
#include "CurrentTime.h"
#include "GraphicsContext.h"
#include "HTMLMediaElement.h"
#include "HTMLNames.h"
#include "Image.h"
#include "MediaControlElements.h"
#include "PlatformContextSkia.h"
#include "RenderBox.h"
#include "RenderObject.h"
#include "RenderProgress.h"
#include "RenderSlider.h"
#include "ScrollbarTheme.h"
#include "TimeRanges.h"
#include "TransformationMatrix.h"
#include "UserAgentStyleSheets.h"

/* FYWEBKITMOD BEGIN */
#include "SkShader.h"
#include "SkGradientShader.h"
/* FYWEBKITMOD END */

#include <limits>
#include <wtf/MathExtras.h>

namespace WebCore {

enum PaddingType {
    TopPadding,
    RightPadding,
    BottomPadding,
    LeftPadding
};

static const int styledMenuListInternalPadding[4] = { 1, 4, 1, 4 };

// These values all match Safari/Win.
static const float defaultControlFontPixelSize = 13;
static const float defaultCancelButtonSize = 9;
static const float minCancelButtonSize = 5;
static const float maxCancelButtonSize = 21;
static const float defaultSearchFieldResultsDecorationSize = 13;
static const float minSearchFieldResultsDecorationSize = 9;
static const float maxSearchFieldResultsDecorationSize = 30;
static const float defaultSearchFieldResultsButtonWidth = 18;

static void setSizeIfAuto(RenderStyle* style, const IntSize& size)
{
    if (style->width().isIntrinsicOrAuto())
        style->setWidth(Length(size.width(), Fixed));
    if (style->height().isAuto())
        style->setHeight(Length(size.height(), Fixed));
}

static void drawVertLine(SkCanvas* canvas, int x, int y1, int y2, const SkPaint& paint)
{
    SkIRect skrect;
    skrect.set(x, y1, x + 1, y2 + 1);
    canvas->drawIRect(skrect, paint);
}

static void drawHorizLine(SkCanvas* canvas, int x1, int x2, int y, const SkPaint& paint)
{
    SkIRect skrect;
    skrect.set(x1, y, x2 + 1, y + 1);
    canvas->drawIRect(skrect, paint);
}

static void drawBox(SkCanvas* canvas, const IntRect& rect, const SkPaint& paint)
{
    const int right = rect.x() + rect.width() - 1;
    const int bottom = rect.y() + rect.height() - 1;
    drawHorizLine(canvas, rect.x(), right, rect.y(), paint);
    drawVertLine(canvas, right, rect.y(), bottom, paint);
    drawHorizLine(canvas, rect.x(), right, bottom, paint);
    drawVertLine(canvas, rect.x(), rect.y(), bottom, paint);
}

/* FYWEBKITMOD BEGIN */
#if ENABLE(VIDEO)
// Attempt to retrieve a HTMLMediaElement from a Node. Returns 0 if one cannot be found.
static HTMLMediaElement* mediaElementParent(Node* node)
{
    if (!node)
        return NULL;
    Node* mediaNode = node->shadowAncestorNode();
    if (!mediaNode || !mediaNode->isElementNode()) // NOT YET IN THIS WK? || !static_cast<Element*>(mediaNode)->isMediaElement())
        return NULL;

    return static_cast<HTMLMediaElement*>(mediaNode);
}
#endif
/* FYWEBKITMOD END */

// We aim to match IE here.
// -IE uses a font based on the encoding as the default font for form controls.
// -Gecko uses MS Shell Dlg (actually calls GetStockObject(DEFAULT_GUI_FONT),
// which returns MS Shell Dlg)
// -Safari uses Lucida Grande.
//
// FIXME: The only case where we know we don't match IE is for ANSI encodings.
// IE uses MS Shell Dlg there, which we render incorrectly at certain pixel
// sizes (e.g. 15px). So, for now we just use Arial.
const String& RenderThemeFymp::defaultGUIFont()
{
    DEFINE_STATIC_LOCAL(String, fontFace, ("Arial"));
    return fontFace;
}

float RenderThemeFymp::defaultFontSize = 16.0;

/* FYWEBKITMOD BEGIN */
PassRefPtr<RenderTheme> RenderThemeFymp::create()
{
    return adoptRef(new RenderThemeFymp());
}

PassRefPtr<RenderTheme> RenderTheme::themeForPage(Page* page)
{
    static RenderTheme* rt = RenderThemeFymp::create().releaseRef();
    return rt;
}

static struct {
	SkColor	darkGray;
	SkColor	mediumGray;
	SkColor	lightGray;
	SkColor	red;
	SkColor	white;
} _local;
/* FYWEBKITMOD END */

RenderThemeFymp::RenderThemeFymp()
{
/* FYWEBKITMOD BEGIN */
    _local.darkGray = SkColorSetARGB(255, 27, 27, 27);
    _local.mediumGray = SkColorSetARGB(255, 71, 71, 71);
    _local.lightGray = SkColorSetARGB(255, 117, 117, 117);
    _local.red = SkColorSetARGB(255, 185, 31, 31);
    _local.white = SkColorSetARGB(255, 255, 255, 255);
/* FYWEBKITMOD END */
}

RenderThemeFymp::~RenderThemeFymp()
{
}

String RenderThemeFymp::extraDefaultStyleSheet()
{
    return String(); // FYWEBKITMOD removed implementation
}

String RenderThemeFymp::extraQuirksStyleSheet()
{
    return String(); // FYWEBKITMOD removed implementation
}

#if ENABLE(VIDEO)
String RenderThemeFymp::extraMediaControlsStyleSheet()
{
/* FYWEBKITMOD BEGIN removed implementation */
	// AM120127: This 'extra' user agent style sheet seems to be generated via derived sources and ends up in "UserAgentStyleSheetsData.cpp"
	return String();
	//return String(mediaControlsChromiumUserAgentStyleSheet, sizeof(mediaControlsChromiumUserAgentStyleSheet));
/* FYWEBKITMOD END */
}
#endif

bool RenderThemeFymp::supportsHover(const RenderStyle* style) const
{
    return true;
}

bool RenderThemeFymp::supportsFocusRing(const RenderStyle* style) const
{
    // This causes WebKit to draw the focus rings for us.
    return false;
}

Color RenderThemeFymp::platformActiveSelectionBackgroundColor() const
{
    return Color(0x1e, 0x90, 0xff);
}

Color RenderThemeFymp::platformInactiveSelectionBackgroundColor() const
{
    return Color(0xc8, 0xc8, 0xc8);
}

Color RenderThemeFymp::platformActiveSelectionForegroundColor() const
{
    return Color::black;
}

Color RenderThemeFymp::platformInactiveSelectionForegroundColor() const
{
    return Color(0x32, 0x32, 0x32);
}

Color RenderThemeFymp::platformFocusRingColor() const
{
    static Color focusRingColor(229, 151, 0, 255);
    return focusRingColor;
}

double RenderThemeFymp::caretBlinkInterval() const
{
	// FYWEBKITMOD removed early return in case of test-mode to prevent interference with pixel tests
    return caretBlinkIntervalInternal();
}

void RenderThemeFymp::systemFont(int propId, FontDescription& fontDescription) const
{
    float fontSize = defaultFontSize;

    switch (propId) {
    case CSSValueWebkitMiniControl:
    case CSSValueWebkitSmallControl:
    case CSSValueWebkitControl:
        // Why 2 points smaller? Because that's what Gecko does. Note that we
        // are assuming a 96dpi screen, which is the default that we use on
        // Windows.
        static const float pointsPerInch = 96.0f; // FYWEBKITMOD changed from 72
        static const float pixelsPerInch = 96.0f;
        fontSize -= 0;//(2.0f / pointsPerInch) * pixelsPerInch; // FYWEBKITMOD disabled correction
        break;
    }

    fontDescription.firstFamily().setFamily(defaultGUIFont());
    fontDescription.setSpecifiedSize(fontSize);
    fontDescription.setIsAbsoluteSize(true);
    fontDescription.setGenericFamily(FontDescription::NoFamily);
    fontDescription.setWeight(FontWeightNormal);
    fontDescription.setItalic(false);
}

int RenderThemeFymp::minimumMenuListSize(RenderStyle* style) const
{
    return 0;
}

// These are the default dimensions of radio buttons and checkboxes.
static const int widgetStandardWidth = 13;
static const int widgetStandardHeight = 13;

// Return a rectangle that has the same center point as |original|, but with a
// size capped at |width| by |height|.
IntRect center(const IntRect& original, int width, int height)
{
    width = std::min(original.width(), width);
    height = std::min(original.height(), height);
    int x = original.x() + (original.width() - width) / 2;
    int y = original.y() + (original.height() - height) / 2;

    return IntRect(x, y, width, height);
}

bool RenderThemeFymp::paintCheckbox(RenderObject* o, const PaintInfo& i, const IntRect& rect)
{
    static Image* const checkedImage = Image::loadPlatformResource("linuxCheckboxOn").releaseRef();
    static Image* const uncheckedImage = Image::loadPlatformResource("linuxCheckboxOff").releaseRef();
    static Image* const indeterminateImage = Image::loadPlatformResource("linuxCheckboxIndeterminate").releaseRef();
    static Image* const disabledCheckedImage = Image::loadPlatformResource("linuxCheckboxDisabledOn").releaseRef();
    static Image* const disabledUncheckedImage = Image::loadPlatformResource("linuxCheckboxDisabledOff").releaseRef();
    static Image* const disabledIndeterminateImage = Image::loadPlatformResource("linuxCheckboxDisabledIndeterminate").releaseRef();

    Image* image;

    if (isIndeterminate(o))
        image = isEnabled(o) ? indeterminateImage : disabledIndeterminateImage;
    else if (isChecked(o))
        image = isEnabled(o) ? checkedImage : disabledCheckedImage;
    else
        image = isEnabled(o) ? uncheckedImage : disabledUncheckedImage;

    i.context->drawImage(image, o->style()->colorSpace(), center(rect, widgetStandardHeight, widgetStandardWidth));
    return false;
}

void RenderThemeFymp::setCheckboxSize(RenderStyle* style) const
{
    // If the width and height are both specified, then we have nothing to do.
    if (!style->width().isIntrinsicOrAuto() && !style->height().isAuto())
        return;

    // FIXME:  A hard-coded size of 13 is used.  This is wrong but necessary
    // for now.  It matches Firefox.  At different DPI settings on Windows,
    // querying the theme gives you a larger size that accounts for the higher
    // DPI.  Until our entire engine honors a DPI setting other than 96, we
    // can't rely on the theme's metrics.
    const IntSize size(widgetStandardHeight, widgetStandardWidth);
    setSizeIfAuto(style, size);
}

bool RenderThemeFymp::paintRadio(RenderObject* o, const PaintInfo& i, const IntRect& rect)
{
    static Image* const checkedImage = Image::loadPlatformResource("linuxRadioOn").releaseRef();
    static Image* const uncheckedImage = Image::loadPlatformResource("linuxRadioOff").releaseRef();
    static Image* const disabledCheckedImage = Image::loadPlatformResource("linuxRadioDisabledOn").releaseRef();
    static Image* const disabledUncheckedImage = Image::loadPlatformResource("linuxRadioDisabledOff").releaseRef();

    Image* image;
    if (this->isEnabled(o))
        image = this->isChecked(o) ? checkedImage : uncheckedImage;
    else
        image = this->isChecked(o) ? disabledCheckedImage : disabledUncheckedImage;

    i.context->drawImage(image, o->style()->colorSpace(), center(rect, widgetStandardHeight, widgetStandardWidth));
    return false;
}

void RenderThemeFymp::setRadioSize(RenderStyle* style) const
{
    // Use same sizing for radio box as checkbox.
    setCheckboxSize(style);
}

static SkColor brightenColor(double h, double s, double l, float brightenAmount)
{
    l += brightenAmount;
    if (l > 1.0)
        l = 1.0;
    if (l < 0.0)
        l = 0.0;

    return makeRGBAFromHSLA(h, s, l, 1.0);
}

static void paintButtonLike(RenderTheme* theme, RenderObject* o, const PaintInfo& i, const IntRect& rect)
{
    SkCanvas* const canvas = i.context->platformContext()->canvas();
    SkPaint paint;
    SkRect skrect;
    const int right = rect.x() + rect.width();
    const int bottom = rect.y() + rect.height();
    SkColor baseColor = SkColorSetARGB(0xff, 0xdd, 0xdd, 0xdd);
    if (o->hasBackground())
        baseColor = o->style()->visitedDependentColor(CSSPropertyBackgroundColor).rgb();
    double h, s, l;
    Color(baseColor).getHSL(h, s, l);
    // Our standard gradient is from 0xdd to 0xf8. This is the amount of
    // increased luminance between those values.
    SkColor lightColor(brightenColor(h, s, l, 0.105));

    // If the button is too small, fallback to drawing a single, solid color
    if (rect.width() < 5 || rect.height() < 5) {
        paint.setColor(baseColor);
        skrect.set(rect.x(), rect.y(), right, bottom);
        canvas->drawRect(skrect, paint);
        return;
    }

    const int borderAlpha = theme->isHovered(o) ? 0x80 : 0x55;
    paint.setARGB(borderAlpha, 0, 0, 0);
    canvas->drawLine(rect.x() + 1, rect.y(), right - 1, rect.y(), paint);
    canvas->drawLine(right - 1, rect.y() + 1, right - 1, bottom - 1, paint);
    canvas->drawLine(rect.x() + 1, bottom - 1, right - 1, bottom - 1, paint);
    canvas->drawLine(rect.x(), rect.y() + 1, rect.x(), bottom - 1, paint);

    paint.setColor(SK_ColorBLACK);
    SkPoint p[2];
    const int lightEnd = theme->isPressed(o) ? 1 : 0;
    const int darkEnd = !lightEnd;
    p[lightEnd].set(SkIntToScalar(rect.x()), SkIntToScalar(rect.y()));
    p[darkEnd].set(SkIntToScalar(rect.x()), SkIntToScalar(bottom - 1));
    SkColor colors[2];
    colors[0] = lightColor;
    colors[1] = baseColor;

    SkShader* shader = SkGradientShader::CreateLinear(
        p, colors, NULL, 2, SkShader::kClamp_TileMode, NULL);
    paint.setStyle(SkPaint::kFill_Style);
    paint.setShader(shader);
    shader->unref();

    skrect.set(rect.x() + 1, rect.y() + 1, right - 1, bottom - 1);
    canvas->drawRect(skrect, paint);

    paint.setShader(NULL);
    paint.setColor(brightenColor(h, s, l, -0.0588));
    canvas->drawPoint(rect.x() + 1, rect.y() + 1, paint);
    canvas->drawPoint(right - 2, rect.y() + 1, paint);
    canvas->drawPoint(rect.x() + 1, bottom - 2, paint);
    canvas->drawPoint(right - 2, bottom - 2, paint);
}

bool RenderThemeFymp::paintButton(RenderObject* o, const PaintInfo& i, const IntRect& rect)
{
    paintButtonLike(this, o, i, rect);
    return false;
}

void RenderThemeFymp::adjustButtonStyle(CSSStyleSelector*, RenderStyle* style, Element*) const
{
    if (style->appearance() == PushButtonPart) {
        // Ignore line-height.
        style->setLineHeight(RenderStyle::initialLineHeight());
    }
}


bool RenderThemeFymp::paintTextField(RenderObject* o, const PaintInfo& i, const IntRect& rect)
{
    return true;
}

bool RenderThemeFymp::paintTextArea(RenderObject* o, const PaintInfo& i, const IntRect& r)
{
    return paintTextField(o, i, r);
}

void RenderThemeFymp::adjustSearchFieldStyle(CSSStyleSelector*, RenderStyle* style, Element*) const
{
     // Ignore line-height.
     style->setLineHeight(RenderStyle::initialLineHeight());
}

bool RenderThemeFymp::paintSearchField(RenderObject* o, const PaintInfo& i, const IntRect& r)
{
    return paintTextField(o, i, r);
}

void RenderThemeFymp::adjustSearchFieldCancelButtonStyle(CSSStyleSelector*, RenderStyle* style, Element*) const
{
    // Scale the button size based on the font size
    float fontScale = style->fontSize() / defaultControlFontPixelSize;
    int cancelButtonSize = lroundf(std::min(std::max(minCancelButtonSize, defaultCancelButtonSize * fontScale), maxCancelButtonSize));
    style->setWidth(Length(cancelButtonSize, Fixed));
    style->setHeight(Length(cancelButtonSize, Fixed));
}

IntRect RenderThemeFymp::convertToPaintingRect(RenderObject* inputRenderer, const RenderObject* partRenderer, IntRect partRect, const IntRect& localOffset) const
{
    // Compute an offset between the part renderer and the input renderer.
    IntSize offsetFromInputRenderer = -(partRenderer->offsetFromAncestorContainer(inputRenderer));
    // Move the rect into partRenderer's coords.
    partRect.move(offsetFromInputRenderer);
    // Account for the local drawing offset.
    partRect.move(localOffset.x(), localOffset.y());

    return partRect;
}

bool RenderThemeFymp::paintSearchFieldCancelButton(RenderObject* cancelButtonObject, const PaintInfo& paintInfo, const IntRect& r)
{
    // Get the renderer of <input> element.
    Node* input = cancelButtonObject->node()->shadowAncestorNode();
    if (!input->renderer()->isBox())
        return false;
    RenderBox* inputRenderBox = toRenderBox(input->renderer());
    IntRect inputContentBox = inputRenderBox->contentBoxRect();

    // Make sure the scaled button stays square and will fit in its parent's box.
    int cancelButtonSize = std::min(inputContentBox.width(), std::min(inputContentBox.height(), r.height()));
    // Calculate cancel button's coordinates relative to the input element.
    // Center the button vertically.  Round up though, so if it has to be one pixel off-center, it will
    // be one pixel closer to the bottom of the field.  This tends to look better with the text.
    IntRect cancelButtonRect(cancelButtonObject->offsetFromAncestorContainer(inputRenderBox).width(),
                             inputContentBox.y() + (inputContentBox.height() - cancelButtonSize + 1) / 2,
                             cancelButtonSize, cancelButtonSize);
    IntRect paintingRect = convertToPaintingRect(inputRenderBox, cancelButtonObject, cancelButtonRect, r);

    static Image* cancelImage = Image::loadPlatformResource("searchCancel").releaseRef();
    static Image* cancelPressedImage = Image::loadPlatformResource("searchCancelPressed").releaseRef();
    paintInfo.context->drawImage(isPressed(cancelButtonObject) ? cancelPressedImage : cancelImage,
                                 cancelButtonObject->style()->colorSpace(), paintingRect);
    return false;
}

void RenderThemeFymp::adjustSearchFieldDecorationStyle(CSSStyleSelector*, RenderStyle* style, Element*) const
{
    IntSize emptySize(1, 11);
    style->setWidth(Length(emptySize.width(), Fixed));
    style->setHeight(Length(emptySize.height(), Fixed));
}

void RenderThemeFymp::adjustSearchFieldResultsDecorationStyle(CSSStyleSelector*, RenderStyle* style, Element*) const
{
    // Scale the decoration size based on the font size
    float fontScale = style->fontSize() / defaultControlFontPixelSize;
    int magnifierSize = lroundf(std::min(std::max(minSearchFieldResultsDecorationSize, defaultSearchFieldResultsDecorationSize * fontScale),
                                         maxSearchFieldResultsDecorationSize));
    style->setWidth(Length(magnifierSize, Fixed));
    style->setHeight(Length(magnifierSize, Fixed));
}

bool RenderThemeFymp::paintSearchFieldResultsDecoration(RenderObject* magnifierObject, const PaintInfo& paintInfo, const IntRect& r)
{
    // Get the renderer of <input> element.
    Node* input = magnifierObject->node()->shadowAncestorNode();
    if (!input->renderer()->isBox())
        return false;
    RenderBox* inputRenderBox = toRenderBox(input->renderer());
    IntRect inputContentBox = inputRenderBox->contentBoxRect();

    // Make sure the scaled decoration stays square and will fit in its parent's box.
    int magnifierSize = std::min(inputContentBox.width(), std::min(inputContentBox.height(), r.height()));
    // Calculate decoration's coordinates relative to the input element.
    // Center the decoration vertically.  Round up though, so if it has to be one pixel off-center, it will
    // be one pixel closer to the bottom of the field.  This tends to look better with the text.
    IntRect magnifierRect(magnifierObject->offsetFromAncestorContainer(inputRenderBox).width(),
                          inputContentBox.y() + (inputContentBox.height() - magnifierSize + 1) / 2,
                          magnifierSize, magnifierSize);
    IntRect paintingRect = convertToPaintingRect(inputRenderBox, magnifierObject, magnifierRect, r);

    static Image* magnifierImage = Image::loadPlatformResource("searchMagnifier").releaseRef();
    paintInfo.context->drawImage(magnifierImage, magnifierObject->style()->colorSpace(), paintingRect);
    return false;
}

void RenderThemeFymp::adjustSearchFieldResultsButtonStyle(CSSStyleSelector*, RenderStyle* style, Element*) const
{
    // Scale the button size based on the font size
    float fontScale = style->fontSize() / defaultControlFontPixelSize;
    int magnifierHeight = lroundf(std::min(std::max(minSearchFieldResultsDecorationSize, defaultSearchFieldResultsDecorationSize * fontScale),
                                           maxSearchFieldResultsDecorationSize));
    int magnifierWidth = lroundf(magnifierHeight * defaultSearchFieldResultsButtonWidth / defaultSearchFieldResultsDecorationSize);
    style->setWidth(Length(magnifierWidth, Fixed));
    style->setHeight(Length(magnifierHeight, Fixed));
}

bool RenderThemeFymp::paintSearchFieldResultsButton(RenderObject* magnifierObject, const PaintInfo& paintInfo, const IntRect& r)
{
    // Get the renderer of <input> element.
    Node* input = magnifierObject->node()->shadowAncestorNode();
    if (!input->renderer()->isBox())
        return false;
    RenderBox* inputRenderBox = toRenderBox(input->renderer());
    IntRect inputContentBox = inputRenderBox->contentBoxRect();

    // Make sure the scaled decoration will fit in its parent's box.
    int magnifierHeight = std::min(inputContentBox.height(), r.height());
    int magnifierWidth = std::min(inputContentBox.width(), static_cast<int>(magnifierHeight * defaultSearchFieldResultsButtonWidth / defaultSearchFieldResultsDecorationSize));
    IntRect magnifierRect(magnifierObject->offsetFromAncestorContainer(inputRenderBox).width(),
                          inputContentBox.y() + (inputContentBox.height() - magnifierHeight + 1) / 2,
                          magnifierWidth, magnifierHeight);
    IntRect paintingRect = convertToPaintingRect(inputRenderBox, magnifierObject, magnifierRect, r);

    static Image* magnifierImage = Image::loadPlatformResource("searchMagnifierResults").releaseRef();
    paintInfo.context->drawImage(magnifierImage, magnifierObject->style()->colorSpace(), paintingRect);
    return false;
}

bool RenderThemeFymp::paintMediaControlsBackground(RenderObject* object, const PaintInfo& paintInfo, const IntRect& rect)
{
#if ENABLE(VIDEO)
/* FYWEBKITMOD BEGIN */
    SkCanvas* const canvas = paintInfo.context->platformContext()->canvas();
    SkPaint paint;
    SkRect skrect;

	// Background
    if (object->hasBackground())
        paint.setColor(object->style()->visitedDependentColor(CSSPropertyBackgroundColor).rgb());
	else
		paint.setColor(_local.darkGray);
	skrect.set(rect.x(), rect.y(), rect.right(), rect.bottom());
	canvas->drawRect(skrect, paint);
	return true;
/* FYWEBKITMOD END */
#else
    UNUSED_PARAM(object);
    UNUSED_PARAM(paintInfo);
    UNUSED_PARAM(rect);
    return false;
#endif
}

bool RenderThemeFymp::paintMediaSliderTrack(RenderObject* object, const PaintInfo& paintInfo, const IntRect& rect)
{
#if ENABLE(VIDEO)
/* FYWEBKITMOD BEGIN */
    SkCanvas* const canvas = paintInfo.context->platformContext()->canvas();
    SkPaint paint;
    SkRect skrect;

	// Background
    if (object->hasBackground())
        paint.setColor(object->style()->visitedDependentColor(CSSPropertyBackgroundColor).rgb());
	else
        paint.setColor(_local.darkGray);
	skrect.set(rect.x(), rect.y(), rect.right(), rect.bottom());
	canvas->drawRect(skrect, paint);

	// The progress indicator
	HTMLMediaElement *mediaElement = mediaElementParent(object->node());
	if (mediaElement)
	{
		float yt = rect.y() + rect.height() * 0.25f;
		float yb = rect.y() + rect.height() * 0.75f;

		float duration = mediaElement->duration();
		if (isinf(duration) || isnan(duration))
			duration = 0.0f;

		float playX = rect.x() + ((duration <= 0.0f) ? 0.0f : (rect.width() * mediaElement->currentTime() / duration));
		float loadX = rect.x() + mediaElement->percentLoaded() * rect.width();

		// Play position
		paint.setColor(_local.red);
		skrect.set(rect.x(), yt, playX, yb);
		canvas->drawRect(skrect, paint);

		// Load ahead range (if any)
		if (loadX > playX)
		{
			paint.setColor(_local.lightGray);
			skrect.set(playX, yt, loadX, yb);
			canvas->drawRect(skrect, paint);
		}

		// Remaining slider core
		paint.setColor(_local.mediumGray);
		skrect.set(std::max(playX, loadX), yt, rect.right(), yb);
		canvas->drawRect(skrect, paint);
	}
	return true;
/* FYWEBKITMOD END */
#else
    UNUSED_PARAM(object);
    UNUSED_PARAM(paintInfo);
    UNUSED_PARAM(rect);
    return false;
#endif
}

bool RenderThemeFymp::paintMediaVolumeSliderTrack(RenderObject* object, const PaintInfo& paintInfo, const IntRect& rect)
{
/* FYWEBKITMOD BEGIN disabled */
#if 0 //ENABLE(VIDEO)
//    return RenderMediaControlsChromium::paintMediaControlsPart(MediaVolumeSlider, object, paintInfo, rect);
//DO WE NEED THIS? -> MIGHT WANT TO DISABLE IT. UNIT HAS A PHYSCIAL SLIDER FOR VOLUME! ;-)
/* FYWEBKITMOD END */
#else
    UNUSED_PARAM(object);
    UNUSED_PARAM(paintInfo);
    UNUSED_PARAM(rect);
    return false;
#endif
}

void RenderThemeFymp::adjustSliderThumbSize(RenderObject* object) const
{
#if 0 // ENABLE(VIDEO) // FYWEBKITMOD disabled
    RenderMediaControlsChromium::adjustMediaSliderThumbSize(object);
#else
    UNUSED_PARAM(object);
#endif
}

bool RenderThemeFymp::paintMediaSliderThumb(RenderObject* object, const PaintInfo& paintInfo, const IntRect& rect)
{
#if ENABLE(VIDEO)
/* FYWEBKITMOD BEGIN */
//    return RenderMediaControlsChromium::paintMediaControlsPart(MediaSliderThumb, object, paintInfo, rect);
//DUMMY
    SkCanvas* const canvas = paintInfo.context->platformContext()->canvas();
    SkPaint paint;
    SkRect skrect;

    SkColor baseColor = SkColorSetARGB(0xff, 0xff, 0xff, 0xff);
    if (object->hasBackground())
        baseColor = object->style()->visitedDependentColor(CSSPropertyBackgroundColor).rgb();

	paint.setColor(baseColor);
	skrect.set(rect.x(), rect.y(), rect.right(), rect.bottom());
	canvas->drawRect(skrect, paint);
	return true;
/* FYWEBKITMOD END */
#else
    UNUSED_PARAM(object);
    UNUSED_PARAM(paintInfo);
    UNUSED_PARAM(rect);
    return false;
#endif
}

bool RenderThemeFymp::paintMediaVolumeSliderThumb(RenderObject* object, const PaintInfo& paintInfo, const IntRect& rect)
{
#if 0 //ENABLE(VIDEO) // FYWEBKITMOD disabled
//DO WE NEED THIS? -> MIGHT WANT TO DISABLE IT. UNIT HAS A PHYSCIAL SLIDER FOR VOLUME! ;-)
//    return RenderMediaControlsChromium::paintMediaControlsPart(MediaVolumeSliderThumb, object, paintInfo, rect);
#else
    UNUSED_PARAM(object);
    UNUSED_PARAM(paintInfo);
    UNUSED_PARAM(rect);
    return false;
#endif
}

bool RenderThemeFymp::paintMediaPlayButton(RenderObject* object, const PaintInfo& paintInfo, const IntRect& rect)
{
#if ENABLE(VIDEO)
/* FYWEBKITMOD BEGIN */
    SkCanvas* const canvas = paintInfo.context->platformContext()->canvas();
    SkPaint paint;
    SkRect skrect;

    if (object->hasBackground())
        paint.setColor(object->style()->visitedDependentColor(CSSPropertyBackgroundColor).rgb());
	else
		paint.setColor(_local.darkGray);
	skrect.set(rect.x(), rect.y(), rect.right(), rect.bottom());
	canvas->drawRect(skrect, paint);

	paint.setColor(_local.lightGray);

	bool bPlaying = false;
	HTMLMediaElement *mediaElement = mediaElementParent(object->node());
	if (mediaElement)
		bPlaying = !mediaElement->paused();

	if (bPlaying)
	{
		// Pause symbol

		float bw = rect.width() * (1.0f / 5.0f);
		float bh = rect.height() * 0.5f;
		float byt = rect.y() + bh * 0.5f;
		float byb = byt + bh;
	
		skrect.set(rect.x() + 1.0f * bw, byt, rect.x() + 2.0f * bw, byb);
		canvas->drawRect(skrect, paint);
		skrect.set(rect.x() + 3.0f * bw, byt, rect.x() + 4.0f * bw, byb);
		canvas->drawRect(skrect, paint);
	}
	else
	{
		// Play symbol

		float dx = rect.width() * (3.0f / 5.0f);
		float dy = rect.height() * 0.25f;

		SkPath tri;
		tri.moveTo(rect.x() + rect.width() * (1.0f / 5.0f), rect.y() + rect.height() * (1.0f / 4.0f));
		tri.rLineTo( dx, dy);
		tri.rLineTo(-dx, dy);
		tri.rLineTo(0.0f, -2.0f * dy);
//		tri.close();
		canvas->drawPath(tri, paint);
	}

	return true;
/* FYWEBKITMOD END */
#else
    UNUSED_PARAM(object);
    UNUSED_PARAM(paintInfo);
    UNUSED_PARAM(rect);
    return false;
#endif
}

bool RenderThemeFymp::paintMediaMuteButton(RenderObject* object, const PaintInfo& paintInfo, const IntRect& rect)
{
#if 0 // ENABLE(VIDEO) // FYWEBKITMOD disabled
    return RenderMediaControlsChromium::paintMediaControlsPart(MediaMuteButton, object, paintInfo, rect);
#else
    UNUSED_PARAM(object);
    UNUSED_PARAM(paintInfo);
    UNUSED_PARAM(rect);
    return false;
#endif
}

void RenderThemeFymp::adjustMenuListStyle(CSSStyleSelector* selector, RenderStyle* style, WebCore::Element* e) const
{
    // Height is locked to auto on all browsers.
    style->setLineHeight(RenderStyle::initialLineHeight());
}

bool RenderThemeFymp::paintMenuList(RenderObject* o, const PaintInfo& i, const IntRect& rect)
{
    SkCanvas* const canvas = i.context->platformContext()->canvas();
    const int right = rect.x() + rect.width();
    const int middle = rect.y() + rect.height() / 2;

    paintButtonLike(this, o, i, rect);

    SkPaint paint;
    paint.setColor(SK_ColorBLACK);
    paint.setAntiAlias(true);
    paint.setStyle(SkPaint::kFill_Style);

    int arrowXPosition = (o->style()->direction() == RTL) ? rect.x() + 7 : right - 13;
    SkPath path;
    path.moveTo(arrowXPosition, middle - 3);
    path.rLineTo(6, 0);
    path.rLineTo(-3, 6);
    path.close();
    canvas->drawPath(path, paint);

    return false;
}

void RenderThemeFymp::adjustMenuListButtonStyle(CSSStyleSelector* selector, RenderStyle* style, Element* e) const
{
    adjustMenuListStyle(selector, style, e);
}

// Used to paint styled menulists (i.e. with a non-default border)
bool RenderThemeFymp::paintMenuListButton(RenderObject* o, const PaintInfo& i, const IntRect& rect)
{
    return paintMenuList(o, i, rect);
}

bool RenderThemeFymp::paintSliderTrack(RenderObject*, const PaintInfo& i, const IntRect& rect)
{
    // Just paint a grey box for now (matches the color of a scrollbar background.
    SkCanvas* const canvas = i.context->platformContext()->canvas();
    int verticalCenter = rect.y() + rect.height() / 2;
    int top = std::max(rect.y(), verticalCenter - 2);
    int bottom = std::min(rect.y() + rect.height(), verticalCenter + 2);

    SkPaint paint;
    const SkColor grey = SkColorSetARGB(0xff, 0xe3, 0xdd, 0xd8);
    paint.setColor(grey);

    SkRect skrect;
    skrect.set(rect.x(), top, rect.x() + rect.width(), bottom);
    canvas->drawRect(skrect, paint);

    return false;
}

bool RenderThemeFymp::paintSliderThumb(RenderObject* o, const PaintInfo& i, const IntRect& rect)
{
    // Make a thumb similar to the scrollbar thumb.
    const bool hovered = isHovered(o) || toRenderSlider(o->parent())->inDragMode();
    const int midx = rect.x() + rect.width() / 2;
    const int midy = rect.y() + rect.height() / 2;
    const bool vertical = (o->style()->appearance() == SliderThumbVerticalPart);
    SkCanvas* const canvas = i.context->platformContext()->canvas();

    const SkColor thumbLightGrey = SkColorSetARGB(0xff, 0xf4, 0xf2, 0xef);
    const SkColor thumbDarkGrey = SkColorSetARGB(0xff, 0xea, 0xe5, 0xe0);
    SkPaint paint;
    paint.setColor(hovered ? SK_ColorWHITE : thumbLightGrey);

    SkIRect skrect;
    if (vertical)
        skrect.set(rect.x(), rect.y(), midx + 1, rect.bottom());
    else
        skrect.set(rect.x(), rect.y(), rect.right(), midy + 1);

    canvas->drawIRect(skrect, paint);

    paint.setColor(hovered ? thumbLightGrey : thumbDarkGrey);

    if (vertical)
        skrect.set(midx + 1, rect.y(), rect.right(), rect.bottom());
    else
        skrect.set(rect.x(), midy + 1, rect.right(), rect.bottom());

    canvas->drawIRect(skrect, paint);

    const SkColor borderDarkGrey = SkColorSetARGB(0xff, 0x9d, 0x96, 0x8e);
    paint.setColor(borderDarkGrey);
    drawBox(canvas, rect, paint);

    if (rect.height() > 10 && rect.width() > 10) {
        drawHorizLine(canvas, midx - 2, midx + 2, midy, paint);
        drawHorizLine(canvas, midx - 2, midx + 2, midy - 3, paint);
        drawHorizLine(canvas, midx - 2, midx + 2, midy + 3, paint);
    }

    return false;
}

int RenderThemeFymp::popupInternalPaddingLeft(RenderStyle* style) const
{
    return menuListInternalPadding(style, LeftPadding);
}

int RenderThemeFymp::popupInternalPaddingRight(RenderStyle* style) const
{
    return menuListInternalPadding(style, RightPadding);
}

int RenderThemeFymp::popupInternalPaddingTop(RenderStyle* style) const
{
    return menuListInternalPadding(style, TopPadding);
}

int RenderThemeFymp::popupInternalPaddingBottom(RenderStyle* style) const
{
    return menuListInternalPadding(style, BottomPadding);
}

#if ENABLE(VIDEO)
bool RenderThemeFymp::shouldRenderMediaControlPart(ControlPart part, Element* e)
{
/* FYWEBKITMOD BEGIN inlining code (RenderMediaControlsChromium::shouldRenderMediaControlPart(part, e);) */
    UNUSED_PARAM(e);
    switch (part) {
    case MediaMuteButtonPart:
    case MediaPlayButtonPart:
    case MediaSliderPart:
    case MediaSliderThumbPart:
    case MediaVolumeSliderContainerPart:
    case MediaVolumeSliderPart:
    case MediaVolumeSliderThumbPart:
    case MediaControlsBackgroundPart:
    case MediaCurrentTimePart:
    case MediaTimeRemainingPart:
        return true;
    default:
        ;
    }
    return false;
/* FYWEBKITMOD END */
}
#endif

// static
void RenderThemeFymp::setDefaultFontSize(int fontSize)
{
    defaultFontSize = static_cast<float>(fontSize);
}

double RenderThemeFymp::caretBlinkIntervalInternal() const
{
    return RenderTheme::caretBlinkInterval();
}

int RenderThemeFymp::menuListInternalPadding(RenderStyle* style, int paddingType) const
{
    // This internal padding is in addition to the user-supplied padding.
    // Matches the FF behavior.
    int padding = styledMenuListInternalPadding[paddingType];

    // Reserve the space for right arrow here. The rest of the padding is
    // set by adjustMenuListStyle, since PopMenuWin.cpp uses the padding from
    // RenderMenuList to lay out the individual items in the popup.
    // If the MenuList actually has appearance "NoAppearance", then that means
    // we don't draw a button, so don't reserve space for it.
    const int barType = style->direction() == LTR ? RightPadding : LeftPadding;
    if (paddingType == barType && style->appearance() != NoControlPart)
        padding += ScrollbarTheme::nativeTheme()->scrollbarThickness();

    return padding;
}

#if ENABLE(PROGRESS_TAG)

//
// Following values are come from default of GTK+
//
static const int progressDeltaPixelsPerSecond = 100;
static const int progressActivityBlocks = 5;
static const int progressAnimationFrmaes = 10;
static const double progressAnimationInterval = 0.125;

IntRect RenderThemeFymp::determinateProgressValueRectFor(RenderProgress* renderProgress, const IntRect& rect) const
{
    int dx = rect.width() * renderProgress->position();
    if (renderProgress->style()->direction() == RTL)
        return IntRect(rect.x() + rect.width() - dx, rect.y(), dx, rect.height());
    return IntRect(rect.x(), rect.y(), dx, rect.height());
}

IntRect RenderThemeFymp::indeterminateProgressValueRectFor(RenderProgress* renderProgress, const IntRect& rect) const
{

    int valueWidth = rect.width() / progressActivityBlocks;
    int movableWidth = rect.width() - valueWidth;
    if (movableWidth <= 0)
        return IntRect();

    double progress = renderProgress->animationProgress();
    if (progress < 0.5)
        return IntRect(rect.x() + progress * 2 * movableWidth, rect.y(), valueWidth, rect.height());
    return IntRect(rect.x() + (1.0 - progress) * 2 * movableWidth, rect.y(), valueWidth, rect.height());
}

double RenderThemeFymp::animationRepeatIntervalForProgressBar(RenderProgress*) const
{
    return progressAnimationInterval;
}

double RenderThemeFymp::animationDurationForProgressBar(RenderProgress* renderProgress) const
{
    return progressAnimationInterval * progressAnimationFrmaes * 2; // "2" for back and forth
}

bool RenderThemeFymp::paintProgressBar(RenderObject* renderObject, const PaintInfo& paintInfo, const IntRect& rect)
{
    static Image* barImage = Image::loadPlatformResource("linuxProgressBar").releaseRef();
    static Image* valueImage = Image::loadPlatformResource("linuxProgressValue").releaseRef();
    static Image* leftBorderImage = Image::loadPlatformResource("linuxProgressBorderLeft").releaseRef();
    static Image* rightBorderImage = Image::loadPlatformResource("linuxProgressBorderRight").releaseRef();
    ASSERT(barImage->height() == valueImage->height());

    if (!renderObject->isProgress())
        return true;

    paintInfo.context->platformContext()->setImageResamplingHint(barImage->size(), rect.size());

    RenderProgress* renderProgress = toRenderProgress(renderObject);
    double tileScale = static_cast<double>(rect.height()) / barImage->height();
    IntSize barTileSize(static_cast<int>(barImage->width() * tileScale), rect.height());
    ColorSpace colorSpace = renderObject->style()->colorSpace();

    paintInfo.context->drawTiledImage(barImage, colorSpace, rect, IntPoint(0, 0), barTileSize);

    IntRect valueRect = progressValueRectFor(renderProgress, rect);
    if (valueRect.width()) {

        IntSize valueTileSize(static_cast<int>(valueImage->width() * tileScale), valueRect.height());
        int leftOffset = valueRect.x() - rect.x();
        int roundedLeftOffset= (leftOffset / valueTileSize.width()) * valueTileSize.width();
        int dstLeftValueWidth = roundedLeftOffset - leftOffset + (leftOffset % valueImage->width()) ? valueTileSize.width() : 0;

        IntRect dstLeftValueRect(valueRect.x(), valueRect.y(), dstLeftValueWidth, valueRect.height());
        int srcLeftValueWidth = dstLeftValueWidth / tileScale;
        IntRect srcLeftValueRect(valueImage->width() - srcLeftValueWidth, 0, srcLeftValueWidth, valueImage->height());
        paintInfo.context->drawImage(valueImage, colorSpace, dstLeftValueRect, srcLeftValueRect);

        int rightOffset = valueRect.right() - rect.x();
        int roundedRightOffset = (rightOffset / valueTileSize.width()) * valueTileSize.width();
        int dstRightValueWidth = rightOffset - roundedRightOffset;
        IntRect dstRightValueRect(rect.x() + roundedRightOffset, valueRect.y(), dstRightValueWidth, valueTileSize.height());
        int srcRightValueWidth = dstRightValueWidth / tileScale;
        IntRect srcRightValueRect(0, 0, srcRightValueWidth, valueImage->height());
        paintInfo.context->drawImage(valueImage, colorSpace, dstRightValueRect, srcRightValueRect);

        IntRect alignedValueRect(dstLeftValueRect.right(), dstLeftValueRect.y(),
                                 dstRightValueRect.x() - dstLeftValueRect.right(), dstLeftValueRect.height());
        paintInfo.context->drawTiledImage(valueImage, colorSpace, alignedValueRect, IntPoint(0, 0), valueTileSize);
    }

    int dstLeftBorderWidth = leftBorderImage->width() * tileScale;
    IntRect dstLeftBorderRect(rect.x(), rect.y(), dstLeftBorderWidth, rect.height());
    paintInfo.context->drawImage(leftBorderImage, colorSpace, dstLeftBorderRect, leftBorderImage->rect());

    int dstRightBorderWidth = rightBorderImage->width() * tileScale;
    IntRect dstRightBorderRect(rect.right() - dstRightBorderWidth, rect.y(), dstRightBorderWidth, rect.height());
    paintInfo.context->drawImage(rightBorderImage, colorSpace, dstRightBorderRect, rightBorderImage->rect());

    paintInfo.context->platformContext()->clearImageResamplingHint();

    return false;
}


IntRect RenderThemeFymp::progressValueRectFor(RenderProgress* renderProgress, const IntRect& rect) const
{
    return renderProgress->isDeterminate() ? determinateProgressValueRectFor(renderProgress, rect) : indeterminateProgressValueRectFor(renderProgress, rect);
}

#endif

} // namespace WebCore

/* FYWEBKITMOD END */
