#include "define.h"
#include "XMLNode.hpp"
#include "XMLAttribute.hpp"
#include "StringProxy.h"

#include <vector>

namespace MyXMLParser{
using std::vector;
using std::string;

class XMLElement : public XMLNode{
    public:
        string getTagName();
        void setTagName(const string& name);

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
    private:
        StringProxy _tag_name;
        vector<XMLAttribute*> _attributes;
};
}