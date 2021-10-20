#ifndef __XML_NONTERMINALNODE__
#define __XML_NONTERMINALNODE__
#include "XMLNode.hpp"
#include "XMLVisitor.hpp"

namespace QSimpleXMLParser {
    /**
    * Base class of nonterminal node(Element and Document).
    */
    class XMLNonterminalNode : public XMLNode
    {
        friend class XMLNode;   //use to cancel link in XMLNode's destruction
    public:
        XMLNode* firstChild() override { return _first_child; }
        XMLNode* lastChild() override { return _last_child; }
        XMLElement* fisrtElementChild() override;
        XMLElement* lastElementChild() override;
        XMLElement* findElementByTagName(const std::string& tag_name, XMLNode* start = nullptr) override;

        bool addFirstChild(XMLNode* node) override;
        bool addLastChild(XMLNode* node) override;
        bool insertChild(XMLNode* node, XMLNode* after_this = nullptr) override;
        bool removeFirstChild() override;
        bool removeLastChild() override;
        bool removeChild(XMLNode* node) override;
        bool removeAllChildren() override;
        
        /// Delete all its descentants in recursively.
        ~XMLNonterminalNode();
    protected:
        enum class Token {
            ELEMENT_BEG,
            ELEMENT_END,
            DECLARATION, TEXT, COMMENT, CDATA, UNKNOWN
        };
        //parsing recurively from beg to end until encounter a corresponding closing tag, product nodes as children of this node.
        const char* parseChildren(const char* beg, const char* end, XMLNonterminalNode* parent, ParseError& parsing_error);
        Token checkStart(const char* beg, const char* end); 
        XMLNode* createNode(Token type);
        const char* matchTag(const char* beg, const char* end, const std::string& parent_tag_name, ParseError& parsing_error);

        //<a>....</a> closing; <a>.... unclosing.
        bool _is_closing = false;

        XMLNode* doDeepClone();
    
        void visitChildern(XMLVisitor& visitor);
    protected:
        XMLNode* _first_child = nullptr;
        XMLNode* _last_child = nullptr;
    };
}

#endif