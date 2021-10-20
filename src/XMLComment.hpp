#ifndef __XML_COMMENT__
#define __XML_COMMENT__
#include "XMLTerminalNode.hpp"
#include "StringUtility.hpp"
#include "XMLVisitor.hpp"

#include <string>

namespace QSimpleXMLParser {
	/**
	* XML Comment node class.
	*/
	class XMLComment : public XMLTerminalNode {
	public:
		XMLComment() = default;
		XMLComment(const std::string& content) : _content(content){}
		XMLComment(std::string&& content) : _content(content) {}

		/// Get comment std::string.
		const std::string& getValue() const override { return _content; }
	
		/// Set comment std::string.
		void setValue(const std::string& value) { _content.assign(value); }
		/// Set comment std::string.
		void setValue(std::string&& value) { _content.assign(value); }
	
		XMLComment* clone() override { return new XMLComment(_content); }
		XMLComment* deepClone() override { return clone(); }

		bool accept(XMLVisitor& visitor) override { return visitor.visit(*this); }
	private:
		const char* parse(const char* beg, const char* end, XMLNonterminalNode* parent, ParseError& parsing_error) override;
		std::string _content;
	};
}

#endif