#include <iostream>
#include "define.h"
#include "StringProxy.h"
#include "XMLComment.hpp"
#include "XMLDeclaration.hpp"
#include "XMLDocument.hpp"

#include <fstream>
#include <iostream>
using namespace std;
using namespace MyXMLParser;

void travelAll(XMLNode* node) {
    if (node != nullptr) {
        cout << node->getValue() << endl;
        
        for (XMLNode* p = node->firstChild(); p != nullptr; p = p->nextSibling()) {
            travelAll(p);
        }
    }
}

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

    ifstream f("test.xml");
    if (!f.good()) cout << "can't open file."<<endl;
    char xml[1000];
    memset(xml, 0, sizeof(xml));
    f.read(xml, 1000);
    cout << "read " << strlen(xml) << "bytes" << endl;
    cout << xml << endl << "----------------------\n";

    XMLDocument doc;
    doc.parse(xml,strlen(xml));
    travelAll(&doc);
}