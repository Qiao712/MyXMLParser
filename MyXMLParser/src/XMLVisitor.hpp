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
		/*return false to abort downward recursion*/
		virtual bool visitEntry(XMLDocument* node) { return true; }
		virtual bool visitExit(XMLDocument* node) { return true; }
		virtual bool visitEntry(XMLElement* node) { return true; }
		virtual bool visitExit(XMLElement* node) { return true; }

		virtual void visit(XMLText* node) { }
		virtual void visit(XMLCDATA* node) { }
		virtual void visit(XMLComment* node) { }
		virtual void visit(XMLDeclaration* node) { }
	};
}

