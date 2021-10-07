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
    XMLDocument() = default;

    bool parse(const char* xml, size_t len);
    bool parse(const string& xml);
    
    void clear();
    
    bool good() const { return _parsing_error.error == XMLError::XML_SUCCESS; }
    string getErrorDetail() const { return _parsing_error.error_detail; }
    XMLError getError() const { return _parsing_error.error; }
    size_t getErrorLine() const { return _parsing_error.error_line; }

    const string& getValue() const override { static string empty_str; return empty_str; }
    void setValue(const string& value) override { }
    void setValue(string&& value) override { }
    
    XMLDocument* clone() override { return new XMLDocument(); }
    XMLDocument* deepClone() override { return reinterpret_cast<XMLDocument*>(doDeepClone()); }

    void accept(XMLVisitor& visitor) override;
private:
    const char* parse(const char* beg, const char* end, XMLNonterminalNode* parent, ParsingError& parsing_error) override;
    ParsingError _parsing_error;
};
}