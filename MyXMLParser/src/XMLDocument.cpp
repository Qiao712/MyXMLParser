#include "XMLDocument.hpp"
#include "XMLComment.hpp"
#include "XMLDeclaration.hpp"
#include "XMLElement.hpp"
#include "XMLText.hpp"
#include "StringUtility.hpp"

namespace MyXMLParser {
	bool XMLDocument::parse(const char* xml, size_t len)
	{
		_parsing_error.raw_xml_beg = xml;
		_parsing_error.raw_xml_end = xml + len;
		return parse(_parsing_error.raw_xml_beg, _parsing_error.raw_xml_end, this, _parsing_error);
	}
	void XMLDocument::clear()
	{
		//clear error
		_parsing_error.clear();
	}
	void XMLDocument::accept(XMLVisitor& visitor)
	{
		visitor.visitEntry(this);
		XMLNonterminalNode::visitChildern(visitor);
		visitor.visitExit(this);
	}
	const char* XMLDocument::parse(const char* beg, const char* end, XMLNonterminalNode* parent, ParsingError& parsing_error)
	{
		const char* p = StringUtility::skipWhitespace(beg, end);
		parseChildren(p, end, parent, parsing_error);
        return p;
	}
}