#ifndef DOM_ELEMENT_H
#define DOM_ELEMENT_H

// cross use of classes
#include "DOM_ElementChildren.h"
#include "DOM_Text.h"

#include <vector>
#include <string>
#include <set>
#include <map>
#include <memory> // std::shared_ptr

namespace Core {
	using pElement = std::shared_ptr<HTML::Element>;
}

namespace HTML {
	class Element {
	public:
		Element();
		~Element();

		bool setName(const std::string& name);
		bool setId(const std::string& id);

		bool isExistClass(const std::string& _class);
		bool addClass(const std::string& _class);
		bool removeClass(const std::string& _class);
		void removeClasses();
				
		bool isExistAttribute(const std::string& attr);
		bool addAttribute(const std::string& attr);
		bool setAttributeValue(const std::string& attr, const std::string& value);
		bool removeAttribute(const std::string& attr);
		const std::string& getAttributeValue(const std::string& attr);
		
		const std::string& name();
		const std::string& id();
		const std::set<std::string>& classes();
		std::vector<std::string>& attributes(std::vector<std::string>& buf);
		Text& text();
		ElementChildren& children();

		Element& operator = (const Element& other);
		Element& copy(const Element& other);

	private:
		std::string _name;
		std::string _id;
		std::set<std::string> _classes;
		std::map<std::string, std::string> _attributes;

		HTML::Text _text;
		HTML::ElementChildren _children;

		friend class ElementChildren;
	};
};

#endif // DOM_ELEMENT_H
