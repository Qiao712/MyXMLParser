#include "XMLComment.hpp"

#include <cstring>
namespace MyXMLParser {
	const char* XMLComment::parse(const char* beg, const char* end, const string& parent_tag_name, size_t& line_num)
	{
		const char* comment_end = findSubstr(beg, end, COMMENT_END);
		line_num += countChar('\n', beg, comment_end);
		_content.assign(beg + LENGTH_COMMENT_START, comment_end);

		if (comment_end == end) return end;
		else return comment_end + LENGTH_COMMENT_END;
		return nullptr;
	}
}
