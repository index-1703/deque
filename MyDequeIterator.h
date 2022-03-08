#pragma once
#include "MyDeque.h"

template <typename value_type, typename Alloc>
class MyDeque;

template <class value_type, class Alloc = std::allocator<value_type>>
class MyDequeIterator {
private:
	
	using node_iterator = typename MyDeque<value_type, Alloc>::node_t;
	node_iterator*node;

public:
	MyDequeIterator(node_iterator* node) :node(node) {};
	MyDequeIterator(const MyDequeIterator& x) :node(x.node) {};
	~MyDequeIterator() = default;

	MyDequeIterator& operator++();
	MyDequeIterator operator++(int);

	MyDequeIterator& operator--();
	MyDequeIterator operator--(int);

	bool operator==(const MyDequeIterator& rhs) const;
	bool operator!=(const MyDequeIterator& rhs) const;

	value_type& operator*(void);

};

#include "MyDequeIterator.inl"
;