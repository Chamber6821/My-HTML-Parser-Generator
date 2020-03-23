#include "DOM_Text.h"

namespace HTML {

	Text::Text() {}
	Text::~Text() {}

	Text& Text::operator= (const Text& other) {
		text = other.text;
		return *this;
	}

	bool Text::isSeparator(char ch) {
		static const std::string space_chars = " \n\t\r";
		return space_chars.find(ch) != std::string::npos;
	}

	std::string& Text::formatText(const std::string& text, std::string& buf) {
		int real_size = 0;
		buf.resize(text.size());
		bool need_separator = false;
		for (size_t i = 0; i < text.size(); i++) {
			if (isSeparator(text[i])) {
				if (need_separator) {
					buf[real_size++] = ' ';
					need_separator = false;
				}
			}
			else { buf[real_size++] = text[i]; need_separator = true; }
		}
		buf.resize(real_size);
		return buf;
	}
};
