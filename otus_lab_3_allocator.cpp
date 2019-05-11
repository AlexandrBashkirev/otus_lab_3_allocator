// otus_lab_3_allocator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <algorithm>
#include "list.h"
#include "fallocator.h"

int main()
{
	std::list<int, fallocator<int>> t;
	t.push_back(1);
	std::cout << "t.size == " << t.size() << "\n";

	flaber::list<int, fallocator<int>> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	int a = 4;
	l.push_back(a);

	l.insert_at(0, 10);

	/*std::for_each(l.cbegin(), l.cend(), []( const int& r) {
		r = 5; 
	});*/

	std::for_each(l.cbegin(), l.cend(), [](const int& r) {
		std::cout << r << "\n";
	});

	std::cout << "l.size == " << l.size() << "\n";

	l.pop_front();

	std::for_each(l.begin(), l.end(), [](int& r) {
		r = 5; });

	std::for_each(l.begin(), l.end(), [](int& r) {
		std::cout << r << "\n";  });

	std::cout << "l.size == " << l.size() << "\n";
}

