#ifndef BARRAY1D_HPP
#define BARRAY1D_HPP

#include <iostream>
#include "Board.hpp"

namespace GTU_Board{

	class BoardArray1D : public AbstractBoard{
	public:
		BoardArray1D(int NewRowNumber=3,int NewColumnNumber=3);
		BoardArray1D(const BoardArray1D &obj);
		BoardArray1D& operator=(const BoardArray1D &obj);
		~BoardArray1D();

		int operator()(int index_i,int index_j)const override;

		int& operator()(int index_i,int index_j)override;

		void setsize(const int &newrow,const int &newcolumn)override;
	private:
		int *grid;
	};
}

#endif