#include "XMLNode.hpp"
#include "XMLNonterminalNode.h"
#include "XMLDeclaration.hpp"
#include "XMLComment.hpp"
#include "XMLElement.hpp"
#include "XMLText.hpp"
#include "XMLDocument.hpp"

#include <iostream>

namespace MyXMLParser {
	XMLNode::~XMLNode()
	{
		//cancel link with its siblings
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
	}
	void XMLNode::setParsingError(XMLError error, const char* where_error)
	{
		_root->setParsingError(error, where_error);
	}
}
