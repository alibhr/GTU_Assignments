#include <iostream>
#include <cstdlib>
#include <ctime>

//I am gonna use just these stuff from namespace std.
using std::cin;
using std::cout;
using std::endl;

//Problem siz can be max 9
const int MAX_SIZE=9;

//these are the all possible inputs
enum inputs{
	LEFT_MOVE,RIGT_MOVE,UP_MOVE,DOWN_MOVE,INTELLIGENT_MOVE,SHUFFLE,QUIT,EMPTY
};

//To use for idex of costs array
enum costs_E{
	COST_R,COST_L,COST_U,COST_D,EMPTY_c
};

void say_hello();
void get_problem_size(int *problem_size);
void init_the_board(int board[MAX_SIZE][MAX_SIZE],int problem_size);
void take_theboard_to_finalsolution(int board[MAX_SIZE][MAX_SIZE], int problem_size);
void find_the_empty_cell(int board[MAX_SIZE][MAX_SIZE], int problem_size,int *x,int *y);
bool move_to_right(int board[MAX_SIZE][MAX_SIZE], int problem_size,int x,int y);
bool move_to_left(int board[MAX_SIZE][MAX_SIZE], int problem_size,int x,int y);
bool move_to_up(int board[MAX_SIZE][MAX_SIZE], int problem_size,int x,int y);
bool move_to_down(int board[MAX_SIZE][MAX_SIZE], int problem_size,int x,int y);
void shuffle(int board[MAX_SIZE][MAX_SIZE], int problem_size);
void game(int board[MAX_SIZE][MAX_SIZE],int goal_board[MAX_SIZE][MAX_SIZE], int problem_size);
void show_board(int board[MAX_SIZE][MAX_SIZE],int problem_size);
void get_input(enum inputs *input);
void do_a_intelligentMove(int board[MAX_SIZE][MAX_SIZE],int goal_board[MAX_SIZE][MAX_SIZE],int problem_size,int x,int y,enum inputs *prev_motion);
int calculate_cost(int board[MAX_SIZE][MAX_SIZE],int goal_board[MAX_SIZE][MAX_SIZE],int problem_size);
bool is_puzzle_solved(int board[MAX_SIZE][MAX_SIZE],int goal_board[MAX_SIZE][MAX_SIZE], int problem_size);
void free_the_board(int board[MAX_SIZE][MAX_SIZE],int problem_size);


