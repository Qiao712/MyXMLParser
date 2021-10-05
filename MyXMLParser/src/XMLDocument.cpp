#include "XMLDocument.hpp"
#include "XMLComment.hpp"
#include "XMLDeclaration.hpp"
#include "XMLElement.hpp"
#include "XMLText.hpp"
#include "StringUtility.hpp"

namespace MyXMLParser {
	bool XMLDocument::parse(const char* xml, size_t len)
	{
		_raw_xml_beg = xml;
		_raw_xml_end = xml + len;
		return parse(_raw_xml_beg, _raw_xml_end, this);
		_raw_xml_beg = nullptr;
		_raw_xml_end = nullptr;
	}
	void XMLDocument::clear()
	{
		//clear error
		_parsing_error = XML_SUCCESS;
		_error_line = 0;
		_error_detail.clear();
		_raw_xml_beg = nullptr;
		_raw_xml_end = nullptr;
	}
	void XMLDocument::setParsingError(XMLError error, const char* where_error)
	{
		_parsing_error = error;

		//find error line
		const char* line_beg = StringUtility::countNewline(_raw_xml_beg, where_error, _error_line);
		const char* line_end = StringUtility::findNewline(line_beg, _raw_xml_end);
		_error_detail.assign(line_beg, line_end);

		_error_line++;
	}
	const char* XMLDocument::parse(const char* beg, const char* end, XMLNonterminalNode* parent)
	{
		const char* p = StringUtility::skipWhitespace(beg, end);
		parseChildren(p, end, parent);
        return p;
	}
}