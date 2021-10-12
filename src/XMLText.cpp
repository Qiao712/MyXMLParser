#include "XMLText.hpp"
#include "StringUtility.hpp"

namespace QSimpleXMLParser {
    const char* XMLText::parse(const char* beg, const char* end, XMLNonterminalNode* parent, ParsingError& parsing_error)
    {
        const char* text_end = StringUtility::findChar('<', beg, end);
        _content = StringUtility::processText(beg, text_end, StringUtility::NORMALIZE_NEWLINE | StringUtility::TRANSLATE_ENTITY);
        return text_end;
    }
}
