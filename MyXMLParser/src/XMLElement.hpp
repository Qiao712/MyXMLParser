#pragma once
#include "XMLNonterminalNode.hpp"
#include "XMLAttribute.hpp"
#include "StringUtility.hpp"

#include <map>
#include <string>

namespace MyXMLParser{
using std::map;
using std::string;

class XMLElement : public XMLNonterminalNode {
    friend class XMLNonterminalNode;
public:
    XMLElement() = default;
    XMLElement(const string& tag_name) : _tag_name(tag_name) {}
    XMLElement(string&& tag_name):_tag_name(tag_name){ }

    bool containAttribute(const string& name) { return _attributes.find(name) != _attributes.end(); }
    
    bool deleteAttribute(const string& name);
    
    const string& getAttribute(const string& name) const;
    bool getAttribute(const string& name, string& value) const { value = getAttribute(name); }
    bool getAttribute(const string& name, double& value) const;
    bool getAttribute(const string& name, long double& value) const;
    bool getAttribute(const string& name, float& value) const;
    bool getAttribute(const string& name, int& value) const;
    bool getAttribute(const string& name, long& value) const;
    bool getAttribute(const string& name, long long& value) const;
    bool getAttribute(const string& name, unsigned int& value) const;
    bool getAttribute(const string& name, unsigned long& value) const;
    bool getAttribute(const string& name, unsigned long long& value) const;
    bool getAttribute(const string& name, bool& value) const;
    const map<string, string> getAllAttributes() { return _attributes; }

    void setAttribute(const string& name, const string& value) { _attributes[name].assign(value); }
    void setAttribute(const string& name, string&& value) { _attributes[name].assign(value); }
    void setAttribute(const string& name, double value) { _attributes[name].assign(std::to_string(value)); }
    void setAttribute(const string& name, long double value) { _attributes[name].assign(std::to_string(value)); }
    void setAttribute(const string& name, float value) { _attributes[name].assign(std::to_string(value)); }
    void setAttribute(const string& name, int value) { _attributes[name].assign(std::to_string(value)); }
    void setAttribute(const string& name, long value) { _attributes[name].assign(std::to_string(value)); }
    void setAttribute(const string& name, long long value) { _attributes[name].assign(std::to_string(value)); }
    void setAttribute(const string& name, unsigned int value) { _attributes[name].assign(std::to_string(value)); }
    void setAttribute(const string& name, unsigned long value) { _attributes[name].assign(std::to_string(value)); }
    void setAttribute(const string& name, unsigned long long value) { _attributes[name].assign(std::to_string(value)); }
    void setAttribute(const string& name, bool value) { value ? _attributes[name].assign("true") : _attributes[name].assign("false"); }

    const string& getTagName() const { return _tag_name; }
    void setTagName(const string& tag_name) { _tag_name = tag_name; }
    void setTagName(string&& tag_name) { _tag_name = tag_name; }
    const string& getValue() const override { return getTagName(); }
    void setValue(const string& value) override { setTagName(value); }
    void setValue(string&& value) override { setTagName(value); }

    XMLElement* clone() override;
    XMLElement* deepClone() override { return reinterpret_cast<XMLElement*>(doDeepClone()); }

    bool accept(XMLVisitor& visitor) override;
private:
    const char* parse(const char* beg, const char* end, XMLNonterminalNode* parent, ParsingError& parsing_error) override;
    XMLParseError parseAttribute(const char* beg, const char* end);
    bool checkName(const char* beg, const char* end);

    string _tag_name;
    map<string, string> _attributes;
};
}