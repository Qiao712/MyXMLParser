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

        //XML_PARSING_ERROR_UNPAIRED_TAG, //Unpaired tag 未配对的标签
        //XML_PARSING_ERROR_WRONG_END_TAG,   //wrong end tag 错误的结束标签
        //XML_PARSING_ERROR_UNCLOSED_PARENTHESE,  //Unclosed parenthese 未封闭的括号 <....
        //XML_PARSING_ERROR_INVALID_TAG_NAME,      //Invalid tag name 无效的标签名

        //XML_PARSING_ERROR_ATTR,
        //XML_PARSING_ERROR_DUPLICATE_ATTR_NAME,   //重复的属性名
        //XML_PARSING_ERROR_INVALID_ATTR_NAME      //无效的属性名
	};

}