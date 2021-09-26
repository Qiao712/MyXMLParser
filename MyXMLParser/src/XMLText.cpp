#include "XMLText.hpp"

namespace MyXMLParser {
    const char* XMLText::parse(const char* beg, const char* end, XMLNonterminalNode* parent, size_t& line_num)
    {
        const char* text_end = findChar('<', beg, end);
        _content.setString(beg, text_end, STR_PROCESSING::NORMALIZE_NEWLINE & STR_PROCESSING::TRANSLATE_ENTITY);
        line_num += _content.countChar('\n');
        return text_end;
    }
}
