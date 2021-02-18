#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;


//using 'new' was forbidden so ı put a limit and ı have used a static array.
const int MAX_COLUMN=20;
const int MAX_RAW=20;


//these are the all possible inputs and directions.
enum inputs{
	LEFT_MOVE=0,RIGT_MOVE=1,UP_MOVE=2,DOWN_MOVE=3,MAX_DIRECTION=4,INTELLIGENT_MOVE,SHUFFLE,QUIT,SOLVE,PRINT_REPORT,STORE,LOAD,EMPTY
};

void say_hello();
void get_problem_size(ifstream &file,const string fileName,int &columnNumber,int &rawNumber);
void get_problem_size(int &problem_size);
int find_columnNumber(ifstream &file,const string fileName);
int find_rawNumber(ifstream &file,const string fileName);
void initTheBoard(int board[MAX_RAW][MAX_COLUMN],ifstream &file,const string fileName,const int columnNumber,const int rawNumber);
void initTheBoard(int board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber);
void initTheGoalBoard(const int board[MAX_RAW][MAX_COLUMN],int goal_board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber);
int convertStringToInteger(const string s);
int power(const int base,const int exp);
void show_board(const int board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber);
void game(int board[MAX_RAW][MAX_COLUMN],int goal_board[MAX_RAW][MAX_COLUMN], int &columnNumber,int &rawNumber);
void get_input(enum inputs &input);
bool isitAvaliableCell(enum inputs direction,const int board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber);
void find_the_empty_cell(const int board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber,int &x,int &y);
bool move_to_right(int board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber);
bool move_to_left(int board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber);
bool move_to_up(int board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber);
bool move_to_down(int board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber);
void shuffle(int board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber);
bool is_puzzle_solved(const int board[MAX_RAW][MAX_COLUMN],const int goal_board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber);
void do_a_intelligentMove(int board[MAX_RAW][MAX_COLUMN],int goal_board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber,enum inputs &prev_motion);
int calculate_cost(const int board[MAX_RAW][MAX_COLUMN],const int goal_board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber);
enum inputs find_best_direction(int board[MAX_RAW][MAX_COLUMN],int goal_board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber);
bool solve(int board[MAX_RAW][MAX_COLUMN],int goal_board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber,enum inputs &prev_motion,int &total_moves);
void StoreCurrentPuzzle(const int board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber);
void load(int board[MAX_RAW][MAX_COLUMN],int goal_board[MAX_RAW][MAX_COLUMN],int &columnNumber,int &rawNumber);
void random_move(int board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber);

int main(int argc,char const *argv[]){

    //to use read a file
    ifstream file;
    string fileName;
    int columnNumber,rawNumber,i;

    //board is gonna keep the grid of game
    int board[MAX_RAW][MAX_COLUMN];
    int goal_board[MAX_RAW][MAX_COLUMN];

    //To generate a random number from cstdlib
    srand(time(NULL));

    say_hello();

    //if there is arguament more than one then the game will initialise with the given shapefile by user.
    if(argc >= 2){
        fileName=argv[1];
        //Problem size will take from file by reading the file from the given by user.
        get_problem_size(file,fileName,columnNumber,rawNumber);

        //initialising the boards
        initTheBoard(board,file,fileName,columnNumber,rawNumber);
        initTheGoalBoard(board,goal_board,columnNumber,rawNumber);
    }
    else{
        //Take the problem size from user.
        get_problem_size(columnNumber);
        rawNumber=columnNumber;

        //initialising the boards
        initTheBoard(board,columnNumber,rawNumber);
        initTheBoard(goal_board,columnNumber,rawNumber);
        for(i=0;i<1;i++)
            shuffle(board,columnNumber,rawNumber);
    }

    cout<<"Your goal board is:\n";
    show_board(goal_board,columnNumber,rawNumber);
    cout<<"\n\n";

    cout<<"Your inital board is :\n";
    game(board,goal_board,columnNumber,rawNumber);

    cout<<endl;
    return 0;
}

