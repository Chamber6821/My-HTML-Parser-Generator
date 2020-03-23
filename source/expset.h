
/*
 * Created by Chamber6821 (github)
 * 
 * Expansion for std::set
 * 
 * Сontents:
 *   
 *   isExistKey (in c++20 exit 'contains')
 *   symmetric difference for list sets (identical allocators and comparators)
 *   
 *   operator +=, operator |=
 *   operator -=
 *   operator &=
 *   opeartor ^=
 *   note: different allocators and comporators can be used
 * 
 *   operator +, operator |
 *   operator -
 *   operator &
 *   opeartor ^
 *   note: identical allocators and comparators
 *  
 */

#ifndef EXPSET_H
#define EXPSET_H

#include <set>

#define SET_KEY          _Key
#define SET_COMP1        _Compare1
#define SET_COMP2        _Compare2
#define SET_ALLOC1       _Allocator1
#define SET_ALLOC2       _Allocator2
#define SET              std::set<SET_KEY, SET_COMP1, SET_ALLOC1>
#define SET1             std::set<SET_KEY, SET_COMP1, SET_ALLOC1>
#define SET2             std::set<SET_KEY, SET_COMP2, SET_ALLOC2>
#define SET_FOR_TEMPLATE class SET_KEY, \
                         class SET_COMP1,             class SET_ALLOC1, \
                         class SET_COMP2 = SET_COMP1, class SET_ALLOC2 = SET_ALLOC1
#define SET_TEMPLATE     template <SET_FOR_TEMPLATE>

#define SET_NAMESPACE expset


namespace SET_NAMESPACE {
	
	// bool isExisKey(const SET& set, const SET_KEY& key);
	//
	// SET& symmetric_difference(iterator<SET> begin, iterator<SET> end, SET& buf)
	// SET  symmetric_difference(iterator<SET> begin, iterator<SET> end)
	//
	// SET& symmetric_difference(std::initializer_list<SET> sets, SET& buf)
	// SET  symmetric_difference(std::initializer_list<SET> sets);
	
	// in c++20 exist 'std::set::containts'
	SET_TEMPLATE
	bool isExistKey(const SET& set, const SET_KEY& key) { return set.find(key) != set.end(); }

	template <SET_FOR_TEMPLATE, class itType>
	SET& symmetric_difference(itType begin, itType end, SET& buf) {
		buf.clear();
		SET excluded_items;
		for (auto it_set = begin; it_set != end; ++it_set) {
			for (auto it = it_set->begin(); it != it_set->end(); ++it) {
				if (SET_NAMESPACE::isExistKey(buf, *it)) {
					buf.erase(*it);
					excluded_items.insert(*it);
				}
				else if (!SET_NAMESPACE::isExistKey(excluded_items, *it)) {
					buf.insert(*it);
				}
			}
		}
		return buf;
	}

	template<SET_FOR_TEMPLATE, class itType>
	SET symmetric_difference(itType begin, itType end) {
		SET buf;
		symmetric_difference(begin, end, buf);
		return buf;
	}

	SET_TEMPLATE
	SET& symmetric_difference(std::initializer_list<SET> sets, SET& buf) {
		symmetric_difference(sets.begin(). sets.end(), buf);
		return buf;
	}

	SET_TEMPLATE
	SET symmetric_difference(std::initializer_list<SET> sets) {
		SET buf;
		symmetric_difference(sets.begin(), sets.end(), buf);
		return buf;
	}

};



// SET1& operator += (SET1& left, const SET2& right); // union
// SET1& operator |= (SET1& left, const SET2& right); // union
// SET1& operator -= (SET1& left, const SET2& right); // exception
// SET1& operator &= (SET1& left, const SET2& right); // intersection
// SET1& operator ^= (SET1& left, const SET2& right); // symmetric difference

// SET operator + (const SET& left, const SET& right); // union
// SET operator | (const SET& left, const SET& right); // union
// SET operator - (const SET& left, const SET& right); // exception
// SET operator & (const SET& left, const SET& right); // intersection
// SET operator ^ (const SET& left, const SET& right); // symmetric difference

SET_TEMPLATE
SET1& operator += (SET1& left, const SET2& right) {
	for (auto it = right.begin(); it != right.end(); ++it)
		left.insert(*it);
	return left;
}

SET_TEMPLATE
SET1& operator |= (SET1& left, const SET2& right) {
	for (auto it = right.begin(); it != right.end(); ++it)
		left.insert(*it);
	return left;
}

SET_TEMPLATE
SET1& operator -= (SET1& left, const SET2& right) {
	for (auto it = right.begin(); it != right.end(); ++it)
		left.erase(*it);
	return left;
}

SET_TEMPLATE
SET1& operator &= (SET1& left, const SET2& right) {
	typename SET::iterator items_to_delete[left.size()];
	size_t size = 0;
	
	for (auto it = left.begin(); it != left.end(); ++it)
		if (!SET_NAMESPACE::isExistKey(right, *it))
			items_to_delete[size++] = it;
	
	for (auto it = items_to_delete; it != items_to_delete + size; ++it)
		left.erase(*it);
	
	return left;
}

SET_TEMPLATE
SET1& operator ^= (SET1& left, const SET2& right) {
	const SET& smallest = (left.size() < right.size() ? left : right);
	const SET& bigger   = (left.size() > right.size() ? left : right);
	
	const SET_KEY* items_to_delete[left.size()];
	size_t size = 0;
	
	for (auto it = smallest.begin(); it != smallest.end(); ++it)
		if (SET_NAMESPACE::isExistKey(bigger, *it))
			items_to_delete[size++] = &*it;
	
	for (auto it = items_to_delete; it != items_to_delete + size; ++it)
		left.erase(**it);
	
	return left;
}


SET_TEMPLATE
SET operator + (const SET& left, const SET& right) {
	SET result_set(left);
	result_set += right;
	return result_set;
}

SET_TEMPLATE
SET operator | (const SET& left, const SET& right) {
	SET result_set(left);
	result_set += right;
	return result_set;
}

SET_TEMPLATE
SET operator - (const SET& left, const SET& right) {
	SET result_set(left);
	result_set -= right;
	return result_set;
}

SET_TEMPLATE
SET operator & (const SET& left, const SET& right) {
	SET result_set;
	
	for (auto it = left.begin(); it != left.end(); ++it)
		if (SET_NAMESPACE::isExistKey(right, *it)) 
			result_set.insert(*it);
			
	for (auto it = right.begin(); it != right.end(); ++it)
		if (SET_NAMESPACE::isExistKey(left, *it))
			result_set.insert(*it);
	
	return result_set;
}

SET_TEMPLATE
SET operator ^ (const SET& left, const SET& right) {
	SET result_set;
	
	for (auto it = left.begin(); it != left.end(); ++it)
		if (!SET_NAMESPACE::isExistKey(right, *it)) 
			result_set.insert(*it);
			
	for (auto it = right.begin(); it != right.end(); ++it)
		if (!SET_NAMESPACE::isExistKey(left, *it))
			result_set.insert(*it);
	
	return result_set;
}

#undef SET_KEY
#undef SET_COMP1
#undef SET_COMP2
#undef SET_ALLOC1
#undef SET_ALLOC2
#undef SET
#undef SET1
#undef SET2
#undef SET_FOR_TEMPLATE
#undef SET_TEMPLATE
#undef SET_NAMESPACE

#endif // EXPSET_H
