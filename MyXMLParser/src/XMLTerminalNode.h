#pragma once
#include "XMLNode.hpp"

namespace MyXMLParser {
class XMLTerminalNode : public XMLNode
{
public:
    XMLNode* firstChild() override { return nullptr; }
    XMLNode* lastChild() override { return nullptr; }
    XMLElement* fisrtElementChild() override { return nullptr; }
    XMLElement* lastElementChild()  override { return nullptr; }
    XMLElement* findElementByTagName(const string& tag_name, XMLNode* start = nullptr) override { return nullptr; }

    bool addFirstChild(XMLNode* child) override { return false; }
    bool addLastChild(XMLNode* child) override { return false; }
    bool insertChild(XMLNode* child, XMLNode* after_this) override { return false; }
    bool removeFirstChild() override { return false; }
    bool removeLastChild() override { return false; }
    bool removeChild(XMLNode* child) override { return false; }
};
}

