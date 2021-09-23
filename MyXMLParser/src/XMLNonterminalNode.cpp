#include "XMLNonterminalNode.h"
#include "XMLElement.hpp"
#include "XMLText.hpp"

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
    const char* XMLNonterminalNode::parse(const char* beg, const char* end, size_t& line_num)
    {
        const char* p = beg;
        XMLNode* new_node;
        while (p != end) {
            new_node = createNodeByStartChar(p, end);

            if (new_node != nullptr) {
                p = new_node->parse(p, end, line_num);
                if (p == nullptr) {
                    
                    return nullptr;
                }
                else {
                    //discard text node of whitespace
                    XMLText* text_node = dynamic_cast<XMLText*>(new_node);
                    if (text_node != nullptr && text_node->_content.isAllWhitespace())
                        delete new_node;
                    else
                        addLastChild(new_node);
                }
            }
            else {
                return nullptr;
            }
        }
        
        return end;
    }
}
