#include "StringProxy.h"
#include "define.h"

#include <cstring>

#include <map>
#include <cstdint>

namespace MyXMLParser{
    void StringProxy::setString(const char* beg, const char* end, int processing_flag)
    {
        _processing_flag = processing_flag;
        _str.reserve(end - beg);
        processAndStore(beg, end);
    }

    size_t StringProxy::countChar(char x)
    {
        size_t n = 0;
        for (char c : _str) n += (x == c);
        return n;
    }

    bool StringProxy::isAllWhitespace()
    { 
        if (_str.empty()) return true;
        size_t holder;
        const char* p = skipWhitespace(&_str.front(), &_str.back() + 1, holder);
        return p == &_str.back() + 1;
    }

    void StringProxy::processAndStore(const char* beg, const char* end)
    {        
        bool entity_translation = _processing_flag & STR_PROCESSING::TRANSLATE_ENTITY;
        bool newline_normalization = _processing_flag & STR_PROCESSING::NORMALIZE_NEWLINE;
        const char* p = beg;
        while(p < end) {
            if (entity_translation && *p == '&') {
                static string substitute(6,'\0');
                //longest : "&#1114111" 1114111 is the max code in Unicode
                const char* q;
                for (q = p; q < end && q - p <= 9 && *q != ';'; q++);
                
                if (*q == ';' && parseReference(p + 1, q, substitute)) {
                    _str.append(substitute);
                    p = q + 1;
                }
                else {
                    _str.push_back(*p);
                    p++;
                }
            }
            else if (newline_normalization) {
                if (*p == '\n') {
                    if (p + 1 != end && p[1] == '\r') p += 2;
                    else p++;
                    _str.push_back('\n');
                }
                else if (*p == '\r') {
                    if (p + 1 != end && p[1] == '\n') p += 2;
                    else p++;
                    _str.push_back('\n');
                }
                else {
                    _str.push_back(*p);
                    p++;
                }
            }
            else {
                _str.push_back(*p);
                p++;
            }
        }

    }

    bool StringProxy::parseReference(const char* beg, const char* end, string& substitute) 
    {
        struct Entity {
            const char* entity;
            int length;
            char chr;
        };
        static const Entity ENTITIES[] = {
            Entity{"lt", 2, '<'},
            Entity{"gt", 2, '>'},
            Entity{"amp", 3, '&'},
            Entity{"apos", 4, '\''},
            Entity{"quot", 4, '\"'}
        };

        if (beg >= end) return false;

        if (beg[0] == '#') {
            //char reference, convert to utf-8
            uint32_t unicode;
            if (beg + 1 < end && beg[1] == 'x') unicode = strToIntHex(beg + 2, end);
            else unicode = strToIntDec(beg, end);
            
            return unicodeToUtf8(unicode, substitute);
        }
        else {
            //entity reference
            int length = end - beg;
            for (int i = 0; i < sizeof(ENTITIES) / sizeof(Entity); i++) {
                if (ENTITIES[i].length != length) continue;
                const char* j,* k;
                for (j = beg, k = ENTITIES[i].entity; j < end; j++, k++) {
                    if (*j != *k) break;
                }
                if (j == end) {
                    substitute.clear();
                    substitute.push_back(ENTITIES[i].chr);
                    return true;
                }
            }

            return false;
        }
    }

    string StringProxy::translateCharToEntity(const string& str){
        static const string char_to_entity[5] = {"&lt;", "&gt;", "&amp;", "&apos;", "&quot;"};

        string new_str;
        new_str.reserve(str.size() * 2);

        for(char c : str){
            switch(c){
                case '<': new_str.append(char_to_entity[0]); break;
                case '>': new_str.append(char_to_entity[1]); break;
                case '&': new_str.append(char_to_entity[2]); break;
                case '\'': new_str.append(char_to_entity[3]); break;
                case '\"': new_str.append(char_to_entity[4]); break;
                default: new_str.push_back(c);
            }
        }

        return new_str;
    }
}