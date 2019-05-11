#pragma once
#include "list_node.h"
#include <iostream>
namespace flaber
{
	template<typename T, bool is_const>
	class _list_iterator
	{
	public:

		using value_type = std::conditional_t<is_const, const T, T>;
		using node_type = std::conditional_t<is_const, const list_node<T>, list_node<T>>;
		using value_ref = std::conditional_t<is_const, const T&, T&>;
		using value_ptr = std::conditional_t<is_const, const T*, T*>;

		value_ptr operator->()
		{
			return &(current->value);
		}

		value_ref operator*()
		{
			return current->value;
		}

		_list_iterator& operator++()
		{
			current = current->next;
			return *this;
		}

		bool operator!=(const _list_iterator& right)
		{
			return current != right.current;
		}

		bool operator==(const _list_iterator& right)
		{
			return current == right.current;
		}

		_list_iterator(const _list_iterator& node) = default;
		~_list_iterator() = default;
		
	protected:
		_list_iterator(node_type* _current) : current(_current) { }

		_list_iterator() = delete;

		_list_iterator(_list_iterator&& node) = delete;
		_list_iterator& operator=(const _list_iterator& node) = delete;
		_list_iterator& operator=(_list_iterator&& node) = delete;

		node_type* current;
	};

	template<typename T>
	class list_iterator : public _list_iterator<T, false> 
	{
	private:
		using base = _list_iterator<T, false>;

		list_iterator(typename base::node_type* _current) : base(_current) { }

		template<typename, typename> friend class list;
	};

	template<typename T>
	class list_iterator_c : public _list_iterator<T, true>
	{
		
	private:
		using base = _list_iterator<T, true>;

		list_iterator_c(typename base::node_type* _current) : base(_current) { }

		template<typename, typename> friend class list;
	};
}