#include "XMLTerminalNode.h"

namespace MyXMLParser {
class XMLComment : public XMLTerminalNode {
public:
	XMLComment() = default;
	XMLComment(const string& content);
	XMLComment(string&& content);

	const string& getValue() const override { return _content; }
	void setValue(const string& value) { _content = value; }
	void setValue(string&& value) { _content = value; }
protected:
	const char* parse(const char* beg, const char* end, XMLNonterminalNode* parent, size_t& line_num) override;
private:
	string _content;
};
}