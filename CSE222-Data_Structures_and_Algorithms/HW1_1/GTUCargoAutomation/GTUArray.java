package GTUCargoAutomation;

/**
 * The GTUArray class implements a growable array of objects.
 * @param <T> The type of data which will be kept.
 * @author Ali Bahar
 * @author 171044066
 */
public class GTUArray <T> {
    private Object[] Data;
    private int used;
    private int capacity;

    /**
     * Creates a new GTUArray with given capacity.
     * @param NewCapacity First capacity.
     */
    public GTUArray(int NewCapacity){this.setCapacity(NewCapacity);}

    /**
     * Creates a new GTUArray with Default(2) capacity.
     */
    public GTUArray(){this(2);}

    /**
     * gets capacity of GTUArray.
     * @return capacity of GTUArray.
     */
    public int getCapacity(){return this.capacity;}

    /**
     * gets How many data have been stored.
     * @return How many data have been stored.
     */
    public int getUsed(){return this.used;}

    /**
     * Gets data in The given index.
     * @param index index of array.
     * @return data in The given index.
     */
    @SuppressWarnings("unchecked")
    public T getData(int index){
        if (index >= used)
            throw new ArrayIndexOutOfBoundsException();
        return (T) Data[index];
    }

    private void setCapacity(int NewCapacity){
        this.used = 0;
        this.capacity = NewCapacity;
        if(this.capacity < 1){
            this.capacity = 2;
        }
        this.Data = new Object[this.getCapacity()];
    }

    /**
     * Adds data.
     * @param NewData The data which will be added.
     */
    public void addData(T NewData) {
        if(this.used >= this.capacity){
            this.capacity *=2;
            Object[] temp = new Object[capacity];

            for(int i=0;i<used;++i)
                temp[i] = this.Data[i];

            this.Data = temp;
            temp = null;
        }
        Data[used] = NewData;
        ++used;
    }

    /**
     * Erases the data which is in the index.
     * @param index the index of data which will be erased.
     */
    public void eraseData(int index){
        if(index < 0 || index >= used)
            throw new ArrayIndexOutOfBoundsException();

        for(int i=index ; i < used-1 ; ++i)
            Data[i] = Data[i+1];

        --used;
    }

    /**
     * Finds the index of data.
     * @param toFind The data which will be searched.
     * @return if the Data can be found returns index.if the Data can't be found returns -1.
     */
    public int find(T toFind){
        for(int i=0 ; i<getUsed() ; ++i)
            if(Data[i] == toFind)
                return i;
        return -1;
    }

    /**
     * Creates a string which have all data.
     * @return All data as String.
     */
    @Override
    public String toString(){

        String to = "[";
        int i=0;
        for(;i<getUsed()-1 ; ++i)
            to = to + Data[i].toString() + ",";
        to = to + Data[i] +"]\n";

        return to;
    }
}