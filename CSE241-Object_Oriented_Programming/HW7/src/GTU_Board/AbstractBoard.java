//File : AbstractBoard.java
package GTU_Board;

import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;


/**
 *This abstract class represents the board configuration.
 * @author Ali Bahar 171044066
 */
public abstract class AbstractBoard {

    /**
     * Counts the created objects so far.
     */
    private static int objectCounter=0;

    /**
     * keeps the last move that have been done on this board.
     */
    private char LastMove;

    /**
     * keeps the move number.
     */
    private int TotalMoves;

    /**
     * keeps the sizes of the board.
     */
    protected int RowNumber,ColumnNumber;

    /**
     * keeps where the empty cell is.
     */
    protected int EmptyCell_X,EmptyCell_Y;

    /**
     * -1 represents the Empty cell on this board.
     */
    private final static int EMPTYCELL=-1;

    /**
     * 0 represents the Border on this board.
     */
    private final static int BORDER=0;

    /**
     * Getter method
     * @return returns how many object created so far belong to this class.
     */
    public int numberOfBoard(){return objectCounter;}

    /**
     * Getter method
     * @return returns what waas the last move.
     */
    public char lastMove(){return LastMove;}

    /**
     * Getter method
     * @return returns how many move have been done so far on this board.
     */
    public int numberOfMoves(){return TotalMoves;}

    /**
     * Getter method
     * @return returns row number of the board
     */
    public int getRowNumber(){return RowNumber;}

    /**
     * Getter method
     * @return returns how many column there is.
     */
    public int getColumnNumber(){return ColumnNumber;}

    /**
     * Getter method
     * @return returns where empty cell in x axis.
     */
    public int getEmptyCellX(){return EmptyCell_X;}

    /**
     * Getter method
     * @return returns where empty cell in y axis.
     */
    public int getEmptyCellY(){return EmptyCell_Y;}

    /**
     * Getter method
     * @param index_i y axis of the board.
     * @param index_j x axis of the board.
     * @return returns the content of corresponding cell of the given parameters.
     */
    public abstract int Cell(int index_i,int index_j);

    /**
     * arranges the last move of the board.
     * @param move new last move.
     */
    public void setLastMove(char move){LastMove=move;}

    /**
     * arranges the last move to default.
     */
    public void resetLastMove(){LastMove='S';}

    /**
     * arranges the Total move to default.
     */
    public void resetTotalMove(){TotalMoves=0;}

    /**
     * arranges the value of the given cell.
     * @param index_i y axis of the board.
     * @param index_j x axis of the board.
     * @param value the new value of the cell.
     */
    protected abstract void setCell(int index_i,int index_j,int value);

    /**
     *arranges the column number also there is error check.
     *size can't be smaller than 3x3
     * @param newColumNumber The new Column number.
     */
    protected void setColumnNumber(int newColumNumber){
        if(newColumNumber<3){
            System.out.println("Column number can't be smaller than 3.\n");
            ColumnNumber=3;
        }
        else if(newColumNumber > 50){
            System.out.println("Column number can't be greater than 50.\n");
            ColumnNumber=50;
        }
        else{
            ColumnNumber=newColumNumber;
        }
    }

    /**
     *arranges the Row number also there is error check.
     *size can't be smaller than 3x3
     * @param newRowNumber The new row number.
     */
    protected void setRowNumber(int newRowNumber){
        if(newRowNumber<3){
            System.out.println("Row number can't be smaller than 3.\n");
            RowNumber=3;
        }
        else if(newRowNumber > 50){
            System.out.println("Row number can't be greater than 50.\n");
            RowNumber=50;
        }
        else{
            RowNumber=newRowNumber;
        }
    }

    /**
     * no parameter constructor.
     * creates the board according to default values.
     */
    public AbstractBoard(){
        setColumnNumber(3);
        setRowNumber(3);
        resetLastMove();
        resetTotalMove();
        ++objectCounter;
    }