void say_hello(){
	//figlet is used for this type writing.
	cout<<"Hello Welcome to\n"
		<<" _   _           ____  _   _ ___________     _____    ____    _    __  __ _____\n"
		<<"| \\ | |         |  _ \\| | | |__  /__  / |   | ____|  / ___|  / \\  |  \\/  | ____|\n"
		<<"|  \\| |  _____  | |_) | | | | / /  / /| |   |  _|   | |  _  / _ \\ | |\\/| |  _|\n"
		<<"| |\\  | |_____| |  __/| |_| |/ /_ / /_| |___| |___  | |_| |/ ___ \\| |  | | |___\n"
		<<"|_| \\_|         |_|    \\___//____/____|_____|_____|  \\____/_/   \\_\\_|  |_|_____|\n\n\n";	
}

void get_problem_size(ifstream &file,const string fileName,int &columnNumber,int &rawNumber){
    //take the sizes from file.
    columnNumber=find_columnNumber(file,fileName);
    rawNumber=find_rawNumber(file,fileName);

    //There is a limint that can be arranged
    if(columnNumber > MAX_COLUMN){
        cout<<"Size of coulumn can't be greater than MAX_COLUMN\n";
        exit(1);
    }

    if(rawNumber > MAX_RAW){
        cout<<"Size of raw can't be greater than MAX_COLUMN\n";
        exit(1);
    }
}

void get_problem_size(int &problem_size){
	//take input untill taking an appropriate input.
	do{
		cout<<"Please enter the problem size :";
		cin>>problem_size;

		//if there is a invalid input then warn the user
		if(problem_size<3 || problem_size>MAX_COLUMN){
			cout<<"problem size should be beetwen 3-MAX.\n";
		}
	//if there is a invalid input then take one more input form user
	}while(problem_size<3 || problem_size>MAX_COLUMN);
}

