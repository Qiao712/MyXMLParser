#pragma once
#include "XMLNode.hpp"

namespace MyXMLParser {
class XMLNonterminalNode : public XMLNode
{
    friend class XMLNode;   //use to cancel link in XMLNode's destruction
public:
    XMLNode* firstChild() override { return _first_child; }
    XMLNode* lastChild() override { return _last_child; }
    XMLElement* fisrtElementChild() override;
    XMLElement* lastElementChild() override;
    XMLElement* findElementByTagName(string tag_name, XMLNode* start) override;

    XMLError addFirstChild(XMLNode* child) override;
    XMLError addLastChild(XMLNode* child) override;
    XMLError addSibling(XMLNode* child) override;

    XMLError removeFirstChild() override;
    XMLError removeLastChild() override;
    XMLError removeChild(XMLNode* child) override;

    ~XMLNonterminalNode();
protected:
    const char* parseChildren(const char* beg, const char* end, XMLNonterminalNode* parent);
    Token checkStart(const char* beg, const char* end);
    XMLNode* createNode(Token type);
    const char* matchTag(const char* beg, const char* end, const string& parent_tag_name);

    //<a>....</a> closing; <a>.... unclosing.
    bool _is_closing = false;
private:
    XMLNode* _first_child = nullptr;
    XMLNode* _last_child = nullptr;
};
}

