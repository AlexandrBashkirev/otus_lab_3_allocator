#pragma once

#include <queue>

template<typename T, size_t al_size = 10>
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
	fallocator() { }
	~fallocator() {}

	struct batch
	{
		pointer p;
		size_t s;
		std::queue<pointer> unused;
	};

	std::list<batch*> batchs;

	T *allocate(std::size_t n) {
		
	
		if (n == 1 && !batchs.empty()) {

			auto it = find_if(batchs.begin(), batchs.end(), [](batch* b) {return !b->unused.empty(); });

			if (it != batchs.end()) {
				T* p = (*it)->unused.front();
				(*it)->unused.pop();
				return p;
			}
		}


		size_t real_n = n;
		if (real_n < al_size)
			real_n = al_size;

		
		void* p = std::malloc(real_n * sizeof(T));
		if (!p)
			throw std::bad_alloc();
		std::cout << __FUNCTION__ << "[real_n = " << real_n << "]" << "[p = " << p << "]" << std::endl;

		batch* _batch  = new batch();
		_batch->p = reinterpret_cast<T *>(p);
		_batch->s = real_n;
			
		for (size_t i = n; i < real_n; i++)
			_batch->unused.push(_batch->p + i);
		batchs.push_front(_batch);
		
		
		return _batch->p;
	}

	void deallocate(T *p, std::size_t n) {

		auto it = find_if(batchs.begin(), batchs.end(), [p](batch* b) {return p >= b->p && p < b->p + b->s; });
		if(it == batchs.end())
			throw std::bad_exception();

		for(size_t i = 0; i < n; i ++)
			(*it)->unused.push(p + i);
		if ((*it)->unused.size() == (*it)->s) {
			std::cout << __FUNCTION__ << "[p = " << (*it)->p << "]" << std::endl;
			std::free((*it)->p);
		}
	}

	template<typename U, typename ...Args>
	void construct(U *p, Args &&...args) {
		std::cout << __FUNCTION__ << "[p = " << p << "]" << std::endl;
		new(p) U(std::forward<Args>(args)...);
	}

	void destroy(T *p) {
		std::cout << __FUNCTION__ << "[p = " << p << "]" << std::endl;
		p->~T();
	}
};