int find_columnNumber(ifstream &file,const string fileName){
    //count how many spaces in a line in order to find the number of column.

    char temp;
    int counter=0;

    //open a file to read.
    file.open(fileName);
    if(!file.is_open()){
        cout<<"file couldn't opened !1\n";
        exit(1);
    }
    //get a character from file
    temp=file.get();

    //check whether the file empty or not.if the file is empty halt the program.
    if(temp==EOF){
        cout<<"file error1.\n";
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

int find_rawNumber(ifstream &file,const string fileName){
    //count how many '\n' in the file in order to find the number of raw.
    char temp;
    int counter=0;

    //open a file to read.
    file.open(fileName);
    if(!file.is_open()){
        cout<<"file couldn't opened !!2\n";
        exit(1);
    }

     //get a character from file
    temp=file.get();

    //check whether the file empty or not.if the file is empty halt the program.
    if(temp==EOF){
        cout<<"file error2.\n";
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

void initTheBoard(int board[MAX_RAW][MAX_COLUMN],ifstream &file,const string fileName,const int columnNumber,const int rawNumber){
    //init the board from file.
    string temp_s;
    int temp_i;
    int i,j;

    file.open(fileName);
    if(!file.is_open()){
        cout<<"file couldn't opened !!!3";
        exit(1);
    }

    //take the cell form file
    for(i=0;i<rawNumber;i++){
        for(j=0;j<columnNumber;j++){
            file>>temp_s;
            if(temp_s[0]=='b'){
                board[i][j]=-1;
            }
            else{
                //i take the data as string so i have to conver it to integer.
                temp_i=convertStringToInteger(temp_s);
                board[i][j]=temp_i;
            }
        }
    }

    file.close();
}

void initTheBoard(int board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber){
    int i,j;
    int consecutive_numbers=1;

    //init the board with consecutive number.
    for(i=0;i<rawNumber;i++){
        for(j=0;j<columnNumber;j++){
            board[i][j]=consecutive_numbers;
            consecutive_numbers++;
        }
    }
    //put the moveable cell end of the grid.
    board[rawNumber-1][columnNumber-1]=-1;
}

void initTheGoalBoard(const int board[MAX_RAW][MAX_COLUMN],int goal_board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber){
    int i,j;
    int consecutive_numbers=1;

    //init the board with consecutive number but also consider the shape of the grid.
    for(i=0;i<rawNumber;i++){
        for(j=0;j<columnNumber;j++){
            //0 means empty cell
            if(board[i][j]==0){
                goal_board[i][j]=0;
            }
            else{
                goal_board[i][j]=consecutive_numbers;
                consecutive_numbers++;
            }
        }
    }
    //find the last cell and do it a moveable cell.-1 means moveable cell.
    for(i=columnNumber-1;i>=0;i--){
        if(goal_board[rawNumber-1][i]!=0){
            goal_board[rawNumber-1][i]=-1;
            i=-1;
        }
    }
}

int convertStringToInteger(const string s){
    int i,result=0;
    int size=s.size();
    int temp_size=size;
    for(i=0;i<size;i++){
        result+=(s[i]-48)*power(10,temp_size-1);
        temp_size--;
    }
    return result;
}

int power(const int base,const int exp){
    //power(base,exponent)=base^(exponent)

    int result=1;
    int i;
    if(exp==0){
        return 1;
    }
    if(exp < 0){
        cout<<"exponent is negative !!\n";
        return 0;
    }
    for(i=0;i<exp;i++){
        result *= base;
    }
    return result;
}

void show_board(const int board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber){
    int i,j;

    //print the game grid on the terminal.
    for(i=0;i<rawNumber;i++){
        for(j=0;j<columnNumber;j++){
            if(board[i][j]==-1){
                cout<<"**\t";
            }
            else if(board[i][j]==0){
               cout<<"  \t"; 
            }
            else{
                cout<<board[i][j]<<"\t";
            }
        }
        cout<<"\n\n";
    }
}

void game(int board[MAX_RAW][MAX_COLUMN],int goal_board[MAX_RAW][MAX_COLUMN], int &columnNumber,int &rawNumber){
    //condition of main game loop
    bool quit=false;

	//to get input from user
    enum inputs input;

    //To report how many move have done 
    int total_moves=0;

    //ı need to keep the previous move
    enum inputs prev_motion=EMPTY;

    //The puzzle which is solved can be come first so i check this situation.
    if(is_puzzle_solved(board,goal_board,columnNumber,rawNumber)){
        show_board(board,columnNumber,rawNumber);
        cout<<"Problem Solved!\n"
		    <<"Total number of moves "<<total_moves<<endl;
		return;
    }
    
    //main game loop.
    while(!quit){
        show_board(board,columnNumber,rawNumber);

        cout<<"Your move:";
		get_input(input);

        //consider the input and do sometihng according to input
        switch(input){
			case RIGT_MOVE:
				if(move_to_right(board,columnNumber,rawNumber)){
                    prev_motion=EMPTY;
					total_moves++;
				}					
				break;
			case LEFT_MOVE:
				if(move_to_left(board,columnNumber,rawNumber)){
                    prev_motion=EMPTY;
					total_moves++;
				}
				break;
			case UP_MOVE:
				if(move_to_up(board,columnNumber,rawNumber)){
                    prev_motion=EMPTY;
					total_moves++;
				}
				break;
			case DOWN_MOVE:
				if(move_to_down(board,columnNumber,rawNumber)){
                    prev_motion=EMPTY;
					total_moves++;
				}
				break;
			case INTELLIGENT_MOVE:
                do_a_intelligentMove(board,goal_board,columnNumber,rawNumber,prev_motion);
                total_moves++;
				break;
			case SHUFFLE:
                initTheGoalBoard(goal_board,board,columnNumber,rawNumber);
                shuffle(board,columnNumber,rawNumber);
                total_moves=0;
				break;
			case QUIT:
				quit=true;
				break;
            case SOLVE:
                if(solve(board,goal_board,columnNumber,rawNumber,prev_motion,total_moves)){
			        quit=true;  
                }
                break;
            case PRINT_REPORT:
                cout<<"Total number of moves : "<<total_moves<<endl;
                if(is_puzzle_solved(board,goal_board,columnNumber,rawNumber)){
                    cout<<"puzzle SOLVED !\n";
                }
                break;
            case STORE:
                StoreCurrentPuzzle(board,columnNumber,rawNumber);
                break;
            case LOAD:
                load(board,goal_board,columnNumber,rawNumber);
                total_moves=0;
                break;
			default:
				cout<<"invalid selection!!\n";
				break;
		}
        //check whether the game is solved
        if(is_puzzle_solved(board,goal_board,columnNumber,rawNumber)){
            cout<<"Problem Solved!\n"
			    <<"Total number of moves "<<total_moves<<endl;
			quit=true;
            show_board(board,columnNumber,rawNumber);
        }
    }
}

void get_input(enum inputs &input){
	char temp;

	//this flag is used for loop,if there is invalid input the loop will be continue
	int flag=0;

	//take input untill taking an appropriate input.
	do{
		cin>>temp;
		if(temp=='R' || temp=='r')	input=RIGT_MOVE;
		else if(temp=='L' || temp=='l')	input=LEFT_MOVE,flag=0;
		else if(temp=='U' || temp=='u')	input=UP_MOVE,flag=0;
		else if(temp=='D' || temp=='d')	input=DOWN_MOVE,flag=0;
		else if(temp=='S' || temp=='s')	input=SHUFFLE,flag=0;
		else if(temp=='I' || temp=='i') input=INTELLIGENT_MOVE,flag=0;
		else if(temp=='Q' || temp=='q')	input=QUIT,flag=0;
        else if(temp=='V' || temp=='v') input=SOLVE,flag=0;
        else if(temp=='T' || temp=='t') input=PRINT_REPORT,flag=0;
        else if(temp=='E' || temp=='e') input=STORE,flag=0;
        else if(temp=='Y' || temp=='y') input=LOAD,flag=0;
		else cout<<"invalid selection,try again !! :",flag=1;
	}while(flag);
}

bool isitAvaliableCell(enum inputs direction,const int board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber){
    int x,y;
    //find the moveable cell.
    find_the_empty_cell(board,columnNumber,rawNumber,x,y);

    //check whether the mooveable cell can go to this direction. 
    if(direction==RIGT_MOVE && x+1 < columnNumber && board[y][x+1]!=0){
        return true;
    }
    else if(direction==LEFT_MOVE && x > 0 && board[y][x-1]!=0){
        return true;
    }
    else if(direction==UP_MOVE && y > 0 && board[y-1][x]!=0){
        return true;
    }
    else if(direction==DOWN_MOVE && y+1 < rawNumber && board[y+1][x]!=0){
        return true;
    }
    return false;
}

void find_the_empty_cell(const int board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber,int &x,int &y){
	//Before the motion we have to know where empty cell is
	int i,j;
	for(i=0;i<rawNumber;i++){
		for(j=0;j<columnNumber;j++){
			//scan all board and if there is 0 it means there is empty area
			if(board[i][j]==-1){
				x=j;
				y=i;
			}
		}
	}
}

bool move_to_right(int board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber){
    //moves the empty cell right if there is room
    int x,y;
    find_the_empty_cell(board,columnNumber,rawNumber,x,y);
    if(isitAvaliableCell(RIGT_MOVE,board,columnNumber,rawNumber)){
        //swap empty area and the value which stand on right side
        board[y][x]=board[y][x+1];
	    board[y][x+1]=-1;
		//if motion is done correctly return true value
        return true;
    }
    return false;
}

bool move_to_left(int board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber){
    //moves the empty cell left if there is room
    int x,y;
    find_the_empty_cell(board,columnNumber,rawNumber,x,y);
    if(isitAvaliableCell(LEFT_MOVE,board,columnNumber,rawNumber)){
        board[y][x]=board[y][x-1];
	    board[y][x-1]=-1;
        return true;
    }
    return false;
}

bool move_to_up(int board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber){
    //moves the empty cell up if there is room
    int x,y;
    find_the_empty_cell(board,columnNumber,rawNumber,x,y);
    if(isitAvaliableCell(UP_MOVE,board,columnNumber,rawNumber)){
        board[y][x]=board[y-1][x];
	    board[y-1][x]=-1;
        return true;
    }
    return false;
}

bool move_to_down(int board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber){
    //moves the empty cell down if there is room
    int x,y;
    find_the_empty_cell(board,columnNumber,rawNumber,x,y);
    if(isitAvaliableCell(DOWN_MOVE,board,columnNumber,rawNumber)){
        board[y][x]=board[y+1][x];
	    board[y+1][x]=-1;
        return true;
    }
    return false;
}

void shuffle(int board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber){
	int i,j,x,y;

	//we have to know where empty cell to make a move
	find_the_empty_cell(board,columnNumber,rawNumber,x,y);

	//do randome move problem_size*problem_size times 
	for(i=0;i<columnNumber*rawNumber;i++){
		j=rand()%4;
		find_the_empty_cell(board,columnNumber,rawNumber,x,y);
		if(j==0 && isitAvaliableCell(RIGT_MOVE,board,columnNumber,rawNumber))	           	move_to_right(board,columnNumber,rawNumber);
		else if(j==1 && isitAvaliableCell(LEFT_MOVE,board,columnNumber,rawNumber))			move_to_left(board,columnNumber,rawNumber);
		else if(j==2 && isitAvaliableCell(UP_MOVE,board,columnNumber,rawNumber))			move_to_up(board,columnNumber,rawNumber);
		else if(j==3 && isitAvaliableCell(DOWN_MOVE,board,columnNumber,rawNumber))          move_to_down(board,columnNumber,rawNumber);

		//if there is no valid random move then provide the loop keep continue one more
		else i--;
	}
}

bool is_puzzle_solved(const int board[MAX_RAW][MAX_COLUMN],const int goal_board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber){
	//check whether the puzzle is solved
	int i,j;

	for(i=0;i<rawNumber;i++){
		for(j=0;j<columnNumber;j++){
			if(board[i][j] != goal_board[i][j]){
				return false;
			}
		}
	}
	return true;
}

void do_a_intelligentMove(int board[MAX_RAW][MAX_COLUMN],int goal_board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber,enum inputs &prev_motion){

    //find the best direction and do a move
    enum inputs best_direction=find_best_direction(board,goal_board,columnNumber,rawNumber);

    if(best_direction==RIGT_MOVE && prev_motion != LEFT_MOVE){
        prev_motion=RIGT_MOVE;
        move_to_right(board,columnNumber,rawNumber);
        cout<<"Intelligent move chooses R\n";
    }
    else if(best_direction==LEFT_MOVE && prev_motion != RIGT_MOVE){
        prev_motion=LEFT_MOVE;
        move_to_left(board,columnNumber,rawNumber);
        cout<<"Intelligent move chooses L\n";
    }
    else if(best_direction==UP_MOVE && prev_motion != DOWN_MOVE){
        prev_motion=UP_MOVE;
        move_to_up(board,columnNumber,rawNumber);
        cout<<"Intelligent move chooses U\n";
    }
    else if(best_direction==DOWN_MOVE && prev_motion != UP_MOVE){
        prev_motion=DOWN_MOVE;
        move_to_down(board,columnNumber,rawNumber);
        cout<<"Intelligent move chooses D\n";
    }
    //if two intelligent move is same do a random move.
    else{
        random_move(board,columnNumber,rawNumber);
    }
}

enum inputs find_best_direction(int board[MAX_RAW][MAX_COLUMN],int goal_board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber){
    int cost,min_cost,costs[MAX_DIRECTION];
    int i,r,equalCostCounter=1;
    enum inputs best_direction=EMPTY,equalCosts[MAX_DIRECTION];

    for(i=0;i<MAX_DIRECTION;i++){
        equalCosts[i]=EMPTY;
        costs[i]=-1;
    }

    //calculate the costs and find which direction has the min cost.
    if(isitAvaliableCell(RIGT_MOVE,board,columnNumber,rawNumber)){
        move_to_right(board,columnNumber,rawNumber);
        cost=calculate_cost(board,goal_board,columnNumber,rawNumber);
        move_to_left(board,columnNumber,rawNumber);

        costs[RIGT_MOVE]=cost;
        min_cost=cost;
        best_direction=RIGT_MOVE;
    }
    if(isitAvaliableCell(LEFT_MOVE,board,columnNumber,rawNumber)){
        move_to_left(board,columnNumber,rawNumber);
        cost=calculate_cost(board,goal_board,columnNumber,rawNumber);
        move_to_right(board,columnNumber,rawNumber);

        costs[LEFT_MOVE]=cost;
        if(cost < min_cost){
            min_cost=cost;
            best_direction=LEFT_MOVE;
        }
    }
    if(isitAvaliableCell(UP_MOVE,board,columnNumber,rawNumber)){
        move_to_up(board,columnNumber,rawNumber);
        cost=calculate_cost(board,goal_board,columnNumber,rawNumber);
        move_to_down(board,columnNumber,rawNumber);

        costs[UP_MOVE]=cost;
        if(cost < min_cost){
            min_cost=cost;
            best_direction=UP_MOVE;
        }

    }
    if(isitAvaliableCell(DOWN_MOVE,board,columnNumber,rawNumber)){
        move_to_down(board,columnNumber,rawNumber);
        cost=calculate_cost(board,goal_board,columnNumber,rawNumber);
        move_to_up(board,columnNumber,rawNumber);

        costs[DOWN_MOVE]=cost;
        if(cost < min_cost){
            min_cost=cost;
            best_direction=DOWN_MOVE;
        }
    }

    //check whether there is a same cost with min cost.
    for(i=0;i<MAX_DIRECTION;i++){
        if(min_cost==costs[i]){
            equalCosts[i]=(enum inputs)i;
            equalCostCounter++;
        }
    }
    if(equalCostCounter==0){
        equalCostCounter=1;
    }
    r=rand()%equalCostCounter;

    //if there is same cost select one of the directions randomly.
    for(i=0;i<MAX_DIRECTION;i++){
        while(equalCosts[i]==EMPTY){
            i++;
            r++;
        }
        if(i==r){
            return equalCosts[i];
        }
    }

    return best_direction;
}

int calculate_cost(const int board[MAX_RAW][MAX_COLUMN],const int goal_board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber){
    int i,j;
	int cost=0;
	
	//if the number is not in the position where it should be in then the cost increase one
	for(i=0;i<rawNumber;i++){
		for(j=0;j<columnNumber;j++){
			if(board[i][j]!=goal_board[i][j]){
				cost++;
			}
		}
	}
	return cost;
}

bool solve(int board[MAX_RAW][MAX_COLUMN],int goal_board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber,enum inputs &prev_motion,int &total_moves){
    int step=0;
    //do intelligent move untill the puzzle solve
    while(!is_puzzle_solved(board,goal_board,columnNumber,rawNumber)){
        do_a_intelligentMove(board,goal_board,columnNumber,rawNumber,prev_motion);
        total_moves++;
        //show the every step
        show_board(board,columnNumber,rawNumber);
        cout<<step++<<endl;
    }
    return true;
}

void StoreCurrentPuzzle(const int board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber){
    //Write the current puzzle to a file
    int i,j;
    ofstream file;
    string fileNameToStore;

    cout<<"File Name: ";
    cin>>fileNameToStore;

    file.open(fileNameToStore);
    if(!file.is_open()){
        cout<<"file couldn't opened !!!!4";
        exit(1);
    }

    for(i=0;i<rawNumber;i++){
        for(j=0;j<columnNumber;j++){
            if(board[i][j]==-1)
                file<<"bb ";

            else if(board[i][j]<10)
                file<<"0"<<board[i][j]<<" ";

            else
                file<<board[i][j]<<" ";
        }
        file<<endl;
    }

    file.close();
}

void load(int board[MAX_RAW][MAX_COLUMN],int goal_board[MAX_RAW][MAX_COLUMN],int &columnNumber,int &rawNumber){

    //take the new game grid from file.

    string ShapeFileName;
    ifstream fileToLoad;

    cout<<"Enter a file name : ";
    cin>>ShapeFileName;

    columnNumber=find_columnNumber(fileToLoad,ShapeFileName);
    rawNumber=find_rawNumber(fileToLoad,ShapeFileName);

    initTheBoard(board,fileToLoad,ShapeFileName,columnNumber,rawNumber);
    initTheGoalBoard(board,goal_board,columnNumber,rawNumber);

    cout<<"Your new goal board is :\n";
    show_board(goal_board,columnNumber,rawNumber);
    cout<<"\n\n";

    cout<<"Your new board is :\n";
}

void random_move(int board[MAX_RAW][MAX_COLUMN],const int columnNumber,const int rawNumber){
    int r;
    bool flag=false;
    //take a random number and do a random move according to random number.
    while(!flag){
        r=rand()%4;
        if(r==1){
            flag=move_to_right(board,columnNumber,rawNumber);
            cout<<"Intelligent move chooses R\n";
        }
        else if(r==2){
            flag=move_to_left(board,columnNumber,rawNumber);
            cout<<"Intelligent move chooses L\n";
        }
        else if(r==3){
            flag=move_to_up(board,columnNumber,rawNumber);
            cout<<"Intelligent move chooses U\n";
        }
        else if(r==4){
            flag=move_to_down(board,columnNumber,rawNumber);
            cout<<"Intelligent move chooses D\n";
        }
    }
}