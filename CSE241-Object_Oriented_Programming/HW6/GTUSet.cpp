#include "GTUSet.hpp"

namespace _GTU_HW_6_{

	template<class T>
	GTUSet<T>::GTUSet(){
		HeadOfContent=nullptr;
		_size = 0;
	}

	template<class T>
	GTUSet<T>::GTUSet(T val){
		HeadOfContent=std::make_shared< node<T> >();
		HeadOfContent->data=val;
		HeadOfContent->next=nullptr;
		HeadOfContent->prev=nullptr;
		_size = 1;

	}

	template<class T>
	GTUSet<T>::GTUSet(int n,T value){
		if(MAX_SIZE < n)
			GTUExceptions("MAX_SIZE problem !");

		if(n > 0){
			HeadOfContent=std::make_shared< node<T> >();
			std::shared_ptr< node<T> > temp = HeadOfContent;
			temp->data=value;
			for(int i=0;i<n-1;i++){
				temp->next=std::make_shared< node<T> >();
				temp->next->data=value;
				temp->next->prev=temp;
				temp->next->next=nullptr;
				temp=temp->next;
			}
			_size = n;
		}
		else{
			HeadOfContent=nullptr;
			_size = 0;
		}
	}

	template <class T>
	GTUSet<T>::GTUSet(const GTUSet<T> &obj){

		this->HeadOfContent=std::make_shared< node<T> >();

		std::shared_ptr< node<T> > temp_obj=obj.HeadOfContent;
		std::shared_ptr< node<T> > temp_this=this->HeadOfContent;
		
		if(temp_obj!=nullptr){
			temp_this->data=temp_obj->data;

			temp_obj=temp_obj->next;
		}

		while(temp_obj!=nullptr){
			temp_this->next = std::make_shared< node <T> >();
			temp_this->next->data=temp_obj->data;
			temp_this->next->prev=temp_this;
			temp_this->next->next=nullptr;

			temp_this=temp_this->next;
			temp_obj=temp_obj->next;
		}

	}

	template<class T>
	GTUSet<T>::~GTUSet(){
		std::shared_ptr<node <T> > toDelete;
		while(this->HeadOfContent != nullptr){
			toDelete=this->HeadOfContent;
			this->HeadOfContent=this->HeadOfContent->next;
			toDelete->prev=nullptr;
			toDelete->next=nullptr;
		}
		this->_size=0;
	}

	template<class T>
	bool GTUSet<T>::empty()const{
		if(HeadOfContent == nullptr){
			return true;
		}
		return false;
	}

	template<class T>
	int GTUSet<T>::size()const{
		return _size;
	}

	template<class T>
	int GTUSet<T>::max_size()const{
		return MAX_SIZE;
	}

	template<class T>
	const GTUIterator<T> GTUSet<T>::begin()const{
		return GTUIterator<T>(HeadOfContent);
	}

	template<class T>
	const GTUIterator<T> GTUSet<T>::end()const{

		if(HeadOfContent == nullptr)
			return HeadOfContent;

		std::shared_ptr< node<T> > temp (HeadOfContent);

		while(temp->next != nullptr)
			temp=temp->next;

		return temp;
	}

	template<class T>
	void GTUSet<T>::clear(){
		std::shared_ptr< node<T> > to_delete;
		while(HeadOfContent != nullptr){
			to_delete = HeadOfContent;
			HeadOfContent=HeadOfContent->next;
			to_delete->prev=nullptr;
			to_delete->next=nullptr;
		}
		this->_size=0;
	}
	
	template<class T>
	const GTUIterator<T> GTUSet<T>::erase(const GTUIterator<T> &position){

		GTUIterator<T> temp_iter(HeadOfContent);
		std::shared_ptr< node<T> > temp_head = HeadOfContent;

		while(temp_iter != position){
			temp_head=temp_head->next;
			++temp_iter;
		}

		if(temp_head==nullptr){
			return HeadOfContent;
		}

		else if(temp_head->prev==nullptr && temp_head->next==nullptr){
			HeadOfContent=nullptr;
		}

		else if(temp_head->prev==nullptr){
			HeadOfContent=HeadOfContent->next;
			HeadOfContent->prev->next=nullptr;
			HeadOfContent->prev=nullptr;
		}

		else if(temp_head->next==nullptr){
			temp_head->prev->next=nullptr;
			temp_head->prev=nullptr;
		}

		else{
			temp_head->prev->next=temp_head->next;
			temp_head->next->prev=temp_head->prev;
			temp_head->next=nullptr;
			temp_head->prev=nullptr;
		}

		--_size;

		return HeadOfContent;
	}

