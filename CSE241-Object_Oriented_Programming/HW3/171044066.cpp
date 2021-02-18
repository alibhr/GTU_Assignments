#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;

class NPuzzle{
public:
    enum inputs{
	    RIGHT_MOVE=0,LEFT_MOVE=1,UP_MOVE=2,DOWN_MOVE=3,MAX_DIRECTION=4,
        INTELLIGENT_MOVE,SHUFFLE,QUIT,SOLVE,PRINT_REPORT,STORE,LOAD,EMPTY
    };
    NPuzzle();
    NPuzzle(const string &fileName);
    void print()const;
    inline void printReport()const;
    void readFromFile(const string &fileName);
    void writeToFile(const string &fileName);
    void shuffle(const int &N);
    void reset();
    inline void setsize(const int &newraw,const int &newcolumn);
    NPuzzle::inputs moveRandom();
    void moveIntelligent();
    bool move(const char &direction);
    void solvePuzzle();
    bool isSolved()const;
    static inputs get_input();
private:
    class Board{
    public:
        Board();
        Board(const string &fileName);
        void print()const;
        void readFromFile(const string &fileName);
        void writeToFile(const string &fileName);
        void reset();
        bool setsize(const int &newraw,const int &newcolumn);
        bool move(const char &direction);
        bool isSolved()const;
        void fill();
        void get_problemSize();
        void find_the_empty_cell();
        bool isitAvaliableCell(const char &direction)const;
        inline int learnRawNumber()const;
        inline int learnColumnNumber()const;
        int calculateCost()const;
    private:
        static const int MAX_RAW=9,MAX_COLUMN=9;
        int rawNumber,columnNumber;
        int grid[MAX_RAW][MAX_COLUMN];
        int emptyCell_x,emptyCell_y;
        int find_columnNumber(const string &fileName);
        int find_rawNumber(const string &fileName);
        int convertStringToInteger(const string &s);
        int power(const int &base,const int &exp);
        bool move_to_right();
        bool move_to_left();
        bool move_to_up();
        bool move_to_down();
    };
    inputs findAllCosts(int costs[NPuzzle::MAX_DIRECTION]);
    Board CurrentGrid;
    int totalMoves;
    enum{
        EMPTYCELL=-1,BORDER=0
    };
};

int main(int argc,char const *argv[]){

    //To generate a random number from cstdlib
    srand(time(NULL));

    string fileName;
    bool quit=false;
    int UserRaw,UserColumn;

    //start the object according to arguments.
    if(argv[1]!=NULL){
        fileName=argv[1];
    }

    NPuzzle Game(fileName);

    //check for the first puzzle.
    if(Game.isSolved()){
        cout<<"Problem Solved!\n";
        Game.print();
        Game.printReport();
		return 0;
    }

    cout<<"Your initial board is :\n";

    //main game loop.
    while(!quit){
        Game.print();

        cout<<"Your Move : ";
        //consider the input and do sometihng according to input
        switch(NPuzzle::get_input()){
            case NPuzzle::RIGHT_MOVE:
                Game.move('R');
                break;
            case NPuzzle::LEFT_MOVE:
                Game.move('L');
                break;
            case NPuzzle::UP_MOVE:
                Game.move('U');
                break;
            case NPuzzle::DOWN_MOVE:
                Game.move('D');
                break;
            case NPuzzle::INTELLIGENT_MOVE:
                Game.moveIntelligent();
                break;
            case NPuzzle::SHUFFLE:
                Game.shuffle(100);
                break;
            case NPuzzle::QUIT:
                quit=true;
                break;
            case NPuzzle::SOLVE:
                Game.solvePuzzle();
                break;
            case NPuzzle::PRINT_REPORT:
                Game.printReport();
                break;
            case NPuzzle::STORE:
                cout<<"File Name : ";
                cin>>fileName;
                Game.writeToFile(fileName);
                break;
            case NPuzzle::LOAD:
                cout<<"File Name : ";
                cin>>fileName;
                Game.readFromFile(fileName);
                break;
            default:
                cerr<<"invalid selection!!\n";
                break;
        }
        if(Game.isSolved()){
            cout<<"Problem Solved!\n";
            Game.print();
            Game.printReport();
            return 0;
        }
    }

    return 0;
}

