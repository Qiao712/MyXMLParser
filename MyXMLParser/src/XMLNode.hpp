#pragma once
#include "define.h"

#include <string>
#include <vector>
using std::string;
using std::vector;

namespace MyXMLParser{

enum class Token {
    ELEMENT_BEG,
    ELEMENT_END,
    DECLARATION, TEXT, COMMENT, CDATA, UNKNOWN
};

//use to report error occurred during parsing
struct ParsingError {
    void setParsingError(XMLError error, const char* where_error);
    void clear();

    XMLError error = XML_SUCCESS;
    size_t   error_line = 0;
    string error_detail;
    const char* raw_xml_beg = nullptr;
    const char* raw_xml_end = nullptr;
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
    
    //if the child already has a parent, return error code
    virtual XMLError addFirstChild(XMLNode* child) = 0;
    virtual XMLError addLastChild(XMLNode* child) = 0;
    virtual XMLError addSibling(XMLNode* child) = 0;

    virtual XMLError removeFirstChild() = 0;
    virtual XMLError removeLastChild() = 0;
    virtual XMLError removeChild(XMLNode* child) = 0;

    //cancel the link with its siblings and its parent.
    void unlink();

    virtual const string& getValue() const = 0;
    virtual void setValue(const string& value) = 0;
    virtual void setValue(string&& value) = 0;

    //build a new tree that is same as this subtree.
    //virtual XMLNode* clone() = 0;
protected:
    virtual const char* parse(const char* beg, const char* end, XMLNonterminalNode* parent, ParsingError& parsing_error) = 0;
private:
    XMLNonterminalNode* _parent = nullptr;
    XMLNode* _next_sibling = nullptr;
    XMLNode* _previous_sibling = nullptr;
};
}