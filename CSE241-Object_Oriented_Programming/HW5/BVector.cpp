#include "BVector.hpp"

namespace GTU_Board{
	BoardVector::BoardVector(int NewRowNumber,int NewColumnNumber):AbstractBoard(NewRowNumber,NewColumnNumber){
		//constructor.
		//first allocate the grid.
		grid.resize(RowNumber);
		for(int i=0;i<RowNumber;++i)
			grid[i].resize(ColumnNumber);

		for(int i=0;i<RowNumber;++i)
			for(int j=0;j<ColumnNumber;++j)
				this->grid[i][j]=1;
		reset();
	}

	int BoardVector::operator()(int index_i,int index_j)const{
		//Terminates program if the indexes are not valid.
		if(index_i >= RowNumber || index_j >= ColumnNumber || index_i < 0 || index_j < 0)	std::cout<<"index problem !!\n",exit(1);

		//returns the corresponding cell content of taken indexes.
		return grid[index_i][index_j];
	}

	int& BoardVector::operator()(int index_i,int index_j){
		//this function also can be used as a setter function in derived class.(this function is protected)
		
		//Terminates program if the indexes are not valid.
		if(index_i >= RowNumber || index_j >= ColumnNumber || index_i < 0 || index_j < 0)	std::cout<<"index problem !!\n",exit(1);
		
		//returns the corresponding cell content of taken indexes.
		return grid[index_i][index_j];
	}

	void BoardVector::setsize(const int &newrow,const int &newcolumn){
		//Boards can not be smaller than 3.
		if(newrow < 3 || newcolumn < 3){
			std::cout<<"size can not be smaller than 3\n";
			exit(1);
		}

		//if there is a discrepancy arrange the allocation again.
		if(ColumnNumber != newcolumn || RowNumber != newrow){
			this->grid.resize(newrow,vector<int>(newcolumn));
			for(int i=0;i<newrow;++i)
				this->grid[i].resize(newcolumn);
		}

		//assing the other variables.
		ColumnNumber=newcolumn;
		RowNumber=newrow;

		EmptyCell_Y = RowNumber-1;
		EmptyCell_X = ColumnNumber-1;

		reset();
	}
}