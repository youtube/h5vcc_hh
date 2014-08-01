
/* FYWEBKITMOD BEGIN custom extension. Support for '::cue' style definitions in WebVTT files. */

#ifndef TextTrackStyleList_h
#define TextTrackStyleList_h

#if ENABLE(VIDEO_TRACK) && ENABLE(WEBVTT_STYLES)

#include "TextTrackStyle.h"
#include <wtf/PassRefPtr.h>
#include <wtf/RefCounted.h>
#include <wtf/Vector.h>

namespace WebCore {

class TextTrackStyleList : public RefCounted<TextTrackStyleList> {
public:
    static PassRefPtr<TextTrackStyleList> create()
    {
        return adoptRef(new TextTrackStyleList());
    }

    ~TextTrackStyleList() { }

    unsigned long length() const;

    TextTrackStyle* item(unsigned index) const;

    void add(PassRefPtr<TextTrackStyle>);

private:
    TextTrackStyleList();
    void clear();

    Vector<RefPtr<TextTrackStyle> > m_list;
};

} // namespace WebCore

#endif
#endif
/* FYWEBKITMOD END */
