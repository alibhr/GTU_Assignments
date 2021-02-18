package GTU_Board;

/**
 *extended class for represent the board configuration
 * @author Ali Bahar 171044066
 */
public class BoardArray2D extends AbstractBoard{

    /**
     * map of the puzzle.
     */
    private int[][] grid;

    /**
     * no parameter constructor.
     * creates the board according to default values.
     */
    public BoardArray2D(){
        this(3,3);
    }

    /**
     * creates the board according to given parameters
     * @param newRowNumber number of row number of created board.
     * @param newColumnNumber number of column number of created board.
     */
    public BoardArray2D(int newRowNumber,int newColumnNumber){
        super(newRowNumber,newColumnNumber);
        grid=new int[getRowNumber()][getColumnNumber()];
        for (int i=0;i<getRowNumber();++i){
            for(int j=0;j<getColumnNumber();++j){
                grid[i][j]=1;
            }
        }
        reset();
    }

    /**
     * helps us to clone of a object.
     * @param o another object of this class to copy
     */
    public BoardArray2D(BoardArray2D o){
        this(o.getRowNumber(),o.getColumnNumber());
        for(int i=0;i<getRowNumber();++i)
            for(int j = 0; j < getColumnNumber(); ++j)
                this.grid[i][j] = o.grid[i][j];
    }

    /**
     * Getter method
     * @param index_i y axis of the board.
     * @param index_j x axis of the board.
     * @return returns the content of corresponding cell of the given parameters.
     */
    @Override
    public int Cell(int index_i, int index_j) {
        //Terminates program if the indexes are not valid.
        if(index_i >= RowNumber || index_j >= ColumnNumber || index_i < 0 || index_j < 0){
            System.out.println("index problem !!\n");
            System.exit(1);

        }

        //returns the corresponding cell content of taken indexes.
        return this.grid[index_i][index_j];
    }

    /**
     * arranges the value of the given cell.
     * @param index_i y axis of the board.
     * @param index_j x axis of the board.
     * @param value the new value of the cell.
     */
    @Override
    protected void setCell(int index_i, int index_j, int value) {

        //Terminates program if the indexes are not valid.
        if(index_i >= RowNumber || index_j >= ColumnNumber || index_i < 0 || index_j < 0){
            System.out.println("index problem !!\n");
            System.exit(1);
        }

        grid[index_i][index_j]=value;
    }

    /**
     * Sets the board size to given values.
     * The board is reset after this operation.
     * @param newrow The new value of row.
     * @param newcolumn The new values of column.
     */
    @Override
    public void setsize(int newrow, int newcolumn) {
        //Boards can not be smaller than 3.
        if(newrow < 3 || newcolumn < 3){
            System.out.println("size can not be smaller than 3\n");
            System.exit(1);
        }

        //if there is a discrepancy arrange the allocation again.
        if(ColumnNumber != newcolumn || RowNumber != newrow){
            grid=null;
            this.grid = new int[newrow][newcolumn];
        }

        //assign the other variables.
        ColumnNumber=newcolumn;
        RowNumber=newrow;

        EmptyCell_Y = RowNumber-1;
        EmptyCell_X = ColumnNumber-1;

        for(int i=0;i<RowNumber;++i)
            for(int j=0;j<ColumnNumber;j++)
                grid[i][j]=1;

        reset();
    }

    /**
     * creates a new object.
     * @return returns the created object.
     */
    @Override
    public Object clone(){
        return new BoardArray2D(this);
    }
}