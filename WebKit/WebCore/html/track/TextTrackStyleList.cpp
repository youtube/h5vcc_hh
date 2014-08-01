/* FYWEBKITMOD BEGIN custom extension. Support for '::cue' style definitions in WebVTT files. */

#include "config.h"

#if ENABLE(VIDEO_TRACK) && ENABLE(WEBVTT_STYLES)

#include "TextTrackStyleList.h"

namespace WebCore {

TextTrackStyleList::TextTrackStyleList()
{
}

unsigned long TextTrackStyleList::length() const
{
    return m_list.size();
}

TextTrackStyle* TextTrackStyleList::item(unsigned index) const
{
    if (index < m_list.size())
        return m_list[index].get();

    return 0;
}

void TextTrackStyleList::add(PassRefPtr<TextTrackStyle> region)
{
    m_list.append(region);
}

void TextTrackStyleList::clear()
{
    m_list.clear();
}

} // namespace WebCore

#endif
/* FYWEBKITMOD END */
