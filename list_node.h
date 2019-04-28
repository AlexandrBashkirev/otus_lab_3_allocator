#pragma once

namespace flaber
{
	template<typename T>
	class list_node
	{
	public:

		template<typename... Args>
		list_node(Args&&... args) : value(args...)
		{ }

		~list_node() = default;
	private:
		T value;
		list_node* next = nullptr;

		list_node() = delete;
		list_node(const list_node<T>& node) = delete;
		list_node(list_node<T>&& node) = delete;
		list_node& operator=(const list_node<T>& node) = delete;
		list_node& operator=(list_node<T>&& node) = delete;

		template<typename T, class Allocator>
		friend class list;
		template<typename T>
		friend class list_iterator;
	};

}
