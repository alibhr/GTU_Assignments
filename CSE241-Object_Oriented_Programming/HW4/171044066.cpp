#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::ostream;
using std::istream;
using std::vector;
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
    inline void setsize(const int &newrow,const int &newcolumn);
    NPuzzle::inputs moveRandom();
    bool move(const char &direction);
    void solvePuzzle();
    bool isSolved()const;
    static inputs get_input();
    static void get_problemSize(int &row,int &column);
    friend ostream& operator>>(ostream &out,const NPuzzle &object);
    friend istream& operator<<(istream &in,NPuzzle &object);
private:
    class Board{
    public:
        Board();
        Board(char move);
        Board(const string &fileName);
        void print()const;
        void readFromFile(const string &fileName);
        void writeToFile(const string &fileName);
        void reset();
        inline void resetNumberOfMoves();
        inline void resetLastMove();
        bool setsize(const int &newrow,const int &newcolumn);
        bool move(const char &direction);
        bool isSolved()const;
        bool isitAvaliableCell(const char &direction)const;
        inline int numberOfMoves()const;
        inline int numberOfBoard()const;
        inline char lastMove()const;
        void operator=(const Board& other);
        bool operator==(const NPuzzle::Board &other)const;
        int operator()(int index_i,int index_j)const;
        void size(int &row,int &column)const;
    private:
        vector<vector<int>> grid;
        int emptyCell_x,emptyCell_y;
        int totalMoves;
        static int objectCounter;
        char prevMove;
        int find_columnNumber(const string &fileName);
        int find_rowNumber(const string &fileName);
        int convertStringToInteger(const string &s);
        int power(const int &base,const int &exp);
        bool move_to_right();
        bool move_to_left();
        bool move_to_up();
        bool move_to_down();
    };
    vector <Board> AllGrids;
    bool WasItIn(const Board &A_grid);
    bool addNewBoard(Board temp,char direction);
    void show_steps(vector <Board> &Grids);
    enum{
        EMPTYCELL=-1,BORDER=0
    };
};

int NPuzzle::Board::objectCounter=0;

int main(int argc,char const *argv[]){

    //To generate a random number from cstdlib
    srand(time(NULL));

    string fileName;
    bool quit=false;
    int UserRow,UserColumn;

    //start the object according to arguments.
    if(argv[1]!=NULL){
        fileName=argv[1];
    }
    NPuzzle Game(fileName);
    if(argv[1]==NULL){
        NPuzzle::get_problemSize(UserRow,UserColumn);
        Game.setsize(UserRow,UserColumn);
    }
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
        cout>>Game;

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
                cin<<Game;
                /*cout<<"File Name : ";
                cin>>fileName;
                Game.readFromFile(fileName);*/
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
    //init the all variable with a valid values.
    if(argv[0] != '\0'){
        AllGrids.push_back(Board(argv));
    }
    else{
        AllGrids.push_back(Board('S'));
    }
}

NPuzzle::Board::Board(){
    //init the all variable with a valid values.
    objectCounter++;
    totalMoves=0;
    prevMove='S';
}
NPuzzle::Board::Board(char move){
    //init the all variable with a valid values.
    objectCounter++;
    totalMoves=0;
    prevMove=move;
}
NPuzzle::Board::Board(const string &fileName){
    //init the all variable with a valid values.
    objectCounter++;
    prevMove='S';
    setsize(find_rowNumber(fileName),find_columnNumber(fileName));
    readFromFile(fileName);
}

void NPuzzle::get_problemSize(int &row,int &column){
    //ask for raw and column numbers from user.
    //check whether the input valid.
    bool proper=false;
    while(!proper){
        cout<<"Please enter the row number of puzzle : ";
        cin>>row;
        if(row > 2){
            proper=true;
        }
        else{
            cout<<"row number should be greater than 2\n";
        }
    }
    proper=false;
    while(!proper){
        cout<<"Please enter the column number of puzzle : ";
        cin>>column;
        if(column > 2){
            proper=true;
        }
        else{
            cout<<"column number should be greater than 2\n";
        }
    }
}

inline void NPuzzle::setsize(const int &newrow,const int &newcolumn){
    //Sets the board size to given value.
    AllGrids.resize(1);
    if(AllGrids.at(0).setsize(newrow,newcolumn)){
        shuffle(newrow*newcolumn);
    }
}

bool NPuzzle::Board::setsize(const int &newrow,const int &newcolumn){
    int i,j;
    int consecutive_numbers=1;
    totalMoves=0;
    grid.resize(newrow,vector<int>(newcolumn));
    for(i=0;i<newrow;i++){
        grid.at(i).resize(newcolumn);
    }
    
    //init the board with consecutive number .
    for(i=0;i<newrow;i++){
        for(j=0;j<newcolumn;j++){
            grid[i][j]=consecutive_numbers++;
        }
    }
    grid[newrow-1][newcolumn-1]=EMPTYCELL;
    emptyCell_x=newcolumn-1;
    emptyCell_y=newrow-1;
    return true;
}

