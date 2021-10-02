#pragma once
#include "XMLTerminalNode.h"

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

	const char* parse(const char* beg, const char* end, XMLNonterminalNode* parent, size_t& line_num) override;
private:
	string _content;
};
}