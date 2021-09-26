#pragma once
#include <cstdint>
#include <string>
namespace MyXMLParser{
    using std::string;
    extern enum XMLError {
        XML_SUCCESS = 0,
        XML_ERROR_TAG_NOT_FOUND,
        XML_ERROR_ATTRIBUTE_NOT_FOUND,
        XML_ERROR_ADD_CHILD_TO_TERMINAL_NODE,
        XML_ERROR_TERMINAL_NODE,
        XML_ERROR_REMOVE_FAIL,
        /*error in parsing*/
        XML_PARSING_ERROR_DECLARATION,
    };

    extern const char* ERROR_DESCRIPTION[];

    //sign of start and end
    extern const char COMMENT_START[];
    extern const int  LENGTH_COMMENT_START;
    extern const char COMMENT_END[];
    extern const int  LENGTH_COMMENT_END;
    extern const char DECLARATION_START[];
    extern const int  LENGTH_DECLARATION_START;
    extern const char DECLARATION_END[];
    extern const int  LENGTH_DECLARATION_END;

    const char* skipWhitespace(const char* beg, const char* end, size_t& line_num);
    const char* findChar(const char chr, const char* beg, const char* end);
    const char* findSubstr(const char* beg, const char* end, const char* substr);
    uint32_t strToIntHex(const char* beg, const char* end);
    uint32_t strToIntDec(const char* beg, const char* end);
    bool unicodeToUtf8(uint32_t unicode, string& utf8);
    bool compareStr(const char* beg, const char* end);
    size_t countChar(const char chr, const char * beg, const char * end);
}