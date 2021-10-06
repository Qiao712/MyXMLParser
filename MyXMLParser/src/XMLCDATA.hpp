#pragma once
#include "XMLText.hpp"

namespace MyXMLParser{
	class XMLCDATA : public XMLText
	{
		const char* parse(const char* beg, const char* end, XMLNonterminalNode* parent, ParsingError& parsing_error) override;
	};
}
