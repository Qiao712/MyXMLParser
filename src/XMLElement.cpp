#include "XMLElement.hpp"
#include "StringUtility.hpp"

#include <cctype>
#include <cstring>
namespace QSimpleXMLParser{
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
	bool XMLElement::deleteAttribute(const std::string& name)
	{
		if (_attributes.erase(name) == 0) return false;
		return true;
	}
	XMLElement* XMLElement::clone()
	{
		XMLElement* new_element = new XMLElement;
		new_element->_tag_name = _tag_name;
		new_element->_attributes = _attributes;
		return new_element;
	}
	bool XMLElement::accept(XMLVisitor& visitor)
	{
		if (visitor.visitEntry(*this)) {
			XMLNonterminalNode::visitChildern(visitor);
		}
		return visitor.visitExit(*this);
	}
	const char* XMLElement::parse(const char* beg, const char* end, XMLNonterminalNode* parent, ParseError& parsing_error)
	{
		const char* tag_beg = beg + 1;
		const char* tag_end = StringUtility::findChar('>', beg + 1, end);
		if (tag_end == end) {
			//<tag_name... ....
			parsing_error.setParseError(XML_PARSE_ERROR_UNCLOSED_PARENTHESE, beg);
			return nullptr;
		}

		//if <.../>
		_is_closing = (*(tag_end - 1) == '/');
		
		const char* tag_name_beg = tag_beg;
		const char* tag_name_end = _is_closing ? StringUtility::findChaOrWhitespace('/', tag_name_beg, tag_end) : 
												 StringUtility::findChaOrWhitespace('>', tag_name_beg, tag_end);
		
		if (!checkName(tag_name_beg, tag_name_end)) {
			//error: bad tag name
			parsing_error.setParseError(XML_PARSE_ERROR_INVALID_TAG_NAME, tag_name_beg);
			return nullptr;
		}
		_tag_name.assign(tag_name_beg, tag_name_end);

		//parse attributes
		XMLParseError attr_error = parseAttribute(tag_name_end, _is_closing ? tag_end - 1 : tag_end);
 		if (attr_error != XML_PARSE_SUCCESS) {
			parsing_error.setParseError(attr_error, beg);
		}

		if (_is_closing) return tag_end + 1;

		//parse xml in the element
		const char* p = parseChildren(tag_end + 1, end, this, parsing_error);
		if (p == end && _is_closing == false) {
			//error: wrong end tag
			parsing_error.setParseError(XML_PARSE_ERROR_WRONG_END_TAG, beg);
			return nullptr;
		}

		return p;
	}
	XMLParseError XMLElement::parseAttribute(const char* beg, const char* end)
	{
		const char* p = beg;
		const char* q;
		const char* r;

		while (p < end) {
			//name
			p = StringUtility::skipWhitespace(p, end);
			if (p == end) return XML_PARSE_SUCCESS;
			q = StringUtility::findChar('=', p, end);
			if (q == end) return XML_PARSE_ERROR_ATTR;
			r = StringUtility::skipBackWhitespace(p, q);
			if (!checkName(p, r)) return XML_PARSE_ERROR_ATTR;
			std::string name(p, r);
			p = q;
			
			// "
			p = StringUtility::skipWhitespace(q + 1, end);
			if (p == end || *p != '\"') return XML_PARSE_ERROR_ATTR;
			p++;

			// value
			q = StringUtility::findChar('\"', p, end);
			if (q == end) return XML_PARSE_ERROR_ATTR;
			std::string value = StringUtility::processText(p, q, StringUtility::NORMALIZE_NEWLINE & StringUtility::TRANSLATE_ENTITY);
			p = q + 1;

			if (_attributes.count(name) != 0) return XML_PARSE_ERROR_DUPLICATE_ATTR_NAME;
			_attributes[std::move(name)].assign( std::move(value) );
		}

		return XML_PARSE_SUCCESS;
	}
	const std::string& XMLElement::getAttribute(const std::string& name) const
	{
		static const std::string empty_str;
		auto it = _attributes.find(name);
		if (it == _attributes.end()) return empty_str;
		return it->second;
	}	
	bool XMLElement::getAttribute(const std::string& name, double& value) const
	{
		try { value = std::stod(getAttribute(name)); }
		catch (std::exception& e) { return false; }
		return true;
	}
	bool XMLElement::getAttribute(const std::string& name, long double& value) const
	{
		try { value = std::stold(getAttribute(name)); }
		catch (std::exception& e) { return false; }
		return true;
	}
	bool XMLElement::getAttribute(const std::string& name, float& value) const
	{
		try { value = std::stof(getAttribute(name)); }
		catch (std::exception& e) { return false; }
		return true;
	}
	bool XMLElement::getAttribute(const std::string& name, int& value) const
	{
		try { value = std::stoi(getAttribute(name)); }
		catch (std::exception& e) { return false; }
		return true;
	}
	bool XMLElement::getAttribute(const std::string& name, long& value) const
	{
		try { value = std::stol(getAttribute(name)); }
		catch (std::exception& e) { return false; }
		return true;
	}
	bool XMLElement::getAttribute(const std::string& name, long long& value) const
	{
		try { value = std::stoll(getAttribute(name)); }
		catch (std::exception& e) { return false; }
		return true;
	}
	bool XMLElement::getAttribute(const std::string& name, unsigned int& value) const
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
	bool XMLElement::getAttribute(const std::string& name, unsigned long& value) const
	{
		try { value = std::stoul(getAttribute(name)); }
		catch (std::exception& e) { return false; }
		return true;
	}
	bool XMLElement::getAttribute(const std::string& name, unsigned long long& value) const
	{
		try { value = std::stoull(getAttribute(name)); }
		catch (std::exception& e) { return false; }
		return true;
	}
	bool XMLElement::getAttribute(const std::string& name, bool& value) const
	{
		static const char* TRUES[] = { "true", "TRUE" };
		static const char* FALSES[] = { "false", "FALSE" };

		const std::string& attr_value = getAttribute(name);
		
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