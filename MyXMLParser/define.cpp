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
	uint32_t strToIntHex(const char* beg, const char* end)
	{
		if(beg >= end) return static_cast<uint16_t>(-1);
		uint32_t result = 0;
		uint32_t x;
		for (const char* p = beg; p < end; p++) {
			if (*p >= 'a' && *p <= 'f') x = *p - 'a' + 10;
			else if (*p >= 'A' && *p <= 'F') x = *p - 'A' + 10;
			else if (*p >= '0' && *p <= '9') x = *p - '0';
			else return static_cast<uint16_t>(-1);
			result = result * 16 + x;
		}

		return result;
	}
	uint32_t strToIntDec(const char* beg, const char* end)
	{
		if (beg >= end) return static_cast<uint16_t>(-1);
		uint32_t result = 0;
		uint32_t x;
		for (const char* p = beg; p < end; p++) {
			if (*p >= '0' && *p <= '9') x = *p - '0';
			else return static_cast<uint16_t>(-1);
			result = result * 10 + x;
		}

		return result;
	}
	bool unicodeToUtf8(uint32_t unicode, string& utf8)
	{
		constexpr uint32_t MARKS[6] = {
			~static_cast<uint32_t>(0x007F),
			~static_cast<uint32_t>(0x07FF),
			~static_cast<uint32_t>(0xFFFF),
			~static_cast<uint32_t>(0x1FFFFF),
			~static_cast<uint32_t>(0x3FFFFFF),
			~static_cast<uint32_t>(0x7FFFFFFF)
		};
		constexpr uint32_t FIRST_BYTE[] = {
			0x00,
			0xC0,
			0xE0,
			0xF0,
			0xF8,
			0xFC
		};
		constexpr uint32_t LOWER_BYTE = 0x80;	//1000 0000
		constexpr uint32_t LOWER_6BITS = 0x3F;	//0011 1111
		constexpr uint32_t MAX_UNICODE = 0x10FFFF;
		static char buf[6];

		if (unicode > MAX_UNICODE) return false;

		int n = 0;
		while (unicode & MARKS[n]) n++;
		
		for (int i = n; i > 0; i--) {
			//10xxxxxx
			buf[i] = static_cast<char>(LOWER_BYTE | (unicode & LOWER_6BITS));
			unicode >>= 6;
		}
		buf[0] = static_cast<char>(FIRST_BYTE[n] | unicode);

		utf8.assign(buf, buf + n + 1);

		return true;
	}
	
	size_t countChar(const char chr, const char * beg, const char * end)
	{
		size_t count = 0;
		for (const char* p = beg; p < end; p++) count += (*p == chr);
		return count;
	}
	bool isAllWhitespace(const char* beg, const char* end)
	{

		return false;
	}
}