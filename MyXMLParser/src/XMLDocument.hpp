#pragma once
#include "XMLNonterminalNode.h"

namespace MyXMLParser{
class XMLDocument : public XMLNonterminalNode{
    friend class XMLTerminalNode;
    friend class XMLNonterminalNode;
    friend class XMLDocument;
    friend class XMLComment;
    friend class XMLDeclaration;
    friend class XMLElement;
    friend class XMLText;
    friend class XMLNode;
public:
    XMLDocument() { _root = this; }

    bool parse(const char* xml, size_t len);
    bool parse(const string& xml);
    
    bool good() const { return _parsing_error == XMLError::XML_SUCCESS; }
    string getErrorDetail() const;
    XMLError getError() const { return _parsing_error; }
    size_t getErrorLine() const { return _error_line; }

    const string& getValue() const override { static string empty_str; return empty_str; }
    void setValue(const string& value) override { }
    void setValue(string&& value) override { }
    
private:
    void setParsingError(XMLError error, size_t line_num) { _parsing_error = error; _error_line = line_num; }

    const char* parse(const char* beg, const char* end, XMLNonterminalNode* parent, size_t& line_num) override;

    XMLError _parsing_error = XML_SUCCESS;
    size_t   _error_line    = 0;
    const char* _where_error = nullptr;
};
}