#pragma once
#include <string>
namespace QSimpleXMLParser{
    /// code of parsing error
    enum XMLParseError {
        XML_PARSE_SUCCESS = 0,
        XML_PARSE_ERROR_DECLARATION,

        XML_PARSE_ERROR_UNPAIRED_TAG,      //Unpaired tag 未配对的标签
        XML_PARSE_ERROR_WRONG_END_TAG,     //wrong end tag 错误的结束标签
        XML_PARSE_ERROR_UNCLOSED_PARENTHESE,  //Unclosed parenthese 未封闭的括号 <....
        XML_PARSE_ERROR_INVALID_TAG_NAME,      //Invalid tag name 无效的标签名

        XML_PARSE_ERROR_ATTR,
        XML_PARSE_ERROR_DUPLICATE_ATTR_NAME,   //重复的属性名
        XML_PARSE_ERROR_INVALID_ATTR_NAME,      //无效的属性名

        XML_PARSE_ERROR_UNCLOSED_CDATA
    };

    struct ParseError {
        void setParseError(XMLParseError error, const char* where_error);
        void clear();

        XMLParseError error = XML_PARSE_SUCCESS;
        size_t   error_line = 0;
        std::string   error_detail;
        const char* raw_xml_beg = nullptr;
        const char* raw_xml_end = nullptr;
    };

    class XMLElement;
    class XMLDocument;
    class XMLNonterminalNode;
    class XMLVisitor;

    /**
    * XMLNode is the base class of all other types of nodes.
    * 
    * @note Attibutes of elements are not treaded as node.
    */
    class XMLNode{
        friend class XMLVisitor;
        friend class XMLTerminalNode;
        friend class XMLNonterminalNode;
        friend class XMLDocument;
        friend class XMLComment;
        friend class XMLDeclaration;
        friend class XMLElement;
        friend class XMLText;
    public:
        XMLNode() = default;

        /// Delete all its descentants in recursively.
        virtual ~XMLNode();

        /// Get the first child node. If no child, return nullptr.
        virtual XMLNode* firstChild() = 0;

        /// Get the last child node. If no child, return nullptr.
        virtual XMLNode* lastChild() = 0;

        /// Get the first child element node. If no element child, return nullptr.
        virtual XMLElement* fisrtElementChild() = 0;
    
        /// Get the last child element node. If no element child, return nullptr.
        virtual XMLElement* lastElementChild() = 0;

        /**
        * @brief Get the first child element node with concrete. If none exists, return nullptr.
        * 
        * @param start A pointer to a child indicate where to start looking.
        */
        virtual XMLElement* findElementByTagName(const std::string& tag_name, XMLNode* start = nullptr) = 0;

        /// Get next sibling node. If no next sibling, return nullptr.
        virtual XMLNode* nextSibling() { return _next_sibling; }

        /// Get the previous node. If no previous sibling, return nullptr.
        virtual XMLNode* previousSibling() { return _previous_sibling; }

        /// Get the parent node. If the node is a root, return nullptr.
        virtual XMLNode* getParent() { return reinterpret_cast<XMLNode*>(_parent); }
    
        /// Get root node of the tree.
        XMLNode* getRoot();

        /// Get the document which is the root node of the tree. If the root node isn't document node,return nullptr.
        XMLDocument* getDocument();

        /**
        * @brief Accept a visitor to traverse the tree.
        * 
        * Accept a visitor to visit this node and all its descentants in preorder traversal.
        * When visit a node, it will call corresponding XMLVisitor interface.
        * 
        * @note see Visitor Pattern
        */
        virtual bool accept(XMLVisitor& visitor) = 0;
    
        /// Add a child at front. If the node already has a parent, return false.
        virtual bool addFirstChild(XMLNode* node) = 0;
    
        /// Add a child at back. If the node already has a parent, return false.
        virtual bool addLastChild(XMLNode* node) = 0;

        /// Add a child after a concrete child . If the node already has a parent, return false.
        virtual bool insertChild(XMLNode* node, XMLNode* after_this) = 0;

        /// Remove(delete) the head child. If no child, return false.
        virtual bool removeFirstChild() = 0;
    
        /// Remove(delete) the tail child. If no child, return false.
        virtual bool removeLastChild() = 0;

        /// Remove(delete) a child. If the given node isn't the child of the node, return false.
        virtual bool removeChild(XMLNode* node) = 0;

        /// Remove(delete) all its children. If no child, return false.
        virtual bool removeAllChildren() = 0;

        /// Unlink the node from its parents and sibling.(Detach the node from the tree.
        void unlink();

        /**
        * @brief Get value of the node.
        * 
        * The meaning of 'value' changes for the specific type.
        * Docment: always empty std::string
        * Element: tag name
        * Text: text
        * CDATA: text
        * Declaration: declaration text
        * Comment: comment text
        */
        virtual const std::string& getValue() const = 0;

    
        /// Set value of the node. Do nothing with document node.
        virtual void setValue(const std::string& value) = 0;

        /// Set value of the node. Do nothing with document node.
        virtual void setValue(std::string&& value) = 0;

        /// Shallow clone.(Clone this node, but not its children. The new node has no child or parent.)
        virtual XMLNode* clone() = 0;

        /// Clone the node and all its descents.
        virtual XMLNode* deepClone() = 0;
    protected:
        virtual const char* parse(const char* beg, const char* end, XMLNonterminalNode* parent, ParseError& parsing_error) = 0;
    private:
        XMLNonterminalNode* _parent = nullptr;
        XMLNode* _next_sibling = nullptr;
        XMLNode* _previous_sibling = nullptr;

        //delete copy operator
        XMLNode& operator=(const XMLNode&) = delete;
        XMLNode(const XMLNode&) = delete;
    };
}