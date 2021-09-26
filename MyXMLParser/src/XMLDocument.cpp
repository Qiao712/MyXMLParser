#include "XMLDocument.hpp"
#include "XMLComment.hpp"
#include "XMLDeclaration.hpp"
#include "XMLElement.hpp"
#include "XMLText.hpp"

namespace MyXMLParser {
	bool XMLDocument::parse(const char* xml, size_t len)
	{
		size_t line_num = 1;
		return parse(xml, xml+len, this, line_num);
	}
	const char* XMLDocument::parse(const char* beg, const char* end, XMLNonterminalNode* parent, size_t& line_num)
	{
		const char* p = skipWhitespace(beg, end, line_num);
		parseChildren(p, end, parent, line_num);
        return p;
	}
}