NPuzzle::NPuzzle():NPuzzle("\0"){/*BLANK*/}

NPuzzle::NPuzzle(const string &argv){
    //fill the all variable with a valid values.
    if(argv[0] != '\0'){
        totalMoves=0;
        CurrentGrid=Board(argv);
    }
    else{
        CurrentGrid.get_problemSize();
    /*    CurrentGrid.fill();
        CurrentGrid.find_the_empty_cell();*/
        shuffle(CurrentGrid.learnColumnNumber()*CurrentGrid.learnRawNumber()*3);
        totalMoves=0;
    }
}

NPuzzle::Board::Board(){/*BLANK*/}

NPuzzle::Board::Board(const string &fileName){
    //fill the all variable with a valid values.
    rawNumber=find_rawNumber(fileName);
    columnNumber=find_columnNumber(fileName);
    if(rawNumber >MAX_RAW || columnNumber > MAX_COLUMN){
        cout<<"raw or column number is bigger than max,please arrange your file again.!!\n";
        exit(1);
    }
    readFromFile(fileName);
    find_the_empty_cell();
}

inline void NPuzzle::setsize(const int &newraw,const int &newcolumn){
    if(CurrentGrid.setsize(newraw,newcolumn)){
        shuffle(newcolumn*newraw*10);
        totalMoves=0;
    }
}

bool NPuzzle::Board::setsize(const int &newraw,const int &newcolumn){
    if(newcolumn < 2 || newcolumn > MAX_COLUMN || newraw < 2 || newraw > MAX_RAW){
        cout<<"Invalid raw or column number.\nraw and column number didn't change. \n";
        return false;
    }
    columnNumber=newcolumn;
    rawNumber=newraw;
    fill();
    find_the_empty_cell();
    return true;
}

NPuzzle::inputs NPuzzle::get_input(){
	char temp;

    inputs input;
    
	//this flag is used for loop,if there is invalid input the loop will be continue
	int flag=0;

	//take input untill taking an appropriate input.
	do{
		cin>>temp;
        //Moves the empty cell right if there is room.
		if(temp=='R' || temp=='r')	input=RIGHT_MOVE;

        //Moves the empty cell left if there is room.
		else if(temp=='L' || temp=='l')	input=LEFT_MOVE,flag=0;

        //Moves the empty cell up if there is room.
		else if(temp=='U' || temp=='u')	input=UP_MOVE,flag=0;

        //Moves the empty cell down if there is room.
		else if(temp=='D' || temp=='d')	input=DOWN_MOVE,flag=0;

        //Takes the puzzle to soliton,and make size*size random moves.
		else if(temp=='S' || temp=='s')	input=SHUFFLE,flag=0;

        //makes an intelligent move.
		else if(temp=='I' || temp=='i') input=INTELLIGENT_MOVE,flag=0;

        //To quit
		else if(temp=='Q' || temp=='q')	input=QUIT,flag=0;

        //Solves the problem by using the intelligent algorithm.
        else if(temp=='V' || temp=='v') input=SOLVE,flag=0;

        //prints a report.
        else if(temp=='T' || temp=='t') input=PRINT_REPORT,flag=0;

        //saves the current board configuration in the file which is determined by user.
        else if(temp=='E' || temp=='e') input=STORE,flag=0;
        else if(temp=='O' || temp=='o') input=LOAD,flag=0;
		else cout<<"invalid selection,try again !! :",flag=1;
	}while(flag);
    return input;
}

bool NPuzzle::isSolved()const{
    CurrentGrid.isSolved();
}

bool NPuzzle::Board::isSolved()const{
    //check whether the puzzle solved.
    //returns true if the board is a solution.
    int consecutiveNumbers=1;
    int i,j,flag=0;
    for(i=0;i<rawNumber;i++){
        for(j=0;j<columnNumber;j++){
            if(grid[i][j]!=consecutiveNumbers && grid[i][j] != BORDER){
                flag++;
            }
            if(grid[i][j] != BORDER){
                consecutiveNumbers++;
            }
        }
    }
    if(flag==1) return true;
    else return false;
}

