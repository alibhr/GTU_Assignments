/*
	Gebze Technical University Department of Computer Engineering CSE 241/505 Object Oriented Programming 
	(HW-5)-Driver Code.

	readFromFile and writewriteToFile takes string as a parameter in this test main.

	The sequence is taken from file in this driver code.
*/

#define ELEMENTNUMBER 11 //for just this scenario.

#include <iostream>
#include <string>
#include <fstream>

#include "BArray1D.hpp"
#include "BArray2D.hpp"
#include "BVector.hpp"

using namespace GTU_Board;

using std::cout;
using std::string;
using std::ifstream;
using std::to_string;
using std::endl;

void CheckCopyconstructor(BoardArray1D obj);
void CheckCopyconstructor(BoardArray2D obj);
void CheckCopyconstructor(BoardVector obj);

void TestFunctions1D();
void TestFunctions2D();
void TestFunctionsVB();
void TestGlobalFunction(const AbstractBoard * const * const All);

int main(){

	//to read the path which will be tested from file.
	ifstream file;
	file.open("path1/lastmoves.txt");

	char lastmove;
	string filename="path1/element";

	//create the boards.
	BoardArray1D *A1=new BoardArray1D,*A2=new BoardArray1D,*A3=new BoardArray1D;
	BoardArray2D *B1=new BoardArray2D,*B2=new BoardArray2D,*B3=new BoardArray2D,*B4=new BoardArray2D;
	BoardVector  *C1=new BoardVector ,*C2=new BoardVector ,*C3=new BoardVector ,*C4=new BoardVector ;


	//creats the array which will be passed to gloabal array.
	AbstractBoard *All[ELEMENTNUMBER]={A1,A2,A3,B1,B2,B3,B4,C1,C2,C3,C4};


	//fill the array which will be passed to gloabal array.
	//reads the path and last moves from file.
	for(int i=0;i<ELEMENTNUMBER;++i){
		file>>lastmove;
		filename = filename + to_string(i+1) + ".txt";
		All[i]->readFromFile(filename);
		All[i]->setLastMove(lastmove);
		filename="path1/element";
	}

	TestFunctions1D();
	cout<<"\n\n";

	TestFunctions2D();
	cout<<"\n\n";

	TestFunctionsVB();
	cout<<"\n\n";

	TestGlobalFunction(All);
	cout<<"\n\n";

	file.close();
	return 0;
}

void CheckCopyconstructor(BoardArray1D obj){
	cout<<"BoardArray1D print test : \n";
	obj.print();
}

void CheckCopyconstructor(BoardArray2D obj){
	cout<<"BoardArray2D print test : \n";
	obj.print();
}

void CheckCopyconstructor(BoardVector obj){
	cout<<"BoardVector print test : \n";
	obj.print();
}

void TestFunctions1D(){
	cout<<"------------------------------Test the all functions of BoardArray1D----------------------------\n";
	//Tests all function of BoardArray1D
	//constructor and destructor is tested automatically
	BoardArray1D Test1D,otherTest1D;
	Test1D.setsize(4,5);
	Test1D.reset();
	Test1D.setLastMove('S');
	Test1D.resetLastMove();
	Test1D.readFromFile("path1/element1.txt");
	Test1D.writeToFile("Test1D.txt");
	otherTest1D=Test1D;
	if(otherTest1D==Test1D){
		CheckCopyconstructor(Test1D);
	}
	cout<<"Column Number : "<<Test1D.getColumnNumber()<<endl;
	cout<<"Row Number : "<<Test1D.getRowNumber()<<endl;
	cout<<"Empty Cell X : "<<Test1D.getEmptyCellX()<<endl;
	cout<<"Empty Cell Y : "<<Test1D.getEmptyCellY()<<endl;
	cout<<"is solved : "<<Test1D.isSolved()<<endl;
	cout<<"number of board : "<<Test1D.numberOfBoard()<<endl;
	cout<<"number of moves : "<<Test1D.numberOfMoves()<<endl;
	cout<<"last move : "<<Test1D.lastMove()<<endl;
	Test1D.move('R');
	cout<<"after move to Right : "<<endl;
	Test1D.print();
	Test1D.move('L');
	cout<<"after move to Left : "<<endl;
	Test1D.print();
}

