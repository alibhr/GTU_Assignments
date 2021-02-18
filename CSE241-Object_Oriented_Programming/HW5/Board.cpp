#include "Board.hpp"

namespace GTU_Board{

	int AbstractBoard::objectCounter=0;

	//these functions are helper function of isit_ValidSequence.
	//these functions are can not be used in other files.
	bool isit_ValidMove(const AbstractBoard *const board1,const AbstractBoard *const board2);
	int findDifferences(const AbstractBoard *const board1,const AbstractBoard *const board2);

	AbstractBoard::AbstractBoard(int NewRowNumber,int NewColumnNumber):LastMove('S'),TotalMoves(0){
		//increase the conject counter.
		++objectCounter;

		//assign the first values.
		RowNumber=NewRowNumber;
		ColumnNumber=NewColumnNumber;
		if(NewColumnNumber < 3){
			std::cout<<"Column Number can not be smaller than 3.\n";
			std::cout<<"Column Number arranged to 3\n";
			ColumnNumber=3;
		}
		if(NewRowNumber < 3){
			std::cout<<"Row Number can not be smaller than 3.\n";
			std::cout<<"Row Number arranged to 3\n";
			RowNumber=3;
		}
	}

	AbstractBoard::AbstractBoard(const AbstractBoard &obj){
		//copy constructor.

		++this->objectCounter;

		this->LastMove=obj.LastMove;
		this->TotalMoves=obj.TotalMoves;
		this->RowNumber=obj.RowNumber;
		this->ColumnNumber=obj.ColumnNumber;
		this->EmptyCell_X=obj.EmptyCell_X;
		this->EmptyCell_Y=obj.EmptyCell_Y;
	}

	AbstractBoard::~AbstractBoard(){
		//destructor
		--objectCounter;
	}

	void AbstractBoard::print()const{
		//prints the current configuration on the screen by sending it to cout.
		for(int i=0;i<RowNumber;++i){
			for(int j=0;j<ColumnNumber;++j){
				if(this->operator()(i,j)==EMPTYCELL){
					std::cout<<"**\t";
				}
				else if(this->operator()(i,j)==BORDER){
					std::cout<<"  \t"; 
				}
				else{
					std::cout<<this->operator()(i,j)<<"\t";
				}
			}
			std::cout<<"\n\n";
		}
	}

	void AbstractBoard::reset(){
		TotalMoves=0;
		//Resets the current configuration to the solution.
		int i,j;
		int consecutive_numbers=1;

		//init the board with consecutive number but also consider the shape of the grid.
		for(i=0;i<RowNumber;i++){
			for(j=0;j<ColumnNumber;j++){
				if(this->operator()(i,j)!=BORDER){
					this->operator()(i,j)=consecutive_numbers;
					consecutive_numbers++;
				}
			}
		}

		//find the last cell and do it a moveable cell.-1 means moveable cell.
		for(i=ColumnNumber-1;i>=0;i--){
			if(this->operator()(RowNumber-1,i)!=0){
				this->operator()(RowNumber-1,i)=EMPTYCELL;
				i=-1;
			}
		}
	}

	void AbstractBoard::readFromFile(const std::string &fileName){
		//Reads the current configuration from the file given as parameter.
		std::ifstream file;
		std::string temp_s;
		int temp_i;
		int i,j;
		file.open(fileName);
		int Row=find_rowNumber(fileName);
		int Column=find_columnNumber(fileName);
		setsize(Row,Column);
		if(!file.is_open()){
			std::cout<<"file couldn't opened !!!3";
			exit(1);
		}
		//take the cell form file
		for(i=0;i<RowNumber;i++){
			for(j=0;j<ColumnNumber;j++){
				file>>temp_s;
				if(temp_s[0]=='b'){
					this->operator()(i,j)=EMPTYCELL;
					EmptyCell_X=j;
					EmptyCell_Y=i;
				}
				else{
					//i take the data as string so i have to conver it to integer.
					temp_i=convertStringToInteger(temp_s);
					this->operator()(i,j)=temp_i;
				}
			}
		}

		file.close();
	}

	void AbstractBoard::writeToFile(const std::string &fileName)const{
		//Writes the current configuration to the file given as function parameter.
		int i,j;
		std::ofstream file;

		file.open(fileName);
		if(!file.is_open()){
			std::cout<<"file couldn't opened !!!!4";
			exit(1);
		}

		for(i=0;i<RowNumber;i++){
			for(j=0;j<ColumnNumber;j++){
				if(this->operator()(i,j)==EMPTYCELL)
					file<<"bb ";

				else if(this->operator()(i,j)<10)
					file<<"0"<<this->operator()(i,j)<<" ";

				else
					file<<this->operator()(i,j)<<" ";
			}
			file<<std::endl;
		}
		file.close();
	}

