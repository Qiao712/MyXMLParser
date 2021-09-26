#include "XMLElement.hpp"

#include <cctype>
#include <cstring>
namespace MyXMLParser{
	bool XMLElement::checkTagName(const char* beg, const char* end)
	{
		if (beg >= end) return false;

		for (const char* p = beg; p != end; p++) {
			if (isalpha(*p) || isdigit(*p) || *p == '.' || *p == '_' || *p == '-' || *p == ':' || *p >= 128) continue;
			else return false;
		}
		return true;
	}
	const char* XMLElement::parse(const char* beg, const char* end, XMLNonterminalNode* parent, size_t& line_num)
	{
		const char* tag_name_beg = beg + 1;
		const char* tag_name_end = findChar('>', beg + 1, end);
		if (tag_name_end == end) {
			//<tag_name... ....

			return nullptr;
		}

		//check <.../>
		if (*(tag_name_end - 1) == '/') {
			if (!checkTagName(tag_name_beg, tag_name_end - 1)) {
				//error: bad tag name
				
				return nullptr;
			}

			_is_closing = true;
			_tag_name.assign(tag_name_beg, tag_name_end - 1);
			return tag_name_end + 1;
		}
		
		if (!checkTagName(tag_name_beg, tag_name_end)) {
			//error: bad tag name

			return nullptr;
		}
		_tag_name.assign(tag_name_beg, tag_name_end);

		//parse xml in the element
		const char* p = parseChildren(tag_name_end + 1, end, this, line_num);
		
		if (p == end && _is_closing == false) {
			//error: not be closed

			return nullptr;
		}

		return p;
	}
}