    /**
     * creates the board according to given parameters
     * @param newRowNumber number of row number of created board.
     * @param newColumnNumber number of column number of created board.
     */
    public AbstractBoard(int newRowNumber,int newColumnNumber){
        setRowNumber(newRowNumber);
        setColumnNumber(newColumnNumber);
        resetLastMove();
        resetTotalMove();
        ++objectCounter;
    }

    /**
     *it produce string form of the board
     * @return returns string form of the board.
     */
    @Override
    public String toString(){
        String grid="";
        for(int i=0;i<getRowNumber();++i) {
            for (int j = 0; j < getColumnNumber(); ++j) {
                if (Cell(i, j) == EMPTYCELL) {
                    grid += "**\t";
                } else if (Cell(i, j) == BORDER) {
                    grid += " \t";
                } else {
                    grid += ("" + Cell(i, j) + "\t");
                }
            }
            grid+="\n\n";
        }
        return grid;
    }

    /**
     * print the board.
     */
    public void print(){System.out.println(this);}

    /**
     * Resets the board to solution.
     */
    public void reset(){

        resetTotalMove();
        resetLastMove();

        //Resets the current configuration to the solution.
        int i,j;
        int consecutive_numbers=1;

        //init the board with consecutive number but also consider the shape of the grid.
        for(i=0;i<getRowNumber();i++){
            for(j=0;j<getColumnNumber();j++){
                if(this.Cell(i,j) != BORDER){
                    this.setCell(i,j,consecutive_numbers);
                    ++consecutive_numbers;
                }
            }
        }

        //find the last cell and do it a movable cell.-1 means movable cell.
        for(i=getColumnNumber()-1;i>=0;i--){
            if(this.Cell(getRowNumber()-1,i) != BORDER){
                this.setCell(getRowNumber()-1,i,EMPTYCELL);
                this.EmptyCell_X=getRowNumber()-1;
                this.EmptyCell_Y=i;
                i=-1;
            }
        }
    }

    /**
     * Sets the board size to given values.
     * The board is reset after this operation.
     * @param newrow The new value of row.
     * @param newcolumn The new values of column.
     */
    public abstract void setsize(int newrow,int newcolumn);

