#include "XMLDocument.hpp"
#include "XMLDeclaration.hpp"
#include "StringProxy.h"

namespace MyXMLParser {
    const char* XMLDeclaration::parse(const char* beg, const char* end, const string& parent_tag_name, size_t& line_num)
    {
        const char* gt = findChar('>', beg, end);
        if (gt == end || *(gt - 1) != '?') {
            _root->setError(XML_PARSING_ERROR_DECLARATION, line_num);
            return nullptr;
        }

        _content.setString(string(beg + LENGTH_DECLARATION_START, gt - 1));

        return gt + 1;
    }
}