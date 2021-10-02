#include "XMLDocument.hpp"
#include "XMLDeclaration.hpp"
#include "StringUtility.hpp"

namespace MyXMLParser {
    const char* XMLDeclaration::parse(const char* beg, const char* end, XMLNonterminalNode* parent, size_t& line_num)
    {
        const char* gt = StringUtility::findChar('>', beg, end);
        if (gt == end || *(gt - 1) != '?') {
            //error: unclosed declaration
            setParsingError(XML_PARSING_ERROR_DECLARATION, line_num);
            return nullptr;
        }

        _content.assign(StringUtility::processText(beg + 2, gt - 1, StringUtility::NORMALIZE_NEWLINE | StringUtility::TRANSLATE_ENTITY));
        line_num += StringUtility::countChar('\n', _content);

        return gt + 1;
    }
}