inline void NPuzzle::print()const{
    AllGrids.back().print();
}

void NPuzzle::Board::print()const{
    //prints the current configuration on the screen by sending it to cout.
    int i,j;
    for(i=0;i<grid.size();i++){
        for(j=0;j<grid.back().size();j++){
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
    AllGrids.resize(1);
    AllGrids.back().resetNumberOfMoves();
    AllGrids.back().resetLastMove();
    
}   

bool NPuzzle::Board::isitAvaliableCell(const char &direction)const{

    //check whether the cell which is the destination is avalible.
    if((direction=='R' || direction=='r')  && emptyCell_x+1 < grid.back().size() && grid[emptyCell_y][emptyCell_x+1]!=0){
        return true;
    }
    else if((direction=='L' || direction=='l') && emptyCell_x > 0 && grid[emptyCell_y][emptyCell_x-1]!=0){
        return true;
    }
    else if((direction=='U' || direction=='u') && emptyCell_y > 0 && grid[emptyCell_y-1][emptyCell_x]!=0){
        return true;
    }
    else if((direction=='D' || direction=='d') && emptyCell_y+1 < grid.size() && grid[emptyCell_y+1][emptyCell_x]!=0){
        return true;
    }
    return false;
}

inline bool NPuzzle::move(const char &direction){
    if(AllGrids.back().move(direction)){
        AllGrids.resize(1);
        return true;
    }
    return false;
}

bool NPuzzle::Board::move(const char &direction){
    //Makes a move according to given char parameter.

    if((direction=='R'||direction=='r') && move_to_right()){
        prevMove='R';
        totalMoves++;
        return true;
    }
    else if((direction=='L'||direction=='l') && move_to_left()){
        prevMove='L';
        totalMoves++;
        return true;
    }
    else if((direction=='U'||direction=='u') && move_to_up()){
        prevMove='U';
        totalMoves++;
        return true;
    }
    else if((direction=='D'||direction=='d') && move_to_down()){
        prevMove='D';
        totalMoves++;
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

inline void NPuzzle::printReport()const{
    cout<<AllGrids.back().numberOfMoves()<<" moves have been done since reset."<<endl;
}

bool NPuzzle::isSolved()const{
    return AllGrids.back().isSolved();
}

bool NPuzzle::Board::isSolved()const{
    //check whether the puzzle solved.
    //returns true if the board is a solution.
    int consecutiveNumbers=1;
    int i,j,flag=0;
    for(i=0;i<grid.size();i++){
        for(j=0;j<grid.back().size();j++){
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

inline void NPuzzle::writeToFile(const string &fileName){
    AllGrids.back().writeToFile(fileName);
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

    for(i=0;i<grid.size();i++){
        for(j=0;j<grid.back().size();j++){
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

inline void NPuzzle::readFromFile(const string &fileName){
    AllGrids.back().readFromFile(fileName);
    AllGrids.resize(1);
    AllGrids.back().resetNumberOfMoves();
}

void NPuzzle::Board::readFromFile(const string &fileName){
    //Reads the current configuration from the file given as parameter.
    ifstream file;
    string temp_s;
    int temp_i;
    int i,j;
    file.open(fileName);
    int rawNumber=find_rowNumber(fileName);
    int columnNumber=find_columnNumber(fileName);
    setsize(rawNumber,columnNumber);
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

int NPuzzle::Board::find_rowNumber(const string &fileName){
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

inline void NPuzzle::Board::resetNumberOfMoves(){
    totalMoves=0;
}

inline void NPuzzle::Board::resetLastMove(){
    prevMove='S';
}

inline int NPuzzle::Board::numberOfMoves()const{
    return totalMoves;
}

inline int NPuzzle::Board::numberOfBoard()const{
    return objectCounter;
}

inline char NPuzzle::Board::lastMove()const{
    return prevMove;
}

ostream& operator>>(ostream &out,const NPuzzle &object){
    //prints the current configuration on the screen by sending it to ostream object.

    int i,j,row,column;

    //find row and column number.
    object.AllGrids.back().size(row,column);
    for(i=0;i<row;i++){
        for(j=0;j<column;j++){
            if(object.AllGrids.back()(i,j)==NPuzzle::EMPTYCELL){  
                out<<"**\t";
            }
            else if(object.AllGrids.back()(i,j)==NPuzzle::BORDER){
               out<<"  \t"; 
            }
            else{
                out<<object.AllGrids.back()(i,j)<<"\t";
            }
        }
        out<<"\n\n";
    }
    //object.AllGrids.back().print();
    return out;
}

void NPuzzle::Board::size(int &row,int &column)const{
    //learn the row and column number of grid.
    row=grid.size();
    column=grid.back().size();
}

istream& operator<<(istream &in,NPuzzle &object){
    //reads the current configuration from file.
    
    //takes the name of the file form user.
    string fileName;
    cout<<"Enter the file name : ";
    in>>fileName;

    //reset some values.
    object.AllGrids.back().readFromFile(fileName);
    object.AllGrids.resize(1);
    object.AllGrids.back().resetNumberOfMoves();

    return in;
}

bool NPuzzle::Board::operator==(const NPuzzle::Board &other)const{
    //returns if the board are same.
    //This operator just consider the grids.

    int i,j;
    int row=grid.size(),column=grid.back().size();

    if(row != other.grid.size())                return false;
    if(column != other.grid.back().size())      return false;

    for(i=0;i<row;i++){
        for(j=0;j<column;j++){
            if(grid[i][j] != other.grid[i][j]){
                return false;
            }
        }
    }

    return true;
}

int NPuzzle::Board::operator()(int index_i,int index_j)const{

    //check wheter the paremeters are valid or not.
    if(grid.size() < index_i || grid.back().size() < index_j){
        cout<<"index ERROR\n";
        exit(1);
    }

    //return the corresponding cell content.
    else {
        return grid[index_i][index_j];
    }
}

void NPuzzle::Board::operator=(const Board& other){
    //assigns a board object to another board object.
    //considers the all content.

    int i,j;

    grid.resize(other.grid.size(),vector<int>(0));
    for(i=0;i<other.grid.size();i++){
        grid.at(i).resize(other.grid.back().size());
    }

    for(i=0;i<other.grid.size();i++){
        for(j=0;j<other.grid.back().size();j++){
            grid.at(i).at(j)=other.grid.at(i).at(j);
        }
    }
    emptyCell_x=other.emptyCell_x;
    emptyCell_y=other.emptyCell_y;

    totalMoves=other.totalMoves;

    objectCounter=other.objectCounter;

    prevMove=other.prevMove;
}

void NPuzzle::solvePuzzle(){
    //solves the problem from the current configuration.

    //The index of the element which taken from vector of board object.
    int controlindex=0;

    bool flag=true;
    Board Temp;
    cerr<<"...\n";
    while(flag){

        Temp=AllGrids.at(controlindex);
        //apply all possible moves.
        if(addNewBoard(Temp,'R')){
            flag=false;
        }
        if(addNewBoard(Temp,'L')){
            flag=false;
        }
        if(addNewBoard(Temp,'U')){
            flag=false;
        }
        if(addNewBoard(Temp,'D')){
            flag=false;
        }
        controlindex++;
    }

    show_steps(AllGrids);
}

bool NPuzzle::addNewBoard(Board temp,char direction){
    //if this direction is possible to go,
    if(temp.isitAvaliableCell(direction)){
        temp.move(direction);
        //check whether the puzzle solved.
        if(isSolved()){
            return true;
        }
        //check whether there is same board in vector.
        else if(!WasItIn(temp)){
            AllGrids.push_back(temp);
        }
    }
    return false;
}

bool NPuzzle::WasItIn(const Board &A_grid){
    //check whether there is same board in vector.
    int i;
    for(i=0;i<AllGrids.size();i++){
        if(AllGrids.at(i)==A_grid){
            return true;
        }
    }
    return false;
}

void NPuzzle::show_steps(vector <Board> &Grids){
    //arrange the vector of board , find the best path and print it.

    int i;
    char inverseMove;
    vector <char> path;
    Board A_Temp;
    for(i=Grids.size()-1;Grids.at(i).lastMove()!='S';i--){
        inverseMove=Grids.at(i).lastMove();

        if(inverseMove=='R'){
            Grids.at(i).move('L');
            path.push_back('R');
        }

        if(inverseMove=='L'){
            Grids.at(i).move('R');
            path.push_back('L');
        }

        if(inverseMove=='U'){
            Grids.at(i).move('D');
            path.push_back('U');
        }

        if(inverseMove=='D'){
            Grids.at(i).move('U');
            path.push_back('D');
        }
        A_Temp=Grids.at(i);
        while(!(A_Temp==Grids.at(i-1)))
            i--;
    }

    for(i=path.size();i>0;i--){
        Grids.at(0).print();
        cout<<"Move : "<<path.at(i-1)<<endl;
        Grids.at(0).move(path.at(i-1));
    }
    AllGrids.push_back(Grids.at(0));
}

inline void NPuzzle::reset(){
    AllGrids.back().reset();
}

void NPuzzle::Board::reset(){

    totalMoves=0;
    //Resets the current configuration to the solution.
    int i,j;
    int consecutive_numbers=1;

    //init the board with consecutive number but also consider the shape of the grid.
    for(i=0;i<grid.size();i++){
        for(j=0;j<grid.back().size();j++){
            if(grid[i][j]!=BORDER){
                grid[i][j]=consecutive_numbers;
                consecutive_numbers++;
            }
        }
    }
    //find the last cell and do it a moveable cell.-1 means moveable cell.
    for(i=grid.back().size()-1;i>=0;i--){
        if(grid[grid.size()-1][i]!=0){
            grid[grid.size()-1][i]=EMPTYCELL;
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