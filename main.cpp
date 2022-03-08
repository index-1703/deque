#include <iostream>
#include "MyDeque.h"

int main()
{
	MyDeque<int> d;
	d.push_back(1);
	d.push_back(2);
	d.push_front(3);
	d.push_back(4);


	for (MyDeque<int>::iterator it = d.begin(); it != d.end(); ++it) {
		std::cout << *it << std::endl;
	}

	d.clear();

	return 0;
}
