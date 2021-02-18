#include "BArray2D.hpp"

namespace GTU_Board{

	BoardArray2D::BoardArray2D(int NewRowNumber,int NewColumnNumber):AbstractBoard(NewRowNumber,NewColumnNumber){
		//constructor.
		//first allocate the grid.
		grid=new int*[RowNumber];

		for(int i=0;i<RowNumber;++i)
			*(grid+i)=new int[ColumnNumber];

		reset();
	}

	BoardArray2D::BoardArray2D(const BoardArray2D &obj):AbstractBoard(obj){
		//copy constructor.

		//allocate the destination object.
		this->grid=new int*[RowNumber];
		for(int i=0;i<RowNumber;++i)
			*(this->grid+i)=new int[ColumnNumber];
		
		//copy all data from this to other.
		for(int i=0;i<RowNumber;++i)
			for(int j=0 ;j<ColumnNumber;++j)
				this->grid[i][j]=obj.grid[i][j];

	}

	BoardArray2D& BoardArray2D::operator=(const BoardArray2D &obj){
		//assignment operator.
		//check the memory allocation for both side and if there is a discrepancy arrange the allocation .
		if(this->RowNumber != obj.RowNumber || this->ColumnNumber!= obj.ColumnNumber){
			for(int i=0;i<this->RowNumber;++i)
				delete[] this->grid[i];

			this->grid=new int*[obj.RowNumber];
			for(int i=0;i<obj.RowNumber;++i)
				*(this->grid+i)=new int[obj.ColumnNumber];
		}

		//call the base class assignment.
		this->AbstractBoard::operator=(obj);

		//copy the all data from other to this.
		for(int i=0;i<RowNumber;++i)
			for(int j=0;j<ColumnNumber;++j)
				this->grid[i][j]=obj.grid[i][j];

		for(int i=0;i<RowNumber;++i)
			for(int j=0;j<ColumnNumber;++j)
				this->grid[i][j]=1;

		return *this;
	}

	BoardArray2D::~BoardArray2D(){
		//destructor.
		//free the memory.
		for(int i=0;i<this->RowNumber;++i){
			delete[] this->grid[i];
		}
	}

	int BoardArray2D::operator()(int index_i,int index_j)const{

		//Terminates program if the indexes are not valid.
		if(index_i >= RowNumber || index_j >= ColumnNumber || index_i < 0 || index_j < 0)	std::cout<<"index problem !!\n",exit(1);

		//returns the corresponding cell content of taken indexes.
		return this->grid[index_i][index_j];
	}

	int& BoardArray2D::operator()(int index_i,int index_j){
		//this function also can be used as a setter function in derived class.(this function is protected)

		//Terminates program if the indexes are not valid.
		if(index_i >= RowNumber || index_j >= ColumnNumber || index_i < 0 || index_j < 0)	std::cout<<"index problem !!\n",exit(1);
		
		//returns the corresponding cell content of taken indexes.
		return this->grid[index_i][index_j];
	}

	void BoardArray2D::setsize(const int &newrow,const int &newcolumn){

		//Boards can not be smaller than 3.
		if(newrow < 3 || newcolumn < 3){
			std::cout<<"size can not be smaller than 3\n";
			exit(1);
		}

		//if there is a discrepancy arrange the allocation again.
		if(ColumnNumber != newcolumn || RowNumber != newrow){
			for(int i=0;i<this->RowNumber;++i){
				delete[] this->grid[i];
			}

			this->grid = new int*[newrow];
			for(int i=0;i<newrow;++i){
				this->grid[i]=new int [newcolumn];
			}
		}

		//assing the other variables.
		ColumnNumber=newcolumn;
		RowNumber=newrow;

		EmptyCell_Y = RowNumber-1;
		EmptyCell_X = ColumnNumber-1;

		reset();
	}
}