	int AbstractBoard::find_columnNumber(const std::string &fileName){
		//count how many spaces in a line in order to find the number of column.

		std::ifstream file;
		char temp;
		int counter=0;

		//open a file to read.
		file.open(fileName);

		if(!file.is_open()){
			std::cout<<"file couldn't opened !1\n";
			exit(1);
		}

		//get a character from file
		temp=file.get();

		//check whether the file empty or not.if the file is empty halt the program.
		if(temp==EOF){
			std::cout<<"file is empty!!\n";
			exit(1);
		}

		//read the file untill the end of the line.
		while(temp!='\n'){
			//if there is a space count it.
			if(temp==' '){
				counter++;
				//there may be more than one space between two column so i ignore the spaces after the space.
				while(temp==' '){
					temp=file.get();

					//if there is space at the end of the line ignore it.
					if(temp=='\n'){
						counter--;
					}
				}
			}

			//get a character from file.
			if(temp!='\n'){
				temp=file.get();
			}

			//count the last space
			if(temp=='\n'){
				counter++;
			}
		}

		//close the file.
		file.close();
		return counter;
	}

	int AbstractBoard::find_rowNumber(const std::string &fileName){
		//count how many '\n' in the file in order to find the number of raw.

		std::ifstream file;
		char temp;
		int counter=0;

		//open a file to read.
		file.open(fileName);
		if(!file.is_open()){
			std::cout<<"file couldn't opened !!2\n";
			exit(1);
		}

		//get a character from file
		temp=file.get();

		//check whether the file empty or not.if the file is empty halt the program.
		if(temp==EOF){
			std::cout<<"file error2.\n";
			exit(1);
		}

		//read the file untill the end of file.
		while(temp != EOF){

			//if there is a '\n' count it.
			if(temp=='\n'){
				counter++;

				//there may be more than one '\n' between two raw so i ignore the raws after the raw.
				while(temp=='\n'){
					temp=file.get();

					//if there is EOF at the end of the file after a '\n' ignore it.
					if(temp==EOF){
						counter--;
					}
				}
			}
			temp=file.get();
			if(temp==EOF){
				counter++;
			}
		}
		
		file.close();
		return counter;
	}

	int AbstractBoard::convertStringToInteger(const std::string &s){
		//opteins integers form string.
		int i,result=0;
		int size=s.size();
		int temp_size=size;
		for(i=0;i<size;i++){
			result+=(s[i]-48)*power(10,temp_size-1);
			temp_size--;
		}
		return result;
	}

	int AbstractBoard::power(const int &base,const int &exp){
		//power(base,exponent)=base^(exponent)

		int result=1;
		int i;
		if(exp==0){
			return 1;
		}
		if(exp < 0){
			std::cout<<"exponent is negative !!\n";
			return 0;
		}
		for(i=0;i<exp;i++){
			result *= base;
		}
		return result;
	}

	bool AbstractBoard::move(const char &direction){
		//Makes a move according to given char parameter.

		if((direction=='R'||direction=='r') && move_to_right()){
			LastMove='R';
			TotalMoves++;
			return true;
		}
		else if((direction=='L'||direction=='l') && move_to_left()){
			LastMove='L';
			TotalMoves++;
			return true;
		}
		else if((direction=='U'||direction=='u') && move_to_up()){
			LastMove='U';
			TotalMoves++;
			return true;
		}
		else if((direction=='D'||direction=='d') && move_to_down()){
			LastMove='D';
			TotalMoves++;
			return true;
		}

		return false;
	}

	bool AbstractBoard::move_to_right(){
		//shifts the empty space to right if there is room.
		if(isitAvaliableCell('R')){
			this->operator()(EmptyCell_Y,EmptyCell_X)=this->operator()(EmptyCell_Y,EmptyCell_X+1);
			this->operator()(EmptyCell_Y,EmptyCell_X+1)=EMPTYCELL;
			EmptyCell_X++;
			return true;
		}
		return false;
	}

	bool AbstractBoard::move_to_left(){
		//shifts the empty space to left if there is room.
		if(isitAvaliableCell('L')){
			this->operator()(EmptyCell_Y,EmptyCell_X)=this->operator()(EmptyCell_Y,EmptyCell_X-1);
			this->operator()(EmptyCell_Y,EmptyCell_X-1)=EMPTYCELL;
			EmptyCell_X--;
			return true;
		}
		return false;
	}

