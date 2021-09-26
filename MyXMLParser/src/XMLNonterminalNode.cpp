#include "XMLNonterminalNode.h"
#include "XMLElement.hpp"
#include "XMLText.hpp"
#include "XMLComment.hpp"
#include "XMLDeclaration.hpp"

#include <algorithm>

namespace MyXMLParser {
    XMLElement* XMLNonterminalNode::fisrtElementChild()
    {
        XMLElement* element;
        for (XMLNode* p = _first_child; p != nullptr; p = p->_next_sibling) {
            element = dynamic_cast<XMLElement*>(p);
            if (element != nullptr) return element;
        }
        return nullptr;
    }
    XMLElement* XMLNonterminalNode::lastElementChild()
    {
        XMLElement* element;
        for (XMLNode* p = _last_child; p != nullptr; p = p->_previous_sibling) {
            element = dynamic_cast<XMLElement*>(p);
            if (element != nullptr) return element;
        }
        return nullptr;
    }
    XMLElement* XMLNonterminalNode::findElementByTagName(string tag_name, XMLNode* start)
    {
        XMLElement* element;
        XMLNode* p = _first_child;
        while (p != start && p != nullptr) p = p->_next_sibling;
        for (; p != nullptr; p = p->_next_sibling) {
            element = dynamic_cast<XMLElement*>(p);
            if (element != nullptr && element->getValue() == tag_name) {
                return element;
            }
        }
        return nullptr;
    }
    XMLError XMLNonterminalNode::addFirstChild(XMLNode* child)
    {
        child->_next_sibling = _first_child;
        child->_previous_sibling = nullptr;
        if (_first_child != nullptr)
            _first_child->_previous_sibling = child;
        else
            _last_child = child;
        _first_child = child;
        child->_parent = this;
        child->_root = _root;
        return XML_SUCCESS;
    }
    XMLError XMLNonterminalNode::addLastChild(XMLNode* child)
    {
        child->_next_sibling = nullptr;
        child->_previous_sibling = _last_child;
        if (_last_child != nullptr)
            _last_child->_next_sibling = child;
        else
            _first_child = child;
        _last_child = child;
        child->_parent = this;
        child->_root = _root;
        return XML_SUCCESS;
    }
    XMLError XMLNonterminalNode::addSibling(XMLNode* child)
    {
        child->_next_sibling = _next_sibling;
        child->_previous_sibling = this;
        if(_next_sibling != nullptr)
            _next_sibling->_previous_sibling = child;
        _next_sibling = child;
        child->_parent = _parent;
        child->_root = _parent->_root;
        return XML_SUCCESS;
    }
    XMLError XMLNonterminalNode::removeFirstChild()
    {
        if (_first_child == nullptr) return XML_ERROR_REMOVE_FAIL;
        XMLNode* x = _first_child;
        _first_child = _first_child->_next_sibling;
        if(_first_child != nullptr)
            _first_child->_previous_sibling = nullptr;
        delete x;
        return XML_SUCCESS;
    }
    XMLError XMLNonterminalNode::removeLastChild()
    {
        if (_last_child == nullptr) return XML_ERROR_REMOVE_FAIL;
        XMLNode* x = _last_child;
        _last_child = _last_child->_previous_sibling;
        if (_first_child != nullptr)
            _last_child->_next_sibling = nullptr;
        delete x;
        return XML_SUCCESS;
    }
    XMLError XMLNonterminalNode::removeChild(XMLNode* child)
    {
        if (child == nullptr || child->_parent != this) return XML_ERROR_REMOVE_FAIL;
        //child's destructor will cancel the link with other nodes
        delete child;
        return XML_SUCCESS;
    }
    XMLNonterminalNode::~XMLNonterminalNode()
    {

    }
    const char* XMLNonterminalNode::parse(const char* beg, const char* end, const string& parent_tag_name, size_t& line_num)
    {
        const char* p = beg;
        XMLNode* new_node;
        while (p < end) {
            Token token = checkStart(p, end);
            if (token == Token::ELEMENT_END) {
                p = matchTag(p, end, parent_tag_name);
                if (p != nullptr) {
                    
                    return p;
                }
                else {
                    //error: wrong end tag

                    return nullptr;
                }
            }
            else {
                new_node = createNode(token);
            }
            

            if (new_node != nullptr) {
                //elements' getValue() return tag name; docments' getValue() return empty string;
                p = new_node->parse(p, end, parent_tag_name, line_num);
                if (p == nullptr) {

                    return nullptr;
                }

                ////check end tag of the parent node
                //XMLElement* element_node = dynamic_cast<XMLElement*>(new_node);
                //if (element_node != nullptr && element_node->_is_closing_tag) {
                //    if (element_node->getTagName() == parent_tag_name) {
                //        delete new_node;
                //        return p;
                //    }
                //    else {
                //        //error

                //        delete new_node;
                //        return nullptr;
                //    }
                //}

                //discard text node of whitespace
                XMLText* text_node = dynamic_cast<XMLText*>(new_node);
                if (text_node != nullptr && text_node->_content.isAllWhitespace()) {
                    delete new_node;
                    continue;
                }

                //success
                addLastChild(new_node);
            }
            else {
                return nullptr;
            }
        }

        return p;
    }
    Token XMLNonterminalNode::checkStart(const char* beg, const char* end)
    {
        if (beg != end) {
            if (*beg == '<') {
                if (beg + 1 != end && beg[1] == '?') return Token::DECLARATION;				//<?
                if (end - beg >= 4 && beg[1] == '!' && beg[2] == '-' && beg[3] == '-') return Token::COMMENT;	//<!--
                if (beg + 1 != end && beg[1] == '/') return Token::ELEMENT_BEG;
                return Token::ELEMENT_END;		   //<
            }
            return Token::TEXT;
        }
        return Token::UNKNOWN;
    }
    XMLNode* XMLNonterminalNode::createNode(Token type)
    {
        XMLNode* new_node = nullptr;
        switch (type) {
        case Token::COMMENT: {
            new_node = new XMLComment;
            break;
        }
        case Token::DECLARATION: {
            new_node = new XMLDeclaration;
            break;
        }
        case Token::ELEMENT_BEG: {
            new_node = new XMLElement;
            break;
        }
        case Token::TEXT: {
            new_node = new XMLText;
            break;
        }
        default: {

        }
        }
        return new_node;
    }
    const char* XMLNonterminalNode::matchTag(const char* beg, const char* end, const string& parent_tag_name)
    {
        const char* tag_name_beg = beg + 2;
        const char* tag_name_end = findChar('>', beg, end);

        size_t len = tag_name_end - tag_name_beg;
        if (len != parent_tag_name.length()) return nullptr;
        
        for (size_t i = 0; i < len; i++) {
            if (tag_name_beg[i] != parent_tag_name[i]) return nullptr;
        }
        
        return tag_name_end + 1;
    }
}
