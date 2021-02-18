#include "GTUIterator.hpp"

namespace _GTU_HW_6_{

	template<class T>
	GTUIterator<T>::GTUIterator(){
		CurrentNode=nullptr;
	}

	template<class T>
	GTUIterator<T>::GTUIterator(std::shared_ptr< node<T> > other){
		CurrentNode = other;
	}

	template<class T>
	GTUIterator<T>::GTUIterator(const GTUIterator<T> &obj){
		CurrentNode = std::make_shared< node <T> >();
		CurrentNode = obj.CurrentNode;
	}

	template<class T>
	const T GTUIterator<T>::operator*()const{
		return this->CurrentNode->data;
	}

	template<class T>
	T& GTUIterator<T>::operator*(){
		return this->CurrentNode->data;
	}

	template<class T>
	GTUIterator<T> GTUIterator<T>::operator++(){
		this->CurrentNode=this->CurrentNode->next;
		return *this;
	}

	template<class T>
	GTUIterator<T> GTUIterator<T>::operator++(int junk){
		GTUIterator<T> temp=*this;
		this->CurrentNode=this->CurrentNode->next;
		return temp;
	}

	template<class T>
	GTUIterator<T> GTUIterator<T>::operator--(){
		this->CurrentNode=this->CurrentNode->prev;
		return *this;
	}

	template<class T>
	GTUIterator<T> GTUIterator<T>::operator--(int junk){
		GTUIterator<T> temp=*this;
		this->CurrentNode=this->CurrentNode->prev;
		return temp;
	}

	template<class T>
	bool GTUIterator<T>::operator==(const GTUIterator &other)const{
		return (this->CurrentNode==other.CurrentNode);
	}

	template<class T>
	bool GTUIterator<T>::operator!=(const GTUIterator &other)const{
		return !(this->CurrentNode==other.CurrentNode);
	}

	template<class T>
	GTUIterator<T>& GTUIterator<T>::operator=(const GTUIterator &other){
		this->CurrentNode=other.CurrentNode;
		return *this;
	}

	template<class T>
	GTUIterator<T> GTUIterator<T>::operator+(int n)const{
		GTUIterator<T> temp=*this;
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
	GTUIterator<T> GTUIterator<T>::operator-(int n)const{
		GTUIterator<T> temp=*this;
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
	const T* GTUIterator<T>::operator->()const{
		return &(CurrentNode->data);
	}

}