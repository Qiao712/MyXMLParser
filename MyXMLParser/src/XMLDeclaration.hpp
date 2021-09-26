#include "XMLTerminalNode.h"
#include "StringProxy.h"

namespace MyXMLParser {
class XMLDeclaration : public XMLTerminalNode{
public:
	XMLDeclaration() = default;
	XMLDeclaration(const string& content);
	XMLDeclaration(string&& content);

	const string& getValue() const override { return _content.getString(); }
	virtual void setValue(const string& value) { _content.setString(value); }
	virtual void setValue(string&& value) { _content.setString(value); };

	const char* parse(const char* beg, const char* end, const string& parent_tag_name, size_t& line_num) override;
private:
	StringProxy _content;
};
}