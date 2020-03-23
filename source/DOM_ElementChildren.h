#ifndef DOM_ELEMENTCHILDREN_H
#define DOM_ELEMENTCHILDREN_H

// cross use of classes
namespace HTML { class Element; }

#include <vector>
#include <memory> // std::shared_ptr

namespace Core {
	using pElement = std::shared_ptr<HTML::Element>;
}

namespace HTML {
	class ElementChildren {
	public:
		using iterator       = std::vector<Core::pElement>::iterator;
		using const_iterator = std::vector<Core::pElement>::const_iterator;
		
		ElementChildren();
		~ElementChildren();

		Core::pElement& add();
		Core::pElement& add(size_t index);
		Core::pElement& add(Core::pElement& other);
		Core::pElement& add(Core::pElement& other, size_t index);
		bool remove(size_t index);
		
		Core::pElement get(size_t index);
		
		Core::pElement front();
		Core::pElement back();

		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;

		ElementChildren& copyLinks(const ElementChildren& other);
		ElementChildren& copy(const ElementChildren& other);

		size_t size();
		bool empty();

	private:
		std::shared_ptr<std::vector<Core::pElement>> elements;

		friend class Element;
	};
};

#endif // DOM_ELEMENTCHILDREN_H
