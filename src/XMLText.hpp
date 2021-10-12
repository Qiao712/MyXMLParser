#pragma once
#include "XMLTerminalNode.hpp"
#include "XMLVisitor.hpp"

#include <string>

namespace QSimpleXMLParser {
using std::string;
class XMLText : public XMLTerminalNode{
	//allow them to access _content to check weather it is white
	friend class XMLNonterminalNode;
	friend class XMLDocument;
	friend class XMLElement;
	friend class XMLCDATA;
public:
	XMLText() = default;
	XMLText(const string & content) : _content(content) {}
	XMLText(string && content) : _content(content) {}

	const string& getValue() const override { return _content; }
	virtual void setValue(const string & value) { _content.assign(value); }
	virtual void setValue(string && value) { _content.assign(value); };

	XMLText* clone() override { return new XMLText(_content); }
	XMLText* deepClone() override { return clone(); }

	bool accept(XMLVisitor& visitor) override { return visitor.visit(this); }
private:
	const char* parse(const char* beg, const char* end, XMLNonterminalNode* parent, ParsingError& parsing_error) override;
	std::string _content;
};
}