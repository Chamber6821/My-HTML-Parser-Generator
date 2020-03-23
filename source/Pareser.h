#ifndef PARSER_H
#define PARSER_H

#include "ParserConfig.h"
#include "DOM_Element.h"

#include <istream>
#include <string>

namespace Core {
	class Parser {
	public:
		enum class ErrorParsing { NoError, InvalidSyntaxHTML, InvalidSyntaxDocument, NotFoundHTMLCode };

		Parser();
		~Parser();
		
		//ErrorParsing parseDocument(std::string& htmlCode, HTML::Document& document, const ParserConfig& config = ParserConfig::defoult());
		ErrorParsing parseElement(std::istream& htmlCode, HTML::Element& container, const ParserConfig& config = ParserConfig::defoult());
	private:
		HTML::Element stringToElement(const std::string& text);
		std::string* getTagOrText(std::istream& htmlCode);
	};
};

#endif // PARSER_H
