#ifndef GTUVECTOR_HPP
#define GTUVECTOR_HPP

#include <iostream>
#include "GTUExceptions.hpp"
#include "GTUContainer.hpp"
#include "node.hpp"
#include "GTUIterator.hpp"

namespace _GTU_HW_6_{
	
	template<class T>
	class GTUVector : public GTUContainer<T>{
	public:
		GTUVector();//Constructs an empty container, with no elements.
		GTUVector(T value);//Constructs a container which have one element.
		GTUVector(int n,T value);//Constructs a container with n elements. Each element is a copy of value.
		GTUVector(const GTUVector<T> &obj);//copy constructor.
		GTUVector<T> operator=(const GTUVector<T>& other);
		virtual ~GTUVector();

		bool empty()const override;
		int size()const override;
		int max_size()const override;

		const T operator[](int index)const;
		T& operator[](int index);
		const GTUIterator<T> begin()const override;
		const GTUIterator<T> end()const override;
		void clear() override;
		const GTUIterator<T> erase(const GTUIterator<T> &position)override;
		const GTUIterator<T> erase(const GTUIterator<T> &first,const GTUIterator<T> &last)override;
		virtual const GTUIterator<T> insert(T val)override;
		virtual const GTUIterator<T> insert(const GTUIterator<T> &position, T val)override;
		const T* operator->()const;
	private:
		int _size;
		const static int MAX_SIZE = 100;
		std::shared_ptr< node<T> > HeadOfContent;
	};
}

#endif