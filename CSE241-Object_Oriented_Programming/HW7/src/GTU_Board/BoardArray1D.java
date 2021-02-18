package GTU_Board;

/**
 *extended class for represent the board configuration
 */
public class BoardArray1D extends AbstractBoard{

    /**
     * map of the puzzle.
     */
    private int[] grid;

    /**
     * no parameter constructor.
     * creates the board according to default values.
     */
    public BoardArray1D(){
        this(3,3);
    }

    /**
     * creates the board according to given parameters
     * @param newRowNumber number of row number of created board.
     * @param newColumnNumber number of column number of created board.
     */
    public BoardArray1D(int newRowNumber,int newColumnNumber){
        super(newRowNumber,newColumnNumber);
        grid = new int[getRowNumber() * getColumnNumber()];

        for(int i=0;i<getRowNumber() * getColumnNumber();++i)
            grid[i]=1;

        super.reset();
    }

    /**
     * helps us to clone of a object.
     * @param o another object of this class to copy
     */
    public BoardArray1D(BoardArray1D o){
        this(o.getRowNumber(),o.getColumnNumber());
        for(int i=0;i<RowNumber * ColumnNumber;++i)
            this.grid[i] = o.grid[i];
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
        if(index_i >= RowNumber || index_j >= ColumnNumber || index_i < 0 || index_j < 0)	{
            System.out.println("index problem");
            System.exit(1);
        }
        //returns the corresponding cell content of taken indexes.
        int index = index_i * ColumnNumber + index_j;
        return this.grid[index];
    }

    /**
     * arranges the value of the given cell.
     * @param index_i y axis of the board.
     * @param index_j x axis of the board.
     * @param value the new value of the cell.
     */
    @Override
    protected void setCell(int index_i, int index_j, int value) {
        if(index_i >= RowNumber || index_j >= ColumnNumber || index_i < 0 || index_j < 0)	{
            System.out.println("index problem");
            System.exit(1);
        }
        int index = index_i * ColumnNumber + index_j;
        this.grid[index]=value;
    }

    /**
     * Sets the board size to given values.
     * The board is reset after this operation.
     * @param newrow The new value of row.
     * @param newcolumn The new values of column.
     */
    @Override
    public void setsize(int newrow, int newcolumn) {
        if(newrow < 3 || newcolumn < 3){
            System.out.println("size can not be smaller than 3\n");
            System.exit(1);
        }

        //if there is a discrepancy arrange the allocation again.
        if(ColumnNumber != newcolumn || RowNumber != newrow){
            this.grid=null;
            this.grid=new int[newcolumn*newrow];
        }

        //assign the other variables.
        ColumnNumber=newcolumn;
        RowNumber=newrow;

        EmptyCell_Y = RowNumber-1;
        EmptyCell_X = ColumnNumber-1;

        for(int i=0;i<getRowNumber() * getColumnNumber();++i)
            grid[i]=1;

        reset();
    }

    /**
     * creates a new object.
     * @return returns the created object.
     * @author Ali Bahar 171044066
     */
    @Override
    public Object clone(){
        return new BoardArray1D(this);
    }
}