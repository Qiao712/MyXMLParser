#include "XMLText.hpp"

namespace MyXMLParser {
    const char* MyXMLParser::XMLText::parse(const char* beg, const char* end, size_t& line_num)
    {
        line_num += countChar('\n', beg, end);

        _content.setString(string(beg, end));

        return end;
    }
}
