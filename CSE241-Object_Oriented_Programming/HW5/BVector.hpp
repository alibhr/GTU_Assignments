#ifndef BVECTOR_HPP
#define BVECTOR_HPP

#include <iostream>
#include <vector>

#include "Board.hpp"
using std::vector;

namespace GTU_Board{

	class BoardVector:public AbstractBoard{
	public:
		BoardVector(int NewRowNumber=3,int NewColumnNumber=3);

		int operator()(int index_i,int index_j)const override;

		int& operator()(int index_i,int index_j)override;

		void setsize(const int &newrow,const int &newcolumn)override;
	private:
		vector< vector<int> > grid;
	};
}

#endif