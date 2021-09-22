#include "define.h"
#include "XMLNonterminalNode.h"
#include "XMLAttribute.hpp"
#include "StringProxy.h"

#include <vector>

namespace MyXMLParser{
using std::vector;
using std::string;

class XMLElement : public XMLNonterminalNode{
    public:
        XMLElement() = default;

        XMLAttribute* getAttribute();
        XMLAttribute* getAttribute(const string& name);
        XMLAttribute* getAttribute(size_t index);

        int getAttribute(const string& name, string& value);
        int getAttribute(const string& name, double& value);
        int getAttribute(const string& name, float& value);
        int getAttribute(const string& name, int& value);
        int getAttribute(const string& name, long long& value);
        int getAttribute(const string& name, unsigned int& value);
        int getAttribute(const string& name, unsigned long long& value);
        int getAttribute(const string& name, char& value);
        int getAttribute(const string& name, bool& value);
        
        int setAttribute(const string& name, const string& value);
        int setAttribute(const string& name, string&& value);
        int setAttribute(const string& name, double value);
        int setAttribute(const string& name, float value);
        int setAttribute(const string& name, int value);
        int setAttribute(const string& name, long long value);
        int setAttribute(const string& name, unsigned int value);
        int setAttribute(const string& name, unsigned long long value);
        int setAttribute(const string& name, char value);
        int setAttribute(const string& name, bool value);
        int deleteAttribute(const string& name);

        const string& getTagName() const { return _tag_name.getString(); }
        void setTagName(const string& tag_name) { _tag_name.setString(tag_name); }
        void setTagName(string&& tag_name) { _tag_name.setString(tag_name); }
        const string& getValue() const override { return getTagName(); }
        void setValue(const string& value) override { setTagName(value); }
        void setValue(string&& value) override { setTagName(value); }
    private:
        const char* parse(const char* beg,const char* end, size_t& line_num) override;

        StringProxy _tag_name;
        vector<XMLAttribute*> _attributes;
};
}