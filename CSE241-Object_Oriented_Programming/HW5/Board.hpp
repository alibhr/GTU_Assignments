#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <fstream>

namespace GTU_Board{

	enum{EMPTYCELL=-1,BORDER=0};

	class AbstractBoard{
	public:
		AbstractBoard(int NewRowNumber=3,int NewColumnNUmber=3);
		AbstractBoard(const AbstractBoard &obj);
		//memberwise assign enough for this abstract class.
		virtual ~AbstractBoard();

		inline int numberOfBoard()const{return objectCounter;}
		inline char lastMove()const{return LastMove;}
		inline int numberOfMoves()const{return TotalMoves;}
		inline int getRowNumber()const{return RowNumber;}
		inline int getColumnNumber()const{return ColumnNumber;}
		inline int getEmptyCellX()const{return EmptyCell_X;}
		inline int getEmptyCellY()const{return EmptyCell_Y;}
		virtual int operator()(int index_i,int index_j)const=0;

		inline void setLastMove(const char move){LastMove=move;}
		inline void resetLastMove(){LastMove='S';}
		inline void resetTotalMove(){TotalMoves=0;}

		void print()const;
		void readFromFile(const std::string &fileName);
		void writeToFile(const std::string &fileName)const;
		void reset();
		virtual void setsize(const int &newrow,const int &newcolumn)=0;
		bool move(const char &direction);
		bool isSolved()const;
		bool operator==(const AbstractBoard &other)const;

	private:
		static int objectCounter;
		char LastMove;
		int TotalMoves;

		static int find_columnNumber(const std::string &fileName);
		static int find_rowNumber(const std::string &fileName);
		static int convertStringToInteger(const std::string &s);
		static int power(const int &base,const int &exp);

		bool move_to_right();
		bool move_to_left();
		bool move_to_up();
		bool move_to_down();
		bool isitAvaliableCell(const char &direction)const;

	protected:
		int RowNumber,ColumnNumber;
		int EmptyCell_X,EmptyCell_Y;

		virtual int& operator()(int index_i,int index_j)=0;
	};

	//global function.
	bool isit_ValidSequence(const AbstractBoard * const * const Sequence,int arraysize);
}
#endif