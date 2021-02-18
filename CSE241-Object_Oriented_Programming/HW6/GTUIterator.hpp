#ifndef GTUITERATOR_HPP
#define GTUITERATOR_HPP

#include <iostream>
#include <memory>
#include "node.hpp"


namespace _GTU_HW_6_{
	template<class T>
	class GTUIterator{
	public:
		GTUIterator();
		GTUIterator(std::shared_ptr< node<T> > other);
		GTUIterator(const GTUIterator<T> &obj);

		const T operator*()const;
		T& operator*();
		GTUIterator<T> operator++();
		GTUIterator<T> operator++(int junk);
		GTUIterator<T> operator--();
		GTUIterator<T> operator--(int junk);
		bool operator==(const GTUIterator &other)const;
		bool operator!=(const GTUIterator &other)const;
		GTUIterator<T>& operator=(const GTUIterator &other);
		GTUIterator<T> operator+(int n)const;
		GTUIterator<T> operator-(int n)const;

		const T* operator->()const;

	private:
		std::shared_ptr< node<T> > CurrentNode;
	};
}

#endif