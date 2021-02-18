#ifndef GTUCONTAINER_HPP
#define GTUCONTAINER_HPP

#include <iostream>
#include <string>
#include <memory>
#include "GTUExceptions.hpp"
#include "GTUIterator.hpp"


namespace _GTU_HW_6_{

	template<class T>
	class GTUContainer{
	public:
		GTUContainer(){}
		virtual ~GTUContainer(){}
		//assing, if it is necessary.??????????????????
		//copy constructor, if it is necessary.????????

		virtual bool empty()const=0;
		virtual int size()const=0;
		virtual int max_size()const=0;

		virtual const GTUIterator<T> begin()const=0;
		virtual const GTUIterator<T> end()const=0;

		virtual void clear()=0;

		virtual const GTUIterator<T> erase(const GTUIterator<T> &position)=0;
		virtual const GTUIterator<T> erase(const GTUIterator<T> &first,const GTUIterator<T> &last)=0;

		virtual const GTUIterator<T> insert(T val)=0;
		virtual const GTUIterator<T> insert(const GTUIterator<T> &position, T val)=0;

	private:
	};





}

#endif