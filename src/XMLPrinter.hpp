#ifndef __XML_PRINTER__
#define __XML_PRINTER__
#include "XMLVisitor.hpp"
#include "XMLText.hpp"

#include <iostream>
#include <string>
namespace QSimpleXMLParser {
	/**
	* A visitor that print a XML DOM to a XML document.
	*/
	class XMLPrinter : public XMLVisitor
	{
	public:
		/**
		* @param out where output.
		* @param indent the characters that controls indentation. Default is two space.
		*/
		XMLPrinter(std::ostream& out, const std::string& indent = "  ") : _out(out), _indent(indent) { }

		bool visitEntry(XMLElement& node) override;
		bool visitExit(XMLElement& node) override;
		bool visit(XMLText& node) override;
		bool visit(XMLCDATA& node) override;
		bool visit(XMLComment& node) override;
		bool visit(XMLDeclaration& node) override;
	private:
		void print(const std::string& str) { _out << str; }
		void print(const char* str) { _out << str; }
		void print(char chr) { _out.put(chr); }
		void controlIndent() { for (int i = 0; i < _deep; i++) print(_indent); }
		bool isText(XMLNode* node) { return node != nullptr && typeid(*node) == typeid(XMLText); }
		
		size_t _deep = 0;
		std::string _indent;
		std::ostream& _out;
	};
}

#endif