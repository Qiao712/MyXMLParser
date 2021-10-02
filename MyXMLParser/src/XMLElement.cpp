#include "XMLElement.hpp"
#include "XMLAttribute.hpp"
#include "StringUtility.hpp"

#include <cctype>
#include <cstring>
namespace MyXMLParser{
	bool XMLElement::checkName(const char* beg, const char* end)
	{
		if (beg >= end) return false;

		if (isdigit(*beg)) return false;

		for (const char* p = beg; p != end; p++) {
			if (isalpha(*p) || isdigit(*p) || *p == '.' || *p == '_' || *p == '-' || *p == ':' || *p >= 128) continue;
			else return false;
		}
		return true;
	}
	XMLError XMLElement::deleteAttribute(const string& name)
	{
		if (_attributes.erase(name) == 0) return XML_ERROR_ATTRIBUTE_NOT_FOUND;
		return XML_SUCCESS;
	}
	const char* XMLElement::parse(const char* beg, const char* end, XMLNonterminalNode* parent, size_t& line_num)
	{
		const char* tag_beg = beg + 1;
		const char* tag_end = StringUtility::findChar('>', beg + 1, end);
		if (tag_end == end) {
			//<tag_name... ....
			setParsingError(XML_PARSING_ERROR_UNCLOSED_PARENTHESE, line_num);
			return nullptr;
		}

		//if <.../>
		_is_closing = (*(tag_end - 1) == '/');
		
		const char* tag_name_beg = tag_beg;
		const char* tag_name_end = StringUtility::findWhitespace(tag_beg, tag_end);
		
		if (!checkName(tag_name_beg, tag_name_end)) {
			//error: bad tag name
			setParsingError(XML_PARSING_ERROR_INVALID_TAG_NAME, line_num);
			return nullptr;
		}
		_tag_name.assign(tag_name_beg, tag_name_end);

		XMLError attr_error = parseAttribute(tag_name_end, _is_closing ? tag_end - 1 : tag_end, line_num);
		if (attr_error != XML_SUCCESS) {
			setParsingError(attr_error, line_num);
		}

		if (_is_closing) return tag_end + 1;

		//parse xml in the element
		const char* p = parseChildren(tag_end + 1, end, this, line_num);
		if (p == end && _is_closing == false) {
			//error: wrong end tag
			setParsingError(XML_PARSING_ERROR_WRONG_END_TAG, line_num);
			return nullptr;
		}

		return p;
	}
	XMLError XMLElement::parseAttribute(const char* beg, const char* end, size_t& line_num)
	{
		const char* p = beg;
		const char* q;
		const char* r;

		while (p < end) {
			//name
			p = StringUtility::skipWhitespace(p, end, line_num);
			if (p == end) return XML_SUCCESS;
			q = StringUtility::findChar('=', p, end, line_num);
			if (q == end) return XML_PARSING_ERROR_ATTR;
			r = StringUtility::skipBackWhitespace(p, q, line_num);
			if (!checkName(p, r)) return XML_PARSING_ERROR_ATTR;
			string name(p, r);
			p = q;
			
			// "
			p = StringUtility::skipWhitespace(q + 1, end, line_num);
			if (p == end || *p != '\"') return XML_PARSING_ERROR_ATTR;
			p++;

			// value
			q = StringUtility::findChar('\"', p, end);
			if (q == end) return XML_PARSING_ERROR_ATTR;
			string value = StringUtility::processText(p, q, StringUtility::NORMALIZE_NEWLINE & StringUtility::TRANSLATE_ENTITY);
			p = q + 1;

			if (_attributes.count(name) != 0) return XML_PARSING_ERROR_DUPLICATE_ATTR_NAME;
			_attributes[std::move(name)].assign( std::move(value) );
		}

		return XML_SUCCESS;
	}
	const string& XMLElement::getAttribute(const string& name) const
	{
		static const string empty_str;
		auto it = _attributes.find(name);
		if (it == _attributes.end()) return empty_str;
		return it->second;
	}	
	bool XMLElement::getAttribute(const string& name, double& value) const
	{
		try { value = std::stod(getAttribute(name)); }
		catch (std::exception& e) { return false; }
		return true;
	}
	bool XMLElement::getAttribute(const string& name, long double& value) const
	{
		try { value = std::stold(getAttribute(name)); }
		catch (std::exception& e) { return false; }
		return true;
	}
	bool XMLElement::getAttribute(const string& name, float& value) const
	{
		try { value = std::stof(getAttribute(name)); }
		catch (std::exception& e) { return false; }
		return true;
	}
	bool XMLElement::getAttribute(const string& name, int& value) const
	{
		try { value = std::stoi(getAttribute(name)); }
		catch (std::exception& e) { return false; }
		return true;
	}
	bool XMLElement::getAttribute(const string& name, long& value) const
	{
		try { value = std::stol(getAttribute(name)); }
		catch (std::exception& e) { return false; }
		return true;
	}
	bool XMLElement::getAttribute(const string& name, long long& value) const
	{
		try { value = std::stoll(getAttribute(name)); }
		catch (std::exception& e) { return false; }
		return true;
	}
	bool XMLElement::getAttribute(const string& name, unsigned int& value) const
	{
		try {
			unsigned long t = std::stoul(getAttribute(name));
			//check range
			if (t > std::numeric_limits<unsigned int>::max()) return false;
			value = t;
		}
		catch (std::exception& e) {
			return false;
		}
		return true;
	}
	bool XMLElement::getAttribute(const string& name, unsigned long& value) const
	{
		try { value = std::stoul(getAttribute(name)); }
		catch (std::exception& e) { return false; }
		return true;
	}
	bool XMLElement::getAttribute(const string& name, unsigned long long& value) const
	{
		try { value = std::stoull(getAttribute(name)); }
		catch (std::exception& e) { return false; }
		return true;
	}
	bool XMLElement::getAttribute(const string& name, bool& value) const
	{
		static const char* TRUES[] = { "true", "TRUE" };
		static const char* FALSES[] = { "false", "FALSE" };

		const string& attr_value = getAttribute(name);
		
		int i;
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
}