#pragma once
#include "XMLTerminalNode.hpp"
#include "XMLVisitor.hpp"

#include <string>

namespace QSimpleXMLParser {
	/**
	* XML Declaration node class.
	* 
	* Just store the string.
	*/
	class XMLDeclaration : public XMLTerminalNode{
	public:
		XMLDeclaration() = default;
		XMLDeclaration(const std::string& content) : _content(content){ }
		XMLDeclaration(std::string&& content) : _content(content){ }

		/// Get declaration std::string.
		const std::string& getValue() const override { return _content; }
	
		/// Set declaration std::string.
		virtual void setValue(const std::string& value) { _content.assign(value); }
	
		/// Set declaration std::string.
		virtual void setValue(std::string&& value) { _content.assign(value); }

		XMLDeclaration* clone() override { return new XMLDeclaration(_content); }
		XMLDeclaration* deepClone() override { return clone(); }

		bool accept(XMLVisitor& visitor) override { return visitor.visit(*this); }
	private:
		const char* parse(const char* beg, const char* end, XMLNonterminalNode* parent, ParseError& parsing_error) override;
		std::string _content;
	};
}