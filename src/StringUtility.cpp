#include "StringUtility.hpp"

#include <cstring>
#include <cctype>

using std::string;

namespace QSimpleXMLParser {
	string StringUtility::processText(const char* beg, const char* end, unsigned int process)
	{
		string result;
		result.reserve(end - beg);

		bool entity_translation = process & TEXT_PROCESS::TRANSLATE_ENTITY;
		bool newline_normalization = process & TEXT_PROCESS::NORMALIZE_NEWLINE;
		
		const char* p = beg;
		while (p < end) {
			if (entity_translation && *p == '&') {
				static string substitute(6, '\0');
				//longest : "&#1114111" 1114111 is the max code in Unicode
				const char* q;
				for (q = p; q < end && q - p <= 9 && *q != ';'; q++);

				if (*q == ';' && parseReference(p + 1, q, substitute)) {
					result.append(substitute);
					p = q + 1;
				}
				else {
					result.push_back(*p);
					p++;
				}
			}
			else if (newline_normalization) {
				if (*p == '\n') {
					if (p + 1 != end && p[1] == '\r') p += 2;
					else p++;
					result.push_back('\n');
				}
				else if (*p == '\r') {
					if (p + 1 != end && p[1] == '\n') p += 2;
					else p++;
					result.push_back('\n');
				}
				else {
					result.push_back(*p);
					p++;
				}
			}
			else {
				result.push_back(*p);
				p++;
			}
		}

		return result;
	}

	string StringUtility::translateCharToEntity(const string& str)
	{
		static const string char_to_entity[5] = { "&lt;", "&gt;", "&amp;", "&apos;", "&quot;" };

		string new_str;
		new_str.reserve(str.size() * 2);

		for (char c : str) {
			switch (c) {
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

	bool StringUtility::parseReference(const char* beg, const char* end, string& substitute)
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
				const char* j, * k;
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

}
