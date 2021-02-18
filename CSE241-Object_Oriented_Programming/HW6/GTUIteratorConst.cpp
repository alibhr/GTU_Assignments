#include "GTUIteratorConst.hpp"

namespace _GTU_HW_6_{

	template<class T>
	GTUIteratorConst<T>::GTUIteratorConst(){
		CurrentNode=nullptr;
	}

	template<class T>
	GTUIteratorConst<T>::GTUIteratorConst(std::shared_ptr< node<T> > other){
		CurrentNode = other;
	}

	template<class T>
	GTUIteratorConst<T>::GTUIteratorConst(const GTUIteratorConst<T> &obj){
		CurrentNode = std::make_shared< node <T> >();
		CurrentNode = obj.CurrentNode;
	}

	template<class T>
	const T GTUIteratorConst<T>::operator*()const{
		return this->CurrentNode->data;
	}

	template<class T>
	GTUIteratorConst<T> GTUIteratorConst<T>::operator++(){
		this->CurrentNode=this->CurrentNode->next;
		return *this;
	}

	template<class T>
	GTUIteratorConst<T> GTUIteratorConst<T>::operator++(int junk){
		GTUIteratorConst<T> temp=*this;
		this->CurrentNode=this->CurrentNode->next;
		return temp;
	}

	template<class T>
	GTUIteratorConst<T> GTUIteratorConst<T>::operator--(){
		this->CurrentNode=this->CurrentNode->prev;
		return *this;
	}

	template<class T>
	GTUIteratorConst<T> GTUIteratorConst<T>::operator--(int junk){
		GTUIteratorConst<T> temp=*this;
		this->CurrentNode=this->CurrentNode->prev;
		return temp;
	}

	template<class T>
	bool GTUIteratorConst<T>::operator==(const GTUIteratorConst &other)const{
		return (this->CurrentNode==other.CurrentNode);
	}

	template<class T>
	bool GTUIteratorConst<T>::operator!=(const GTUIteratorConst &other)const{
		return !(this->CurrentNode==other.CurrentNode);
	}

	template<class T>
	GTUIteratorConst<T>& GTUIteratorConst<T>::operator=(const GTUIteratorConst &other){
		this->CurrentNode=other.CurrentNode;
		return *this;
	}

	template<class T>
	GTUIteratorConst<T> GTUIteratorConst<T>::operator+(int n)const{
		GTUIteratorConst<T> temp=*this;
		for(int i=0;i<n;++i){
			temp.CurrentNode=temp.CurrentNode->next;
			if(temp.CurrentNode==nullptr){
				i=n;
				return *this;
				//exceptions.
			}
		}
		return temp;
	}

	template<class T>
	GTUIteratorConst<T> GTUIteratorConst<T>::operator-(int n)const{
		GTUIteratorConst<T> temp=*this;
		for(int i=0;i<n;++i){
			temp.CurrentNode=temp.CurrentNode->prev;
			if(temp.CurrentNode==nullptr){
				i=n;
				return *this;
				//exceptions.
			}
		}
		return temp;
	}

	template<class T>
	const T* GTUIteratorConst<T>::operator->()const{
		return &(CurrentNode->data);
	}

}