#include "DOM_Element.h"

#include <string>
#include <iostream>

#include <sstream>
#include <streambuf>
#include <fstream>
#include <stack>
#include <memory> // std::shared_ptr

// устарели и требуют велосипеда
//#include <strstream> // istrtsream (strstreambuf)

using namespace std;

void print(HTML::Element& element, int shift = 0);

string& getline(string& s, istream& in, const string& terminators = " \n\r\t", int length_step = 512) {
	s.resize(length_step);
	size_t real_size = 0;
	while (in.peek() != istream::traits_type::eof() && terminators.find(in.peek()) == std::string::npos) {
		if (real_size >= s.size()) s.resize(real_size + length_step);
		s[real_size++] = in.get();
	}
	s.resize(real_size);
	return s;
}

streamsize ignoreTo(std::istream& stream, std::string terminators = " \n\r\t") {
	streamsize length = 0;
	while (stream.peek() != istream::traits_type::eof() && terminators.find(stream.get()) == std::string::npos) length++;
	stream.unget();
	return length - 1;
}

streamsize ignoreWhile(std::istream& stream, std::string terminators = " \n\r\t") {
	streamsize length = 0;
	while (stream.peek() != istream::traits_type::eof() && terminators.find(stream.get()) != std::string::npos) length++;
	stream.unget();
	return length - 1;
}

bool isClosingTag(const string& tag) {
	if (tag.size() <= 3) return false;
	return tag[1] == '/';
}

string& getTagName(string& container_tag_name, const string& tag) {
	if (tag.empty()) return container_tag_name = "";
	istringstream in(tag.c_str()); in.get();
	if (isClosingTag(tag)) in.get();
	getline(container_tag_name, in, " \n\t\r>/");
	return container_tag_name;
}

bool isSingleTag(const string& tag_name) {
	static const char* tags[] = { "meta", "img", "svg", "br", "link" };
	for (size_t i = 0; i < sizeof(tags) / sizeof(char*); i++)
		if (tags[i] == tag_name) return true;
	return false;
}

string& getTag(string& tag, istream& in) {
	tag.resize(1024);
	size_t real_size = 0;
	ignoreTo(in, "<");
	char bracket_type = 0;
	while (in.peek() != istream::traits_type::eof() && (in.peek() != '>' || bracket_type != 0)) {
		char newch = in.get();
		if (bracket_type == ' ' && (newch == '"' || newch == '\''))
			bracket_type = newch;
		else if (newch == bracket_type) bracket_type = 0;
		if (real_size >= tag.size()) tag.resize(real_size * 15 / 10);
		tag[real_size++] = newch;
	}
	if (tag.empty()) { tag.resize(0); return tag; }
	tag.resize(real_size + 1);
	tag.back() = '>';
	in.get();
	return tag;
}

bool isSeparator(char ch) {
	static const string space_chars = " \n\t\r";
	return space_chars.find(ch) != string::npos;
}

string& formatText(string& out, const string& text) {
	out.resize(text.size());
	int real_size = 0;
	bool need_separator = false;
	for (size_t i = 0; i < text.size(); i++) {
		if (isSeparator(text[i])) {
			if (need_separator) {
				out[real_size++] = ' ';
				need_separator = false;
			}
		}
		else { out[real_size++] = text[i]; need_separator = true; }
	}
	out.resize(real_size);
	return out;
}

string& getTextContent(string& text, istream& in) {
	getline(text, in, "<");
	return text;
}

bool nextIsTag(istream& in) {
	ignoreWhile(in);
	return in.peek() == '<';
}

Core::pElement tagToElement(const string& tag) {
	std::istringstream in(tag);
	HTML::Element* element = new HTML::Element;;
	//bool isOneline = false;
	string name, attr, value;
	ignoreTo(in, "<");
	if (in.peek() == '<') {
		in.get();
		getline(name, in, " \n\r\t<>");
		element->setName(name);
		ignoreWhile(in);
		while (in.peek() != '>') {
			ignoreWhile(in);
			getline(attr, in, " \n\r\t>/");
			element->addAttribute(attr);
			ignoreWhile(in);
			if (in.peek() == '=') {
				in.get();
				ignoreWhile(in);
				if (in.peek() == '\"') {
					in.get();
					getline(value, in, "\"");
					in.get();
				}
				else if (in.peek() == '\'') {
					in.get();
					getline(value, in, "\'");
					in.get();
				}
				element->setAttributeValue(attr, value);
			}
		}
	}
	return Core::pElement(element);
}

int main()
{	
	cout << "Start Programm.\n\n";

	cout << "Open: code.html";
	ifstream file("code.html");
	if (file.is_open()) cout << " - OK\n";
	else cout << " - Error\n";
	
	stack<Core::pElement> _stack;

	Core::pElement main_element(new HTML::Element);
	Core::pElement cur_element(main_element);
	_stack.push(main_element);

	main_element->setName("document");

	cout << "Start while\n\n";

	//bool lastIsSingleTag = false;
	string new_tag, text, tag_name;
	Core::pElement new_element;
	while (file.peek() != istream::traits_type::eof()) {
		if (nextIsTag(file)) {
			getTag(new_tag, file);
			getTagName(tag_name, new_tag);
			if (isClosingTag(new_tag)) {
				// close tag
			}
			else {
				if (isSingleTag(tag_name)) {

				}
			}
		}
		else {
			getTextContent(text, file);
			formatText(text, text);
			//cur_element->text()->add(text);
		}
	}
	main_element = main_element->children().back();
	cout << endl;
	file.close();
	print(*main_element);
	cout << "Program end.\n";
}

void print(HTML::Element& element, int shift) {
	cout << string(shift * 2, ' ') << '<';
	cout << element.name();
	if (!element.id().empty()) cout << " id=\"" << element.id() << '\"';
	if (!element.classes().empty()) {
		cout << " class=\"";
		for (auto _class : element.classes()) cout << _class << ' ';
		cout << "\b\"";
	}
	if (!element.attributes().empty()) {
		for (auto& el : element.attributes()) {
			cout << ' ' << el.key;
			if (!el.value.empty()) cout << "=\"" << el.value << '"';
		}
	}
	cout << ">";

	for (auto child : element.children()) {
		cout << endl;
		print(*child, shift + 1);
	}

	//if (!element.text.empty()) {
		//cout << endl << string((shift + 1) * 2, ' ') << element.text;
	//}

	if (!isSingleTag(element.name())) {
		cout << "</" << element.name() << ">";
	}
	if (shift == 0) cout << endl;
}

