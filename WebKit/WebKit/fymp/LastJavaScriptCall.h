#ifndef LASTJAVASCRIPTCALL_H
#define LASTJAVASCRIPTCALL_H

#include "unicode\umachine.h"

// uncomment to enable info on last javascript call in red-screen-of-death. This brings performance hit with every call of a javascript function.
//#define FYCOLLECTLASTJAVASCRIPTCALLINFO

namespace WebKit {

	class JSCallInfo
		{
	public:
		static JSCallInfo sLastCall;

		JSCallInfo();
		~JSCallInfo();

		void setLine      (int line);
		void setUrl       (const UChar *url,  int length);
		void setCallerName(const UChar *name, int length);
		void setCalleeName(const UChar *name, int length);

		int         getLine()       const { return mLine; }
		const char* getUrl()        const { return mUrl; }
		const char* getCallerName() const { return mCallerName; }
		const char* getCalleeName() const { return mCalleeName; }

	private:
		int  mLine;
		char *mUrl;
		char *mCallerName;
		char *mCalleeName;

		void convert(const UChar *source, int length, char **pTarget);
		};
	}

#endif

