package _GTU__HW_8_;

import java.util.NoSuchElementException;

/**
 * An iterator over a container.
 * @param <T> generic parameter
 */
public class GTUIterator<T>{

    private Object[] DataArr;
    private int index;
    private int used;

    /**
     * constructs a new iterator with default capacity.
     * @param otherDataArr an array which will be iterated
     * @param used How many field used from this array.
     */
    protected GTUIterator(Object[] otherDataArr,int used){this(otherDataArr,used,0);}

    /**
     * constructs a new iterator with default capacity.
     * @param otherDataArr an array which will be iterated
     * @param New_used How many field from in this array.
     * @param New_index which element iterating currently
     */
    protected GTUIterator(Object[] otherDataArr,int New_used,int New_index){
        used = New_used;
        index = New_index;

        this.DataArr = otherDataArr;
    }

    /**
     * copy constructor
     * @param o To copy
     */
    protected GTUIterator(GTUIterator<T> o){this(o.DataArr,o.used,o.index);}

    /**
     * Returns which element is iterated currently
     * @return Returns which element is iterated currently
     */
    public int get_index(){return index;}

    /**
     * Returns true if the iteration has more element
     * @return true if iteration has more elelemt.
     */
    public boolean hasNext(){return (index < used);}

    /**
     * Returns the next element in the iteration
     * @return the next element in the iteration
     * @throws NoSuchElementException - if the iteration has no more elements
     */
    @SuppressWarnings("unchecked")
    public T next()throws NoSuchElementException {
        T temp = (T)this.DataArr[index];
        ++index;
        return temp;
    }

    /**
     * Returns a string representation of element which is iterated.
     * @return Returns a string representation of element which is iterated.
     */
    @SuppressWarnings("unchecked")
    public String toString(){return ((T)DataArr[index]).toString();}

    /**
     * Returns a clone of this iterator .
     * @return Returns a clone of this iterator .
     */
    public GTUIterator<T> clone(){return new GTUIterator<T>(this);}

    /**
     * Compares each element of the iterator.
     * @param other the object to be compared for equality with this iterator.
     * @return return true if both iterator are same.
     */
    @SuppressWarnings("unchecked")
    public boolean equals(Object other){

        if(other == null)
            return false;

        if(this == other)
            return true;

        if(!(other instanceof GTUIterator))
            return false;

        if(this.index != ((GTUIterator<T>) other).index || this.used != ((GTUIterator<T>) other).used)
            return false;

        for(int i=0 ; i<this.used ; ++i)
            if(this.DataArr[i] != ((GTUIterator<T>) other).DataArr[i])
                return false;

        return true;
    }

    @Override
    public int hashCode() {
        return super.hashCode();
    }
}