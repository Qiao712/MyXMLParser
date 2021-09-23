#include "XMLDocument.hpp"
#include "XMLComment.hpp"
#include "XMLDeclaration.hpp"
#include "XMLElement.hpp"
#include "XMLText.hpp"

namespace MyXMLParser {
	bool XMLDocument::parse(const char* xml, size_t len)
	{
		size_t line_num = 1;
		return parse(xml, xml+len, line_num);
	}
	const char* XMLDocument::parse(const char * beg, const char * end, size_t & line_num)
	{
		const char* p = skipWhitespace(beg, end, line_num);
		XMLNode* new_node;
		while (p != end) {
			new_node = createNodeByStartChar(p, end);
			
			if (new_node != nullptr) {
				p = new_node->parse(p, end, line_num);
				if (p == nullptr) {
					
					return nullptr;
				}
				else {
					//discard text node of whitespace
					XMLText* text_node = dynamic_cast<XMLText*>(new_node);
					if (text_node != nullptr && text_node->_content.isAllWhitespace())
						delete new_node;
					else
						addLastChild(new_node);
				}
			}
			else {
				return nullptr;
			}
		}

		return end;
	}
}