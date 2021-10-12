#include "XMLPrinter.hpp"
#include "XMLElement.hpp"
#include "XMLText.hpp"
#include "XMLCDATA.hpp"
#include "XMLComment.hpp"
#include "XMLDeclaration.hpp"
#include "XMLNode.hpp"

namespace QSimpleXMLParser {
	bool XMLPrinter::visitEntry(XMLElement* node)
	{
		if(!isText(node->previousSibling())) controlIndent();
		_deep++;
		
		print("<");
		print(node->getValue());	
		
		auto attributes = node->getAllAttributes();
		for (auto attr : attributes) {
			print(' ');
			print(attr.first);
			print("=\"");
			print(attr.second);
			print('\"');
		}

		if (node->firstChild()) {
			print(">");
			if (!isText(node->firstChild())) print('\n');
			return true;
		}
		else {
			print("/>");
			return false;
		}
	}

	bool XMLPrinter::visitExit(XMLElement* node)
	{
		_deep--;
		if (node->firstChild()) {
			if (!isText(node->lastChild())) controlIndent();
			print("</");
			print(node->getValue());
			print(">");
		}
		if (!isText(node->nextSibling())) print('\n');

		return true;
	}

	bool XMLPrinter::visit(XMLText* node)
	{
		print(node->getValue());
		return true;
	}

	bool XMLPrinter::visit(XMLCDATA* node)
	{
		if (!isText(node->previousSibling())) controlIndent();
		print("<![");
		print(node->getValue());
		print("]]>");
		if (!isText(node->nextSibling())) print('\n');
		return true;
	}

	bool XMLPrinter::visit(XMLComment* node)
	{
		if (!isText(node->previousSibling())) controlIndent();
		print("<!--");
		print(node->getValue());
		print("-->");
		if (!isText(node->nextSibling())) print('\n');
		return true;
	}

	bool XMLPrinter::visit(XMLDeclaration* node)
	{
		if (!isText(node->previousSibling())) controlIndent();
		print("<?");
		print(node->getValue());
		print("?>");
		if (!isText(node->nextSibling())) print('\n');
		return true;
	}
	
}