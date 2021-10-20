#ifndef __XML_CDATA__
#define __XML_CDATA__
#include "XMLText.hpp"
#include "XMLVisitor.hpp"

namespace QSimpleXMLParser{
	/**
	* XML CDATA node class
	*/
	class XMLCDATA : public XMLText
	{
	public:
		using XMLText::XMLText;
		XMLCDATA* clone() override { return new XMLCDATA(_content); }
		XMLCDATA* deepClone() override { return clone(); }

		bool accept(XMLVisitor& visitor) override { return visitor.visit(*this); }
	private:
		const char* parse(const char* beg, const char* end, XMLNonterminalNode* parent, ParseError& parsing_error) override;
	};
}

#endif