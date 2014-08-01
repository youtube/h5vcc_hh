

/* FYWEBKITMOD BEGIN custom extension. support for '::cue' style definitions in WebVTT files. */

#include "config.h"

#if ENABLE(VIDEO_TRACK) && ENABLE(WEBVTT_STYLES)

#include "TextTrackStyle.h"
#include "WebVTTParser.h"


namespace WebCore {


TextTrackStyle::TextTrackStyle()
    : m_selector(emptyString())
    , m_style(emptyString())
{
}

TextTrackStyle::~TextTrackStyle()
{
}

void TextTrackStyle::parseStyle(const String& webvttLine)
{
	// parse selector
	int openBracket  = webvttLine.find('(',0);
	int closeBracket = webvttLine.find(')',0);

	if (openBracket != -1 && closeBracket != -1 && openBracket < closeBracket)
		{
		m_selector = webvttLine.substring(openBracket+1, closeBracket - openBracket - 1).stripWhiteSpace();
		}

	// parse style
	int startStyle = webvttLine.find('{', 0);
	if (startStyle != -1)
		{
		m_style = webvttLine.substring(startStyle).stripWhiteSpace();
		}

	// parse all key/value pairs in the style.
	m_styleJSON.append('{');
	int startKeyValue = startStyle + 1;
	while (startKeyValue != -1)
		{
		startKeyValue = parseNextKeyValue(webvttLine, startKeyValue);
		}
	m_styleJSON.truncate(m_styleJSON.length() - 1);
	m_styleJSON.append('}');

	return;
}

int TextTrackStyle::parseNextKeyValue(const String& line, int startPos)
{
	int startKey = startPos;
	int endKey   = line.find(':', startKey);
	if (endKey == -1 || endKey == line.length() - 1)
		return -1;

	String key = line.substring(startKey, endKey - startKey).stripWhiteSpace();

	int startVal = endKey + 1;
	int endVal = line.find(',', startVal);
	if (endVal == -1)
		{
		endVal = line.find(';', startVal);
		if (endVal == -1)
			{
			endVal = line.find('}', startVal);
			}
		}
	if (endVal == -1)
		{
		return -1;
		}

	String value = line.substring(startVal, endVal - startVal).stripWhiteSpace();

	m_styleJSON.append('"');
	m_styleJSON.append(key);
	m_styleJSON.append('"');
	m_styleJSON.append(':');
	m_styleJSON.append('"');
	m_styleJSON.append(value);
	m_styleJSON.append("\",");

	if (endVal < line.length() + 1) // is there the chance that there are more value/key pairs?
		{
		return endVal + 1;
		}

	return -1;
}

} // namespace WebCore

#endif

/* FYWEBKITMOD END */
