#include "XMLCDATA.hpp"
#include "StringUtility.hpp"

namespace MyXMLParser {
	const char* MyXMLParser::XMLCDATA::parse(const char* beg, const char* end, XMLNonterminalNode* parent)
	{
        //CDATA <![CDATA[ .... ]]>
        constexpr char CDATA_END[] = "]]>";
        constexpr int LEN_CDATA_BEG = 8;
        constexpr int LEN_CDATA_END = 3;

        const char* data_beg = beg + 1 + LEN_CDATA_BEG;
        const char* data_end = StringUtility::findSubstr(data_beg, end, CDATA_END);

        if (data_end == end) {
            //error unclosed cdata
            setParsingError(XML_PARSING_ERROR_UNCLOSED_CDATA, beg);
            return nullptr;
        }

        _content.assign(data_beg, data_end);
        return data_end + LEN_CDATA_END;
	}
}
