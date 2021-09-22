#include "XMLText.hpp"

namespace MyXMLParser {
    const char* MyXMLParser::XMLText::parse(const char* beg, const char* end, size_t& line_num)
    {
        const char* text_end = findChar('<', beg, end) - 1;
        line_num += countChar('\n', beg, text_end);

        _content.setString(string(beg, text_end));

        return text_end + 1;
    }
}