	bool AbstractBoard::move_to_up(){
		//shifts the empty space to up if there is room.
		if(isitAvaliableCell('U')){
			this->operator()(EmptyCell_Y,EmptyCell_X)=this->operator()(EmptyCell_Y-1,EmptyCell_X);
			this->operator()(EmptyCell_Y-1,EmptyCell_X)=EMPTYCELL;
			EmptyCell_Y--;
			return true;
		}
		return false;
	}

	bool AbstractBoard::move_to_down(){
		//shifts the empty space to down if there is room.
		if(isitAvaliableCell('D')){
			this->operator()(EmptyCell_Y,EmptyCell_X)=this->operator()(EmptyCell_Y+1,EmptyCell_X);
			this->operator()(EmptyCell_Y+1,EmptyCell_X)=EMPTYCELL;
			EmptyCell_Y++;
			return true;
		}
		return false;
	}

	bool AbstractBoard::isitAvaliableCell(const char &direction)const{
		//check whether the cell which is the destination is avalible.
		if((direction=='R' || direction=='r')  && EmptyCell_X+1 < ColumnNumber && this->operator()(EmptyCell_Y,EmptyCell_X+1) != BORDER){
			return true;
		}
		else if((direction=='L' || direction=='l') && EmptyCell_X > 0 && this->operator()(EmptyCell_Y,EmptyCell_X-1) != BORDER){
			return true;
		}
		else if((direction=='U' || direction=='u') && EmptyCell_Y > 0 && this->operator()(EmptyCell_Y-1,EmptyCell_X) != BORDER ){
			return true;
		}
		else if((direction=='D' || direction=='d') && EmptyCell_Y+1 < RowNumber && this->operator()(EmptyCell_Y+1,EmptyCell_X) != BORDER){
			return true;
		}
		return false;
	}

	bool AbstractBoard::isSolved()const{
		//check whether the puzzle solved.
		//returns true if the board is a solution.
		int consecutiveNumbers=1;
		int i,j,flag=0;
		for(i=0;i<RowNumber;i++){
			for(j=0;j<ColumnNumber;j++){
				if(this->operator()(i,j)!=consecutiveNumbers && this->operator()(i,j) != BORDER){
					flag++;
				}
				if(this->operator()(i,j) != BORDER){
					consecutiveNumbers++;
				}
			}
		}
		if(flag==1) return true;
		else return false;
	}

	bool AbstractBoard::operator==(const AbstractBoard &other)const{
		//returns if the board are same.
		//This operator just consider the grids.

		int i,j;

		if(this->RowNumber != other.RowNumber)			return false;
		if(this->ColumnNumber != other.ColumnNumber)	return false;

		for(i=0;i<RowNumber;i++){
			for(j=0;j<ColumnNumber;j++){
				if(this->operator()(i,j) != other.operator()(i,j)){
					return false;
				}
			}
		}

		return true;
	}

	//gloabal Functions.
	bool isit_ValidSequence(const AbstractBoard * const * const Sequence,int arraysize){

		//the last element shoul be solved.
		if(!Sequence[arraysize-1]->isSolved())
			return false;

		//last move of the first element should be 'S'
		if( Sequence[0]->lastMove() != 'S' && Sequence[0]->lastMove() != 's')
			return false;

		//look whether all moves valid or not.
		for(int i=0;i<arraysize-1;++i){
			if(!isit_ValidMove(Sequence[i],Sequence[i+1]))
				return false;
		}

		return true;
	}

	bool isit_ValidMove(const AbstractBoard *const board1,const AbstractBoard *const board2){
		char move;
		//this function also consider the last move of the board.
		//there should be two different cell if there is a valid move.

		//if there is a valid move there should be just two differences.
		if(findDifferences(board1,board2) != 2)
			return false;

		//find which move had done.
		if(board1->getEmptyCellX()==board2->getEmptyCellX()){
			if(board1->getEmptyCellY()==1+board2->getEmptyCellY()){
				move='U';
			}
			else{
				move='D';
			}
		}

		if(board1->getEmptyCellY()==board2->getEmptyCellY()){
			if(board1->getEmptyCellX()==1+board2->getEmptyCellX()){
				move='L';
			}
			else{
				move='R';
			}
		}
		
		//last move and move that found in this function should be same.
		if(move != board2->lastMove())
			return false;

		return true;
	}

	int findDifferences(const AbstractBoard *const board1,const AbstractBoard *const board2){
		int counter=0;
		//if their row number or column number different this means they are entirely different.
		if(board1->getRowNumber()!=board2->getRowNumber() || board1->getColumnNumber()!=board2->getColumnNumber())
			return -1;

		//look all cell and find how many different cells there is.
		for(int i=0;i<board1->getRowNumber();++i)
			for(int j=0;j<board1->getColumnNumber();++j)
				if(board1->operator()(i,j) != board2->operator()(i,j))
					++counter;

		return counter;
	}
}