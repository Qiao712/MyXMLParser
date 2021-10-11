#pragma once
#include <string>
#include <sstream>
namespace MyXMLParser{
using std::string;
class XMLAttribute{
    friend class XMLElement;
public:
    const string& getValueString() const { return *_value; }
    bool getValue(string& value) const { value = *_value; }
    bool getValue(double& value) const;
    bool getValue(float& value) const;
    bool getValue(long double& value) const;
    bool getValue(int& value) const;
    bool getValue(long& value) const;
    bool getValue(long long& value) const;
    bool getValue(unsigned int& value) const;
    bool getValue(unsigned long& value) const;
    bool getValue(unsigned long long& value) const;
    bool getValue(bool& value) const;

    void setValue(const string& value) const { _value->assign(value); }
    void setValue(string&& value) const { _value->assign(value); }
    void setValue(double value) const { _value->assign(std::to_string(value)); }
    void setValue(float value) const { _value->assign(std::to_string(value)); }
    void setValue(long double& value) const { _value->assign(std::to_string(value)); }
    void setValue(int value) const { _value->assign(std::to_string(value)); }
    void setValue(long value) const { _value->assign(std::to_string(value)); }
    void setValue(long long value) const { _value->assign(std::to_string(value)); }
    void setValue(unsigned int value) const { _value->assign(std::to_string(value)); }
    void setValue(unsigned long value) const { _value->assign(std::to_string(value)); }
    void setValue(unsigned long long value) const { _value->assign(std::to_string(value)); }
    void setValue(bool value) const { value ? _value->assign("true") : _value->assign("false"); }
    

    bool operator<(const XMLAttribute& rhs) const { return *_name < *(rhs._name); }
    ~XMLAttribute();
private:
    //use to search in set
    XMLAttribute(string* name) : _name(name), _value(nullptr){ }

    XMLAttribute(const string& name, const string& value) : _name(new string(name)), _value(new string(value)){ }
    XMLAttribute(string&& name, string&& value) : _name(new string(name)), _value(new string(value)){ }

    string* _name;
    string* _value;
};
}