package DataStructureHW5_Q4;

import DataStructureHW5_Q3.AgeDataInterface;
import java.util.ArrayList;
import java.util.Comparator;

/**
 * Max Heap implementation (Where the maximum element is in the root node.
 * @param <E> the type of data which extends from AgeDataInterface.
 * @author Ali Bahar 171044066
 */
public class MaxHeap<E extends AgeDataInterface<E>>{

    /**
     * The All data will be in this ArrayList.
     */
    private ArrayList<E> theData;

    /**
     * The comparator to compare two objects.
     */
    private Comparator<E> comparator;

    /**
     * constructs a new empty MaxHeap with default comparator (compares the number of people)
     */
    public MaxHeap(){
        this.theData = new ArrayList<>();
        this.comparator = Comparator.comparingInt(AgeDataInterface::getNumberOfPeople);
    }

    /**
     * Constructs a new empty MaxHeap with given comparator.
     * @param c the given comparator.
     */
    public MaxHeap(Comparator<E> c){
        this.theData = new ArrayList<>();
        this.comparator = c;
    }

    /**
     * add a new record. It will first check if an AgeData object with that age exists in any index of the ArrayList.
     * @param item the item to be added.
     * @return true if the item has been added, otherwise returns false.
     */
    public boolean add(E item){
        if(item.getNumberOfPeople() < 1)
            return false;

        for(int i=0 ; i<theData.size() ; ++i){
            if(theData.get(i).compareTo(item)==0){
                theData.get(i).setNumberOfPeople(theData.get(i).getNumberOfPeople() + item.getNumberOfPeople());

                reHeap((i-1)/2 ,i);

                return true;
            }
        }

        theData.add(item);

        return true;
    }
    private void swap(int index1, int index2){
        E temp = theData.get(index1);
        theData.set(index1,theData.get(index2));
        theData.set(index2,temp);
    }
    private void reHeap(int parent,int child){
        while(comparator.compare(theData.get(child),theData.get(parent)) > 0){
            swap(child,parent);
            child = parent;
            parent = ( (parent-1)/2 );
        }
    }

    /**
     * first check if a node with that age exists. If it exists and If the number of people field is 1, it will remove the node,
     * If the number of people filed is greater than 1, it will decrease the number of people field.
     * @param item the item to be removed.
     * @return true if the item has been removed, otherwise returns false.
     */
    public boolean remove(E item){
        int age = item.getAge();
        int parent;

        if( (parent = findIndex(age)) != -1){
            if(theData.get(parent).getNumberOfPeople() > 1 ){
                theData.get(parent).decrementNumberOfPeople();
                reHeap(parent);
            }
            else{
                swap(parent,theData.size()-1);
                theData.remove(theData.size()-1);
            }
            return true;
        }

        return  false ;
    }
    private int findIndex(int age){
        for(int i=0 ; i<theData.size() ; ++i){
            if(theData.get(i).getAge() == age){
                return i;
            }
        }
        return -1;
    }
    private void reHeap(int parent){
        int leftChild = 2 * parent + 1;
        int rightChild = leftChild + 1;
        int maxChild = leftChild;
        while(leftChild < theData.size()){
            //maxChild = leftChild; //odevi gonderdikten sonra ekledim.
            if(rightChild < theData.size() && comparator.compare(theData.get(maxChild),theData.get(rightChild)) < 0){
                maxChild = rightChild;
            }
            if(comparator.compare(theData.get(parent),theData.get(maxChild)) < 0){
                swap(parent,maxChild);
                leftChild = 2 * maxChild + 1;
                rightChild = leftChild + 1;
            }
            else {
                leftChild = theData.size();
            }
        }
    }

    /**
     * gets an AgeData object of any age and find the AgeData object with the same age and return it.
     * @param toFind the item to be found.
     * @return AgeData which is found or null.
     */
    public E find(E toFind){
        int index = findIndex(toFind.getAge());

        if(index != -1)
            return theData.get(index);

        return null;
    }

    /**
     * returns the number of people younger than an age.
     * @param anAge an age to compare.
     * @return the number of people younger than an age.
     */
    public int youngerThan(int anAge){
        int younger = 0;
        for(E e : theData){
            if(e.getAge() < anAge){
                younger += e.getNumberOfPeople();
            }
        }
        return younger;
    }

    /**
     * returns number of people older than an age.
     * @param anAge an age to compare.
     * @return number of people older than an age.
     */
    public int olderThan(int anAge){
        int older = 0;
        for(E e : theData){
            if(e.getAge() > anAge){
                older += e.getNumberOfPeople();
            }
        }
        return older;
    }

    /**
     * Returns a string representation of the Heap.
     * @return a string representation of the Heap.
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for(E e : theData){
            sb.append(e.toString()).append("\n");
        }

        return sb.toString();
    }
}