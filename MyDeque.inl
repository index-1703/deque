#include "MyDeque.h"



template<class value_type, class Alloc>
MyDeque<value_type, Alloc>::MyDeque(void)
	: first(nullptr), last(nullptr), count_nodes(0)
{
}

template<class value_type, class Alloc>
MyDeque<value_type, Alloc>::MyDeque(size_t n, const value_type& val)
	: first(nullptr), last(nullptr), count_nodes(0)
{
	for (size_t i = 0; i < n; i++) {
		push_back(val);
	}
}

template<class value_type, class Alloc>
MyDeque<value_type, Alloc>::MyDeque(iterator first, iterator last)
	: first(nullptr), last(nullptr), count_nodes(0)
{
	for (iterator it = first; it != last; it++) {
		push_back(*it);
	}
}

template<class value_type, class Alloc>
MyDeque<value_type, Alloc>::MyDeque(const MyDeque& x)
	: first(nullptr), last(nullptr), count_nodes(0)
{
	for (iterator it = x.begin(); it != x.end(); it++) {
		push_back(*it);
	}
}

template<class value_type, class Alloc>
MyDeque<value_type, Alloc>::MyDeque(MyDeque&& x)
	: first(x.first), last(x.last), count_nodes(x.count_nodes)
{
	alloc = std::move(x.alloc);
	x.first = nullptr;
	x.last = nullptr;
	x.count_nodes = 0;
}

template<class value_type, class Alloc>
MyDeque<value_type, Alloc>::~MyDeque(void)
{
	clear();
}

template<class value_type, class Alloc>
MyDeque<value_type, Alloc>& MyDeque<value_type, Alloc>::operator=(const MyDeque& x)
{
	clear();
	for (iterator it = x.begin(); it != x.end(); it++) {
		push_back(*it);
	}
}

template<class value_type, class Alloc>
MyDeque<value_type, Alloc>& MyDeque<value_type, Alloc>::operator=(MyDeque&& x)
{
	first = x.first;
	last = x.last;
	count_nodes = x.count_nodes;
	alloc = std::move(x.alloc);

	x.first = nullptr;
	x.last = nullptr;
	x.count_nodes = 0;

	return *this;
}

template<class value_type, class Alloc>
MyDequeIterator<value_type, Alloc> MyDeque<value_type, Alloc>::begin(void)
{
	return MyDequeIterator<value_type, Alloc>(first);
}

template<class value_type, class Alloc>
MyDequeIterator<value_type, Alloc> MyDeque<value_type, Alloc>::end(void)
{
	return MyDequeIterator<value_type, Alloc>(nullptr);
}

template<class value_type, class Alloc>
size_t MyDeque<value_type, Alloc>::size(void) const
{
	return count_nodes;
}

template<class value_type, class Alloc>
size_t MyDeque<value_type, Alloc>::max_size(void) const
{
	return alloc.max_size();
}

template<class value_type, class Alloc>
bool MyDeque<value_type, Alloc>::empty(void) const
{
	return count_nodes == 0;
}

template<class value_type, class Alloc>
value_type& MyDeque<value_type, Alloc>::operator[](size_t n)
{
	iterator it = begin();
	
	for (size_t index = 0; it != end() && index < n; it++, index++);

	if (it == end() && index == n) {
		return *it;
	}
	else
	{
		return nullptr;
	}
}

template<class value_type, class Alloc>
const value_type& MyDeque<value_type, Alloc>::operator[](size_t n) const
{
	iterator it = begin();

	for (size_t index = 0; it != end() && index < n; it++, index++);

	if (it == end() && index == n) {
		return *it;
	}
	else
	{
		return nullptr;
	}
}

template<class value_type, class Alloc>
value_type& MyDeque<value_type, Alloc>::at(size_t n)
{
	if (n >= count_nodes) {
		throw std::out_of_range("MyDeque::at");
	}

	iterator it = begin();

	for (size_t index = 0; it != end() && index < n; it++, index++);

	if (it == end() && index == n) {
		return *it;
	}
	else
	{
		return nullptr;
	}
}

template<class value_type, class Alloc>
const value_type& MyDeque<value_type, Alloc>::at(size_t n) const
{
	if (n >= count_nodes) {
		throw std::out_of_range("MyDeque::at");
	}

	iterator it = begin();

	for (size_t index = 0; it != end() && index < n; it++, index++);

	if (it == end() && index == n) {
		return *it;
	}
	else
	{
		return nullptr;
	}
}

template<class value_type, class Alloc>
value_type& MyDeque<value_type, Alloc>::front(void)
{
	return first->data;
}

template<class value_type, class Alloc>
const value_type& MyDeque<value_type, Alloc>::front(void) const
{
	return first->data;
}

template<class value_type, class Alloc>
value_type& MyDeque<value_type, Alloc>::back(void)
{
	return last->data;
}

template<class value_type, class Alloc>
const value_type& MyDeque<value_type, Alloc>::back(void) const
{
	return last->data;
}

template<class value_type, class Alloc>
void MyDeque<value_type, Alloc>::assign(iterator first, iterator last)
{
	clear();
	for (iterator it = first; it != last; it++) {
		push_back(*it);
	}
}

template<class value_type, class Alloc>
void MyDeque<value_type, Alloc>::assign(size_t n, const value_type& val)
{
	clear();
	for (size_t i = 0; i < n; i++) {
		push_back(val);
	}
}

