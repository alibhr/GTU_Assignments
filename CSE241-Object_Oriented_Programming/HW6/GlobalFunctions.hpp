#ifndef GLOBALFUNCTIONS_HPP
#define GLOBALFUNCTIONS_HPP

#include <iostream>
#include "GTUIterator.hpp"

namespace _GTU_HW_6_{

	template<class iter,class T>
	iter find(iter first,const iter last,T val);

	template<class Function,class iter>
	iter find_if(iter first,iter last,Function f);

	template<class Function,class iter>
	iter for_each(iter first,iter last,Function f);

}


#endif