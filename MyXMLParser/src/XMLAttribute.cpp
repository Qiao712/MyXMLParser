#include "XMLAttribute.hpp"

#include <string>
#include <sstream>
#include <exception>
#include <numeric>

namespace MyXMLParser {
	bool XMLAttribute::getValue(double& value) const
	{
		try {
			value = std::stod(*_value);
		}
		catch (std::exception& e) {
			return false;
		}
		return true;
	}
	bool XMLAttribute::getValue(float& value) const
	{
		try {
			value = std::stof(*_value);
		}
		catch (std::exception& e) {
			return false;
		}
		return true;
	}
	bool XMLAttribute::getValue(long double& value) const
	{
		try {
			value = std::stold(*_value);
		}
		catch (std::exception& e) {
			return false;
		}
		return true;
	}
	bool XMLAttribute::getValue(int& value) const
	{
		try {
			value = std::stoi(*_value);
		}
		catch (std::exception& e) {
			return false;
		}
		return true;
	}
	bool XMLAttribute::getValue(long& value) const
	{
		try {
			value = std::stol(*_value);
		}
		catch (std::exception& e) {
			return false;
		}
		return true;
	}
	bool XMLAttribute::getValue(long long& value) const
	{
		try {
			value = std::stoll(*_value);
		}
		catch (std::exception& e) {
			return false;
		}
		return true;
	}
	bool XMLAttribute::getValue(unsigned int& value) const
	{
		try {
			unsigned long t = std::stoul(*_value);
			//check range
			if (t > std::numeric_limits<unsigned int>::max()) return false;
			value = t;
		}
		catch (std::exception& e) {
			return false;
		}
		return true;
	}
	bool XMLAttribute::getValue(unsigned long& value) const
	{
		try {
			value = std::stoul(*_value);
		}
		catch (std::exception& e) {
			return false;
		}
		return true;
	}
	bool XMLAttribute::getValue(unsigned long long& value) const
	{
		try {
			value = std::stoull(*_value);
		}
		catch (std::exception& e) {
			return false;
		}
		return true;
	}
	bool XMLAttribute::getValue(bool& value) const
	{
		static const char* TRUES[] = { "true", "TRUE" };
		static const char* FALSES[] = { "false", "FALSE" };
		
		int i;
		if (!getValue(i) && (i == 1 || i == 0)) {
			value = i;
			return true;
		}
		
		const string& attr_value = *_value;
		if (attr_value.length() == 4) {
			for (i = 0; i < 4 && (attr_value[i] == TRUES[0][i] || attr_value[i] == TRUES[1][i]); i++);
			if (i == 4) {
				value = true;
				return true;
			}
		}

		if (attr_value.length() == 5) {
			for (i = 0; i < 5 && (attr_value[i] == FALSES[0][i] || attr_value[i] == FALSES[1][i]); i++);
			if (i == 5) {
				value = false;
				return true;
			}
		}

		return false;
	}
	XMLAttribute::~XMLAttribute()
	{
		if (_value != nullptr) {
			delete _name;
			delete _value;
		}
	}
}

