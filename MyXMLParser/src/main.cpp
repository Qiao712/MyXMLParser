#include <iostream>
#include "define.h"
#include "StringUtility.hpp"
#include "XMLComment.hpp"
#include "XMLDeclaration.hpp"
#include "XMLDocument.hpp"
#include "XMLElement.hpp"
#include "XMLAttribute.hpp"
#include "XMLText.hpp"
#include "XMLCDATA.hpp"
#include "XMLVisitor.hpp"

#include <fstream>
#include <iostream>
#include <set>
#include <cstdio>
#include <sstream>
#include <map>
using namespace std;
using namespace MyXMLParser;

class PrintVisitor : public XMLVisitor {
    void controlByDeep() {
        for (int i = 0; i < deep; i++) cout << "   ";
    }
    
    bool visit(XMLText* text) override {
        controlByDeep();
        cout << "TEXT:" << text->getValue() << endl;
        return true;
    }
    bool visit(XMLDeclaration* dec) override {
        controlByDeep();
        cout << "DECLARATION:" << dec->getValue() << endl;
        return true;
    }
    bool visit(XMLComment* com) override {
        controlByDeep();
        cout << "COMMENT:" << com->getValue() << endl;
        return true;
    }
    bool visit(XMLCDATA* cd) override {
        controlByDeep();
        cout << "CDATA:" << cd->getValue() << endl;
        return true;
    }

    //document
    bool visitEntry(XMLDocument* doc) {
        controlByDeep();
        cout << "DOCUMENT:"<<endl;
        deep++;
        return true;
    }
    bool visitExit(XMLDocument* doc) {
        deep--;
        controlByDeep();
        cout << "DOCUMENT END;"<<endl;
        return true;
    }

    //element
    bool visitEntry(XMLElement* ele) {
        controlByDeep();
        cout << "ELEMENT:" << ele->getValue() << " ATTRIBUTES( ";
        auto attributes = ele->getAllAttributes();
        for (auto i : attributes) {
            cout << i.first << "=\"" << i.second << "\" ";
        }
        cout << ")"<<endl;
        deep++;
        return true;
    }
    bool visitExit(XMLElement* ele) {
        deep--;
        controlByDeep();
        cout << "ELEMENT:" << ele->getValue() << " END;" << endl;
        return true;
    }


    int deep = 0;
};

void travelAll(XMLNode* node, int level = 0) {
    if (node != nullptr) {
        for (int i = 0; i < level; i++) cout << "  ";
        auto ele = dynamic_cast<XMLElement*>(node);
        auto text = dynamic_cast<XMLText*>(node);
        auto comment = dynamic_cast<XMLComment*>(node);
        auto decl = dynamic_cast<XMLDeclaration*>(node);
        auto cdata = dynamic_cast<XMLCDATA*>(node);
        auto doc = dynamic_cast<XMLDocument*>(node);
        if (ele) {
            cout<<"Element: "<< node->getValue() << '(';
            for (auto& attr : ele->getAllAttributes()) {
                cout << attr.first << "=\"" << attr.second <<"\" ";
            }
            cout << ')'<<endl;
        }
        else if(!doc){
            if (cdata) cout << "CDATA: ";
            else if (text) cout << "TEXT: ";
            if (comment) cout << "Comment: ";
            if (decl) cout << "Declaration: ";
            cout <<'\"'<< node->getValue() <<'\"'<<endl;
        }
        
        
        for (XMLNode* p = node->firstChild(); p != nullptr; p = p->nextSibling()) {
            travelAll(p, level + 1);
        }
    }
}

int main(){
    //-----------------------------
    //test reference translation
    /*char s[] = "&#x2C66;\n&#x2C67;\n&#x2C68;\r\n\r\n&dfghjklasdasd;&#1114111;";
    StringProxy sp(s, s + sizeof(s) - 1, STR_PROCESSING::NORMALIZE_NEWLINE | STR_PROCESSING::TRANSLATE_ENTITY);
    fstream f("test.txt", ios::out);
    f << sp.getString();*/
    //-----------------------------

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

    ifstream f("test.xml", ios_base::binary);
    if (!f.good()) cout << "can't open file."<<endl;
    char xml[1000];
    memset(xml, 0, sizeof(xml));
    xml[999] = 0;
    f.read(xml, 999);
    cout << "read " << strlen(xml) << "bytes" << endl;
    
    /*for (int i = 0; i < strlen(xml); i++) {
        if (xml[i] == '\r') cout << "\\r";
        else cout << xml[i];
    }*/
    
    //cout << xml << endl << "----------------------\n";

    XMLDocument doc;
    doc.parse(xml, strlen(xml));
    cout<<"error code: "<<doc.getError()<<" in line:"<<doc.getErrorLine()<<endl;
    cout << "error :" << doc.getErrorDetail() << endl;
    travelAll(&doc);
    cout << "--------------------------" << endl;
    XMLNode* e4 = doc.findElementByTagName("e1")->findElementByTagName("e4");
    XMLNode* copy = e4->deepClone();
    travelAll(copy);
    /*e4->unlink();
    cout << "----------------------" << endl;
    travelAll(&doc);
    cout << "-----------------------------------" << endl;
    cout << e4->getParent()<<endl;
    cout << e4->getValue();*/
    cout << "----------------------------------" << endl;
    PrintVisitor p;
    doc.accept(p);
    //travelAll(&doc);
    /*XMLAttribute x("sds", "123.00");
    double d;
    x.getValue(d);
    cout << d<<endl;
    x.setValue(15548);
    cout << x.getValueString();*/
};


//&#x2C66\n ⱦ 在拉丁字母“t”上加一条对角斜线“ / ”
//&#x2C67\n Ⱨ 在拉丁字母“H”下加一条尾巴
//&#x2C68\n ⱨ 在拉丁字母“h”下加一条尾巴
//&#x2C69\n Ⱪ 在拉丁字母“K”下加一条尾巴
//&#x2C6A\n ⱪ 在拉丁字母“k”下加一条尾巴
//&#x2C6B\n Ⱬ 在拉丁字母“Z”下加一条尾巴
//&#x2C6C\n ⱬ 在拉丁字母“z”下加一条尾巴
//&#x2C74\n ⱴ 在拉丁字母“v”的起笔加一个弯勾
//&#x2C75\n Ⱶ 拉丁字母“H”的左半部
//&#x2C76\n ⱶ 拉丁字母“h”的左半部
//&#x2C77\n ⱷ 希腊字母“φ”