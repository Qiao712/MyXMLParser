#include "XMLDocument.hpp"
#include "XMLComment.hpp"
#include "XMLDeclaration.hpp"
#include "XMLElement.hpp"
#include "XMLText.hpp"
#include "StringUtility.hpp"

#include <cstring>
#include <fstream>
using std::string;

namespace QSimpleXMLParser {
	bool XMLDocument::parse(const char* xml)
	{
		clear();
		size_t len = strlen(xml);
		_parse_error.raw_xml_beg = xml;
		_parse_error.raw_xml_end = xml + len;
		return parse(_parse_error.raw_xml_beg, _parse_error.raw_xml_end, this, _parse_error);
	}
	bool XMLDocument::parse(const string& xml)
	{
		clear();
		_parse_error.raw_xml_beg = &xml.front();
		_parse_error.raw_xml_end = &xml.back() + 1;
		return parse(_parse_error.raw_xml_beg, _parse_error.raw_xml_end, this, _parse_error);
	}
	bool XMLDocument::loadFile(const std::string path)
	{
		std::ifstream ifs(path, std::ios_base::binary);
		if (!ifs.good()) return false;
		ifs.seekg(0, std::ios_base::end);
		size_t size = ifs.tellg();
		ifs.seekg(0);
		char* buffer = new char[size + 1];
		ifs.read(buffer, size);
		buffer[size] = 0;
		return parse(buffer);
	}
	void XMLDocument::clear()
	{
		clearError();
		removeAllChildren();
	}
	bool XMLDocument::accept(XMLVisitor& visitor)
	{
		if (visitor.visitEntry(*this)) {
			XMLNonterminalNode::visitChildern(visitor);
		}
		return visitor.visitExit(*this);
	}
	const char* XMLDocument::parse(const char* beg, const char* end, XMLNonterminalNode* parent, ParseError& parsing_error)
	{
		const char* p = StringUtility::skipWhitespace(beg, end);
		parseChildren(p, end, parent, parsing_error);
        return p;
	}
}