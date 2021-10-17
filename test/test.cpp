#include <iostream>
#include "src/StringUtility.hpp"
#include "src/XMLComment.hpp"
#include "src/XMLDeclaration.hpp"
#include "src/XMLDocument.hpp"
#include "src/XMLElement.hpp"
#include "src/XMLText.hpp"
#include "src/XMLCDATA.hpp"
#include "src/XMLVisitor.hpp"
#include "src/XMLPrinter.hpp"

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

class ShowDOM : public XMLVisitor {
    void controlByDeep() {
        for (int i = 0; i < deep; i++) cout << (i == deep - 1 ? "|--" : "|  ");
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

    bool visit(XMLText& text) override {
        controlByDeep();
        cout << "TEXT:";
        print(text.getValue());
        return true;
    }
    bool visit(XMLDeclaration& dec) override {
        controlByDeep();
        cout << "DECLARATION:" << dec.getValue() << endl;
        return true;
    }
    bool visit(XMLComment& com) override {
        controlByDeep();
        cout << "COMMENT:" << com.getValue() << endl;
        return true;
    }
    bool visit(XMLCDATA& cd) override {
        controlByDeep();
        cout << "CDATA:";
        print(cd.getValue());
        return true;
    }

    //document
    bool visitEntry(XMLDocument& doc) {
        controlByDeep();
        cout << "DOCUMENT:" << endl;
        deep++;
        return true;
    }
    bool visitExit(XMLDocument& doc) {
        deep--;
        controlByDeep();
        cout << "DOCUMENT END;" << endl;
        return true;
    }

    //element
    bool visitEntry(XMLElement& ele) {
        controlByDeep();
        cout << "ELEMENT:" << ele.getValue() << " ATTRIBUTES( ";
        auto attributes = ele.getAllAttributes();
        for (auto i : attributes) {
            cout << i.first << "=\"" << i.second << "\" ";
        }
        cout << ")" << endl;
        deep++;
        return true;
    }
    bool visitExit(XMLElement& ele) {
        deep--;
        return true;
    }


    int deep = 0;
};

class RandomGen : public XMLVisitor {
public:
    RandomGen() {
        time_t seed = time(nullptr);
        srand(seed);
    }

    void addRandomAttributes(XMLElement* ele) {
        int n = 1 + rand() % 26;
        string name = "A";
        for (int i = 0; i < n; i++) {
            ele->setAttribute(name, rand());
            name[0]++;
        }
    }

    XMLNode* createRandom(int i) {
        string pos = to_string(deep) + "_" + to_string(i);

        int type = rand() % 3;
        switch (type) {
        case 0: {
            XMLElement* ele = new XMLElement("ele" + pos);
            addRandomAttributes(ele);
            return ele;
        }
        case 1: return new XMLText("text" + pos);
        case 2: return new XMLComment("comment" + pos);
        }
    }

    bool visitEntry(XMLDocument& doc) {
        doc.addLastChild(new XMLElement("Root"));

        deep++;
        return true;
    }

    bool visitExit(XMLDocument& doc) {
        deep--;
        return true;
    }

    bool visitEntry(XMLElement& ele) {
        int rand_num = rand() % max(1, 15 - deep);
        for (int i = 1; i <= rand_num; i++) {
            ele.addLastChild(createRandom(i));
        }
        deep++;
        return true;
    }

    bool visitExit(XMLElement& ele) {
        deep--;
        return true;
    }

    int deep = 0;
};

void traverseAll(XMLNode* node, int level = 0) {
    if (node != nullptr) {
        for (int i = 0; i < level; i++) cout << "  ";
        auto ele = dynamic_cast<XMLElement*>(node);
        auto text = dynamic_cast<XMLText*>(node);
        auto comment = dynamic_cast<XMLComment*>(node);
        auto decl = dynamic_cast<XMLDeclaration*>(node);
        auto cdata = dynamic_cast<XMLCDATA*>(node);
        auto doc = dynamic_cast<XMLDocument*>(node);
        if (ele) {
            cout << "Element: " << node->getValue() << '(';
            for (auto& attr : ele->getAllAttributes()) {
                cout << attr.first << "=\"" << attr.second << "\" ";
            }
            cout << ')' << endl;
        }
        else if (!doc) {
            if (cdata) cout << "CDATA: ";
            else if (text) cout << "TEXT: ";
            if (comment) cout << "Comment: ";
            if (decl) cout << "Declaration: ";
            cout << '\"' << node->getValue() << '\"' << endl;
        }


        for (XMLNode* p = node->firstChild(); p != nullptr; p = p->nextSibling()) {
            traverseAll(p, level + 1);
        }
    }
}

int main(){
    // Randomly generate a document.
    cout << "---------Randomly generate a document.-------------" << endl;
    XMLDocument doc0;
    RandomGen rgv;
    ShowDOM show0;
    ofstream fo("test_out.xml");
    XMLPrinter xp(fo);
    doc0.accept(rgv);
    doc0.accept(show0);
    doc0.accept(xp);
    cout << endl;

    cout << "---------Parse a document--------------------------" << endl;
    XMLDocument doc1;
    doc1.loadFile("test.xml");
    ShowDOM show1;
    doc1.accept(show1);
};

