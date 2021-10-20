#ifndef __XML_DOCUMENT__
#define __XML_DOCUMENT__
#include "XMLNonterminalNode.hpp"

namespace QSimpleXMLParser{
    /**
    * XML Document node class.
    * 
    * Represent the entire document. It is always a root and can be a child of other node.
    * It can parse a xml document from std::string.
    */
    class XMLDocument : public XMLNonterminalNode{
        friend class XMLTerminalNode;
        friend class XMLNonterminalNode;
        friend class XMLDocument;
        friend class XMLComment;
        friend class XMLDeclaration;
        friend class XMLElement;
        friend class XMLText;
        friend class XMLNode;
    public:
        XMLDocument() = default;

        /**
        * @brief Parse an XML from C-style std::string.
        * 
        * Generate DOM tree whoes root node is this document node.
        * Warning: All its provious descentants will be deleted.
        * 
        * @return Return true on success, or false. You can use getErrorDetail(), getError and getErrorLine() to get detailed error information.
        */
        bool parse(const char* xml);

        /**
        * @brief Parse an XML from std::string.
        *
        * Generate DOM tree whoes root node is this document node.
        * Warning: All its provious descentants will be deleted.
        *
        * @return Return true on success, or false. You can use getErrorDetail(), getError and getErrorLine() to get detailed error information.
        */
        bool parse(const std::string& xml);

        /**
        * @brief Parse an XML from xml file.
        *
        * Generate DOM tree whoes root node is this document node.
        * Warning: All its provious descentants will be deleted.
        *
        * @return Return true on success, or false. You can use getErrorDetail(), getError and getErrorLine() to get detailed error information.
        */
        bool loadFile(const std::string path);
    
        /// Delete all its descentants and clear parse erorr record.
        void clear();

        /// Clear parse error record.
        void clearError() { _parse_error.clear(); }
    
        /// Check Whether errors occur during parsing.
        bool good() const { return _parse_error.error == XMLParseError::XML_PARSE_SUCCESS; }

        /// Get detail parse error description.
        std::string getErrorDetail() const { return _parse_error.error_detail; }
    
        /// Get parse error code.
        XMLParseError getError() const { return _parse_error.error; }

        /// Number of line parse error occur in.
        size_t getErrorLine() const { return _parse_error.error_line; }

        /// Always return empty std::string.
        const std::string& getValue() const override { static const std::string empty_str; return empty_str; }
    
        /// Do nothing.
        void setValue(const std::string& value) override { }

        /// Do nothing.
        void setValue(std::string&& value) override { }
    
        XMLDocument* clone() override { return new XMLDocument(); }
        XMLDocument* deepClone() override { return reinterpret_cast<XMLDocument*>(doDeepClone()); }

        bool accept(XMLVisitor& visitor) override;
    private:
        const char* parse(const char* beg, const char* end, XMLNonterminalNode* parent, ParseError& parsing_error) override;
        ParseError _parse_error;
    };
}

#endif