#include "XMLElement.hpp"

namespace MyXMLParser{
	const char* XMLElement::parse(const char* beg, const char* end, size_t& line_num)
	{
		const char* tag_name_end = findChar('>', beg, end);
		if (tag_name_end == end) {
			//<tag_name... ....
			
			return nullptr;
		}

		
		_tag_name.assign(beg + 1, tag_name_end);


		return nullptr;
	}
}
