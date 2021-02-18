package _GTU__HW_8_;

import javax.naming.SizeLimitExceededException;

/**
 * Generic Abstract class
 * @author Ali BAHAR - 171044066
 * @param <T> generic parameter
 */
public abstract class GTUContainer <T>{

    /**
     * keeps actual data.
     */
    protected Object[] Data;

    /**
     *used space in container.
     */
    protected int used;

    /**
     * usable space in container.
     */
    protected int capacity;

    /**
     * Max size can be possible.
     */
    protected static final int MAX_SIZE = 100;

    /**
     * Default capacity of containers.
     */
    protected static final int DefaultFirstCapacity = 2;

    /**
     * constructs a new container with default capacity.
     */
    GTUContainer(){this(DefaultFirstCapacity);}

    /**
     * constructs a new container with capacity which determined by user.
     * @param New_capacity initial capacity which determined by user.
     */
    GTUContainer(int New_capacity){this.set_capacity(New_capacity);}

    protected void set_capacity(int New_capacity){
        this.used=0;
        this.capacity = New_capacity;
        if(New_capacity <= 0){
            this.capacity = DefaultFirstCapacity;
        }
        Data = new Object[this.get_capacity()];
    }

    /**
     * Gets the component in this container.
     * @param index the index of the component to get.
     * @return index^th component of this container.
     */
    @SuppressWarnings("unchecked")
    public T get(int index){return (T)Data[index];}

    /**
     * Getter method
     * @return used
     */
    public int get_used(){return used;}

    /**
     * Getter method
     * @return capacity
     */
    public int get_capacity(){return capacity;}

    /**
     * Getter method
     * @return MAX_SIZE
     */
    public int get_MAXSIZE(){return MAX_SIZE;}

    /**
     * Checks whether the container has any element.
     * @return returns true if there is any element in container.
     */
    public abstract boolean empty();

    /**
     * gets how many element there is in container.
     * @return returns how many element this container has.
     */
    public abstract int size();

    /**
     *gets limit of the container.
     * @return return limit of the container.
     */
    public abstract int max_size();

    /**
     *Returns iterator to beginning.
     * @return returns iterator to beginning of container.
     */
    public abstract GTUIterator<T> iterator();

    /**
     * Appends the specified component to the end of this container
     * @param value the component to be inserted
     * @return iterator of the content which is inserted.
     * @throws IllegalArgumentException if there is a null argument
     * @throws SizeLimitExceededException This exception is thrown when a method produces a result that exceeds a size-related limit.
     */
    public abstract GTUIterator<T> insert(T value)throws IllegalArgumentException, SizeLimitExceededException;

    /**
     * Adds the specified component to this container at the given position.
     * @param position the position at which to insert the component.
     * @param value the component to be added.
     * @return iterator of the content which is inserted.
     * @throws ArrayIndexOutOfBoundsException to indicate that someone trying to access array element with an inappropriate index.
     * @throws IllegalArgumentException to indicate that the method has been passed an illegal or inappropriate argument.
     * @throws SizeLimitExceededException This exception is thrown when a method produces a result that exceeds a size-related limit.
     */
    public abstract GTUIterator<T> insert(GTUIterator<T> position,T value)throws ArrayIndexOutOfBoundsException ,IllegalArgumentException,SizeLimitExceededException;

    /**
     * erases the component which specified by index from this container.
     * @param position the index of the component to be erased.
     * @return return iterator of position
     * @throws ArrayIndexOutOfBoundsException if index is not in range.
     * @throws IllegalArgumentException to indicate that the method has been passed an illegal or inappropriate argument.
     */
    public abstract GTUIterator<T> erase(GTUIterator<T> position)throws ArrayIndexOutOfBoundsException ,IllegalArgumentException;

    /**
     * erases range of element from container.
     * @param first first element of the range which will be erased
     * @param last last element of the range which will be erased
     * @return return iterator of first
     * @throws ArrayIndexOutOfBoundsException if index is not in range.
     * @throws IllegalArgumentException to indicate that the method has been passed an illegal or inappropriate argument.
     */
    public abstract GTUIterator<T> erase(GTUIterator<T> first,GTUIterator<T> last)throws ArrayIndexOutOfBoundsException ,IllegalArgumentException;

    /**
     * Removes all content from this container.
     */
    public abstract void clear();

    /**
     * Returns true if this container contains the specified element.
     * @param o element whose presence in this container to be tested.
     * @return returns true if this container contains the specified element.
     */
    public abstract boolean contains(Object o);
}