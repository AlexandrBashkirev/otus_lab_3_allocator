#pragma once


template<typename T>
struct log_allocator {
	using value_type = T;

	using size_type = size_t;
	using pointer = T * ;
	using const_pointer = const T*;
	using reference = T & ;
	using const_reference = const T&;

	template<typename U>
	struct rebind {
		using other = log_allocator<U>;
	};


	template <class U> log_allocator(const log_allocator<U>&) { std::cout << "+" << __FUNCTION__ << std::endl; }
	template <class U> log_allocator( log_allocator<U>&&) { std::cout << "+" << __FUNCTION__ << std::endl; }
	log_allocator() { std::cout << "+" << __FUNCTION__ << std::endl; }
	~log_allocator() { std::cout << "-" << __FUNCTION__ << std::endl; }

	T *allocate(std::size_t n) {
		auto p = std::malloc(n * sizeof(T));
		std::cout << __FUNCTION__ << "[n = " << n << "]" << "[p = " << p << "]" << std::endl;
		if (!p)
			throw std::bad_alloc();
		return reinterpret_cast<T *>(p);
	}

	void deallocate(T *p, std::size_t n) {
		std::cout << __FUNCTION__ << "[n = " << n << "]" << "[p = " << p << "]" << std::endl;
		std::free(p);
	}

	template<typename U, typename ...Args>
	void construct(U *p, Args &&...args) {
		std::cout << __FUNCTION__ << "[p = " << p << "]" << std::endl;
		new(p) U(std::forward<Args>(args)...);
	};

	void destroy(T *p) {
		std::cout << __FUNCTION__ << "[p = " << p << "]" << std::endl;
		p->~T();
	}
};