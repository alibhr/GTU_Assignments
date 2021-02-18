#include "BArray1D.hpp"

namespace GTU_Board{

	BoardArray1D::BoardArray1D(int NewRowNumber,int NewColumnNumber):AbstractBoard(NewRowNumber,NewColumnNumber){
		//constructor.
		//first allocate the grid.
		grid = new int [RowNumber*ColumnNumber]();
		for(int i=0;i<RowNumber;++i)
			grid[i]=1;
		reset();
	}

	BoardArray1D::BoardArray1D(const BoardArray1D &obj):AbstractBoard(obj){
		//copy constructor.

		//allocate the destination object.
		int size=obj.ColumnNumber * obj.RowNumber;

		this->grid=new int [size];

		//copy all data from this to other.
		for(int i=0;i<size;++i)
			this->grid[i]=obj.grid[i];
	}

	BoardArray1D& BoardArray1D::operator=(const BoardArray1D &obj){
		//assignment operator.
		int size_this = this->RowNumber * this->ColumnNumber;
		int size_obj = obj.RowNumber * obj.ColumnNumber;

		//check the memory allocation for both side and if there is a discrepancy arrange the allocation .
		if(size_this != size_obj){
			delete[] this->grid;
			grid = new int[size_obj];
		}

		//call the base class assignment.
		this->AbstractBoard::operator=(obj);

		//copy the all data from other to this.
		for(int i=0;i<size_obj;++i)
			this->grid[i]=obj.grid[i];

		return *this;
	}

	BoardArray1D::~BoardArray1D(){
		//destructor.
		//free the memory.
		delete[] this->grid;
	}

	int BoardArray1D::operator()(int index_i,int index_j)const{
		//Terminates program if the indexes are not valid.
		if(index_i >= RowNumber || index_j >= ColumnNumber || index_i < 0 || index_j < 0)	std::cout<<"index problem !!\n",exit(1);

		//returns the corresponding cell content of taken indexes.
		int index = index_i * ColumnNumber + index_j;
		return this->grid[index];
	}

	int& BoardArray1D::operator()(int index_i,int index_j){
		//this function also can be used as a setter function in derived class.(this function is protected)

		//Terminates program if the indexes are not valid.
		if(index_i >= RowNumber || index_j >= ColumnNumber || index_i < 0 || index_j < 0)	std::cout<<"index problem !!\n",exit(1);
		
		//returns the corresponding cell content of taken indexes.
		int index = index_i * ColumnNumber + index_j;
		return this->grid[index];
	}

	void BoardArray1D::setsize(const int &newrow,const int &newcolumn){
		//Boards can not be smaller than 3.
		if(newrow < 3 || newcolumn < 3){
			std::cout<<"size can not be smaller than 3\n";
			exit(1);
		}

		//if there is a discrepancy arrange the allocation again.
		if(ColumnNumber != newcolumn || RowNumber != newrow){
			delete[] this->grid;
			this->grid=new int[newcolumn*newrow];
		}

		//assing the other variables.
		ColumnNumber=newcolumn;
		RowNumber=newrow;

		EmptyCell_Y = RowNumber-1;
		EmptyCell_X = ColumnNumber-1;

		reset();
	}
}