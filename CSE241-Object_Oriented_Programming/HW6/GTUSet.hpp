#ifndef GTUSET_HPP
#define GTUSET_HPP

#include <iostream>
#include "GTUExceptions.hpp"
#include "GTUContainer.hpp"
#include "node.hpp"
#include "GTUIterator.hpp"

namespace _GTU_HW_6_{
	
	template<class T>
	class GTUSet : public GTUContainer<T>{
	public:
		GTUSet();//Constructs an empty container, with no elements.
		GTUSet(T value);//Constructs a container which have one element.
		GTUSet(int n,T value);//Constructs a container with n elements. Each element is a copy of value.
		GTUSet(const GTUSet<T> &obj);//copy constructor.
		GTUSet<T> operator=(const GTUSet<T>& other);
		virtual ~GTUSet();

		bool empty()const override;
		int size()const override;
		int max_size()const override;

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