#ifndef __XML_VISITOR__
#define __XML_VISITOR__
namespace QSimpleXMLParser {
	class XMLDocument;
	class XMLElement;
	class XMLText;
	class XMLCDATA;
	class XMLDeclaration;
	class XMLComment;
	class XMLNode;

	/**
	* Interface to a visitor(Visitor Pattern).
	* Call a node's accept(XMLVisitor&) with a XMLVisitor object, then the visitor will 
	* traverses its every descentant in preorder traversal and call corresponding 
	* visit function with the node based on its type.
	*/
	class XMLVisitor
	{
	public:
		/// Visit a document. Will be called before traverse its children recursively. Return false to stop traverse its children.
		virtual bool visitEntry(XMLDocument& node) { return true; }

		/// Visit a document. Will be called after traverse its children recursively. Return false to stop traverse its siblings.
		virtual bool visitExit(XMLDocument& node) { return true; }
		
		/// Visit a element. Will be called before traverse its children recursively. Return false to stop traverse its children.
		virtual bool visitEntry(XMLElement& node) { return true; }

		/// Visit a document. Will be called after traverse its children recursively. Return false to stop traverse its siblings.
		virtual bool visitExit(XMLElement& node) { return true; }

		/// Visit a text node. Return false to stop traverse its siblings.
		virtual bool visit(XMLText& node) { return true; }

		/// Visit a CDATA node. Return false to stop traverse its siblings.
		virtual bool visit(XMLCDATA& node) { return true; }

		/// Visit a Comment node. Return false to stop traverse its siblings.
		virtual bool visit(XMLComment& node) { return true; }
		
		/// Visit a declaration node. Return false to stop traverse its siblings.
		virtual bool visit(XMLDeclaration& node) { return true; }
	};
}

#endif