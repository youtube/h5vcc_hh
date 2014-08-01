
/* FYWEBKITMOD BEGIN custom extension. support for '::cue' style definitions in WebVTT files. */

#ifndef TextTrackStyle_h
#define TextTrackStyle_h

#if ENABLE(VIDEO_TRACK) && ENABLE(WEBVTT_STYLES)

#include "FloatPoint.h"
#include "TextTrack.h"

#include <wtf/PassOwnPtr.h>
#include <wtf/RefCounted.h>
#include <wtf/HashMap.h>
#include <wtf/text/WTFString.h>


namespace WebCore {

class TextTrackStyle : public RefCounted<TextTrackStyle> {
public:
    static PassRefPtr<TextTrackStyle> create()
    {
        return adoptRef(new TextTrackStyle());
    }

    virtual ~TextTrackStyle();

	String selector()  { return m_selector; }
	String style()     { return m_style; }
	String styleJSON() { return m_styleJSON; }

    void parseStyle(const String& webvttLine);

private:
    TextTrackStyle();

    String m_selector;
	String m_style;
	String m_styleJSON;

	int parseNextKeyValue(const String& line, int startPos); //! Returns start pos of next key/value pair or -1 if end was reached.


};

} // namespace WebCore

#endif
#endif

/* FYWEBKITMOD END */
