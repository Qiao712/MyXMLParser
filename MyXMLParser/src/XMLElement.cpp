#include "XMLElement.hpp"

#include <cctype>
#include <cstring>
namespace MyXMLParser{
	bool XMLElement::checkTagName(const char* beg, const char* end)
	{
		for (const char* p = beg; p != end; p++) {
			if (isalpha(*p) || isdigit(*p) || *p == '.' || *p == '_' || *p == '-' || *p == ':' || *p >= 128) continue;
			else return false;
		}
		return true;
	}
	const char* XMLElement::findEndTag(const char* beg, const char* end)
	{
		static string end_tag;
		end_tag = "</" + _tag_name + ">";
		return findSubstr(beg, end, end_tag.c_str());
	}
	const char* XMLElement::parse(const char* beg, const char* end, size_t& line_num)
	{
		const char* tag_name_beg = beg + 1;
		const char* tag_name_end = findChar('>', beg, end);
		if (tag_name_end == end) {
			//<tag_name... ....
			
			return nullptr;
		}

		if (! checkTagName(tag_name_beg, tag_name_end)) {

			return nullptr;
		}
		
		_tag_name.assign(tag_name_beg, tag_name_end);

		const char* element_content_beg = tag_name_end + 1;
		const char* element_content_end = findEndTag(beg, end);

		if (element_content_end == end) {
			
			return nullptr;
		}

		//parse xml in the element
		if (XMLNonterminalNode::parse(element_content_beg, element_content_end, line_num) == element_content_end) {
			//succeed
			return element_content_end + _tag_name.size() + 3;
		}
		else {
			//fail
			return nullptr;
		}
	}
}
