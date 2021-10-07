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

        XML_PARSING_ERROR_UNPAIRED_TAG,      //Unpaired tag δ��Եı�ǩ
        XML_PARSING_ERROR_WRONG_END_TAG,     //wrong end tag ����Ľ�����ǩ
        XML_PARSING_ERROR_UNCLOSED_PARENTHESE,  //Unclosed parenthese δ��յ����� <....
        XML_PARSING_ERROR_INVALID_TAG_NAME,      //Invalid tag name ��Ч�ı�ǩ��

        XML_PARSING_ERROR_ATTR,
        XML_PARSING_ERROR_DUPLICATE_ATTR_NAME,   //�ظ���������
        XML_PARSING_ERROR_INVALID_ATTR_NAME,      //��Ч��������

        XML_PARSING_ERROR_UNCLOSED_CDATA
    };

    extern const char* ERROR_DESCRIPTION[];
}