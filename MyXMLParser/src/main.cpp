#include <iostream>
#include "define.h"
#include "StringProxy.h"
#include "XMLComment.hpp"
#include "XMLDeclaration.hpp"
#include "XMLDocument.hpp"
using namespace std;
using namespace MyXMLParser;

int main(){
    char sub[] = "123";
    char s[] = "asdfsadf123sddfgfdggafg";
    cout << findSubstr(s + 3, s + 16, sub)<<endl;

    //---------------------------------------------------
    /*char comment_test[] = "<!--I'm a\n comment-->";
    XMLComment cmt;
    int line_num = 1;
    cmt.parse(comment_test, comment_test + sizeof(comment_test), line_num);
    cout << cmt.getValue()<<endl;*/
    //---------------------------------------------------

    /*char declaration_test[] = "<?xml sssscasfadf?>";
    XMLDeclaration dcl;
    size_t line_num = 1;
    dcl.parse(declaration_test, declaration_test + sizeof(declaration_test), line_num);
    cout << dcl.getValue() << endl;*/

    char xml[] = "<?xml sssss?>\n<!--commmmmmmment--->";
    XMLDocument doc;
    doc.parse(xml,sizeof(xml)-1);
    cout<<doc.firstChild()->getValue()<<endl;
    cout << doc.firstChild()->nextSibling()->getValue() << endl;
    cout << doc.firstChild()->nextSibling()->nextSibling()->getValue() << endl;
}