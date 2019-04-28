#pragma once


template<typename T>
struct fallocator {
	using value_type = T;

	using size_type = size_t;
	using pointer = T * ;
	using const_pointer = const T*;
	using reference = T & ;
	using const_reference = const T&;

	template<typename U>
	struct rebind {
		using other = fallocator<U>;
	};

	template <class U> fallocator(const fallocator<U>&) {}
	fallocator() {}
	~fallocator() {}

	T *allocate(std::size_t n) {
		std::cout << __FUNCTION__ << "[n = " << n << "]" << std::endl;
		auto p = std::malloc(n * sizeof(T));
		if (!p)
			throw std::bad_alloc();
		return reinterpret_cast<T *>(p);
	}

	void deallocate(T *p, std::size_t n) {
		std::cout << __FUNCTION__ << "[n = " << n << "]" << std::endl;
		std::free(p);
	}

	template<typename U, typename ...Args>
	void construct(U *p, Args &&...args) {
		std::cout << __FUNCTION__ << std::endl;
		new(p) U(std::forward<Args>(args)...);
	};

	void destroy(T *p) {
		std::cout << __FUNCTION__ << std::endl;
		p->~T();
	}
};