void TestFunctions2D(){
	cout<<"------------------------------Test the all functions of BoardArray2D----------------------------\n";
	//Tests all function of BoardArray2D
	//constructor and destructor is tested automatically
	BoardArray2D Test2D,otherTest2D;
	Test2D.setsize(5,6);
	Test2D.reset();
	Test2D.setLastMove('S');
	Test2D.resetLastMove();
	Test2D.readFromFile("path1/element1.txt");
	Test2D.writeToFile("Test2D.txt");
	otherTest2D=Test2D;
	if(otherTest2D==Test2D){
		CheckCopyconstructor(Test2D);
	}
	cout<<"Column Number : "<<Test2D.getColumnNumber()<<endl;
	cout<<"Row Number : "<<Test2D.getRowNumber()<<endl;
	cout<<"Empty Cell X : "<<Test2D.getEmptyCellX()<<endl;
	cout<<"Empty Cell Y : "<<Test2D.getEmptyCellY()<<endl;
	cout<<"is solved : "<<Test2D.isSolved()<<endl;
	cout<<"number of board : "<<Test2D.numberOfBoard()<<endl;
	cout<<"number of moves : "<<Test2D.numberOfMoves()<<endl;
	cout<<"last move : "<<Test2D.lastMove()<<endl;
	Test2D.move('R');
	cout<<"after move to Right : "<<endl;
	Test2D.print();
	Test2D.move('L');
	cout<<"after move to Left : "<<endl;
	Test2D.print();
}

void TestFunctionsVB(){
	cout<<"------------------------------Test the all functions of BoardVector----------------------------\n";
	//Tests all function of BoardVector
	//constructor and destructor is tested automatically
	BoardVector TestVB,otherTestVB;
	TestVB.setsize(5,6);
	TestVB.reset();
	TestVB.setLastMove('S');
	TestVB.resetLastMove();
	TestVB.readFromFile("path1/element1.txt");
	TestVB.writeToFile("TestVB.txt");
	otherTestVB=TestVB;
	if(otherTestVB==TestVB){
		CheckCopyconstructor(TestVB);
	}
	cout<<"Column Number : "<<TestVB.getColumnNumber()<<endl;
	cout<<"Row Number : "<<TestVB.getRowNumber()<<endl;
	cout<<"Empty Cell X : "<<TestVB.getEmptyCellX()<<endl;
	cout<<"Empty Cell Y : "<<TestVB.getEmptyCellY()<<endl;
	cout<<"is solved : "<<TestVB.isSolved()<<endl;
	cout<<"number of board : "<<TestVB.numberOfBoard()<<endl;
	cout<<"number of moves : "<<TestVB.numberOfMoves()<<endl;
	cout<<"last move : "<<TestVB.lastMove()<<endl;
	TestVB.move('R');
	cout<<"after move to Right : "<<endl;
	TestVB.print();
	TestVB.move('L');
	cout<<"after move to Left : "<<endl;
	TestVB.print();
}

void TestGlobalFunction(const AbstractBoard * const * const All){
	cout<<"------------------------------Test of the global function----------------------------\n";
	//prints the Sequence which will be tested.
	cout<<"the Sequence which will be tested\n";
	for(int i=0;i<ELEMENTNUMBER;++i){
		All[i]->print();
		cout<<"Last move : "<<All[i]->lastMove()<<endl;
		cout<<"x : "<<All[i]->getEmptyCellX()<<" ||| y : "<<All[i]->getEmptyCellY()<<endl;
		cout<<endl<<endl;
	}

	//Test the global function.
	//The array which named as All has all different type board.
	if(isit_ValidSequence(All,ELEMENTNUMBER)){
		cout<<"this sequence is valid.\n";
	}
	else{
		cout<<"this sequence is invalid.\n";
	}

	cout<<"numberOfBoard() : "<<All[ELEMENTNUMBER-1]->numberOfBoard()<<endl;
}