template<class value_type, class Alloc>
void MyDeque<value_type, Alloc>::push_back(const value_type& val)
{
	node_t* node = _create_node();
	if (node == nullptr) {
		throw std::bad_alloc();
	}

	node->data = val;
	node->next = nullptr;
	node->prev = last;

	if (last != nullptr) {
		last->next = node;
	}

	last = node;

	if (first == nullptr) {
		first = node;
	}
	
	count_nodes++;
}

template<class value_type, class Alloc>
void MyDeque<value_type, Alloc>::push_back(value_type&& val)
{
	node_t* node = _create_node();
	if (node == nullptr) {
		throw std::bad_alloc();
	}

	node->data = std::move(val);
	node->next = nullptr;
	node->prev = last;

	if (last != nullptr) {
		last->next = node;
	}

	last = node;

	if (first == nullptr) {
		first = node;
	}

	count_nodes++;
}

template<class value_type, class Alloc>
void MyDeque<value_type, Alloc>::push_front(const value_type& val)
{
	node_t* node = _create_node();
	if (node == nullptr) {
		throw std::bad_alloc();
	}

	node->data = val;
	node->next = first;
	node->prev = nullptr;

	if (first != nullptr) {
		first->prev = node;
	}

	first = node;

	if (last == nullptr) {
		last = node;
	}

	count_nodes++;
}

template<class value_type, class Alloc>
void MyDeque<value_type, Alloc>::push_front(value_type&& val)
{
	node_t* node = _create_node();
	if (node == nullptr) {
		throw std::bad_alloc();
	}

	node->data = std::move(val);
	node->next = first;
	node->prev = nullptr;

	if (first != nullptr) {
		first->prev = node;
	}

	first = node;

	if (last == nullptr) {
		last = node;
	}

	count_nodes++;
}

template<class value_type, class Alloc>
void MyDeque<value_type, Alloc>::pop_back(void)
{
	if (count_nodes > 0) {
		node_t* node = last;

		if (first == node) {
			first = nullptr;
		}
		last = node->prev;

		_delete_node(node);

		count_nodes--;
	}
}

template<class value_type, class Alloc>
void MyDeque<value_type, Alloc>::pop_front(void)
{
	if (count_nodes > 0) {
		node_t* node = first;

		if (last == node) {
			last = nullptr;
		}
		first = node->next;

		_delete_node(node);

		count_nodes--;
	}
}

template<class value_type, class Alloc>
MyDequeIterator<value_type, Alloc> MyDeque<value_type, Alloc>::insert(iterator position, const value_type& val)
{
	node_t* node = _create_node();
	if (node == nullptr) {
		throw std::bad_alloc();
	}

	node->data = val;

	if (position->node) 
		if (position->node->prev) {
			position->node->prev->next = node;
		}

	node->prev = position->node->prev;
	position->node->prev = node;

	node->next = position->node;
	position->node = node;

	return position;
}

template<class value_type, class Alloc>
MyDequeIterator<value_type, Alloc> MyDeque<value_type, Alloc>::insert(iterator position, size_t n, const value_type& val)
{
	iterator it = position;

	for (size_t index = 0; index < n; index++) {
		it = insert(it, val);
	}

	return it;
}

template<class value_type, class Alloc>
MyDequeIterator<value_type, Alloc> MyDeque<value_type, Alloc>::insert(iterator position, iterator first, iterator last)
{
	iterator firstIt = insert(position, *first);
	iterator posIt = firstIt;
	++posIt;

	for (iterator it = first; it != last; ++it) {
		posIt = insert(posIt, *it);
		++posIt;
	}

	return firstIt;
}

template<class value_type, class Alloc>
MyDequeIterator<value_type, Alloc> MyDeque<value_type, Alloc>::insert(iterator position, value_type&& val)
{
	node_t* node = _create_node();
	if (node == nullptr) {
		throw std::bad_alloc();
	}

	node->data = std::move(val);

	if (position->node)
		if (position->node->prev) {
			position->node->prev->next = node;
		}

	node->prev = position->node->prev;
	position->node->prev = node;

	node->next = position->node;
	position->node = node;

	return position;
}

template<class value_type, class Alloc>
MyDequeIterator<value_type, Alloc> MyDeque<value_type, Alloc>::erase(iterator position)
{
	node_t* node = position->node;

	if (node->prev != nullptr) {
		node->prev->next = node->next;
	}
	if (node->next != nullptr) {
		node->next->prev = node->prev;
	}

	position->node = node->next;

	return position;
}

template<class value_type, class Alloc>
MyDequeIterator<value_type, Alloc> MyDeque<value_type, Alloc>::erase(iterator first, iterator last)
{
	for (iterator it = first; it != last; ) {
		it = erase(it);
	}

	return it;
}

template<class value_type, class Alloc>
void MyDeque<value_type, Alloc>::swap(MyDeque& x)
{
	node_t* tmpPtr;

	tmpPtr = first;
	first = x.first;
	x.first = tmpPtr;

	tmpPtr = last;
	last = x.last;
	x.last = tmpPtr;

	size_t tmpCount = count_nodes;
	count_nodes = x.count_nodes;
	x.count_nodes = tmpCount;

	Alloc tmpAlloc = std::move(alloc);
	alloc = std::move(x.alloc);
	x.alloc = std::move(tmpAlloc);
}

template<class value_type, class Alloc>
void MyDeque<value_type, Alloc>::clear(void)
{
	node_t* node = first;
	
	while (node != nullptr)
	{
		node_t* delnode = node;
		node = node->next;
		_delete_node(delnode);
	}

	first = nullptr;
	last = nullptr;
	count_nodes = 0;
}


;