// otus_lab_3_allocator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <map>
#include <algorithm>
#include "list.h"
#include "fallocator.h"
#include "log_allocator.h"


int main()
{
	//std::list<int, log_allocator<int>> my_list_my_alloc;
	//my_list_my_alloc.push_back(0);

	std::cout << "my_list_my_alloc" << std::endl;
	flaber::list<int, fallocator<int>> my_list_my_alloc;
	for (int i = 0; i < 10; i++)
		my_list_my_alloc.push_back(i);

	std::cout << "my_list_std_alloc" << std::endl;
	flaber::list<int> my_list_std_alloc;
	for(int i = 0; i < 10; i++)
		my_list_std_alloc.push_back(i);

	std::cout << "map_std_alloc" << std::endl;
	std::map<int, int> map_std_alloc;
	for (int i = 0; i < 10; i++)
		map_std_alloc.emplace(i, i);

	std::cout << "map_my_alloc" << std::endl;
	std::map<int, int, std::less<>, fallocator< std::pair<int,int> > > map_my_alloc;
	for (int i = 0; i < 10; i++)
		map_my_alloc.emplace(i, i);

	std::cout << "end" << std::endl;
}

