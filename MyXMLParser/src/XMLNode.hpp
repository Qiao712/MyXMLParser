#pragma once

#include <string>
#include <vector>
using std::string;
using std::vector;

namespace MyXMLParser{
class XMLNode{
    public:
        XMLNode* firstChild();
        XMLNode* fisrtElementChild();
        XMLNode* lastChild();
        XMLNode* lastElementChild();
        XMLNode* nextSibling();
        XMLNode* previousSibling();
        XMLNode* getParent();

        XMLNode* findElementByTagName(string tag_name, XMLNode* start);
    protected:
        XMLNode();
        virtual ~XMLNode();
    private:
        vector<XMLNode*> _children;
        XMLNode* _parent;
        XMLNode* _next_sibling;
        XMLNode* _previous_sibling;
};
}