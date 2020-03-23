
/*
 * Created by Chamber6821 (github)
 * 
 * Expansion for std::map
 * 
 * Сontents:
 *   
 *   isExistKey (in c++20 exis 'contains')
 *   
 *   update(map, key, value)
 *   update(map, pair)
 *   update(map, begin, end)
 *   update(map, initializer_list<pair>)
 *   update(map, other_map) (different allocators and comporators can be used)
 *  
 */

#ifndef EXPMAP_H
#define EXPMAP_H

#include <map>
#include <utility> // std::pair, std::make_pair

#define MAP_KEY          __Key
#define MAP_VAL          __T
#define MAP_COMP1        _Compare1
#define MAP_COMP2        _Compare2
#define MAP_ALLOC1       _Allocator1
#define MAP_ALLOC2       _Allocator2
#define MAP              std::map<MAP_KEY, MAP_VAL, MAP_COMP1, MAP_ALLOC1>
#define MAP1             std::map<MAP_KEY, MAP_VAL, MAP_COMP1, MAP_ALLOC1>
#define MAP2             std::map<MAP_KEY, MAP_VAL, MAP_COMP2, MAP_ALLOC2>
#define MAP_ITEM         std::pair<MAP_KEY, MAP_VAL>
#define MAP_FOR_TEMPLATE class MAP_KEY, class MAP_VAL, \
                         class MAP_COMP1,             class MAP_ALLOC1, \
                         class MAP_COMP2 = MAP_COMP1, class MAP_ALLOC2 = MAP_ALLOC1
#define MAP_TEMPLATE     template <MAP_FOR_TEMPLATE>

#define MAP_NAMESPACE expmap

namespace MAP_NAMESPACE {
	
	// in c++20 exist 'contains'
	MAP_TEMPLATE
	bool isExistKey(const MAP& map, const MAP_KEY& key) { return map.find(key) != map.end(); }

	MAP_TEMPLATE
	void update(MAP& map, const MAP_KEY& key, const MAP_VAL& value) { map.insert(std::make_pair(key, value)); }
	
	MAP_TEMPLATE
	void update(MAP& map, const MAP_ITEM& item) { map.insert(item); }
	
	template <MAP_FOR_TEMPLATE, class itType>
	void update(MAP& map, itType begin, itType end) {
		for (auto it = begin; it != end; ++it)
			map.insert(*it);
	}
	
	MAP_TEMPLATE
	void update(MAP& map, const std::initializer_list<MAP_ITEM> items) {
		for (auto it = items.begin(); it != items.end(); ++it)
			map.insert(*it);
	}
	
	MAP_TEMPLATE
	void update(MAP1& map, const MAP2& other) {
		for (auto it = other.begin(); it != other.end(); ++it) {
			map.insert({it->first, it->second});
		}
	}
	
};

#undef MAP_KEY
#undef MAP_VAL
#undef MAP_COMP1
#undef MAP_COMP2
#undef MAP_ALLOC1
#undef MAP_ALLOC2
#undef MAP
#undef MAP1
#undef MAP2
#undef MAP_ITEM
#undef MAP_FOR_TEMPLATE
#undef MAP_TEMPLATE
#undef MAP_NAMESPACE

#endif // EXPMAP_H
