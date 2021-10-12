#pragma once
#include <cctype>
#include <cstdint>
#include <string>
namespace QSimpleXMLParser {
class StringUtility
{
public:
	inline static bool isWhitespace(char x);
    inline static bool isAllWhitespace(const std::string& str);                     //is all char is whitespace
	inline static const char* skipWhitespace(const char* beg, const char* end);
	inline static const char* skipBackWhitespace(const char* beg, const char* end);
	inline static const char* findWhitespace(const char* beg, const char* end);
    inline static const char* findChar(const char chr, const char* beg, const char* end);
	inline static const char* findChaOrWhitespace(const char chr, const char* beg, const char* end);
	inline static const char* findNewline(const char* beg, const char* end);
    inline static const char* findSubstr(const char* beg, const char* end, const char* substr);
    inline static size_t countChar(const char chr, const char* beg, const char* end);
    inline static size_t countChar(const char chr, const std::string& str);
	inline static bool compareStr(const char* beg, const char* end, const char* c_str);
	//count num of new line and return the last line's head
	inline static const char* countNewline(const char* beg, const char* end, size_t& num_new_line);

    //translate entity and normalize newline, then store in _str in constructor
    //newline normalization: "\r\n", "\r" and "\n\r" -> "\n"
    enum TEXT_PROCESS{ TRANSLATE_ENTITY = 1, NORMALIZE_NEWLINE = 2 };
    static std::string processText(const char* beg, const char* end, unsigned int process);

    static std::string translateCharToEntity(const std::string& str);
private:
    //serve for processText
    static bool parseReference(const char* beg, const char* end, std::string& substitute);
    inline static uint32_t strToIntHex(const char* beg, const char* end);
    inline static uint32_t strToIntDec(const char* beg, const char* end);
    inline static bool unicodeToUtf8(uint32_t unicode, std::string& utf8);
};

	using std::string;
	inline bool QSimpleXMLParser::StringUtility::isWhitespace(char x)
	{
		//Characters outside the ASCII range are not considered
		return !(x & 0x80) && isspace(x);
	}
	inline bool StringUtility::isAllWhitespace(const string& str)
	{
		if (str.empty()) return true;
		size_t holder;
		const char* p = skipWhitespace(&str.front(), &str.back() + 1);
		return p == &str.back() + 1;
	}

	inline const char* StringUtility::skipWhitespace(const char* beg, const char* end)
	{
		for (; beg < end && isWhitespace(*beg); beg++);
		return beg;
	}
	inline const char* StringUtility::skipBackWhitespace(const char* beg, const char* end)
	{
		for (end--; end >= beg && isWhitespace(*end); end--);
		return end + 1;
	}
	inline const char* StringUtility::findWhitespace(const char* beg, const char* end)
	{
		for (; beg < end && !isWhitespace(*beg); beg++);
		return beg;
	}
	inline const char* StringUtility::findChar(const char chr, const char* beg, const char* end)
	{
		while (beg < end && *beg != chr) beg++;
		return beg;
	}
	inline const char* StringUtility::findChaOrWhitespace(const char chr, const char* beg, const char* end)
	{
		while (beg < end && *beg != chr && !isWhitespace(*beg)) beg++;
		return beg;
	}
	inline const char* StringUtility::findNewline(const char* beg, const char* end)
	{
		const char* p1 = findChar('\n', beg, end);
		const char* p2 = findChar('\r', beg, end);
		return p1 < p2 ? p1 : p2;
	}
	inline const char* StringUtility::findSubstr(const char* beg, const char* end, const char* c_str)
	{
		//TODO: unsafe (end will be writen)
		if (beg == end) return end;
		char t = *end;
		*const_cast<char*>(end) = '\0';
		const char* p = strstr(beg, c_str);
		*const_cast<char*>(end) = t;
		return p != nullptr ? p : end;
	}

	inline uint32_t StringUtility::strToIntHex(const char* beg, const char* end)
	{
		if (beg >= end) return static_cast<uint16_t>(-1);
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

	inline uint32_t StringUtility::strToIntDec(const char* beg, const char* end)
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

	inline bool StringUtility::unicodeToUtf8(uint32_t unicode, std::string& utf8)
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

	inline size_t StringUtility::countChar(const char chr, const char* beg, const char* end)
	{
		size_t count = 0;
		for (const char* p = beg; p < end; p++) count += (*p == chr);
		return count;
	}

	inline size_t StringUtility::countChar(const char chr, const std::string& str)
	{
		return countChar(chr, &str.front(), &str.back() + 1);
	}

	inline bool StringUtility::compareStr(const char* beg, const char* end, const char* c_str)
	{
		for (; beg < end && *c_str != 0; beg++, c_str++) {
			if (*beg != *c_str) return false;
		}

		return beg == end && *c_str == 0;
	}

	inline const char* StringUtility::countNewline(const char* beg, const char* end, size_t& num_new_line)
	{
		char pre = 0;
		const char* last_line = beg;
		for (const char* p = beg; p < end; p++) {
			if (*p == '\n') {
				if (pre != '\r') num_new_line++;
				last_line = p + 1;
			}
			else if (*p == '\r') {
				if (pre != '\n') num_new_line++;
				last_line = p + 1;
			}
		}

		return last_line;
	}
}

