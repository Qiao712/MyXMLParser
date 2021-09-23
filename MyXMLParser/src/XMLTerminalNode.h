#pragma once
#include "define.h"
#include "XMLNode.hpp"

namespace MyXMLParser {
class XMLTerminalNode : public XMLNode
{
public:
    XMLNode* firstChild() override { return nullptr; }
    XMLNode* lastChild() override { return nullptr; }
    XMLElement* fisrtElementChild() override { return nullptr; }
    XMLElement* lastElementChild()  override { return nullptr; }
    XMLElement* findElementByTagName(string tag_name, XMLNode* start) override { return nullptr; }

    XMLError addFirstChild(XMLNode* child) override { return XML_ERROR_ADD_CHILD_TO_TERMINAL_NODE; }
    XMLError addLastChild(XMLNode* child) override { return XML_ERROR_ADD_CHILD_TO_TERMINAL_NODE; }
    XMLError addSibling(XMLNode* child) override { return XML_ERROR_ADD_CHILD_TO_TERMINAL_NODE; }

    XMLError removeFirstChild() override { return  XML_ERROR_TERMINAL_NODE; }
    XMLError removeLastChild() override { return  XML_ERROR_TERMINAL_NODE; }
    XMLError removeChild(XMLNode* child) override { return  XML_ERROR_TERMINAL_NODE; }
};
}
