
#include "DOM_ElementChildren.h"
#include "DOM_Element.h"
#include "DOM_Text.h"
#include "expset.h"
#include "expmap.h"

#include <vector>
#include <string>
#include <set>
#include <map>
#include <memory> // std::shared_ptr

namespace HTML {
	Element::Element() {}
	Element::~Element() {}
	
	
	
	bool Element::setName(const std::string& name) {
		// TODO: обработка всех разделяющих символов
		// TODO: обработка пустой строки для name
		if (name.size() == 0 || name.find(' ') != std::string::npos) return false;
		_name = name;
		return true;
	}
	
	bool Element::setId(const std::string& id) {
		// TODO: обработка всех разделяющих символов
		if (id.size() == 0 || id.find(' ') != std::string::npos) return false;
		_id = id;
		return true;
	}



	bool Element::isExistClass(const std::string& _class) { return expset::isExistKey(_classes, _class); };

	bool Element::addClass(const std::string& _class) {
		// TODO: обработка сипска классов ("class1 class2 class3")
		if (_class.size() == 0) return false;
		
		// TODO: обработка всех разделяющих символов
		if (_class.find(' ') != std::string::npos) return false;
		
		_classes.insert(_class);
		return true;
	}
	
	bool Element::removeClass(const std::string& _class) {
		size_t old_size = _classes.size();
		size_t new_size = _classes.erase(_class); // remove class and get new size
		return  new_size < old_size;
	}
	
	void Element::removeClasses() { _classes.clear(); }



	bool Element::isExistAttribute(const std::string& attr) {
		
		// copy and to lowercase
		std::string attr_lowcase(attr);
		for (char& ch : attr_lowcase) ch = std::tolower(ch);
		
		if (attr_lowcase == "id") { return !_id.empty(); }
		if (attr_lowcase == "class") { return !_classes.empty(); }
		return expmap::isExistKey(_attributes, attr_lowcase);
	}

	bool Element::addAttribute(const std::string& attr) {
		// TODO: обработка всех разделяющих символов
		if (attr.size() == 0 || attr.find(' ') != std::string::npos) return false;
		
		// copy and to lowercase
		std::string attr_lowcase(attr);
		for (char& ch : attr_lowcase) ch = std::tolower(ch);
		
		if (attr == "id" || attr == "class") return true;
		update(attributes, attr, "");
		return true;
	}
	
	bool Element::setAttributeValue(const std::string& attr, const std::string& value) {
		// TODO: обработка всех разделяющих символов
		if (attr.size() == 0 || attr.find(' ') != std::string::npos) return false;
		
		// copy and to lowercase
		std::string attr_lowcase(attr), value_lowcase(value);
		for (char& ch : attr_lowcase)  ch = std::tolower(ch);
		for (char& ch : value_lowcase) ch = std::tolower(ch);
		
		if (attr == "id") { return setId(value); }
		
		if (attr == "class") {
			removeClasses();
			return addClass(value);
		}
		
		if (expmap::isExistKey(_attributes, attr)) {
			update(_attributes, attr, value);
			return true;
		}
		return false;
	}
	
	bool Element::removeAttribute(const std::string& attr) {
		if (attr.size() == 0 || attr.find(' ') == std::string::npos) return false;
		
		// copy and to lowercase
		std::string attr_lowcase(attr);
		for (char& ch : attr_lowcase) ch = std::tolower(ch);
		
		if (attr == "id") {
			bool f = _id.empty();
			_id = "";
			return !f;
		}
		if (attr == "class") {
			bool f = _classes.empty();
			removeClasses();
			return !f;
		}
		return _attributes.remove(attr);
	}

	const std::string& Element::getAttributeValue(const std::string& attr) {
		// TODO: обработка аргумента со значением "class"
		
		// copy and to lowercase
		std::string attr_lowcase(attr);
		for (char& ch : attr_lowcase) ch = std::tolower(ch);
		
		if (attr_lowcase == "id") return _id;
		//if (attr == "class") { return _attributes.get("class"); }
		return _attributes.find(attr_lowcase).second;
	}



	const std::string& Element::name() { return _name; }
	
	const std::string& Element::id() { return _id; }
	
	const std::set<std::string>& Element::classes() { return _classes; };
	
	std::vector<std::string>& Element::attributes(std::string& buf) {
		buf.resize(_attributes.size());
		size_t i = 0;
		for (auto& el : _attributes)
			result[i++] = el.first;
		return buf;
	}
	
	Text& Element::text() { return _text; }
	
	ElementChildren& Element::children() { return _children; }
	
	

	Element& Element::operator=(const Element& other) {
		_name = other._name;
		_id = other._id;
		_classes = other._classes;
		_attributes = other._attributes;
		_text = other._text;
		_children.copy(other._children);
		return *this;
	}
	
	Element& Element::copy(const Element& other) {
		return *this = other;
	}
};
