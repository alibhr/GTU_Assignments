package DataStructureHW7_Q2;

import java.util.Arrays;
import java.util.Random;

/**
 * modified skip list implementation
 * @param <E> generic data type
 */
public class SkipListGTU<E extends Comparable<E>> {
    /**
     * Head of the skip-list
     */
    private SLNodeGTU<E> head;

    /** The current size of the skipList */
    private int size;

    /** Maximum level */
    private int maxLevel;

    /** Nominal maximum capacity */
    private int maxCap;

    /** Nominal maximum node size */
    private int maxNodeSize;

    /** Nominal minimum node size */
    private int minNodeSize;

    /** Natural Log of 2 */
    private static final double LOG2 = Math.log(2.0);

    /** A random number generator */
    private final Random rand = new Random();

    /**
     * Constructs a new skip-list
     * @param max maximum element number of the node.
     * @param min minimum element number of the node.
     */
    public SkipListGTU(int max,int min){
        size = 0;
        maxLevel = 2;
        maxNodeSize = max;
        minNodeSize = min;
        maxCap = computeMaxCap(maxLevel);
        head = new SLNodeGTU<>(maxLevel,maxNodeSize);
    }

    /**
     * Method to compute the maximum capacity, given the maximum
     * level. It computes Math.pow(2, maxLevel) - 1, using shift.
     * @param maxLevel the maximum level.
     * @return Math.pow(2, maxLevel+1) - 1;
     */
    private static int computeMaxCap(int maxLevel) {
        return ~(~0 << maxLevel);
    }

    /**
     * Method to generate a logarithmic distributed integer between 1 and maxLevel.
     *  I.E. 1/2 of the values are 1, 1/4 are 2, etc.
     * @return a random logarithmic distributed int between 1 and maxLevel
     */
    private int logRandom(){
        int r = rand.nextInt(maxCap);
        int k = (int) ( Math.log(r+1) / LOG2 );
        if(k > maxLevel-1){
            k = maxLevel-1;
        }
        return maxLevel - k;
    }

    /**
     * Inserts the given item
     * @param item The item to add
     * @return true as the item is added
     */
    public boolean add(E item){
        boolean flag= false;
        ++size;
        SLNodeGTU<E>[] pred = search(item);
        if(size > maxCap){
            ++maxLevel;
            maxCap = computeMaxCap(maxLevel);
            head.links = Arrays.copyOf(head.links,maxLevel);
            pred = Arrays.copyOf(pred,maxLevel);
            pred[maxLevel-1] = head;
            flag = true;
        }

        if(pred[0] == head){
            pred[0] = pred[0].links[0];
        }

        while(pred[0] != null && pred[0].isFull()){
            E temp = pred[0].popLast();
            pred[0].addToNode(item);
            pred[0] = pred[0].links[0];
            item = temp;
        }

        if(pred[0] == null){
            pred = search(item);
            if(flag){
                pred = Arrays.copyOf(pred,maxLevel);
                pred[maxLevel-1] = head;
            }
            SLNodeGTU<E> newNode = new SLNodeGTU<>(logRandom(),maxNodeSize);
            newNode.addToNode(item);

            for(int i=0 ; i<newNode.links.length ; ++i){
                newNode.links[i] = pred[i].links[i];
                pred[i].links[i] = newNode;
            }
        }else{
            pred[0].addToNode(item);
        }

        return true;
    }

    /**
     * Search for an item in the list
     * @param item The item being sought
     * @return A SLNode array which references the nodes
     *         preceding the sought item at each level.
     */
    @SuppressWarnings("unchecked")
    private SLNodeGTU<E>[] search(E item){
        SLNodeGTU<E>[] pred = (SLNodeGTU<E>[]) new SLNodeGTU[maxLevel];
        SLNodeGTU<E> current = head;

        for(int i=current.links.length-1 ; i>=0 ; --i){
            while(current.links[i] != null && !current.links[i].isEmpty() && current.links[i].getLast().compareTo(item) < 0){
                current = current.links[i];
            }
            pred[i] = current;
        }

        return pred;
    }

    /**
     * returns the string representation of  the skip-list
     * @return the string representation of  the skip-list
     */
    @Override
    public String toString() {
        if(size == 0){
            return "empty";
        }

        StringBuilder sb = new StringBuilder();
        SLNodeGTU<E> temp = head;

        for(int i=0 ; i < maxLevel ; ++i){
            temp = head;
            while(temp != null && temp.links[i] != null){
                sb.append(Arrays.toString(temp.links[i].data)).append(" ");
                temp = temp.links[i];
            }
            sb.append("\n");
        }

        return sb.toString();
    }

    /** Static class to contain the data and the links */
    private static class SLNodeGTU<E extends Comparable<E>>{
        private SLNodeGTU<E>[] links;
        private E[] data;
        private int size;
        private int maxSize;

        /** Create a node of level n */
        @SuppressWarnings("unchecked")
        public SLNodeGTU(int linkSize,int maxSize){
            links = (SLNodeGTU<E>[]) new SLNodeGTU[linkSize];
            data = (E[]) new Comparable[maxSize];
            size = 0;
            this.maxSize = maxSize;
        }

        /**
         * adds a new element in descending order
         * @param item the new item
         * @return true as the item is added
         */
        public boolean addToNode(E item){
            if(isFull()){
                return false;
            }
            int index = 0;

            while(index<size && data[index] != null && item.compareTo(data[index])>0){
                ++index;
            }

            add(index,item);

            return true;
        }

        /**
         * adds a new item to indicated index.
         * @param index
         * @param item
         */
        public void add(int index,E item){
            for(int i=size ; i>index ;--i){
                data[i] = data[i-1];
            }
            data[index] = item;
            ++size;
        }

        /**
         * gets the item from indicated index
         * @param index the index of the element which will be returned.
         * @return the item from indicated index
         */
        public E get(int index){
            if(index >= size){
                return null;
            }
            return data[index];
        }

        /**
         * returns the last element.
         * @return the last element.
         */
        public E getLast(){
            if(size == 0)
                return null;
            return data[this.size-1];
        }

        /**
         * returns the last element and removes it
         * @return the last element.
         */
        public E popLast(){
            if(size == 0){
                return null;

            }
            --size;
            return data[this.size];
        }

        /**
         * returns the element number of the node.
         * @return the element number of the node.
         */
        public int size(){
            return size;
        }

        /**
         * returns true if the node is full, otherwise returns false.
         * @return true if the node is full, otherwise returns false.
         */
        public boolean isFull(){
            return size == maxSize;
        }

        /**
         * returns true if the node is empty, otherwise returns false.
         * @return true if the node is empty, otherwise returns false.
         */
        public boolean isEmpty(){
            return size == 0;
        }

        /**
         * returns the string representation of the node
         * @return the string representation of the node
         */
        @Override
        public String toString() {
            StringBuilder sb = new StringBuilder("[");
            for(int i=0 ; i<size-1 ; ++i){
                sb.append(data[i]).append(", ");
            }
            sb.append(data[size-1]).append("]");
            return sb.toString();
        }
    }
}