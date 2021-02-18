#include "GlobalFunctions.hpp"

namespace _GTU_HW_6_{

	template<class iter,class T>
	iter find(iter first, iter last,T val){
		while(first != last){
			if(*first == val){
				return first;
			}
			++first;
		}
		return first;
	}

	template<class Function,class iter>
	iter find_if(iter first,iter last,Function f){
		while(first != last){
			if(f(*first))
				return first;
			
			++first;
		}
		return first;
	}

	template<class Function,class iter>
	Function for_each(iter first,iter last,Function f){
		while(first != last){
			f(*first);
			++first;
		}
		return f;
	}
}
	