#include "config.h"
#include "LastJavaScriptCall.h"

namespace WebKit {

	JSCallInfo JSCallInfo::sLastCall;

	JSCallInfo::JSCallInfo()
	: mLine(-1), mUrl(0), mCallerName(0), mCalleeName(0)
	{}

	JSCallInfo::~JSCallInfo()
		{
		if (mUrl)         delete[] mUrl;
		if (mCallerName)  delete[] mCallerName;
		if (mCalleeName)  delete[] mCalleeName;
		}

	void JSCallInfo::setLine(int line)
		{
		mLine = line;
		}

	void JSCallInfo::setUrl(const UChar *url, int length)
		{
		convert(url, length, &mUrl);
		}

	void JSCallInfo::setCallerName(const UChar *name, int length)
		{
		convert(name, length, &mCallerName);
		}

	void JSCallInfo::setCalleeName(const UChar *name, int length)
		{
		convert(name, length, &mCalleeName);
		}

	void JSCallInfo::convert(const UChar *source, int length, char **pTarget)
		{
		unsigned neededSize = length + 1;
		if (*pTarget)
			delete[] *pTarget;

		*pTarget = new char[neededSize];

		const UChar*     p = source;
		char*            q = *pTarget;
		const UChar* limit = p + length;
		while (p != limit) {
			*q = static_cast<char>(p[0]);
			++p;
			++q;
			}
		*q = '\0';
		}

	}


