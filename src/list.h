#pragma once

#include <utility>
#include <cassert>
#include "list_node.h"
#include "list_iterator.h"

namespace flaber
{
	template<typename T,
		typename Allocator = std::allocator<T>>
	class list
	{
	public:
		void insert_at(size_t pos, T &value);
		void insert_at(size_t pos, const T &value);
		template<typename... Args>
		void emplace_at(size_t pos, Args&&... args);
		void remove_at(size_t pos);

		void insert(list_node<T>* prev_it, T &value);
		void insert(list_node<T>* prev_it, const T &value);
		template<typename... Args>
		void emplace(list_node<T>* prev_it, Args&&... args);
		void remove(list_node<T>* prev_it);

		void push_front(T& value);
		void push_front(const T& value);
		template<typename... Args>
		void emplace_front(Args&&... args);

		void push_back(T& value);
		void push_back(const T& value);
		template<typename... Args>
		void emplace_back(Args&&... args);

		void pop_front();
		void pop_back();

		list_iterator<T> begin();
		list_iterator<T> back();
		list_iterator<T> end();

		list_iterator_c<T> cbegin();
		list_iterator_c<T> cback();
		list_iterator_c<T> cend();

		void clear();
		size_t size();
		bool is_empty();

		~list();

	private:

		size_t _size = 0;
		list_node<T>* first = nullptr;
		list_node<T>* last = nullptr;
		
		using NodeAllocator = typename Allocator::template rebind<list_node<T>>::other;
		NodeAllocator node_allocator;

		template<typename... Args>
		void _insert(list_node<T>* prev_it, Args&&... args);
		void _remove(list_node<T>* prev_it);
		list_node<T>* prev_elem(size_t pos);
	};

	template<typename T, typename Allocator>
	template<typename... Args>
	void list<T, Allocator>::_insert(list_node<T>* prev_it, Args&&... args)
	{
		list_node<T> *node = node_allocator.allocate(1);
		node_allocator.construct(node, args...);

		if (prev_it != nullptr) {
			node->next = prev_it->next;
			prev_it->next = node;
		}
		else {
			node->next = first;
			first = node;
		}

		if (node->next == nullptr)
			last = node;
		_size++;
	}

	template<typename T, typename Allocator>
	void list<T, Allocator>::_remove(list_node<T>* prev_it)
	{
		if (_size == 0)
			return;

		list_node<T>* node = first;

		if (prev_it != nullptr) {
			node = prev_it->next;
			prev_it->next = node->next;
		}

		if (node == last)
			last = prev_it;

		if (node == first)
			first = node->next;

		node_allocator.destroy(node);
		node_allocator.deallocate(node, 1);
		_size--;
	}

	template<typename T, typename Allocator>
	list<T, Allocator>::~list()
	{
		clear();
	}
	template<typename T, typename Allocator>
	void list<T, Allocator>::insert_at(size_t pos, T &value)
	{
		assert(pos >= 0 && pos < _size);
		_insert(prev_elem(pos), value);
	}
	template<typename T, typename Allocator>
	void list<T, Allocator>::insert_at(size_t pos, const T &value)
	{
		assert(pos >= 0 && pos < _size);
		_insert(prev_elem(pos), value);
	}

	template<typename T, typename Allocator>
	template<typename... Args>
	void list<T, Allocator>::emplace_at(size_t pos, Args&&... args)
	{
		assert(pos >= 0 && pos < _size);
		_insert(prev_elem(pos), args...);
	}

	template<typename T, typename Allocator>
	void list<T, Allocator>::remove_at(size_t pos)
	{
		assert(pos >= 0 && pos < _size);
		_remove(prev_elem(pos));
	}

	template<typename T, typename Allocator>
	void list<T, Allocator>::insert(list_node<T>* prev_it, T &value)
	{
		_insert(prev_it, value);
	}
	template<typename T, typename Allocator>
	void list<T, Allocator>::insert(list_node<T>* prev_it, const T &value)
	{
		_insert(prev_it, value);
	}

	template<typename T, typename Allocator>
	template<typename... Args>
	void list<T, Allocator>::emplace(list_node<T>* prev_it, Args&&... args)
	{
		_insert(prev_it, args...);
	}

	template<typename T, typename Allocator>
	void list<T, Allocator>::remove(list_node<T>* prev_it)
	{
		_remove(prev_it);
	}

	template<typename T, typename Allocator>
	template<typename... Args>
	void list<T, Allocator>::emplace_front(Args&&... args)
	{
		_insert(nullptr, args...);
	}

	template<typename T, typename Allocator>
	void list<T, Allocator>::push_front(T& value)
	{
		_insert(nullptr, value);
	}

	template<typename T, typename Allocator>
	void list<T, Allocator>::push_front(const T& value)
	{
		_insert(nullptr, value);
	}

	template<typename T, typename Allocator>
	template<typename... Args>
	void list<T, Allocator>::emplace_back(Args&&... args)
	{
		_insert(last, args...);
	}

	template<typename T, typename Allocator>
	void list<T, Allocator>::push_back(T& value)
	{
		_insert(last, value);
	}

	template<typename T, typename Allocator>
	void list<T, Allocator>::push_back(const T& value)
	{
		_insert(last, value);
	}

	template<typename T, typename Allocator>
	void list<T, Allocator>::pop_back()
	{
		if (first == nullptr)
			return;

		list_node<T>* prev = first;

		while (prev != nullptr && prev->next != last)
			prev = prev->next;
		
		_remove(prev);
	}

	template<typename T, typename Allocator>
	void list<T, Allocator>::pop_front()
	{
		_remove(nullptr);
	}

	template<typename T, typename Allocator>
	list_node<T>* list<T, Allocator>::prev_elem(size_t pos)
	{
		assert(pos >= 0 && pos < _size);

		list_node<T>* result = nullptr;
		list_node<T>* prev = first;

		size_t cur = 0;
		while (cur < pos)
		{
			result = prev;
			prev = prev->next;
			cur++;
		}

		return result;
	}

	template<typename T, typename Allocator>
	list_iterator<T> list<T, Allocator>::begin()
	{
		return list_iterator<T>(first);
	}

	template<typename T, typename Allocator>
	list_iterator<T> list<T, Allocator>::back()
	{
		return list_iterator<T>(last);
	}

	template<typename T, typename Allocator>
	list_iterator<T> list<T, Allocator>::end()
	{
		return list_iterator<T>(nullptr);
	}

	template<typename T, typename Allocator>
	list_iterator_c<T> list<T, Allocator>::cbegin()
	{
		return list_iterator_c<T>(first);
	}

	template<typename T, typename Allocator>
	list_iterator_c<T> list<T, Allocator>::cback()
	{
		return list_iterator_c<T>(last);
	}

	template<typename T, typename Allocator>
	list_iterator_c<T> list<T, Allocator>::cend()
	{
		return list_iterator_c<T>(nullptr);
	}

	template<typename T, typename Allocator>
	void list<T, Allocator>::clear()
	{
		while (first != nullptr)
			pop_front();
	}

	template<typename T, typename Allocator>
	bool list<T, Allocator>::is_empty()
	{
		return _size == 0;
	}

	template<typename T, typename Allocator>
	size_t list<T, Allocator>::size()
	{
		return _size;
	}
}
