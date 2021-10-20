#ifndef __XML_TEXT__
#define __XML_TEXT__
#include "XMLTerminalNode.hpp"
#include "XMLVisitor.hpp"

#include <string>

namespace QSimpleXMLParser {
	/**
	* XML Text node class.
	*/
	class XMLText : public XMLTerminalNode{
		//allow them to access _content to check weather it is white
		friend class XMLNonterminalNode;
		friend class XMLDocument;
		friend class XMLElement;
		friend class XMLCDATA;
	public:
		XMLText() = default;
		XMLText(const std::string & content) : _content(content) {}
		XMLText(std::string && content) : _content(content) {}

		/// Get text std::string.
		const std::string& getValue() const override { return _content; }
	
		/// Set text std::string.(Entity translation and other operations are not performed here.)
		virtual void setValue(const std::string & value) { _content.assign(value); }
	
		/// Set text std::string.(Entity translation and other operations are not performed here.)
		virtual void setValue(std::string && value) { _content.assign(value); };

		XMLText* clone() override { return new XMLText(_content); }
		XMLText* deepClone() override { return clone(); }

		bool accept(XMLVisitor& visitor) override { return visitor.visit(*this); }
	private:
		const char* parse(const char* beg, const char* end, XMLNonterminalNode* parent, ParseError& parsing_error) override;
		std::string _content;
	};
}

#endif