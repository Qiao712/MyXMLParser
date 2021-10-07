#pragma once
#include "XMLTerminalNode.h"
#include "XMLVisitor.hpp"

#include <string>

namespace MyXMLParser {
class XMLDeclaration : public XMLTerminalNode{
public:
	XMLDeclaration() = default;
	XMLDeclaration(const string& content) : _content(content){ }
	XMLDeclaration(string&& content) : _content(content){ }

	const string& getValue() const override { return _content; }
	virtual void setValue(const string& value) { _content.assign(value); }
	virtual void setValue(string&& value) { _content.assign(value); }

	XMLDeclaration* clone() override { return new XMLDeclaration(_content); }
	XMLDeclaration* deepClone() override { return clone(); }

	void accept(XMLVisitor& visitor) override { visitor.visit(this); }
private:
	const char* parse(const char* beg, const char* end, XMLNonterminalNode* parent, ParsingError& parsing_error) override;
	string _content;
};
}