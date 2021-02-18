#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <memory>
#include "node.hpp"

template<class T>
class node{
public:
	node(){
		next=nullptr;
		prev=nullptr;
	}

	T data;
	std::shared_ptr< node<T> > next;
	std::shared_ptr< node<T> > prev;
};

#endif