#include <iostream>
#include "StringUtility.hpp"
#include "XMLComment.hpp"
#include "XMLDeclaration.hpp"
#include "XMLDocument.hpp"
#include "XMLElement.hpp"
#include "XMLAttribute.hpp"
#include "XMLText.hpp"
#include "XMLCDATA.hpp"
#include "XMLVisitor.hpp"
#include "XMLPrinter.hpp"

#include <fstream>
#include <iostream>
#include <set>
#include <cstdio>
#include <sstream>
#include <map>
#include <ctime>
#include <cstdlib>
using namespace std;
using namespace QSimpleXMLParser;

class PrintVisitor : public XMLVisitor {
    void controlByDeep() {
        for (int i = 0; i < deep; i++) cout <<( i == deep - 1 ? "|--" : "|  ");
    }
    //show whitespace
    void print(const string& s) {
        for (char c : s) {
            switch (c) {
            case '\n': cout << "\\n"; break;
            case '\t': cout << "\\t"; break;
            case '\r': cout << "\\r"; break;
            default:
                cout << c;
            }
        }
        cout << endl;
    }

    bool visit(XMLText* text) override {
        controlByDeep();
        cout << "TEXT:";
        print(text->getValue());
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
        cout << "CDATA:";
        print(cd->getValue());
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
        /*controlByDeep();
        cout << "ELEMENT:" << ele->getValue() << " END;" << endl;*/
        return true;
    }


    int deep = 0;
};

class RandomGenVisitor : public XMLVisitor {
public:
    RandomGenVisitor() {
        time_t seed = time(nullptr);
        srand(seed);
    }

    XMLNode* createRandom(int i) {
        string pos = to_string(deep) + "_" + to_string(i);

        int type = rand() % 3;
        switch (type) {
        case 0: return new XMLElement("ele" + pos);
        case 1: return new XMLText("text" + pos);
        case 2: return new XMLComment("comment" + pos);
        }
    }
    
    bool visitEntry(XMLDocument* doc) {
        int rand_num = rand() % 10 + 10;
        for (int i = 1; i <= rand_num; i++) {
            doc->addLastChild(createRandom(i));
        }
        
        deep++;
        return true;
    }

    bool visitExit(XMLDocument* doc) {
        deep--;
        return true;
    }

    bool visitEntry(XMLElement* ele) {
        int rand_num = rand() % max(1, 15 - deep);
        for (int i = 1; i <= rand_num; i++) {
            ele->addLastChild(createRandom(i));
        }
        deep++;
        return true;
    }
    
    bool visitExit(XMLElement* ele) {
        deep--;
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
    /*XMLDocument doc;
    RandomGenVisitor rgv;
    PrintVisitor pv;
    ofstream f("text_out.xml");
    XMLPrinter xp(f);
    doc.accept(rgv);
    doc.accept(pv);
    doc.accept(xp);*/

    ifstream f("test.xml", ios_base::binary);
    if (!f.good()) cout << "can't open file."<<endl;
    char xml[1000];
    memset(xml, 0, sizeof(xml));
    xml[999] = 0;
    f.read(xml, 999);
    cout << "read " << strlen(xml) << "bytes" << endl;
    
    XMLDocument doc;
    doc.parse(xml, strlen(xml));
    cout<< "----------------------\n";
    cout<<"error code: "<<doc.getError()<<" in line:"<<doc.getErrorLine()<<endl;
    cout << "error :" << doc.getErrorDetail() << endl;
    cout << "----------------------------------" << endl;
    PrintVisitor p;
    //ofstream of("text_out.xml");
    XMLPrinter xp(cout);
    doc.accept(p);
    doc.accept(xp);
};