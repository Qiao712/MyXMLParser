#include "XMLNode.hpp"

#include <string>

namespace MyXMLParser{
class XMLDocument : public XMLNode{
    public:
        bool parse(char* xml, size_t len);
        bool parse(const string& xml);
        string getErrorDetail();
        
    private:
        bool parse(char* beg, char* end);
};
}