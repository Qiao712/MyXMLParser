#include "XMLDocument.hpp"
#include "XMLComment.hpp"
#include "XMLDeclaration.hpp"
#include "XMLElement.hpp"
#include "XMLText.hpp"

namespace MyXMLParser {
	bool XMLDocument::parse(const char* xml, size_t len)
	{
		size_t line_num = 1;
		static const string empty_str;
		return parse(xml, xml+len, empty_str, line_num);
	}
	const char* XMLDocument::parse(const char* beg, const char* end, const string& parent_tag_name, size_t& line_num)
	{
		const char* p = skipWhitespace(beg, end, line_num);
		_is_closing = true;
		XMLNonterminalNode::parse(p, end, parent_tag_name, line_num);
        return p;
	}
}