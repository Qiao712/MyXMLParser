#ifndef __XML_ELEMENT__
#define __XML_ELEMENT__
#include "XMLNonterminalNode.hpp"
#include "StringUtility.hpp"

#include <map>
#include <string>

namespace QSimpleXMLParser{
    /**
    * XML Element node class.
    */
    class XMLElement : public XMLNonterminalNode {
        friend class XMLNonterminalNode;
    public:
        XMLElement() = default;
        XMLElement(const std::string& tag_name) : _tag_name(tag_name) {}
        XMLElement(std::string&& tag_name):_tag_name(tag_name){ }

        /// Query whether the attribute exists.
        bool containAttribute(const std::string& name) { return _attributes.find(name) != _attributes.end(); }
    
        /// Delete the attribute. If not exist, return false.
        bool deleteAttribute(const std::string& name);
    
        /// Return the attribute's std::string value. If not exist, return empty std::string.
        const std::string& getAttribute(const std::string& name) const;
        /// Copy the attribute's value to 'value'. If not exist, return false.
        bool getAttribute(const std::string& name, std::string& value) const { value = getAttribute(name); }
        /// Put the attribute's value in 'value' as double. If the conversion fails or the attribute doesn't exist, return false.
        bool getAttribute(const std::string& name, double& value) const;
        /// Put the attribute's value in 'value' as long double. If the conversion fails or the attribute doesn't exist, return false.
        bool getAttribute(const std::string& name, long double& value) const;
        /// Put the attribute's value in 'value' as float. If the conversion fails or the attribute doesn't exist, return false.
        bool getAttribute(const std::string& name, float& value) const;
        /// Put the attribute's value in 'value' as int. If the conversion fails or the attribute doesn't exist, return false.
        bool getAttribute(const std::string& name, int& value) const;
        /// Put the attribute's value in 'value' as long. If the conversion fails or the attribute doesn't exist, return false.
        bool getAttribute(const std::string& name, long& value) const;
        /// Put the attribute's value in 'value' as long long. If the conversion fails or the attribute doesn't exist, return false.
        bool getAttribute(const std::string& name, long long& value) const;
        /// Put the attribute's value in 'value' as unsigned int. If the conversion fails or the attribute doesn't exist, return false.
        bool getAttribute(const std::string& name, unsigned int& value) const;
        /// Put the attribute's value in 'value' as unsigned long. If the conversion fails or the attribute doesn't exist, return false.
        bool getAttribute(const std::string& name, unsigned long& value) const;
        /// Put the attribute's value in 'value' as unsigned long long. If the conversion fails or the attribute doesn't exist, return false.
        bool getAttribute(const std::string& name, unsigned long long& value) const;
        /// Put the attribute's value in 'value' as bool. Only "true" and "false" are legal(Case insensitive).If the conversion fails or the attribute doesn't exist, return false.
        bool getAttribute(const std::string& name, bool& value) const;
        /// Return the std::map contains all attributes.
        const std::map<std::string, std::string> getAllAttributes() { return _attributes; }

        /// Set the attribute's value. If not exist, add it.
        void setAttribute(const std::string& name, const std::string& value) { _attributes[name].assign(value); }
        /// Set the attribute's value. If not exist, add it.
        void setAttribute(const std::string& name, std::string&& value) { _attributes[name].assign(value); }
        /// Set the attribute's value. If not exist, add it.
        void setAttribute(const std::string& name, double value) { _attributes[name].assign(std::to_string(value)); }
        /// Set the attribute's value. If not exist, add it.
        void setAttribute(const std::string& name, long double value) { _attributes[name].assign(std::to_string(value)); }
        /// Set the attribute's value. If not exist, add it.
        void setAttribute(const std::string& name, float value) { _attributes[name].assign(std::to_string(value)); }
        /// Set the attribute's value. If not exist, add it.
        void setAttribute(const std::string& name, int value) { _attributes[name].assign(std::to_string(value)); }
        /// Set the attribute's value. If not exist, add it.
        void setAttribute(const std::string& name, long value) { _attributes[name].assign(std::to_string(value)); }
        /// Set the attribute's value. If not exist, add it.
        void setAttribute(const std::string& name, long long value) { _attributes[name].assign(std::to_string(value)); }
        /// Set the attribute's value. If not exist, add it.
        void setAttribute(const std::string& name, unsigned int value) { _attributes[name].assign(std::to_string(value)); }
        /// Set the attribute's value. If not exist, add it.
        void setAttribute(const std::string& name, unsigned long value) { _attributes[name].assign(std::to_string(value)); }
        /// Set the attribute's value. If not exist, add it.
        void setAttribute(const std::string& name, unsigned long long value) { _attributes[name].assign(std::to_string(value)); }
        /// Set the attribute's value. ("true" or "false") If not exist, add it.
        void setAttribute(const std::string& name, bool value) { value ? _attributes[name].assign("true") : _attributes[name].assign("false"); }

        /// Get tag name.
        const std::string& getTagName() const { return _tag_name; }
        /// Set tag name.
        void setTagName(const std::string& tag_name) { _tag_name = tag_name; }
        /// Set tag name.
        void setTagName(std::string&& tag_name) { _tag_name = tag_name; }
    
        /// Get tag name.
        const std::string& getValue() const override { return getTagName(); }
        /// Set tag name.
        void setValue(const std::string& value) override { setTagName(value); }
        /// Set tag name.
        void setValue(std::string&& value) override { setTagName(value); }

        XMLElement* clone() override;
        XMLElement* deepClone() override { return reinterpret_cast<XMLElement*>(doDeepClone()); }

        bool accept(XMLVisitor& visitor) override;
    private:
        const char* parse(const char* beg, const char* end, XMLNonterminalNode* parent, ParseError& parsing_error) override;
        XMLParseError parseAttribute(const char* beg, const char* end);
        bool checkName(const char* beg, const char* end);

        std::string _tag_name;
        std::map<std::string, std::string> _attributes;
    };
}

#endif