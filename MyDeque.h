#pragma once
#include <memory>
#include "MyDequeIterator.h"

template <class value_type, class Alloc = std::allocator<value_type>>
class MyDeque {
public:
	struct node_t
	{
		value_type data;
		node_t* prev;
		node_t* next;
	};

private:
	Alloc alloc;
	node_t* first;
	node_t* last;
	size_t count_nodes;

public:
	using iterator = MyDequeIterator<value_type, Alloc>;

	MyDeque(void);
	MyDeque(size_t n, const value_type& val);
	MyDeque(iterator first, iterator last);
	MyDeque(const MyDeque& x);
	MyDeque(MyDeque&& x);

	~MyDeque(void);

	MyDeque& operator= (const MyDeque& x);
	MyDeque& operator= (MyDeque&& x);

private:
	node_t* _create_node(void) {
		node_t* node = (node_t*)alloc.allocate(1);
		return node;
	};
	void _delete_node(node_t* node) {
		alloc.destroy(node);
	};

public:
	/******************
	*	Iterators
	******************/
	iterator begin(void);
	iterator end(void);

	/******************
	*	Capacity
	******************/
	size_t size(void) const;
	size_t max_size(void) const;
	bool empty(void) const;

	/******************
	*	Element access
	******************/
	value_type&			operator[] (size_t n);
	const value_type&	operator[] (size_t n) const;
	value_type&			at(size_t n);
	const value_type&	at(size_t n) const;
	value_type&			front(void);
	const value_type&	front(void) const;
	value_type&			back(void);
	const value_type&	back(void) const;

	/******************
	*	Modifiers
	******************/
	void assign(iterator first, iterator last);
	void assign(size_t n, const value_type& val);
	void push_back(const value_type& val);
	void push_back(value_type&& val);
	void push_front(const value_type& val);
	void push_front(value_type&& val);
	void pop_back(void);
	void pop_front(void);
	iterator insert(iterator position, const value_type& val);
	iterator insert(iterator position, size_t n, const value_type& val);
	iterator insert(iterator position, iterator first, iterator last);
	iterator insert(iterator position, value_type&& val);
	iterator erase(iterator position);
	iterator erase(iterator first, iterator last);
	void swap(MyDeque& x);
	void clear(void);
};

#include "MyDeque.inl"