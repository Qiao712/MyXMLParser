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
    
    void clear();
    
    bool good() const { return _parsing_error == XMLError::XML_SUCCESS; }
    string getErrorDetail() const { return _error_detail; }
    XMLError getError() const { return _parsing_error; }
    size_t getErrorLine() const { return _error_line; }

    const string& getValue() const override { static string empty_str; return empty_str; }
    void setValue(const string& value) override { }
    void setValue(string&& value) override { }
    
private:
    const char* parse(const char* beg, const char* end, XMLNonterminalNode* parent) override;

    //use to report error occurred during parsing
    void setParsingError(XMLError error, const char* where_error);
    XMLError _parsing_error = XML_SUCCESS;
    size_t   _error_line    = 0;
    string _error_detail;
    const char* _raw_xml_beg = nullptr;
    const char* _raw_xml_end = nullptr;
};
}