int main(){

	//board is gonna keep the grid of game
	int board[MAX_SIZE][MAX_SIZE];
	int goal_board[MAX_SIZE][MAX_SIZE];

	//board is gonna be square and size is gonna be adjustable by user
	int problem_size;

	//To generate a random number from cstdlib
	srand(time(NULL));

	//The game is getting started by saying hello
	say_hello();

	//Getting the problem size of game from user
	get_problem_size(&problem_size);

	//create and fill the gola board,purpose of this game is in the goal board 
	take_theboard_to_finalsolution(goal_board,problem_size);

	//initialising the board
	init_the_board(board,problem_size);

	//first showing of map
	cout<<"Your inital board is :\n";

	//main game loop
	game(board,goal_board,problem_size);

	//clean the things remain from game in ram
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

void get_problem_size(int *problem_size){
	//take input untill taking an appropriate input.
	do{
		cout<<"Please enter the problem size :";
		cin>>*problem_size;

		//if there is a invalid input then warn the user
		if(*problem_size<3 || *problem_size>9){
			cout<<"problem size should be beetwen 3-9.\n";
		}
	//if there is a invalid input then take one more input form user
	}while(*problem_size<3 || *problem_size>9);
}

void init_the_board(int board[MAX_SIZE][MAX_SIZE],int problem_size){

	//To obtein the first random solveable problem
	take_theboard_to_finalsolution(board,problem_size);

	//Do random moves problem_size*problem_size
	shuffle(board,problem_size);
}

void take_theboard_to_finalsolution(int board[9][9], int problem_size){

	int i,j;
	for(i=0;i<problem_size;i++){
		for(j=0;j<problem_size;j++){
			//'1+j+i*problem_size' this statement is calculating what value should be in board[i][j]
			board[i][j]=1+j+i*problem_size;
		}
	}
	//0 means empty area and it should be in the end
	board[problem_size-1][problem_size-1]=0;
}

void find_the_empty_cell(int board[MAX_SIZE][MAX_SIZE], int problem_size,int *x,int *y){
	//Before the motion we have to know where empty cell is
	int i,j;
	for(i=0;i<problem_size;i++){
		for(j=0;j<problem_size;j++){
			//scan all board and if there is 0 it means there is empty area
			if(board[i][j]==0){
				*x=j;
				*y=i;
			}
		}
	}
}

bool move_to_right(int board[MAX_SIZE][MAX_SIZE], int problem_size,int x,int y){
	//moves the empty cell right if there is room
	if(x+1 < problem_size){
		//swap empty area and the value which stand on right side
		board[y][x]=board[y][x+1];
		board[y][x+1]=0;
		//if motion is done correctly return true value
		return true;
	}
	else{
		//warn the user if there is no room in selection direction
		cout<<"invalid selection\n";
		return false;
	}
}

bool move_to_left(int board[MAX_SIZE][MAX_SIZE], int problem_size,int x,int y){
	//moves the empty cell left if there is room
	if(x > 0){
		//swap empty area and the value which stand on left side
		board[y][x]=board[y][x-1];
		board[y][x-1]=0;

		return true;
	}
	else{
		//warn the user if there is no room in selection direction
		cout<<"invalid selection\n";
		return false;
	}
}

bool move_to_up(int board[MAX_SIZE][MAX_SIZE], int problem_size,int x,int y){
	//moves the empty cell up if there is room
	if(y > 0){
		//swap empty area and the value which stand on up side
		board[y][x]=board[y-1][x];
		board[y-1][x]=0;
		return true;
	}
	else{
		//warn the user if there is no room in selection direction
		cout<<"invalid selection\n";
		return false;
	}
}

bool move_to_down(int board[MAX_SIZE][MAX_SIZE], int problem_size,int x,int y){
	//moves the empty cell down if there is room
	if(y+1<problem_size){
		//swap empty area and the value which stand on down side
		board[y][x]=board[y+1][x];
		board[y+1][x]=0;
		return true;
	}
	else{
		//warn the user if there is no room in selection direction
		cout<<"invalid selection\n";
		return false;
	}
}

void shuffle(int board[MAX_SIZE][MAX_SIZE], int problem_size){
	int i,j,x,y;

	//we have to know where empty cell to make a move
	find_the_empty_cell(board,problem_size,&x,&y);

	//do randome move problem_size*problem_size times 
	for(i=0;i<problem_size*problem_size;i++){
		j=rand()%4;
		find_the_empty_cell(board,problem_size,&x,&y);
		if(j==0 && x!=problem_size-1)		move_to_right(board,problem_size,x,y);
		else if(j==1 && x!=0)				move_to_left(board,problem_size,x,y);
		else if(j==2 && y!=0)				move_to_up(board,problem_size,x,y);
		else if(j==3 && y!=problem_size-1)	move_to_down(board,problem_size,x,y);

		//if there is no valid random move then provide the loop keep continue one more
		else								i--;
	}
}

void game(int board[MAX_SIZE][MAX_SIZE],int goal_board[MAX_SIZE][MAX_SIZE], int problem_size){
	//condition of main game loop
	bool quit=false;

	//to get input from user
	enum inputs input;

	//x and y keeps coordinates of the empty cell
	int x,y,total_moves=0;

	//ı need to keep the previous move
	enum inputs prev_motion=EMPTY;

	//main game loop
	while(!quit){
		show_board(board,problem_size);
		cout<<"Your move:";
		get_input(&input);
		//Finding where empty cell is
		find_the_empty_cell(board,problem_size,&x,&y);

		//consider the input and do sometihng according to input
		switch(input){
			case RIGT_MOVE:
				if(move_to_right(board,problem_size,x,y)){
					total_moves++;
					prev_motion=RIGT_MOVE;
				}					
				break;
			case LEFT_MOVE:
				if(move_to_left(board,problem_size,x,y)){
					total_moves++;
					prev_motion=LEFT_MOVE;
				}
				break;
			case UP_MOVE:
				if(move_to_up(board,problem_size,x,y)){
					total_moves++;
					prev_motion=UP_MOVE;
				}
				break;
			case DOWN_MOVE:
				if(move_to_down(board,problem_size,x,y)){
					total_moves++;
					prev_motion=DOWN_MOVE;
				}
				break;
			case INTELLIGENT_MOVE:
				do_a_intelligentMove(board,goal_board,problem_size,x,y,&prev_motion);
				total_moves++;
				break;
			case SHUFFLE:
				prev_motion=EMPTY;
				take_theboard_to_finalsolution(board,problem_size);
				shuffle(board,problem_size);
				total_moves=0;
				break;
			case QUIT:
				quit=true;
				break;
			default:
				cout<<"invalid selection!!\n";
				break;
		}
		//check whether the game is done
		if(is_puzzle_solved(board,goal_board,problem_size)){
			prev_motion=EMPTY;
			cout<<"Problem Solved!\n"
				<<"Total number of moves "<<total_moves<<endl;
			quit=true;
		}
	}
}

void show_board(int board[MAX_SIZE][MAX_SIZE],int problem_size){
	//print the game map
	int i,j;
	for(i=0;i<problem_size;i++){
		for(j=0;j<problem_size;j++){
			if(board[i][j]==0){
				//if there is 0 it means there is empty space
				//there is tab between every number
				cout<<" \t";
			}
			else{
				cout<<board[i][j]
				//there is tab between every number
				<<"\t";
			}
		}
		//go to next line to seperate the rows
		cout<<endl<<endl;
	}
}

void get_input(enum inputs *input){
	char temp;

	//this flag is used for loop,if there is invalid input the loop will be continue
	int flag=0;

	//take input untill taking an appropriate input.
	do{
		cin>>temp;
		if(temp=='R' || temp=='r')	*input=RIGT_MOVE;
		else if(temp=='L' || temp=='l')	*input=LEFT_MOVE;
		else if(temp=='U' || temp=='u')	*input=UP_MOVE;
		else if(temp=='D' || temp=='d')	*input=DOWN_MOVE;
		else if(temp=='S' || temp=='s')	*input=SHUFFLE;
		else if(temp=='I' || temp=='i') *input=INTELLIGENT_MOVE;
		else if(temp=='Q' || temp=='q')	*input=QUIT;
		else cout<<"invalid selection!!\n",flag=1;
	}while(flag);
}

void do_a_intelligentMove(int board[MAX_SIZE][MAX_SIZE],int goal_board[MAX_SIZE][MAX_SIZE],int problem_size,int x,int y,enum inputs *prev_motion){
	int i=0,min=problem_size*problem_size;
	int costs[5]={0,0,0,0,0};
	enum costs_E min_c=EMPTY_c;
	//if the empty area can go to right
	if(x+1<problem_size){

		//move to right to calculate the cost
		move_to_right(board,problem_size,x,y);

		//calculate the cost 
		costs[COST_R]=calculate_cost(board,goal_board,problem_size);

		//turn back,we are gonna consider the all costs when we calculate the all costs
		find_the_empty_cell(board,problem_size,&x,&y);
		move_to_left(board,problem_size,x,y);
		find_the_empty_cell(board,problem_size,&x,&y);

		//arrange the min cost as a move of right ,this situation can be changed later
		min_c=COST_R,min=costs[COST_R];
	}

	if(x>0){
		//move to left to calculate the cost
		move_to_left(board,problem_size,x,y);

		//calculate the cost 
		costs[COST_L]=calculate_cost(board,goal_board,problem_size);

		//turn back,we are gonna consider the all costs when we calculate the all costs
		find_the_empty_cell(board,problem_size,&x,&y);
		move_to_right(board,problem_size,x,y);
		find_the_empty_cell(board,problem_size,&x,&y);

		//if there is smaller cost then arrange it as a min cost
		if(min>costs[COST_L]){
			min=costs[COST_L],min_c=COST_L;
		}
	}

	if(y>0){
		//move to up to calculate the cost
		move_to_up(board,problem_size,x,y);

		//calculate the cost 
		costs[COST_U]=calculate_cost(board,goal_board,problem_size);

		//turn back,we are gonna consider the all costs when we calculate the all costs
		find_the_empty_cell(board,problem_size,&x,&y);
		move_to_down(board,problem_size,x,y);
		find_the_empty_cell(board,problem_size,&x,&y);

		//if there is smaller cost then arrange it as a min cost
		if(min>costs[COST_U]){
			min=costs[COST_U],min_c=COST_U;
		}
	}

	if(y+1<problem_size){
		//move to down to calculate the cost
		move_to_down(board,problem_size,x,y);

		//calculate the cost 
		costs[COST_D]=calculate_cost(board,goal_board,problem_size);

		//turn back,we are gonna consider the all costs when we calculate the all costs
		find_the_empty_cell(board,problem_size,&x,&y);
		move_to_up(board,problem_size,x,y);
		find_the_empty_cell(board,problem_size,&x,&y);

		//if there is smaller cost then arrange it as a min cost
		if(min>costs[COST_D]){
			min_c=COST_D;
		}
	}

	//Do the motion according to min cost and previous motion
	find_the_empty_cell(board,problem_size,&x,&y);
	if(min_c==COST_R && *prev_motion != LEFT_MOVE){
		cout<<"Intelligent move chooses R\n";
		move_to_right(board,problem_size,x,y);
		*prev_motion=RIGT_MOVE;
	}			
	else if(min_c==COST_L && *prev_motion != RIGT_MOVE){
		cout<<"Intelligent move chooses L\n";
		move_to_left(board,problem_size,x,y);
		*prev_motion=LEFT_MOVE;
	}	
	else if(min_c==COST_U && *prev_motion != DOWN_MOVE){
		cout<<"Intelligent move chooses U\n";
		move_to_up(board,problem_size,x,y);
		*prev_motion=UP_MOVE;
	}
	else if(min_c==COST_D && *prev_motion != UP_MOVE){
		cout<<"Intelligent move chooses D\n";
		move_to_down(board,problem_size,x,y);
			*prev_motion=DOWN_MOVE;
	}
	else {
		/*if there is same costs then do a random move*/
		if(x+1<problem_size && *prev_motion != LEFT_MOVE)		cout<<"Intelligent move chooses R\n"	,move_to_right(board,problem_size,x,y)	,*prev_motion=RIGT_MOVE;
		else if(x>0 && *prev_motion != RIGT_MOVE)				cout<<"Intelligent move chooses L\n"	,move_to_left(board,problem_size,x,y)	,*prev_motion=LEFT_MOVE;
		else if(y>0 && *prev_motion != DOWN_MOVE)				cout<<"Intelligent move chooses U\n"	,move_to_up(board,problem_size,x,y)		,*prev_motion=UP_MOVE;
		else if(y+1<problem_size && *prev_motion != UP_MOVE)	cout<<"Intelligent move chooses D\n"	,move_to_down(board,problem_size,x,y)	,*prev_motion=DOWN_MOVE;
	}
}

int calculate_cost(int board[MAX_SIZE][MAX_SIZE],int goal_board[MAX_SIZE][MAX_SIZE],int problem_size){
	int i,j;
	int cost=0;
	
	//if the number is not in the position where it should be in then the cost increase one
	for(i=0;i<problem_size;i++){
		for(j=0;j<problem_size;j++){
			if(board[i][j]!=goal_board[i][j]){
				cost++;
			}
		}
	}
	return cost;
}

bool is_puzzle_solved(int board[MAX_SIZE][MAX_SIZE],int goal_board[MAX_SIZE][MAX_SIZE], int problem_size){
	//check whether the puzzle is solved
	int i,j;
	if(board[problem_size-1][problem_size-1] != 0){
		return false;
	}
	for(i=0;i<problem_size;i++){
		for(j=0;j<problem_size;j++){
			if(board[i][j] != goal_board[i][j]){
				if(!(i==problem_size-1 && j==problem_size-1))
					return false;
			}
		}
	}
	return true;
}