	template<class T>
	const GTUIterator<T> GTUSet<T>::erase(const GTUIterator<T> &first,const GTUIterator<T> &last){
		if(first==last)
			return HeadOfContent;

		GTUIterator<T> temp_iter(HeadOfContent);
		std::shared_ptr< node<T> > temp_head_f = HeadOfContent;
		std::shared_ptr< node<T> > temp_head_l = HeadOfContent;

		while(temp_iter != first){
			temp_head_f=temp_head_f->next;
			++temp_iter;
		}
		temp_head_l=temp_head_f;
		while(temp_iter != last){
			temp_head_l=temp_head_l->next;
			++temp_iter;
			--_size;
		}

		if(temp_head_f->prev==nullptr){
			std::shared_ptr< node<T> > temp_to_delete = HeadOfContent;

			HeadOfContent=temp_head_l;
			
			while(temp_to_delete->next != HeadOfContent){
				temp_to_delete=temp_to_delete->next;
				temp_to_delete->prev->next=nullptr;
				temp_to_delete->prev=nullptr;
			}
		}

		else{
			temp_head_f->prev->next=temp_head_l->prev->next;
			temp_head_l->prev->next=nullptr;
			temp_head_l->prev=temp_head_f->prev;
			temp_head_f->prev=nullptr;

			while(temp_head_f->next != nullptr){
				temp_head_f=temp_head_f->next;
				temp_head_f->prev->next=nullptr;
				temp_head_f->prev=nullptr;
			}
		}

		return HeadOfContent;
	}

	template<class T>
	const GTUIterator<T> GTUSet<T>::insert(T val){
		if(_size >= MAX_SIZE){
			exit(1);
		}

		GTUIterator<T> scanit = this->begin();
		while(scanit != this->end()){
			if(*scanit == val){
				return scanit;
			}
			++scanit;
		}
		if(*scanit == val)
			return scanit;

		if(HeadOfContent==nullptr){

			HeadOfContent=std::make_shared< node<T> >();

			HeadOfContent->data=val;
			HeadOfContent->next=nullptr;
			HeadOfContent->prev=nullptr;
			++_size;
			return HeadOfContent;
		}

		std::shared_ptr<node <T> > temp = HeadOfContent;
		
		while(temp->next != nullptr)
			temp=temp->next;

		temp->next = std::make_shared<node <T> >();
		temp->next->data = val;
		temp->next->next = nullptr;
		temp->next->prev = temp;

		++_size;
		return HeadOfContent;
	}

	template<class T>
	const GTUIterator<T> GTUSet<T>::insert(const GTUIterator<T> &position, T val){
		if(_size >= MAX_SIZE){
			exit(1);
		}

		GTUIterator<T> scanit = this->begin();
		while(scanit != this->end()){
			if(*scanit == val){
				return scanit;
			}
			++scanit;
		}
		if(*scanit == val)
			return scanit;

		GTUIterator<T> temp_iter(HeadOfContent);
		std::shared_ptr< node<T> > temp_head=HeadOfContent;

		if(temp_head == nullptr){
			HeadOfContent=std::make_shared< node<T> >();
			HeadOfContent->data=val;
			HeadOfContent->next=nullptr;
			HeadOfContent->prev=nullptr;
			++_size;
			return HeadOfContent;
		}

		while(temp_iter != position){
			temp_head=temp_head->next;
			++temp_iter;
		}

		if(temp_head->next == nullptr){
			temp_head->next = std::make_shared<node <T> >();
			temp_head->next->data = val;
			temp_head->next->next = nullptr;
			temp_head->next->prev = temp_head;
			++_size;
			return HeadOfContent;
		}

		else{
			std::shared_ptr< node<T> > NewNode(new node<T>);
			NewNode->data=val;

			NewNode->prev=temp_head;
			NewNode->next=temp_head->next;

			temp_head->next->prev=NewNode;
			temp_head->next=NewNode;
		}

		++_size;
		return HeadOfContent;
	}

	template<class T>
	GTUSet<T> GTUSet<T>::operator=(const GTUSet<T>& other){
		if(this->_size != other._size){
			this->clear();
		}
		for(int i=0;i<other._size;++i)
			this->insert(other[i]);
		
		return *this; 
	}

}