#ifndef DOM_TEXT_H
#define DOM_TEXT_H

#include <vector>
#include <string>

namespace HTML {
	
	class Text {
	public:
		Text();
		~Text();

		Text& operator= (const Text& other);

		bool isSeparator(char ch);
		std::string& formatText(const std::string& text, std::string& buf);

		std::vector<std::string> text;
	};

};

#endif // DOM_TEXT_H
