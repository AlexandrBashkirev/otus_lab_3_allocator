#pragma once
#include "list_node.h"
#include <iostream>
namespace flaber
{
	template<typename T>
	class list_iterator
	{
	public:
		T* operator->()
		{
			return &(current->value);
		}

		T& operator*()
		{
			return current->value;
		}

		list_iterator& operator++()
		{
			current = current->next;
			return *this;
		}

		list_iterator& operator++(int)
		{
			current = current->next;
			return *this;
		}

		bool operator!=(const list_iterator<T>& right)
		{
			return current != right.current;
		}

		bool operator==(const list_iterator<T>& right)
		{
			return current == right.current;
		}

		list_iterator(const list_iterator& node) = default;
		list_iterator(list_iterator&& node)
		{
			std::swap<list_node<T>*, list_node<T>*>(current, node.current);
		};
		~list_iterator() = default;
		
	private:

		list_iterator(list_node<T>* _current) : current(_current) { }

		list_iterator() = delete;
		list_iterator& operator=(const list_iterator& node) = delete;
		list_iterator& operator=(list_iterator&& node) = delete;


		list_node<T>* current;

		template<typename T, class Allocator>
		friend class list;
	};
}