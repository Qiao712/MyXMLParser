#include "XMLNode.hpp"
#include "XMLNonterminalNode.h"
#include "XMLDeclaration.hpp"
#include "XMLComment.hpp"
#include "XMLElement.hpp"
#include "XMLText.hpp"

namespace MyXMLParser {
	NodeType XMLNode::checkStart(const char* beg, const char* end)
	{
		if (beg != end) {
			if (*beg == '<') {
				if (beg + 1 != end && beg[1] == '?') return NodeType::DECLARATION;				//<?
				if (end - beg >= 4 && beg[1] == '!' && beg[2] ==  '-' && beg[3] == '-') return NodeType::COMMENT;	//<!--
				return NodeType::ELEMENT;
			}
			return NodeType::TEXT;
		}
		return NodeType::UNKNOWN;
	}
	XMLNode* XMLNode::createNodeByStartChar(const char* beg, const char* end)
	{
		XMLNode* new_node = nullptr;
		switch (XMLNode::checkStart(beg, end)) {
		case NodeType::COMMENT: {
			new_node = new XMLComment;
			break;
		}
		case NodeType::DECLARATION: {
			new_node = new XMLDeclaration;
			break;
		}
		case NodeType::ELEMENT: {
			new_node = new XMLElement;
			break;
		}
		default: {
			new_node = new XMLText;
		}
		}

		return new_node;
	}
	XMLNode::~XMLNode()
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
	}
}
