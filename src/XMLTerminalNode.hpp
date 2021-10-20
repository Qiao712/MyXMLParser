#ifndef __XML_TERMINALNODE__
#define __XML_TERMINALNODE__
#include "XMLNode.hpp"

namespace QSimpleXMLParser {
    /**
    * Base class of terminal node(text, comment, declaration).
    */
    class XMLTerminalNode : public XMLNode
    {
    public:
        /// Always return nullptr.
        XMLNode* firstChild() override { return nullptr; } 
        XMLNode* lastChild() override { return nullptr; }   ///< Always return nullptr.
        XMLElement* fisrtElementChild() override { return nullptr; } ///< Always return nullptr.
        XMLElement* lastElementChild()  override { return nullptr; } ///< Always return nullptr.
        /// Always return nullptr.
        XMLElement* findElementByTagName(const std::string& tag_name, XMLNode* start = nullptr) override { return nullptr; } 

        /// Always return flase.
        bool addFirstChild(XMLNode* node) override { return false; }
        bool addLastChild(XMLNode* node) override { return false; } ///< Always return flase.
        bool insertChild(XMLNode* node, XMLNode* after_this) override { return false; } ///< Always return flase.
        bool removeFirstChild() override { return false; } ///< Always return flase.
        bool removeLastChild() override { return false; } ///< Always return flase.
        bool removeChild(XMLNode* node) override { return false; } ///< Always return flase.
        bool removeAllChildren() override { return false; } ///< Always return flase.
};
}

#endif