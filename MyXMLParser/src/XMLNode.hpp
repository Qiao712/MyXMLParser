#pragma once
#include "define.h"

#include <string>
#include <vector>
using std::string;
using std::vector;

namespace MyXMLParser{

enum class NodeType {
    NODE, ELEMENT, DECLARATION, DOCUMENT, TEXT, COMMENT, UNKNOWN
};



class XMLElement;
class XMLDocument;
class XMLNonterminalNode;

class XMLNode{
    friend class XMLTerminalNode;
    friend class XMLNonterminalNode;
    friend class XMLDocument;
    friend class XMLComment;
    friend class XMLDeclaration;
    friend class XMLElement;
    friend class XMLText;
public:
    XMLNode() = default;
    virtual ~XMLNode();

    virtual XMLNode* firstChild() = 0;
    virtual XMLNode* lastChild() = 0;
    virtual XMLElement* fisrtElementChild() = 0;
    virtual XMLElement* lastElementChild() = 0;
    virtual XMLElement* findElementByTagName(string tag_name, XMLNode* start) = 0;
    virtual XMLNode* nextSibling() { return _next_sibling; }
    virtual XMLNode* previousSibling() { return _previous_sibling; }
    virtual XMLNode* getParent() { return reinterpret_cast<XMLNode*>(_parent); }
    
    virtual XMLError addFirstChild(XMLNode* child) = 0;
    virtual XMLError addLastChild(XMLNode* child) = 0;
    virtual XMLError addSibling(XMLNode* child) = 0;

    virtual XMLError removeFirstChild() = 0;
    virtual XMLError removeLastChild() = 0;
    virtual XMLError removeChild(XMLNode* child) = 0;

    virtual const string& getValue() const = 0;
    virtual void setValue(const string& value) = 0;
    virtual void setValue(string&& value) = 0;
protected:
    static NodeType checkStart(const char* beg, const char* end);
    static XMLNode* createNodeByStartChar(const char* beg, const char* end);

    virtual const char* parse(const char * beg, const char * end, size_t & line_num) = 0;
private:
    XMLDocument* _root = nullptr;
    XMLNonterminalNode* _parent = nullptr;
    XMLNode* _next_sibling = nullptr;
    XMLNode* _previous_sibling = nullptr;
};
}