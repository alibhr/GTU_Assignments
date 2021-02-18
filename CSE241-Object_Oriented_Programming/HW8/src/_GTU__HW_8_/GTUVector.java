package _GTU__HW_8_;

import javax.naming.SizeLimitExceededException;

/**
 * The Vector class implements a growable array of objects.
 * @param <T> generic parameter
 */
public class GTUVector<T> extends GTUContainer<T> implements Cloneable{

    /**
     * constructs a new vector with default capacity.
     */
    public GTUVector(){super();}

    /**
     * constructs a new vector with capacity which determined by user.
     * @param New_capacity initial capacity which determined by user.
     */
    public GTUVector(int New_capacity){super(New_capacity);}

    /**
     * Checks whether the vector has any element.
     * @return returns true if there is any element in vector.
     */
    @Override
    public boolean empty() {return 0 == get_used();}

    /**
     * gets how many element there is in vector.
     * @return returns how many element this vector has.
     */
    @Override
    public int size() {return get_used();}

    /**
     * Getter method
     * @return MAX_SIZE
     */
    @Override
    public int max_size() {return get_MAXSIZE();}

    /**
     *Returns iterator to beginning.
     * @return returns iterator to beginning of container.
     */
    @Override
    public GTUIterator<T> iterator() {return new GTUIterator<T>(Data,get_used(),0);}

    /**
     * Appends the specified component to the end of this container
     * @param value the component to be inserted
     * @return iterator of the content which is inserted.
     * @throws IllegalArgumentException if there is a null argument
     * @throws SizeLimitExceededException This exception is thrown when a method produces a result that exceeds a size-related limit.
     */
    @Override
    @SuppressWarnings("unchecked")
    public GTUIterator<T> insert(T value)throws IllegalArgumentException , SizeLimitExceededException {
        if(value == null){
            throw new IllegalArgumentException();
        }
        if(this.get_used()+1 > MAX_SIZE)
            throw new SizeLimitExceededException();

        if(get_used() >= get_capacity() ){
            this.increase_capacity();
        }
        Data[used] = value;
        ++used;
        return new GTUIterator<T>(Data,used,used-1);
    }

    /**
     * Adds the specified component to this container at the given position.
     * @param position the position at which to insert the component.
     * @param value the component to be added.
     * @return iterator of the content which is inserted.
     * @throws ArrayIndexOutOfBoundsException to indicate that someone trying to access array element with an inappropriate index.
     * @throws IllegalArgumentException to indicate that the method has been passed an illegal or inappropriate argument.
     * @throws SizeLimitExceededException This exception is thrown when a method produces a result that exceeds a size-related limit.
     */
    @Override
    public GTUIterator<T> insert(GTUIterator<T> position, T value)throws ArrayIndexOutOfBoundsException ,IllegalArgumentException,SizeLimitExceededException{
        if(this.get_used() + 1 > this.get_MAXSIZE())
            throw new SizeLimitExceededException();
        if(position == null)
            throw new IllegalArgumentException();
        if(position.get_index() >= this.get_capacity())
            throw new ArrayIndexOutOfBoundsException();
        Object[] Temp = new Object[this.get_capacity()];

        if(get_used() >= get_capacity() ){
            this.increase_capacity();
        }

        for(int i=0 ; i<=position.get_index(); ++i)
            Temp[i]=this.Data[i];

        Temp[position.get_index()+1] = value;

        for(int i = position.get_index()+2; i<get_used()+1 ;++i)
            Temp[i]=this.Data[i-1];

        ++used;
        Data = Temp;
        return new GTUIterator<T>(Data,used,used-1);
    }

