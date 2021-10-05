#include "src\define.h"
#include <cctype>
#include <cstring>
#include <string>
#include <exception>

namespace MyXMLParser{
	using std::string;
	const char* ERROR_DESCRIPTION[] = {
		"Success.",
        "Tag not Found",
        "Attribute not Found",
        "Add child to Terminal node",
        "The operation cannot be applied to terminal node",
        //XML_ERROR_REMOVE_FAIL,
        ///*error in parsing*/
        //XML_PARSING_ERROR_DECLARATION,

        //XML_PARSING_ERROR_UNPAIRED_TAG, //Unpaired tag δ��Եı�ǩ
        //XML_PARSING_ERROR_WRONG_END_TAG,   //wrong end tag ����Ľ�����ǩ
        //XML_PARSING_ERROR_UNCLOSED_PARENTHESE,  //Unclosed parenthese δ��յ����� <....
        //XML_PARSING_ERROR_INVALID_TAG_NAME,      //Invalid tag name ��Ч�ı�ǩ��

        //XML_PARSING_ERROR_ATTR,
        //XML_PARSING_ERROR_DUPLICATE_ATTR_NAME,   //�ظ���������
        //XML_PARSING_ERROR_INVALID_ATTR_NAME      //��Ч��������
	};

}