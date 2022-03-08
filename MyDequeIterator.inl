template<class value_type, class Alloc>
MyDequeIterator<value_type, Alloc>& MyDequeIterator<value_type, Alloc>::operator++()
{
	if (node == nullptr) {
		throw std::exception("Iterator is out of range");
	}
	node = node->next;
	return *this;
}

template<class value_type, class Alloc>
MyDequeIterator<value_type, Alloc> MyDequeIterator<value_type, Alloc>::operator++(int)
{
	MyDequeIterator old = *this;
	operator++();
	return old;
}

template<class value_type, class Alloc>
MyDequeIterator<value_type, Alloc>& MyDequeIterator<value_type, Alloc>::operator--()
{
	if (node == nullptr) {
		throw std::exception("Iterator is out of range");
	}
	node = node->prev;
	return *this;
}

template<class value_type, class Alloc>
MyDequeIterator<value_type, Alloc> MyDequeIterator<value_type, Alloc>::operator--(int)
{
	MyDequeIterator old = *this;
	operator--();
	return old;
}

template<class value_type, class Alloc>
bool MyDequeIterator<value_type, Alloc>::operator==(const MyDequeIterator<value_type, Alloc>& rhs) const
{
	return node == rhs.node;
}

template<class value_type, class Alloc>
bool MyDequeIterator<value_type, Alloc>::operator!=(const MyDequeIterator<value_type, Alloc>& rhs) const
{
	return node != rhs.node;
}

template<class value_type, class Alloc>
value_type& MyDequeIterator<value_type, Alloc>::operator*(void)
{
	return node->data;
}