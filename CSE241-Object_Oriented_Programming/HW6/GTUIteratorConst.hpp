#ifndef GTUITERATORCONST_HPP
#define GTUITERATORCONST_HPP

#include <iostream>
#include <memory>
#include "node.hpp"


namespace _GTU_HW_6_{
	template<class T>
	class GTUIteratorConst{
	public:
		GTUIteratorConst();
		GTUIteratorConst(std::shared_ptr< node<T> > other);
		GTUIteratorConst(const GTUIteratorConst<T> &obj);

		const T operator*()const;
		GTUIteratorConst<T> operator++();
		GTUIteratorConst<T> operator++(int junk);
		GTUIteratorConst<T> operator--();
		GTUIteratorConst<T> operator--(int junk);
		bool operator==(const GTUIteratorConst &other)const;
		bool operator!=(const GTUIteratorConst &other)const;
		GTUIteratorConst<T>& operator=(const GTUIteratorConst &other);
		GTUIteratorConst<T> operator+(int n)const;
		GTUIteratorConst<T> operator-(int n)const;

		const T* operator->()const;

	private:
		std::shared_ptr< node<T> > CurrentNode;
	};
}

#endif