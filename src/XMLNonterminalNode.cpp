#pragma once
#include "XMLNonterminalNode.hpp"
#include "XMLElement.hpp"
#include "XMLDocument.hpp"
#include "XMLText.hpp"
#include "XMLComment.hpp"
#include "XMLDeclaration.hpp"
#include "XMLCDATA.hpp"
#include "StringUtility.hpp"

using std::string;

namespace QSimpleXMLParser {
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
    XMLElement* XMLNonterminalNode::findElementByTagName(const string& tag_name, XMLNode* start)
    {
        XMLNode* p;
        if (start == nullptr) {
            p = _first_child;
        }
        else {
            if (start->_parent != this) return nullptr;
            else p = start;
        }

        XMLElement* element;
        for (; p != nullptr; p = p->_next_sibling) {
            element = dynamic_cast<XMLElement*>(p);
            if (element != nullptr && element->getValue() == tag_name) {
                return element;
            }
        }
        return nullptr;
    }
    bool XMLNonterminalNode::addFirstChild(XMLNode* child)
    {
        if (dynamic_cast<XMLDocument*>(child) != nullptr) return false;

        child->_next_sibling = _first_child;
        child->_previous_sibling = nullptr;
        if (_first_child != nullptr)
            _first_child->_previous_sibling = child;
        else
            _last_child = child;
        _first_child = child;
        child->_parent = this;
        return true;
    }
    bool XMLNonterminalNode::addLastChild(XMLNode* child)
    {
        if (dynamic_cast<XMLDocument*>(child) != nullptr) return false;

        child->_next_sibling = nullptr;
        child->_previous_sibling = _last_child;
        if (_last_child != nullptr)
            _last_child->_next_sibling = child;
        else
            _first_child = child;
        _last_child = child;
        child->_parent = this;
        return true;
    }
    bool XMLNonterminalNode::insertChild(XMLNode* child, XMLNode* after_this)
    {
        if (after_this == nullptr) return addLastChild(child);
        if (after_this->_parent != this) return false;
        child->_next_sibling = after_this->_next_sibling;
        if (after_this == _last_child) {
            _last_child = after_this;
        }
        else {
            after_this->_next_sibling->_previous_sibling = child;
        }
        after_this->_next_sibling = child;
        child->_previous_sibling = after_this;
        return true;
    }
    bool XMLNonterminalNode::removeFirstChild()
    {
        if (_first_child == nullptr) return false;
        XMLNode* x = _first_child;
        _first_child = _first_child->_next_sibling;
        if(_first_child != nullptr)
            _first_child->_previous_sibling = nullptr;
        delete x;
        return true;
    }
    bool XMLNonterminalNode::removeLastChild()
    {
        if (_last_child == nullptr) return false;
        XMLNode* x = _last_child;
        _last_child = _last_child->_previous_sibling;
        if (_first_child != nullptr)
            _last_child->_next_sibling = nullptr;
        delete x;
        return true;
    }
    bool XMLNonterminalNode::removeChild(XMLNode* child)
    {
        if (child == nullptr || child->_parent != this) return false;
        //child's destructor (Node::~Node) will cancel the link with other nodes.
        delete child;
        return true;
    }
    bool XMLNonterminalNode::removeAllChildren()
    {
        if (_first_child == nullptr) return false;
        XMLNode* p = _first_child;
        XMLNode* next;
        while (p != nullptr) {
            next = p->_next_sibling;
            delete p;
            p = next;
        }
        return true;
    }
    XMLNonterminalNode::~XMLNonterminalNode()
    {
        //delete all children
        XMLNode* p = _first_child;
        XMLNode* next;
        for (XMLNode* p = _first_child; p != nullptr; p = next) {
            p->_parent = nullptr;       //is p->_parent is nullptr, Node::~Node will not do the redundant operation which cancel the links bewteen p and its siblings.
            next = p->_next_sibling;
            delete p;
        }
    }
    const char* XMLNonterminalNode::parseChildren(const char* beg, const char* end, XMLNonterminalNode* parent, ParseError& parsing_error)
    {
        const char* p = beg;
        XMLNode* new_node;
        while (p < end) {
            Token token = checkStart(p, end);
            if (token == Token::ELEMENT_END) {
                p = matchTag(p, end, parent->getValue(), parsing_error);
                if (p != nullptr) {
                    //succeed to close it's parents
                    parent->_is_closing = true;
                    return p;
                }
                else {
                    //error: unpaired tags <- wrong tag name
                    parsing_error.setParseError(XML_PARSE_ERROR_UNPAIRED_TAG, beg);
                    return nullptr;
                }
            }
            else {
                new_node = createNode(token);
            }


            if (new_node != nullptr) {
                p = new_node->parse(p, end, this, parsing_error);
                
                if (p == nullptr) {
                    delete new_node;
                    return nullptr;
                }

                //discard text node of whitespace
                XMLText* text_node = dynamic_cast<XMLText*>(new_node);
                if (text_node != nullptr && StringUtility::isAllWhitespace(text_node->_content)) {
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
    XMLNonterminalNode::Token XMLNonterminalNode::checkStart(const char* beg, const char* end)
    {
        constexpr char CDATA_BEG[] = "![CDATA[";
        constexpr int LEN_CDATA_BEG = 8;
        if (beg != end) {
            if (*beg == '<') {
                if (beg + 1 != end && beg[1] == '?') return Token::DECLARATION;				//<?
                if (beg + 1 != end && beg[1] == '/') return Token::ELEMENT_END;             //</
                if (end - beg >= 4 && beg[1] == '!' && beg[2] == '-' && beg[3] == '-') return Token::COMMENT;	//<!--
                if (end - beg >= LEN_CDATA_BEG + 1 && StringUtility::compareStr(beg + 1, beg + 1 + LEN_CDATA_BEG, CDATA_BEG)) return Token::CDATA;      //<![CDATA[
                return Token::ELEMENT_BEG;		   //<
            }
            return Token::TEXT;
        }
        return Token::UNKNOWN;
    }
    XMLNode* XMLNonterminalNode::createNode(Token type)
    {
        switch (type) {
        case Token::COMMENT: {
            return new XMLComment;
        }
        case Token::DECLARATION: {
            return new XMLDeclaration;
        }
        case Token::ELEMENT_BEG: {
            return new XMLElement;
        }
        case Token::TEXT: {
            return new XMLText;
        }
        case Token::CDATA: {
            return new XMLCDATA;
        }
        }
        return nullptr;
    }
    const char* XMLNonterminalNode::matchTag(const char* beg, const char* end, const string& parent_tag_name, ParseError& parsing_error)
    {
        const char* tag_name_beg = beg + 2;
        const char* tag_name_end = StringUtility::findChar('>', beg, end);

        if (tag_name_end == end) {
            //error: </....
            parsing_error.setParseError(XML_PARSE_ERROR_UNCLOSED_PARENTHESE, beg);
        }

        size_t len = tag_name_end - tag_name_beg;
        if (len != parent_tag_name.length()) return nullptr;
        
        for (size_t i = 0; i < len; i++) {
            if (tag_name_beg[i] != parent_tag_name[i]) return nullptr;
        }
        
        return tag_name_end + 1;
    }
    XMLNode* XMLNonterminalNode::doDeepClone()
    {
        XMLNode* new_node = clone();
        for (XMLNode* p = _first_child; p != nullptr; p = p->_next_sibling) {
            new_node->addLastChild(p->deepClone());
        }
        return new_node;
    }
    void XMLNonterminalNode::visitChildern(XMLVisitor& visitor)
    {
        for (XMLNode* p = _first_child; p != nullptr; p = p->_next_sibling) {
            if (!p->accept(visitor)) return;
        }
    }
}