inline int NPuzzle::Board::learnRawNumber()const{
    return rawNumber;
}

inline int NPuzzle::Board::learnColumnNumber()const{
    return columnNumber;
}

inline void NPuzzle::print()const{
    CurrentGrid.print();
}

void NPuzzle::Board::print()const{
    //prints the current configuration on the screen by sending it to cout.
    int i,j;
    for(i=0;i<rawNumber;i++){
        for(j=0;j<columnNumber;j++){
            if(grid[i][j]==EMPTYCELL){
                cout<<"**\t";
            }
            else if(grid[i][j]==BORDER){
               cout<<"  \t"; 
            }
            else{
                cout<<grid[i][j]<<"\t";
            }
        }
        cout<<"\n\n";
    }
}

inline void NPuzzle::printReport()const{
    cout<<totalMoves<<" moves have been done since reset."<<endl;
}

void NPuzzle::Board::get_problemSize(){
    //ask for raw and column numbers from user.
    //check whether the input valid.
    bool proper=false;
    while(!proper){
        cout<<"Please enter the raw number of puzzle : ";
        cin>>rawNumber;
        if(rawNumber <= MAX_RAW && rawNumber > 2){
            proper=true;
        }
        else{
            cout<<"raw number should be between 2 - "<<MAX_RAW<<endl;
        }
    }
    proper=false;
    while(!proper){
        cout<<"Please enter the column number of puzzle : ";
        cin>>columnNumber;
        if(columnNumber <= MAX_COLUMN && columnNumber > 2){
            proper=true;
        }
        else{
            cout<<"column number should be between 2 - "<<MAX_COLUMN<<endl;
        }
    }
    setsize(rawNumber,columnNumber);

}

