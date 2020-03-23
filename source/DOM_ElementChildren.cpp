
#include "DOM_Element.h"
#include "DOM_ElementChildren.h"

#include <memory> // std::shared_ptr
#include <stdexcept>

namespace HTML {

	ElementChildren::ElementChildren() : elements(std::make_shared<std::vector<Core::pElement>>()) {}
	ElementChildren::~ElementChildren() {}
	
	Core::pElement& ElementChildren::add() {
		elements->push_back(Core::pElement(new Element));
		return elements->back();
	}
	
	Core::pElement& ElementChildren::add(size_t index) {
		if (index > size()) throw std::out_of_range("index more than number children");
		elements->insert(elements->begin() + index, Core::pElement(new Element));
		return elements->at(index);
	}
	
	Core::pElement& ElementChildren::add(Core::pElement& other) {
		elements->push_back(other);
		return elements->back();
	}
	
	Core::pElement& ElementChildren::add(Core::pElement& other, size_t index) {
		if (index > size()) throw std::out_of_range("index more than number children");
		elements->insert(elements->begin() + index, other);
		return elements->at(index);
	}
	
	bool ElementChildren::remove(size_t index) {
		if (index >= size()) return false;
		elements->erase(elements->begin() + index);
		return true;
	}
	
	Core::pElement ElementChildren::get(size_t index) {
		if (index >= size()) return nullptr;
		return elements->at(index);
	}
	
	Core::pElement ElementChildren::front() { return elements->front(); }
	Core::pElement ElementChildren::back() { return elements->back(); }

	ElementChildren::iterator ElementChildren::begin() { return elements->begin(); }
	ElementChildren::iterator ElementChildren::end() { return elements->end(); }
	ElementChildren::const_iterator ElementChildren::begin() const { return elements->begin(); }
	ElementChildren::const_iterator ElementChildren::end() const { return elements->end();; }

	ElementChildren& ElementChildren::copyLinks(const ElementChildren& other) {
		elements = other.elements;
		return *this;
	}
	ElementChildren& ElementChildren::copy(const ElementChildren& other) {
		int _size = other.elements->size();
		elements->resize(_size);
		for (int i = 0; i < _size; i++) {
			elements->at(i) = Core::pElement(new Element);
			elements->at(i)->copy(*other.elements->at(i));
		}
		return *this;
	}

	size_t ElementChildren::size() { return elements->size(); }
	bool ElementChildren::empty() { return elements->empty(); }

};
