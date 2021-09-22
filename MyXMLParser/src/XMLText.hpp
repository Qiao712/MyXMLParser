#include "XMLTerminalNode.h"
#include "StringProxy.h"

#include <string>

namespace MyXMLParser {
using std::string;
class XMLText : public XMLTerminalNode{
public:
	XMLText() = default;
	XMLText(const string & content);
	XMLText(string && content);

	const string& getValue() const override { return _content.getString(); }
	virtual void setValue(const string & value) { _content.setString(value); }
	virtual void setValue(string && value) { _content.setString(value); };

	const char* parse(const char* beg, const char* end, size_t & line_num) override;
private:
	

	StringProxy _content;
};
}