#pragma once
#include <string>

namespace MyXMLParser{
using std::string;
    
enum STR_PROCESSING {
    TRANSLATE_ENTITY = 1,
    NORMALIZE_NEWLINE = 2,
};

class StringProxy{
    friend class XMLNode;
    friend class XMLElement;
    friend class XMLComment;
    friend class XMLDeclaration;
    friend class XMLAttribute;
    friend class XMLText;
public:
    void setString(string&& str) { _str = str; }
    void setString(const string& str) { _str = str; }
    void setString(const char* beg, const char* end, int processing_flag);
    const string& getString() const { return _str; }

    size_t countChar(char x);
            
    //is all char is whitespace
    bool isAllWhitespace();

    static string translateCharToEntity(const string& str);
private:
    StringProxy() = default;

    //translate entity and normalize newline, then store in _str in constructor
    //newline normalization: "\r\n", "\r" and "\n\r" -> "\n"
    void processAndStore(const char* beg, const char* end);
    bool parseReference(const char* beg, const char* end, string& substitute);

    string _str;
    unsigned char _processing_flag;
};
}