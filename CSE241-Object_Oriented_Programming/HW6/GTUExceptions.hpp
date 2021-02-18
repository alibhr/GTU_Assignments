#ifndef GTUEXCEPTIONS_HPP
#define GTUEXCEPTIONS_HPP

#include <iostream>
#include<string>

namespace _GTU_HW_6_{
	class GTUExceptions{
	public:
		GTUExceptions(std::string Newstr="\0"){str=Newstr;}
		virtual ~GTUExceptions(){};

		void what(){std::cout<<str;}
	private:
		std::string str;
	};
}

namespace std{
	class bad_pafram : public _GTU_HW_6_::GTUExceptions{
		bad_pafram(std::string Newstr="bad_pafram"):_GTU_HW_6_::GTUExceptions(Newstr){}
	};
}

#endif