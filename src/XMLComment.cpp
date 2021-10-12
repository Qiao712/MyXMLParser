#include "XMLComment.hpp"

#include <cstring>
namespace QSimpleXMLParser {
	const char* XMLComment::parse(const char* beg, const char* end, XMLNonterminalNode* parent, ParsingError& parsing_error)
	{
		constexpr char COMMENT_START[] = "<!--";
		constexpr char COMMENT_END[] = "-->";
		constexpr int  LENGTH_COMMENT_START = sizeof(COMMENT_START)/sizeof(char) - 1;
		constexpr int  LENGTH_COMMENT_END = sizeof(COMMENT_END)/sizeof(char) - 1;

		const char* comment_end = StringUtility::findSubstr(beg, end, COMMENT_END);
		
		_content = StringUtility::processText(beg + LENGTH_COMMENT_START, comment_end, StringUtility::NORMALIZE_NEWLINE);

		if (comment_end == end) return end;
		else return comment_end + LENGTH_COMMENT_END;
		return nullptr;
	}
}
