#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

namespace MyXMLParser{
//code of parsing error
enum XMLParseError {
    XML_PARSE_SUCCESS = 0,
    XML_PARSE_ERROR_DECLARATION,

    XML_PARSE_ERROR_UNPAIRED_TAG,      //Unpaired tag 未配对的标签
    XML_PARSE_ERROR_WRONG_END_TAG,     //wrong end tag 错误的结束标签
    XML_PARSE_ERROR_UNCLOSED_PARENTHESE,  //Unclosed parenthese 未封闭的括号 <....
    XML_PARSE_ERROR_INVALID_TAG_NAME,      //Invalid tag name 无效的标签名

    XML_PARSE_ERROR_ATTR,
    XML_PARSE_ERROR_DUPLICATE_ATTR_NAME,   //重复的属性名
    XML_PARSE_ERROR_INVALID_ATTR_NAME,      //无效的属性名

    XML_PARSE_ERROR_UNCLOSED_CDATA
};
struct ParsingError {
    void setParsingError(XMLParseError error, const char* where_error);
    void clear();

    XMLParseError error = XML_PARSE_SUCCESS;
    size_t   error_line = 0;
    string error_detail;
    const char* raw_xml_beg = nullptr;
    const char* raw_xml_end = nullptr;
};

class XMLElement;
class XMLDocument;
class XMLNonterminalNode;
class XMLVisitor;

enum class Token {
    ELEMENT_BEG,
    ELEMENT_END,
    DECLARATION, TEXT, COMMENT, CDATA, UNKNOWN
};

class XMLNode{
    friend class XMLVisitor;

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
    virtual XMLElement* findElementByTagName(const string& tag_name, XMLNode* start = nullptr) = 0;
    virtual XMLNode* nextSibling() { return _next_sibling; }
    virtual XMLNode* previousSibling() { return _previous_sibling; }
    virtual XMLNode* getParent() { return reinterpret_cast<XMLNode*>(_parent); }
    //If it is the root(has no parent), return nullptr.
    XMLNode* getRoot();
    XMLDocument* getDocument();

    //accept a visitor - Visitor Pattern
    virtual bool accept(XMLVisitor& visitor) = 0;
    
    //if the child already has a parent, return error code
    virtual bool addFirstChild(XMLNode* child) = 0;
    virtual bool addLastChild(XMLNode* child) = 0;
    virtual bool insertChild(XMLNode* child, XMLNode* after_this) = 0;
    virtual bool removeFirstChild() = 0;
    virtual bool removeLastChild() = 0;
    virtual bool removeChild(XMLNode* child) = 0;

    //cancel the link with its siblings and its parent.
    void unlink();

    virtual const string& getValue() const = 0;
    virtual void setValue(const string& value) = 0;
    virtual void setValue(string&& value) = 0;

    
    virtual XMLNode* clone() = 0;
    //build a new tree that is same as this subtree.
    virtual XMLNode* deepClone() = 0;
protected:
    virtual const char* parse(const char* beg, const char* end, XMLNonterminalNode* parent, ParsingError& parsing_error) = 0;
private:
    XMLNonterminalNode* _parent = nullptr;
    XMLNode* _next_sibling = nullptr;
    XMLNode* _previous_sibling = nullptr;

    //delete copy operator
    XMLNode& operator=(const XMLNode&) = delete;
    XMLNode(const XMLNode&) = delete;
};
}