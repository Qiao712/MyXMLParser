#include "XMLDocument.hpp"
#include "XMLDeclaration.hpp"
#include "StringUtility.hpp"

namespace MyXMLParser {
    const char* XMLDeclaration::parse(const char* beg, const char* end, XMLNonterminalNode* parent, ParsingError& parsing_error)
    {
        const char* gt = StringUtility::findChar('>', beg, end);
        if (gt == end || *(gt - 1) != '?') {
            //error: unclosed declaration
            parsing_error.setParsingError(XML_PARSING_ERROR_DECLARATION, beg);
            return nullptr;
        }

        _content.assign(StringUtility::processText(beg + 2, gt - 1, StringUtility::NORMALIZE_NEWLINE | StringUtility::TRANSLATE_ENTITY));

        return gt + 1;
    }
}