    /**
     * Reads the board from the file given as a parameter.
     * @param fileName name of the file  which will be read.
     */
    public void readFromFile(String fileName){

        int Row = find_rowNumber(fileName);
        int Column = find_columnNumber(fileName);

        setsize(Row,Column);

        Scanner s = null;
        String next = null;

        try {
            s = new Scanner(new File(fileName));

            for(int i=0 ; i<Row ; ++i){
                for(int j=0 ; j<Column ; ++j){
                    next = s.next();
                    if(next.charAt(0)=='b'){
                        this.setCell(i,j,EMPTYCELL);
                        EmptyCell_X = j;
                        EmptyCell_Y = i;
                    }
                    else{
                        this.setCell(i,j,Integer.parseInt(next));
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * finds the row number of the board which is in the file.
     * @param fileName name of the file which will be read.
     * @return number of the row of the board which is in the file.
     */
    private static int find_rowNumber(String fileName){
        FileReader fr = null;
        int counter = 0;
        int temp;
        try{
            fr = new FileReader( new File(fileName));
            temp = fr.read();

            while(temp != -1){
                //if there is a '\n' count it.
                if( (char)temp == '\n'){
                    counter++;

                    //there may be more than one '\n' between two raw so i ignore the raws after the raw.
                    while( (char)temp=='\n'){
                        temp=fr.read();

                        //if there is EOF at the end of the file after a '\n' ignore it.
                        if(temp == -1){
                            counter--;
                        }
                    }
                }
                temp=fr.read();
                if(temp == -1){
                    counter++;
                }
            }
            fr.close();
            return counter;

        }catch (IOException e){
            e.printStackTrace();
        }finally {
            try{
                fr.close();
            }catch (IOException e){
                e.printStackTrace();
            }
        }
        return 0;
    }

    /**
     * finds the column number of the board which is in the file.
     * @param fileName name of the file which will be read.
     * @return number of the column of the board which is in the file.
     */
    private static int find_columnNumber(String fileName){
        FileReader fr=null;
        int counter = 0;
        int temp;
        try{
            fr = new FileReader(fileName);

            //get a character from file
            temp = fr.read();

            //read the file untill the end of the line.
            while( (char)temp != '\n' ){
                //if there is a space count it.
                if( (char)temp == ' ' ){
                    counter++;
                    //there may be more than one space between two column so i ignore the spaces after the space.
                    while( (char)temp == ' ' ){
                        temp=fr.read();

                        //if there is space at the end of the line ignore it.
                        if( (char)temp == '\n' ){
                            counter--;
                        }
                    }
                }

                //get a character from file.
                if( (char)temp != '\n' ){
                    temp=fr.read();
                }

                //count the last space
                if( (char)temp == '\n' ){
                    counter++;
                }
            }
            fr.close();

        }catch (IOException e){
            e. printStackTrace();
        }finally {
            try{
                fr.close();
            }catch (IOException e){
                e.printStackTrace();
            }
        }
        return counter;
    }

    /**
     * Writes the board to the file given as method parameter.
     * @param fileName name of the file.
     */
    public void writeToFile(String fileName){
        File f = new File(fileName);
        FileWriter fw=null;
        try{
            fw = new FileWriter(f);

            for(int i=0;i<RowNumber;i++){
                for(int j=0;j<ColumnNumber;j++){
                    if(this.Cell(i,j)==EMPTYCELL)
                        fw.write("bb ");

				    else if(this.Cell(i,j)<10)
				        fw.write("0" + Cell(i,j) + " ");

				    else
				        fw.write("" + Cell(i,j) + " ");
                }
                fw.write('\n');
            }
            fw.close();
        }catch (IOException e){
            e.printStackTrace();
        }
        finally {
            try{
                fw.close();
            }catch (IOException e){
                e.printStackTrace();

            }
        }
    }

    /**
     * Makes a move according to the given char parameter.
     * @param direction which move should be done.
     * @return returns whether the move has been done.
     */
    public boolean move(char direction){
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
    private boolean move_to_right(){
        if(isitAvaliableCell('R')){
            this.setCell(getEmptyCellY(),getEmptyCellX(),this.Cell(getEmptyCellY(),getEmptyCellX()+1));
            this.setCell(getEmptyCellY(),getEmptyCellX()+1,EMPTYCELL);
            ++EmptyCell_X;
            return true;
        }
        return false;
    }
    private boolean move_to_left(){
        if(isitAvaliableCell('L')){
            this.setCell(getEmptyCellY(),getEmptyCellX(),this.Cell(getEmptyCellY(),getEmptyCellX()-1));
            this.setCell(getEmptyCellY(),getEmptyCellX()-1,EMPTYCELL);
            --EmptyCell_X;
            return true;
        }
        return false;
    }
    private boolean move_to_up(){
        if(isitAvaliableCell('U')){
            this.setCell(getEmptyCellY(),getEmptyCellX(),this.Cell(getEmptyCellY()-1,getEmptyCellX()));
            this.setCell(getEmptyCellY()-1,getEmptyCellX(),EMPTYCELL);
            --EmptyCell_Y;
            return true;
        }
        return false;
    }
    private boolean move_to_down(){
        if(isitAvaliableCell('D')){
            this.setCell(getEmptyCellY(),getEmptyCellX(),this.Cell(getEmptyCellY()+1,getEmptyCellX()));
            this.setCell(getEmptyCellY()+1,getEmptyCellX(),EMPTYCELL);
            ++EmptyCell_Y;
            return true;
        }
        return false;
    }
    private boolean isitAvaliableCell(char direction){
        //check whether the cell which is the destination is available.
        if((direction=='R' || direction=='r')  && EmptyCell_X+1 < ColumnNumber &&
                this.Cell(EmptyCell_Y,EmptyCell_X+1) != BORDER){
            return true;
        }
		else if((direction=='L' || direction=='l') && EmptyCell_X > 0 &&
                this.Cell(EmptyCell_Y,EmptyCell_X-1) != BORDER){
            return true;
        }
		else if((direction=='U' || direction=='u') && EmptyCell_Y > 0 &&
                this.Cell(EmptyCell_Y-1,EmptyCell_X) != BORDER ){
            return true;
        }
		else if((direction=='D' || direction=='d') && EmptyCell_Y+1 < RowNumber &&
                this.Cell(EmptyCell_Y+1,EmptyCell_X) != BORDER){
            return true;
        }
        return false;
    }

    /**
     * Checks the board whether this board is a solution.
     * @return true if the board is a solution.
     */
    public boolean isSolved(){
        //check whether the puzzle solved.
        //returns true if the board is a solution.
        int consecutiveNumbers=1;
        int i,j,flag=0;
        for(i=0;i<RowNumber;i++){
            for(j=0;j<ColumnNumber;j++){
                if(this.Cell(i,j)!=consecutiveNumbers && this.Cell(i,j) != BORDER){
                    flag++;
                }
                if(this.Cell(i,j) != BORDER){
                    consecutiveNumbers++;
                }
            }
        }
        if(flag==1) return true;
        else return false;
    }

    /**
     *compares the content of the cells
     * donesn't consider last move or number of steps.
     * @param other other other parameter to compare.
     * @return return true if the boards are same.
     */
    public boolean equals(Object other){
        //returns if the board are same.
        //This operator just consider the grids.

        //self check
        if(this==other)
            return true;
        //null check
        if(other == null)
            return false;

        if(this.getClass() != other.getClass())
            return false;

        AbstractBoard o = (AbstractBoard)other;

        if(this.RowNumber != o.RowNumber)       return false;
        if(this.ColumnNumber != o.ColumnNumber) return false;

        int i,j;

        for(i=0;i<RowNumber;i++){
            for(j=0;j<ColumnNumber;j++){
                if(this.Cell(i, j) != o.Cell(i, j)){
                    return false;
                }
            }
        }

        return true;
    }

    /**
     *checks whether the array is a valid sequence of moves for a solution.
     * also considers the last moves.
     * doesn't consider the number of moves.
     * @param Sequence The array which will be checked.
     * @return returns true if the array contains a valid sequence of moves for a solutions
     */
    public static boolean isit_ValidSequence(AbstractBoard[] Sequence){
        //the last element should be solved.
        if(!Sequence[Sequence.length-1].isSolved())
            return false;

        if( Sequence[0].lastMove() != 'S' && Sequence[0].lastMove() != 's')
            return false;

        for(int i=0 ; i<Sequence.length-1;++i){
            if(!isit_ValidMove(Sequence[i],Sequence[i+1])) {
                return false;
            }
        }
        return true;
    }
    private static boolean isit_ValidMove(AbstractBoard board1,AbstractBoard board2){
        char move = 'x';
        //this method also consider the last move of the board.
        //there should be two different cell if there is a valid move.
        //if there is a valid move there should be just two differences.
        if(findDifferences(board1,board2) != 2) {
            return false;
        }
        //find which move had done.
        if(board1.getEmptyCellX()==board2.getEmptyCellX()){
            if(board1.getEmptyCellY()==1+board2.getEmptyCellY()){
                move='U';
            }
            else{
                move='D';
            }
        }

        if(board1.getEmptyCellY()==board2.getEmptyCellY()){
            if(board1.getEmptyCellX()==1+board2.getEmptyCellX()){
                move='L';
            }
            else{
                move='R';
            }
        }
        //last move and move that found in this method should be same.
        if(move != board2.lastMove())
            return false;

        return true;
    }
    private static int findDifferences(AbstractBoard board1,AbstractBoard board2){
        int counter=0;
        //if their row number or column number different this means they are entirely different.
        if(board1.getRowNumber() != board2.getRowNumber() || board1.getColumnNumber() != board2.getColumnNumber())
            return -1;

        //look all cell and find how many different cells there is.
        for(int i=0;i<board1.getRowNumber();++i)
            for(int j=0;j<board1.getColumnNumber();++j)
                if(board1.Cell(i,j) != board2.Cell(i,j))
                    ++counter;

        return counter;
    }
}