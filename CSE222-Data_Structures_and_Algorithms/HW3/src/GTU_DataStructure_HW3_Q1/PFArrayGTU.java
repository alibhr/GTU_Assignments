package GTU_DataStructure_HW3_Q1;

/**
 * An array class implementation to be able to manipulate  an array easily.
 * @param <E> The type of data which will be kept.
 */
public class PFArrayGTU<E> implements Cloneable{

    private E[] data;
    private int used;
    private int capacity;
    private static final int Const_capacity = 5;

    /**
     * Creates a new PFArrayGTU with Default capacity.
     */
    public PFArrayGTU(){
        this(Const_capacity);
    }

    /**
     * Creates a new PFArrayGTU with given capacity.
     * @param initCapacity First capacity.
     */
    @SuppressWarnings("unchecked")
    public PFArrayGTU(int initCapacity){
        this.data = (E[]) new Object[initCapacity];
        this.capacity = initCapacity;
        this.used = 0;
    }

    /**
     * Create a new PFArrayGTU same with PFArrayGTU which came as parameter.
     * @param toClone the PFArrayGTU which will be cloned.
     */
    @SuppressWarnings("unchecked")
    public PFArrayGTU(PFArrayGTU<E> toClone){
        if(toClone == null)
            throw new NullPointerException();

        this.data = (E[]) new Object[toClone.getCapacity()];
        this.capacity = toClone.getCapacity();
        this.used = toClone.getUsed();

        if (toClone.getUsed() >= 0)
            System.arraycopy(toClone.data, 0, this.data, 0, toClone.getUsed());
    }

    /**
     * returns the capacity of the array.
     * @return the capacity of the array.
     */
    public int getCapacity() {
        return capacity;
    }

    /**
     * returns the constant capacity of the array.
     * @return the const capacity of the array.
     */
    public static int getConstCapacity() {
        return Const_capacity;
    }

    /**
     * returns the size.
     * @return the size.
     */
    public int getUsed() {
        return used;
    }

    /**
     * gets the data at the specified position in this PFArrayGTU.
     * @param index index of the element to return.
     * @return the element at the specified position in this PFArrayGTU.
     */
    public E getData(int index) {
        if(index >= this.getUsed()){
            throw new ArrayIndexOutOfBoundsException();
        }

        return data[index];
    }

    /**
     * Appends the specified element to the end of this PFArrayGTU.
     * @param newElement element to be appended to this PFArrayGTU.
     */
    public void addElement(E newElement){
        if(this.getUsed() >= capacity){
            throw new ArrayIndexOutOfBoundsException();
        }
        this.data[this.used] = newElement;
        ++this.used;
    }

    /**
     * Inserts the specified element at the specified position in this PFArrayGTU.
     * @param index index at which the specified element is to be inserted.
     * @param newElement element to be inserted to this PFArrayGTU.
     */
    public void insertElement(int index,E newElement){
        if(this.getUsed() >= capacity){
            throw new ArrayIndexOutOfBoundsException();
        }

        for(int i = this.used ; i > index ; --i)
            data[i] = data[i-1];

        this.data[index] = newElement;
        ++this.used;
    }

    /**
     * Finds the element and returns the index of this element if the element inside this PFArrayGTU.
     * @param elementToSearch The element which will be searched inside this PFArrayGTU.
     * @return the index of the element, if the element can't be found -1 will be returned.
     */
    public int findElement(E elementToSearch){
        for(int i=0 ; i<this.used ; ++i){
            if(data[i].equals(elementToSearch))
                return i;
        }
        return -1;
    }

    /**
     * Removes the element at he specified position in this PFArrayGTU.
     * @param index index of the element to be removed.
     */
    public void removeAnElement(int index){
        if(index >= this.used){
            throw new ArrayIndexOutOfBoundsException();
        }

        for(int i=index ; i<this.used-1 ; ++i){
            data[i] = data[i + 1];
        }

        --this.used;
    }

    /**
     * Replaces the element at the specified position in this LinkedArrayList with the specified element.
     * @param index index of the element to replace.
     * @param newData element to be stored at the specified position.
     */
    public void setData(int index,E newData){
        if(index >= this.used){
            throw new ArrayIndexOutOfBoundsException();
        }
        data[index] = newData;
    }

    /**
     * returns true if there is no element in this PFArrayGTU.
     * @return true if there is no element in this PFArrayGTU.
     */
    public boolean isEmpty(){
        return this.used == 0;
    }

    /**
     * returns true if there is no space to add a new element in this PFArrayGTU.
     * @return true if there is no space to add a new element in this PFArrayGTU.
     */
    public boolean isFull(){
        return this.capacity == this.used;
    }

    /**
     * returns the PFArrayGTU as a string.
     * @return the PFArrayGTU as a string.
     */
    @Override
    public String toString() {
        if (this.used == 0){
            return "{}";
        }
        StringBuilder sB = new StringBuilder("{ ");
        int i = 0;
        for(i=0 ; i<this.used-1 ; ++i)
            sB.append(data[i].toString()).append(", ");
        sB.append(data[i].toString()).append(" }");

        return sB.toString();
    }

    /**
     * returns true if the array has same elements with the array which came as parameter.
     * @param obj the other object which will be compared.
     * @return true if the array has same elements with the array which came as parameter.
     */
    @SuppressWarnings("unchecked")
    @Override
    public boolean equals(Object obj) {
        if(obj == null)
            return false;
        if(this == obj)
            return true;
        if(this.getClass() != obj.getClass())
            return false;

        for(int i=0 ; i<this.used ; ++i)
            if(!  data[i].equals(  ( (PFArrayGTU<E>)obj ).getData(i))  )
                return false;

        return true;
    }

    /**
     * Creates the clone of the this array.
     * @return the clone of the this array.
     * @throws CloneNotSupportedException to indicate that an object could not or should not be cloned.
     */
    @Override
    protected Object clone() throws CloneNotSupportedException {
        super.clone();
        return new PFArrayGTU<E>(this);
    }

    /**
     * returns a hashcode from super class.
     * @return a hashcode from super class.
     */
    @Override
    public int hashCode() {
        return super.hashCode();
    }
}