#ifndef BARRAY2D_HPP
#define BARRAY2D_HPP

#include <iostream>
#include "Board.hpp"

namespace GTU_Board{
	
	class BoardArray2D : public AbstractBoard{
	public:
		BoardArray2D(int NewRowNumber=3,int NewColumnNumber=3);
		BoardArray2D(const BoardArray2D &obj);
		BoardArray2D& operator=(const BoardArray2D &obj);
		~BoardArray2D();

		int operator()(int index_i,int index_j)const override;

		int& operator()(int index_i,int index_j)override;

		void setsize(const int &newrow,const int &newcolumn)override;
	private:
		int **grid;
	};
}

#endif