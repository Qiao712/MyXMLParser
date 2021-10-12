#include "XMLNode.hpp"
#include "XMLNonterminalNode.hpp"
#include "XMLDeclaration.hpp"
#include "XMLComment.hpp"
#include "XMLElement.hpp"
#include "XMLText.hpp"
#include "XMLDocument.hpp"

#include <iostream>

namespace QSimpleXMLParser {
	XMLNode::~XMLNode()
	{
		unlink();
	}
	void XMLNode::unlink()
	{
		if (_parent != nullptr) {
			if (_parent->_first_child == this) {
				_parent->_first_child = this->_next_sibling;
				if (this->_next_sibling != nullptr) this->_next_sibling->_previous_sibling = nullptr;
			}
			else if (_parent->_last_child == this) {
				_parent->_last_child = this->_previous_sibling;
				if (this->_previous_sibling != nullptr) this->_previous_sibling->_next_sibling = nullptr;
			}
			else {
				_previous_sibling->_next_sibling = _next_sibling;
				_next_sibling->_previous_sibling = _previous_sibling;
			}
		}

		_parent = nullptr;
	}

	void ParsingError::setParsingError(XMLParseError error, const char* where_error)
	{
		ParsingError::error = error;

		//find error line
		const char* line_beg = StringUtility::countNewline(raw_xml_beg, where_error, error_line);
		const char* line_end = StringUtility::findNewline(line_beg, raw_xml_end);
		error_detail.assign(line_beg, line_end);
		error_line++;
	}

	void ParsingError::clear()
	{
		error = XML_PARSE_SUCCESS;
		error_line = 0;
		error_detail.clear();
		raw_xml_beg = nullptr;
		raw_xml_end = nullptr;
	}
	XMLNode* XMLNode::getRoot()
	{
		XMLNode* p;
		if (_parent == nullptr) return nullptr;
		for (p = _parent; p->_parent != nullptr; p = p->_parent);
		return p;
	}
	XMLDocument* XMLNode::getDocument()
	{
		XMLNode* root = getRoot();
		return dynamic_cast<XMLDocument*>(root);
	}
}
