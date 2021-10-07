#pragma once
#include "XMLText.hpp"

namespace MyXMLParser{
	class XMLCDATA : public XMLText
	{
	public:
		using XMLText::XMLText;
		XMLCDATA* clone() override { return new XMLCDATA(_content); }
		XMLCDATA* deepClone() override { return clone(); }
	private:
		const char* parse(const char* beg, const char* end, XMLNonterminalNode* parent, ParsingError& parsing_error) override;
	};
}
