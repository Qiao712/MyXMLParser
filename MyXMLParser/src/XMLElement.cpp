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
	const char* XMLElement::parse(const char* beg, const char* end, const string& parent_tag_name, size_t& line_num)
	{
		const char* tag_name_beg = beg + 1;
		const char* tag_name_end = findChar('>', beg + 1, end);
		if (tag_name_end == end) {
			//<tag_name... ....

			return nullptr;
		}

		//Is end tag? "</...>
		if (*tag_name_beg == '/') {
			_is_closing_tag = true;
			tag_name_beg++;
		}

		//check <.../>
		if (*(tag_name_end - 1) == '/') {
			if (_is_closing_tag || !checkTagName(tag_name_beg, tag_name_end - 1)) {
				//error: bad tag name
				
				return nullptr;
			}

			_tag_name.assign(tag_name_beg, tag_name_end - 1);
			return tag_name_end + 1;
		}
		
		if (!checkTagName(tag_name_beg, tag_name_end)) {
			//error: bad tag name

			return nullptr;
		}
		_tag_name.assign(tag_name_beg, tag_name_end);
		
		if (_is_closing_tag) return tag_name_end + 1;

		//parse xml in the element
		return XMLNonterminalNode::parse(tag_name_end + 1, end, _tag_name, line_num);
	}
}
