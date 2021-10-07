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
        XML_ERROR_ADD_CHILD_FAIL,
        XML_ERROR_REMOVE_FAIL,
        XML_ERROR_DOCUMENT_CAN_NOT_BE_CHILD,
        /*error in parsing*/
        XML_PARSING_ERROR_DECLARATION,

        XML_PARSING_ERROR_UNPAIRED_TAG,      //Unpaired tag 未配对的标签
        XML_PARSING_ERROR_WRONG_END_TAG,     //wrong end tag 错误的结束标签
        XML_PARSING_ERROR_UNCLOSED_PARENTHESE,  //Unclosed parenthese 未封闭的括号 <....
        XML_PARSING_ERROR_INVALID_TAG_NAME,      //Invalid tag name 无效的标签名

        XML_PARSING_ERROR_ATTR,
        XML_PARSING_ERROR_DUPLICATE_ATTR_NAME,   //重复的属性名
        XML_PARSING_ERROR_INVALID_ATTR_NAME,      //无效的属性名

        XML_PARSING_ERROR_UNCLOSED_CDATA
    };

    extern const char* ERROR_DESCRIPTION[];
}