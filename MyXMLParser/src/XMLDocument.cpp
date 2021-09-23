#include "XMLDocument.hpp"
#include "XMLComment.hpp"
#include "XMLDeclaration.hpp"
#include "XMLElement.hpp"
#include "XMLText.hpp"

namespace MyXMLParser {
	bool XMLDocument::parse(const char* xml, size_t len)
	{
		size_t line_num = 1;
		return parse(xml, xml+len, line_num);
	}
	const char* XMLDocument::parse(const char * beg, const char * end, size_t & line_num)
	{
		const char* p = skipWhitespace(beg, end, line_num);
		
		//parse its sub node
		return XMLNonterminalNode::parse(p, end, line_num);
	}
}