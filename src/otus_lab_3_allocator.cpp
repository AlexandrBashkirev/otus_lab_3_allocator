// otus_lab_3_allocator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <map>
#include <algorithm>
#include "list.h"
#include "fallocator.h"
#include "log_allocator.h"
#include "factorial.h"

int main()
{
    //std::cout << "map_std_alloc" << std::endl;
    std::map<int, int> map_std_alloc;
    for (int i = 0; i < 10; i++)
        map_std_alloc.emplace(i, flaber::factorial(i));
    
    //std::cout << "map_my_alloc" << std::endl;
    std::map<int, int, std::less<>, fallocator< std::pair<const int,int> > > map_my_alloc;
    for (int i = 0; i < 10; i++)
        map_my_alloc.emplace(i, flaber::factorial(i));
    
	std::for_each(map_my_alloc.cbegin(), map_my_alloc.cend(), [](const auto& elem) {
		std::cout << elem.first << " " << elem.second << std::endl;
		});

    //std::cout << "my_list_std_alloc" << std::endl;
    flaber::list<int> my_list_std_alloc;
    for(int i = 0; i < 10; i++)
        my_list_std_alloc.push_back(i);
    
	//std::cout << "my_list_my_alloc" << std::endl;
	flaber::list<int, fallocator<int>> my_list_my_alloc;
	for (int i = 0; i < 10; i++)
		my_list_my_alloc.push_back(i);

	std::for_each(my_list_my_alloc.cbegin(), my_list_my_alloc.cend(), [](int elem) {
		std::cout << elem << std::endl;
		});
}

