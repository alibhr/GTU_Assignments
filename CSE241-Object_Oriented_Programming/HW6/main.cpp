#include <iostream>

#include "GTUContainer.hpp"

#include "GTUExceptions.hpp"

#include "node.hpp"

#include "GTUVector.hpp"
#include "GTUVector.cpp"

#include "GTUIterator.hpp"
#include "GTUIterator.cpp"

#include "GTUIteratorConst.hpp"
#include "GTUIteratorConst.cpp"

#include "GlobalFunctions.hpp"
#include "GlobalFunctions.cpp"

#include "GTUSet.hpp"
#include "GTUSet.cpp"

using namespace _GTU_HW_6_;
using namespace std;

template<class T>
bool testfoo(T val){
	return val=="is it okey?";
}

template<class T>
void testfoo1(T val){
	cout<<val<<" ";
}

int main(){

	try{

		GTUVector<string> v1(4,"GTU");//creates 4 elemets which has 0.
		//assing some elemnts.
		v1[1]="MAIN"; 
		v1[2]="TEVAL";
		v1[3]="KARABAS";

		auto iter = v1.begin();

		cout<<"max size of v1 :"<<v1.max_size()<<endl;
		if(!v1.empty()){
			cout<<"This vector is not empty..\n";
			cout<<"size : "<<v1.size()<<endl;

			cout<<"elements of v1 : \n";
			for(iter=v1.begin();iter != v1.end();++iter)
				cout<<*iter<<" size of this word is : "<<iter->size()<<endl;
			cout<<*iter<<" size of this word is : "<<iter->size()<<endl;
		}

		v1.clear();
		if(v1.empty()){
			v1.insert("Hello");
			v1.insert(v1.end(),"Here is END");
		}

		cout<<"elements of v1 : \n";
		for(iter=v1.begin();iter != v1.end();++iter)
			cout<<*iter<<endl;
		cout<<*iter<<endl;

		while(!v1.empty())
			v1.erase(v1.begin());

		cout<<"size : "<<v1.size()<<endl;

		cout<<"--------------------------------------------------------------\n";


		GTUSet<string> s1(1,"Hello");
		auto iter3=s1.begin();
		s1.insert(iter3,"My");
		s1.insert(iter3+1,"Friend");
		s1.insert(iter3+2," !! ");
		s1.insert(s1.end(),"My");
		
		for(iter3=s1.begin();iter3 != s1.end();++iter3)
			cout<<*iter3<<endl;
		cout<<*iter3<<endl;

		while(!s1.empty())
			s1.erase(s1.begin());

		cout<<"max size of s1 :"<<v1.max_size()<<endl;

		s1.clear();

		cout<<"size of s1 : "<<s1.size()<<endl;

		cout<<"--------------------------------------------------------------\n";

		GTUVector<int> Myvector(2);//one element created.2 assind to this element.
		GTUSet<int> MySet(-1);
		GTUIterator<int> myIter;


		Myvector.insert(9);
		Myvector.insert(1905);
		Myvector.insert(95);
		Myvector.insert(19);
		Myvector.insert(99);
		Myvector.insert(199);
		cout<<"size of Myvector : "<<Myvector.size()<<endl;

		MySet.insert(MySet.end(),9);
		MySet.insert(MySet.end(),1905);
		MySet.insert(MySet.end(),95);
		MySet.insert(MySet.end(),19);
		MySet.insert(MySet.end(),99);
		cout<<"size of MySet : "<<MySet.size()<<endl;


		myIter=Myvector.begin();
		for(int i=0;i<Myvector.size()-1;++i){
			cout<<*(++myIter)<<" ";
		}
		cout<<endl;


		myIter=MySet.end();
		for(int i=0;i<MySet.size()-1;++i){
			cout<<*(--myIter)<<" ";
		}
		cout<<endl;

		cout<<"--------------------------------------------------------------\n";

		GTUVector<string> Myvector1(1,"Hello");//one element created.2 assind to this element.
		GTUSet<string> MySet1(1,"Hello");
		GTUIterator<string> myIter1;


		Myvector1.insert("I'm");
		Myvector1.insert("Here");
		Myvector1.insert("is it okey?");
		Myvector1.insert("what do you think about this?");
		Myvector1.insert("99");
		Myvector1.insert("199");
		cout<<"size of Myvector : "<<Myvector1.size()<<endl;

		MySet1.insert(MySet1.end(),"");
		MySet1.insert(MySet1.end(),"1905");
		MySet1.insert(MySet1.end(),"95");
		MySet1.insert(MySet1.end(),"19");
		MySet1.insert(MySet1.end(),"1");
		cout<<"size of MySet : "<<MySet1.size()<<endl;


		auto itasd=find(Myvector1.begin(),Myvector1.end(),"Here");
		cout<<"*it : "<<*itasd<<endl;

		itasd=find_if(Myvector1.begin(),Myvector1.end(),testfoo<string>);
		cout<<"*it : "<<*itasd<<endl;

	//	for_each(Myvector1.begin(),Myvector1.end(),testfoo1<string>);
	}
	catch(const GTUExceptions e){
		exit(1);
	}


	return 0;
}