    /**
     * erases the component which specified by index from this container.
     * @param position the index of the component to be erased.
     * @return return iterator of position
     * @throws ArrayIndexOutOfBoundsException if index is not in range.
     * @throws IllegalArgumentException to indicate that the method has been passed an illegal or inappropriate argument.
     */
    @Override
    public GTUIterator<T> erase(GTUIterator<T> position)throws ArrayIndexOutOfBoundsException , IllegalArgumentException{
        if(position == null)
            throw new IllegalArgumentException();
        if(position.get_index() >= this.get_capacity())
            throw new ArrayIndexOutOfBoundsException();

        int j=0;
        for(int i=0 ; i < this.get_used() ; ++i){
            if(i != position.get_index()){
                Data[j] = Data[i];
                ++j;
            }
        }
        --used;
        return new GTUIterator<T>(Data,used,0);
    }

    /**
     * erases range of element from container.
     * @param first first element of the range which will be erased
     * @param last last element of the range which will be erased
     * @return return iterator of first
     * @throws ArrayIndexOutOfBoundsException if index is not in range.
     * @throws IllegalArgumentException to indicate that the method has been passed an illegal or inappropriate argument.
     */
    @Override
    public GTUIterator<T> erase(GTUIterator<T> first, GTUIterator<T> last)throws ArrayIndexOutOfBoundsException ,IllegalArgumentException{
        if(first == null ||last==null)
            throw new IllegalArgumentException();
        if(first.get_index() >= this.get_capacity() || last.get_index() >= this.get_capacity())
            throw new ArrayIndexOutOfBoundsException();
        int j=0;
        int Temp_used=get_used();
        for(int i=0 ; i<Temp_used ; ++i){
            if(i < first.get_index() || i>last.get_index()){
                Data[j] = Data[i];
                ++j;
            }
            else {
                --used;
            }
        }
        return new GTUIterator<T>(Data,used,0);
    }

    /**
     * Removes all content from this container.
     */
    @Override
    public void clear() {this.set_capacity(DefaultFirstCapacity);}

    /**
     * Returns true if this container contains the specified element.
     * @param o element whose presence in this container to be tested.
     * @return returns true if this container contains the specified element.
     */
    @Override
    @SuppressWarnings("unchecked")
    public boolean contains(Object o) {
        if(o == null)
            return false;
        for(int i=0 ; i<this.get_used();++i){
            if(this.Data[i].equals((T)o))
                return true;
        }
        return false;
    }

    /**
     * increases the capacity to two times of capacity.
     */
    public void increase_capacity(){
        capacity *=2;
        Object[] Temp = new Object[get_capacity()];

        for(int i=0;i<get_used();++i){
            Temp[i]=Data[i];
        }
        Data = Temp;
    }

    /**
     * Returns a string representation of this vector,containing the string representation of each element.
     * @return a string representation of this vector.
     */
    @SuppressWarnings("unchecked")
    public String toString(){
        if(this.get_used() == 0)
            return "";
        String S = "[";
        for(int i=0;i+1<this.get_used();++i)
            S = S + ((T)this.Data[i]).toString() + ",";
        S = S + ((T)this.Data[get_used()-1]).toString();
        S+="]";
        return S;
    }

    /**
     * Compares each element of the vectors.
     * @param o the object to be compared for equality with this vector
     * @return true if both vector have same elements.
     */
    @SuppressWarnings("unchecked")
    public boolean equals(Object o){
        if(o == null)
            return false;
        if(o == this)
            return true;
        if(!(o instanceof GTUVector))
            return false;
        if(this.get_used() != ((GTUVector) o).get_used())
            return false;
        for(int i=0;i<this.get_used();++i){
            if(this.Data[i] != ((GTUVector) o).Data[i])
                return false;
        }
        return true;
    }

    /**
     * Returns a clone of this vector .
     * @return a clone of this vector.
     * @throws CloneNotSupportedException to indicate that an object could not or should not be cloned.
     */
    public Object clone()throws CloneNotSupportedException{
        GTUVector<T> Temp = new GTUVector<T>(this.get_capacity());
        Temp.used = this.used;
            for(int i=0 ; i<this.get_used() ; ++i)
                Temp.Data[i] = this.Data[i];

        return Temp;
    }

    @Override
    public int hashCode() {
        return super.hashCode();
    }
}
