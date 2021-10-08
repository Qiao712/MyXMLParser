#pragma once
namespace MyXMLParser {
	class XMLDocument;
	class XMLElement;
	class XMLText;
	class XMLCDATA;
	class XMLDeclaration;
	class XMLComment;

	class XMLVisitor
	{
	public:
		/*return false: doesn't travel its childern.*/
		virtual bool visitEntry(XMLDocument* node) { return true; }
		virtual bool visitEntry(XMLElement* node) { return true; }

		/*return false: stop traveling its sibling.*/
		virtual bool visitExit(XMLDocument* node) { return true; }
		virtual bool visitExit(XMLElement* node) { return true; }
		virtual bool visit(XMLText* node) { return true; }
		virtual bool visit(XMLCDATA* node) { return true; }
		virtual bool visit(XMLComment* node) { return true; }
		virtual bool visit(XMLDeclaration* node) { return true; }
	};
}

