#pragma once
#include "XMLNode.hpp"
#include "XMLVisitor.hpp"

namespace QSimpleXMLParser {

enum class Token {
    ELEMENT_BEG,
    ELEMENT_END,
    DECLARATION, TEXT, COMMENT, CDATA, UNKNOWN
};

class XMLNonterminalNode : public XMLNode
{
    friend class XMLNode;   //use to cancel link in XMLNode's destruction
public:
    XMLNode* firstChild() override { return _first_child; }
    XMLNode* lastChild() override { return _last_child; }
    XMLElement* fisrtElementChild() override;
    XMLElement* lastElementChild() override;
    XMLElement* findElementByTagName(const string& tag_name, XMLNode* start = nullptr) override;

    bool addFirstChild(XMLNode* child) override;
    bool addLastChild(XMLNode* child) override;
    bool insertChild(XMLNode* child, XMLNode* after_this = nullptr) override;
    bool removeFirstChild() override;
    bool removeLastChild() override;
    bool removeChild(XMLNode* child) override;
    
    ~XMLNonterminalNode();
protected:
    const char* parseChildren(const char* beg, const char* end, XMLNonterminalNode* parent, ParsingError& parsing_error);
    Token checkStart(const char* beg, const char* end);
    XMLNode* createNode(Token type);
    const char* matchTag(const char* beg, const char* end, const string& parent_tag_name, ParsingError& parsing_error);

    //<a>....</a> closing; <a>.... unclosing.
    bool _is_closing = false;

    XMLNode* doDeepClone();
    
    void visitChildern(XMLVisitor& visitor);
protected:
    XMLNode* _first_child = nullptr;
    XMLNode* _last_child = nullptr;
};
}

