#pragma once
#include "XMLTerminalNode.h"

#include <string>

namespace MyXMLParser {
using std::string;
class XMLText : public XMLTerminalNode{
	//allow them to access _content to check weather it is white
	friend class XMLNonterminalNode;
	friend class XMLDocument;
	friend class XMLElement;
public:
	XMLText() = default;
	XMLText(const string & content) : _content(content) {}
	XMLText(string && content) : _content(content) {}

	const string& getValue() const override { return _content; }
	virtual void setValue(const string & value) { _content.assign(value); }
	virtual void setValue(string && value) { _content.assign(value); };

	const char* parse(const char* beg, const char* end, XMLNonterminalNode* parent, size_t & line_num) override;
private:
	std::string _content;
};
}