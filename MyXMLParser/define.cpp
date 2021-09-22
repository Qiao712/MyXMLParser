#include "src\define.h"
#include <cctype>
#include <cstring>

namespace MyXMLParser{
	const char* ERROR_DESCRIPTION[] = {
		"Not find end tag.",
		""
	};

	//sign of start and end
	const char COMMENT_START[] = "<!--";
	const int  LENGTH_COMMENT_START = strlen(COMMENT_START);
	const char COMMENT_END[] = "-->";
	const int  LENGTH_COMMENT_END = strlen(COMMENT_END);
	const char DECLARATION_START[] = "<?";
	const int  LENGTH_DECLARATION_START = strlen(DECLARATION_START);
	const char DECLARATION_END[] = "?>";
	const int  LENGTH_DECLARATION_END = strlen(DECLARATION_END);

	const char* skipWhitespace(const char* beg,const char* end, size_t& line_num)
	{
		const char* p = beg;
		//Characters outside the ASCII range are not considered
		while (!(*p & 0x80) && isspace(*p) && p != end) {
			if (*p == '\n') line_num++;
			p++;
		}
		return p;
	}

	const char* findChar(const char chr, const char* beg, const char* end)
	{
		while (beg != end && *beg != chr) beg++;
		return beg;
	}
	const char* findSubstr(const char* beg, const char* end, const char* substr)
	{
		//TODO: unsafe (end will be writen)
		if (beg == end) return end;
		char t = *end;
		*const_cast<char*>(end) = '\0';
		const char* p = strstr(beg, substr);
		*const_cast<char*>(end) = t;
		return p != nullptr ? p : end;
	}
	size_t countChar(const char chr, const char * beg, const char * end)
	{
		size_t count = 0;
		for (const char* p = beg; p != end; p++) count += (*p == chr);
		return count;
	}
}