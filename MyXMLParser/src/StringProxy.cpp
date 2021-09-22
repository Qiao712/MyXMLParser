#include "StringProxy.h"

#include <cstring>
#include <map>

namespace MyXMLParser{
    StringProxy::StringProxy(char* p, unsigned int len) {
        _str = translateEntityToChar(p, len);
    }

    bool StringProxy::isAllWhitespace()
    {
        return false;
    }

    string StringProxy::translateEntityToChar(const char* p, unsigned int len)
    {
        using EntityCharPair = std::pair<string, char>;
        static const std::map<string, char> entity_to_char{
            EntityCharPair("&lt", '<'),
            EntityCharPair("&gt", '>'),
            EntityCharPair("&amp", '&'),
            EntityCharPair("&apos", '\''),
            EntityCharPair("&quot", '\"'),
        };
        static auto not_found = entity_to_char.cend();

        string new_str, entity;
        new_str.reserve(len);
        entity.reserve(7);

        bool checking_entity = false;
        char c;
        for (size_t i = 0; i < len; i++) {
            c = p[i];
            if (checking_entity) {
                if (c == '&') {
                    new_str.append(entity);
                    entity.clear();
                    entity.push_back('&');
                }
                else if (c == ';') {
                    auto it = entity_to_char.find(entity);
                    if (it == not_found) {
                        new_str.append(entity);
                        new_str.push_back(';');
                    }
                    else {
                        new_str.push_back(it->second);
                    }
                    entity.clear();
                    checking_entity = false;
                }
                else if (entity.size() > 5) {
                    new_str.append(entity);
                    new_str.push_back(c);
                    entity.clear();
                    checking_entity = false;
                }
                else {
                    entity.push_back(c);
                }
            }
            else {
                if (c == '&') {
                    checking_entity = true;
                    entity.push_back('&');
                }
                else {
                    new_str.push_back(c);
                }
            }
        }

        return new_str;
    }

    string StringProxy::translateEntityToChar(const string& str){
        return translateEntityToChar(&str.front(), str.size());
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