#pragma once
#include "XMLTerminalNode.h"
#include "StringUtility.hpp"
#include "XMLVisitor.hpp"

#include <string>

namespace MyXMLParser {
class XMLComment : public XMLTerminalNode {
public:
	XMLComment() = default;
	XMLComment(const string& content) : _content(content){}
	XMLComment(string&& content) : _content(content) {}

	const string& getValue() const override { return _content; }
	void setValue(const string& value) { _content.assign(value); }
	void setValue(string&& value) { _content.assign(value); }
	
	XMLComment* clone() override { return new XMLComment(_content); }
	XMLComment* deepClone() override { return clone(); }

	bool accept(XMLVisitor& visitor) override { return visitor.visit(this); }
private:
	const char* parse(const char* beg, const char* end, XMLNonterminalNode* parent, ParsingError& parsing_error) override;
	string _content;
};
}