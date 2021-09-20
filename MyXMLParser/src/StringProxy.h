#include <string>

namespace MyXMLParser{
    using std::string;
    
    class StringProxy{
        friend class XMLNode;
        friend class XMLElement;
        friend class XMLComment;
        friend class XMLDeclaration;
        friend class XMLAttribute;
        friend class XMLText;
        public:
            void  setString(string&& str) { _str = str; }
            void  setString(const string& str) { _str = str; }
            const string& getString() const { return _str; }
        private:
            StringProxy(char* p, unsigned int len);

            static string translateEntityToChar(const char* p, unsigned int len);
            static string translateEntityToChar(const string& str);
            static string translateCharToEntity(const string& str);

            string _str;
    };
}