int NPuzzle::Board::find_columnNumber(const string &fileName){
    //count how many spaces in a line in order to find the number of column.

    ifstream file;
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
        cout<<"file is empty!!\n";
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

int NPuzzle::Board::find_rawNumber(const string &fileName){
    //count how many '\n' in the file in order to find the number of raw.

    ifstream file;
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

int NPuzzle::Board::convertStringToInteger(const string &s){
    int i,result=0;
    int size=s.size();
    int temp_size=size;
    for(i=0;i<size;i++){
        result+=(s[i]-48)*power(10,temp_size-1);
        temp_size--;
    }
    return result;
}

int NPuzzle::Board::power(const int &base,const int &exp){
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

inline void NPuzzle::readFromFile(const string &fileName){
    CurrentGrid.readFromFile(fileName);
    totalMoves=0;
}

void NPuzzle::Board::readFromFile(const string &fileName){
    ifstream file;
    string temp_s;
    int temp_i;
    int i,j;
    file.open(fileName);
    rawNumber=find_rawNumber(fileName);
    columnNumber=find_columnNumber(fileName);
    if(!file.is_open()){
        cout<<"file couldn't opened !!!3";
        exit(1);
    }

    //take the cell form file
    for(i=0;i<rawNumber;i++){
        for(j=0;j<columnNumber;j++){
            file>>temp_s;
            if(temp_s[0]=='b'){
                grid[i][j]=EMPTYCELL;
                emptyCell_x=j;
                emptyCell_y=i;
            }
            else{
                //i take the data as string so i have to conver it to integer.
                temp_i=convertStringToInteger(temp_s);
                grid[i][j]=temp_i;
            }
        }
    }

    file.close();
}

inline void NPuzzle::writeToFile(const string &fileName){
    CurrentGrid.writeToFile(fileName);
}

void NPuzzle::Board::writeToFile(const string &fileName){
    //Writes the current configuration to the file given as function parameter.
    int i,j;
    ofstream file;

    file.open(fileName);
    if(!file.is_open()){
        cout<<"file couldn't opened !!!!4";
        exit(1);
    }

    for(i=0;i<rawNumber;i++){
        for(j=0;j<columnNumber;j++){
            if(grid[i][j]==EMPTYCELL)
                file<<"bb ";

            else if(grid[i][j]<10)
                file<<"0"<<grid[i][j]<<" ";

            else
                file<<grid[i][j]<<" ";
        }
        file<<endl;
    }

    file.close();
}

void NPuzzle::Board::find_the_empty_cell(){
	//Before the motion we have to know where empty cell is
	int i,j;
	for(i=0;i<rawNumber;i++){
		for(j=0;j<columnNumber;j++){
			//scan all board and if there is -1 it means there is empty area
			if(grid[i][j]==EMPTYCELL){
				emptyCell_x=j;
				emptyCell_y=i;
			}
		}
	}
}

bool NPuzzle::Board::isitAvaliableCell(const char &direction)const{

    //check whether the cell which is the destination is avalible.
    if((direction=='R' || direction=='r')  && emptyCell_x+1 < columnNumber && grid[emptyCell_y][emptyCell_x+1]!=0){
        return true;
    }
    else if((direction=='L' || direction=='l') && emptyCell_x > 0 && grid[emptyCell_y][emptyCell_x-1]!=0){
        return true;
    }
    else if((direction=='U' || direction=='u') && emptyCell_y > 0 && grid[emptyCell_y-1][emptyCell_x]!=0){
        return true;
    }
    else if((direction=='D' || direction=='d') && emptyCell_y+1 < rawNumber && grid[emptyCell_y+1][emptyCell_x]!=0){
        return true;
    }
    return false;
}

inline bool NPuzzle::move(const char &direction){
    if(CurrentGrid.move(direction)){
        totalMoves++;
        return true;
    }
    return false;
}

bool NPuzzle::Board::move(const char &direction){
    //Makes a move according to given char parameter.

    if((direction=='R'||direction=='r') && move_to_right()){
        return true;
    }
    else if((direction=='L'||direction=='l') && move_to_left()){
        return true;
    }
    else if((direction=='U'||direction=='u') && move_to_up()){
        return true;
    }
    else if((direction=='D'||direction=='d') && move_to_down()){
        return true;
    }
    return false;
}

bool NPuzzle::Board::move_to_right(){
    //shifts the empty space to right if there is room.
    if(isitAvaliableCell('R')){
        grid[emptyCell_y][emptyCell_x]=grid[emptyCell_y][emptyCell_x+1];
	    grid[emptyCell_y][emptyCell_x+1]=EMPTYCELL;
        emptyCell_x++;
        return true;
    }
    return false;
}

bool NPuzzle::Board::move_to_left(){
    //shifts the empty space to left if there is room.
    if(isitAvaliableCell('L')){
        grid[emptyCell_y][emptyCell_x]=grid[emptyCell_y][emptyCell_x-1];
	    grid[emptyCell_y][emptyCell_x-1]=EMPTYCELL;
        emptyCell_x--;
        return true;
    }
    return false;
}

bool NPuzzle::Board::move_to_up(){
    //shifts the empty space to up if there is room.
    if(isitAvaliableCell('U')){
        grid[emptyCell_y][emptyCell_x]=grid[emptyCell_y-1][emptyCell_x];
	    grid[emptyCell_y-1][emptyCell_x]=EMPTYCELL;
        emptyCell_y--;
        return true;
    }
    return false;
}

bool NPuzzle::Board::move_to_down(){
    //shifts the empty space to down if there is room.
    if(isitAvaliableCell('D')){
        grid[emptyCell_y][emptyCell_x]=grid[emptyCell_y+1][emptyCell_x];
	    grid[emptyCell_y+1][emptyCell_x]=EMPTYCELL;
        emptyCell_y++;
        return true;
    }
    return false;
}

void NPuzzle::shuffle(const int &N){
    //Makes N times random move.
    int random;
    for(int i=0;i<N;i++){
        random=rand()%4;
        if(random==0 && move('R')){
        }
        else if(random==1 && move('L')){
        }
        else if(random==2 && move('U')){
        }
        else if(random==3 && move('D')){
        }
        else{
            i--;
        }
    }
    totalMoves=0;
}

inline void NPuzzle::reset(){
    CurrentGrid.reset();
    totalMoves=0;
}

void NPuzzle::Board::fill(){
    int i,j;
    int consecutive_numbers=1;

    //init the board with consecutive number .
    for(i=0;i<rawNumber;i++){
        for(j=0;j<columnNumber;j++){
            grid[i][j]=consecutive_numbers;
            consecutive_numbers++;
        }
    }
    grid[rawNumber-1][columnNumber-1]=EMPTYCELL;
}

void NPuzzle::Board::reset(){

    //Resets the current configuration to the solution.
    int i,j;
    int consecutive_numbers=1;

    //init the board with consecutive number but also consider the shape of the grid.
    for(i=0;i<rawNumber;i++){
        for(j=0;j<columnNumber;j++){
            if(grid[i][j]!=BORDER){
                grid[i][j]=consecutive_numbers;
                consecutive_numbers++;
            }
        }
    }
    //find the last cell and do it a moveable cell.-1 means moveable cell.
    for(i=columnNumber-1;i>=0;i--){
        if(grid[rawNumber-1][i]!=0){
            grid[rawNumber-1][i]=EMPTYCELL;
            i=-1;
        }
    }
}

NPuzzle::inputs NPuzzle::moveRandom(){
    //select a random direction and shift the empty cell.
    //if the selected direction is invalid then select another random direction.
    int random;
    bool flag=true;
    while(flag){
        random=rand()%4;
        if(random==0 && move('R')){
            flag=false;
            return NPuzzle::RIGHT_MOVE;
        }
        else if(random==1 && move('L')){
            flag=false;
            return NPuzzle::LEFT_MOVE;
        }
        else if(random==2 && move('U')){
            flag=false;
            return NPuzzle::UP_MOVE;
        }
        else if(random==3 && move('D')){
            flag=false;
            return NPuzzle::DOWN_MOVE;
        }
    }
}

void NPuzzle::moveIntelligent(){

    int i,costs[NPuzzle::MAX_DIRECTION],random;
    int minCost,equalCostCounter = 0,equalCosts[NPuzzle::MAX_DIRECTION];
    static NPuzzle::inputs prevMotion = NPuzzle::EMPTY;
    NPuzzle::inputs bestDirection=NPuzzle::EMPTY;

    //fill the equalCostCounter with empty enums.
    for(i=0;i<NPuzzle::MAX_DIRECTION;i++){
        equalCosts[i]=NPuzzle::EMPTY;
    }

    findAllCosts(costs);

    //find the first valid value of minCost and bestDirection. 
    for(i=0;i<MAX_DIRECTION;i++){
        if(costs[i]!=-1 && i != prevMotion){
            minCost=costs[i];
            bestDirection=(NPuzzle::inputs)i;
        }
    }

    //find the minCost and best direction.
    for(i=0;i<NPuzzle::MAX_DIRECTION;i++){
        if(costs[i]!=-1 && i != prevMotion){
            if(minCost > costs[i]){
                minCost=costs[i];
                bestDirection=(NPuzzle::inputs)i;
            }
        }
    }

    //check whether there is a same cost with min cost.
    for(i=0;i<MAX_DIRECTION;i++){
        if(minCost==costs[i]){
            equalCosts[i]=(enum inputs)i;
            equalCostCounter++;
        }
    }

    //equalCostCounter can't be 0 but ı want to be sure.
    if(equalCostCounter <= 0)
        equalCostCounter=1;

    //take a random number to random move.
    random=rand()%equalCostCounter;

    //if there is same cost ,select one of the directions randomly.
    for(i=0;i<MAX_DIRECTION;i++){
        while(equalCosts[i]==EMPTY){
            i++;
            random++;
        }
        if(i==random){
            bestDirection = (enum inputs)equalCosts[i];
        }
    }

    //Do the best move.
    if(bestDirection==NPuzzle::RIGHT_MOVE)      prevMotion=NPuzzle::LEFT_MOVE   ,move('R')  ,cout<<"Intelligent move chooses R\n";
    else if(bestDirection==NPuzzle::LEFT_MOVE)  prevMotion=NPuzzle::RIGHT_MOVE  ,move('L')  ,cout<<"Intelligent move chooses L\n";
    else if(bestDirection==NPuzzle::UP_MOVE)    prevMotion=NPuzzle::DOWN_MOVE   ,move('U')  ,cout<<"Intelligent move chooses U\n";
    else if(bestDirection==NPuzzle::DOWN_MOVE)  prevMotion=NPuzzle::UP_MOVE     ,move('D')  ,cout<<"Intelligent move chooses D\n";

}

NPuzzle::inputs NPuzzle::findAllCosts(int costs[NPuzzle::MAX_DIRECTION]){
    int i,cost;
    for(i=0;i<NPuzzle::MAX_DIRECTION;i++){
        costs[i]=-1;
    }

    //calculate the costs.
    //if it is possible to go to right then go and calculate the cost of right and go back.
    if(CurrentGrid.isitAvaliableCell('R')){
        move('R');
        cost=CurrentGrid.calculateCost();
        move('L');
        totalMoves-=2;
        costs[NPuzzle::RIGHT_MOVE]=cost;
    }
    //if it is possible to go to left then go and calculate the cost of left and go back.
    if(CurrentGrid.isitAvaliableCell('L')){
        move('L');
        cost=CurrentGrid.calculateCost();
        move('R');
        totalMoves-=2;
        costs[NPuzzle::LEFT_MOVE]=cost;
    }
    //if it is possible to go to up then go and calculate the cost of up and go back.
    if(CurrentGrid.isitAvaliableCell('U')){
        move('U');
        cost=CurrentGrid.calculateCost();
        move('D');
        totalMoves-=2;
        costs[NPuzzle::UP_MOVE]=cost;
    }
    //if it is possible to go to down then go and calculate the cost of down and go back.
    if(CurrentGrid.isitAvaliableCell('D')){
        move('D');
        cost=CurrentGrid.calculateCost();
        move('U');
        totalMoves-=2;
        costs[NPuzzle::DOWN_MOVE]=cost;
    }
}

int NPuzzle::Board::calculateCost()const{
    //create a goal situation and calulate the cost according to goal situation.
    int i,j,consecutiveNumbers=1;
    int x,y;
	int cost=0;
    int goal[MAX_RAW][MAX_COLUMN];
    
    for(i=0;i<rawNumber;i++){
        for(j=0;j<columnNumber;j++){
            goal[i][j]=1;
        }
    }
    //init the board with consecutive number but also consider the shape of the grid.
    for(i=0;i<rawNumber;i++){
        for(j=0;j<columnNumber;j++){
            if(goal[i][j]!=BORDER){
                goal[i][j]=consecutiveNumbers;
                consecutiveNumbers++;
            }
        }
    }
    //find the last cell and do it a moveable cell.-1 means moveable cell.
    for(i=columnNumber-1;i>=0;i--){
        if(goal[rawNumber-1][i]!=0){
            goal[rawNumber-1][i]=EMPTYCELL;
            i=-1;
        }
    }
    //calculate the manhatten distance.
    for(i=0;i<rawNumber;i++){
        for(j=0;j<columnNumber;j++){
            for(x=0;x<rawNumber;x++){
                for(y=0;y<columnNumber;y++){
                    if(grid[i][j]==goal[x][y]){
                        cost+=(i > x) ? (i-x) : (x-i);
                        cost+=(j > y) ? (j-y) : (y-j);
                    }
                }
            }
        }
    }
	return cost;
}

void NPuzzle::solvePuzzle(){
    //try to solve the puzzle by doing intelligent moves.
    //if the puzzle can't be solved up to 100000 moves then ask to user whether should it be continue.
    int moveCounter=0;
    char choice;
    bool quit=false;
    while(!quit){
        moveIntelligent();
        print();
        if(isSolved()){
            quit=true;
        }
        moveCounter++;
        if(moveCounter > 100000){
            cout<<"100000 move have been done,\npress 'y' to to keep continue : ";
            cin>>choice;
            if(choice!='Y' || choice!='y'){
                quit=true;
            }
            else{
                moveCounter=0;
            }
        }
    }
}