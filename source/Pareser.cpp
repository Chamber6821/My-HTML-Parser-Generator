
#include "Pareser.h"
#include "ParserConfig.h"
#include "DOM_Element.h"

#include <istream>
#include <string>
#include <vector>

namespace Core {

	Parser::Parser() {}
	Parser::~Parser() {}

	Parser::ErrorParsing Parser::parseElement(std::istream& htmlCode, HTML::Element& container, const ParserConfig& config) {
		htmlCode.ignore(htmlCode.rdbuf()->in_avail(), '<');
		if (htmlCode.rdbuf()->in_avail() <= 1) { return ErrorParsing::NotFoundHTMLCode; }
		htmlCode.unget();
		std::string* openTag = getTagOrText(htmlCode);
		std::vector<std::string*> children;

		openTag->back() == '>' && *(openTag->end() - 2) == '/';

		if (!(openTag->back() == '>' && *(openTag->end() - 2) == '/')) {
			int nesting = 1;
			while (nesting > 0) {
				break;
			}
		}
		return ErrorParsing::NoError;
	}

	std::string* Parser::getTagOrText(std::istream& htmlCode) {
		std::string* result = new std::string();
		static const std::string terminators = "<>";

		htmlCode.ignore(htmlCode.rdbuf()->in_avail(), '<');
		std::streamsize size = htmlCode.rdbuf()->in_avail();
		if (size <= 1) { delete result; return nullptr; }
		htmlCode.unget();

		result->push_back(htmlCode.get());
		do {
			result->push_back(htmlCode.get());
			if (--size <= 0) break;
			if (result->back() == '/' && htmlCode.peek() == '>') {
				result->push_back(htmlCode.get());
				break;
			}
		} while (terminators.find(result->back()) == std::string::npos);
		if (!result->empty() && result->back() == '<') {
			htmlCode.unget();
			result->pop_back();
		}
		
		return result;
	}
};
