package DataStructureHW7_Q3;

import java.util.Arrays;
import java.util.Random;

/**
 * A Skip List is an alternative to a binary tree that provides for
 * approximately logorithmic searching, insertion, and deletion.
 * Skip Lists were developed by William Pugh and first described in
 * "Skip Lists: A Probabilistic Alternative to Balanced Treees",
 * CACM 13:8 (June 1990) pp 668-676
 * @author Koffman and Wolfgang
 * @param <E> generic data type
 */
public class SkipList<E extends Comparable<E>> {

    /**
     * Head of the skip-list
     */
    private SLNode<E> head;

    /** The current size of the skipList */
    private int size;

    /** Maximum level */
    private int maxLevel;

    /** Nominal maximum capacity */
    private int maxCap;

    /** Natural Log of 2 */
    private static final double LOG2 = Math.log(2.0);

    /** A random number generator */
    private final Random rand = new Random();

    /**
     * Constructs a new skip-list
     */
    public SkipList(){
        maxLevel = 2;
        size = 0;
        maxCap = computeMaxCap(maxLevel);
        head = new SLNode<>(maxLevel,null);
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
        ++size;
        SLNode<E>[] pred = search(item);

        if(size > maxCap){
            ++maxLevel;
            maxCap = computeMaxCap(maxLevel);
            head.links = Arrays.copyOf(head.links,maxLevel);
            pred = Arrays.copyOf(pred,maxLevel);
            pred[maxLevel-1] = head;
        }

        SLNode<E> newNode = new SLNode<>(logRandom(),item);
        for(int i=0 ; i<newNode.links.length ; ++i){
            newNode.links[i] = pred[i].links[i];
            pred[i].links[i] = newNode;
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
    private SLNode<E>[] search(E item){
        SLNode<E>[] pred = (SLNode<E>[]) new SLNode[maxLevel];
        SLNode<E> current = head;

        for(int i=current.links.length-1 ; i>=0 ; --i){
            while(current.links[i] != null && current.links[i].data.compareTo(item) < 0){
                current = current.links[i];
            }
            pred[i] = current;
        }

        return pred;
    }

    /**
     * removes an item
     * @param item item to be removed
     * @return true if the item is removed.
     */
    public boolean remove(E item){
        SLNode<E>[] pred = search(item);

        if(pred[0].links != null &&
                pred[0].links[0].data.compareTo(item) != 0){
            return false;
        } else {
            size--;
            SLNode<E> deleteNode = pred[0];
            for(int i = 0; i < deleteNode.links.length; ++i){
                if(pred[i].links[i] != null)
                    pred[i].links[i] = pred[i].links[i].links[i];
            }
            return true;
        }
    }

    /**
     * Find an object in the skip list
     * @param target The item being sought
     * @return A reference to the object in the skip list that compares
     *         equal as determined by compareTo to the target. If not
     *         found null is returned.
     */
    public E find(E target){
        SLNode<E>[] pred = search(target);

        /*
        for(int i=0 ; i<pred.length ; ++i){
            if(pred[i] != null){
                System.out.print(pred[i].data + " ");
            }
        }
        System.out.print("\n");
        */

        if(pred[0].links != null && pred[0].links[0].data.compareTo(target) == 0){
            return pred[0].links[0].data;
        }
        else{
            return null;
        }
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
        SLNode<E> temp = head;

        for(int i=0 ; i < maxLevel ; ++i){
            temp = head;
            while(temp != null && temp.links[i] != null){
                sb.append(temp.links[i].data).append(" ");
                temp = temp.links[i];
            }
            sb.append("\n");
        }

        return sb.toString();
    }

    /** Static class to contain the data and the links */
    private static class SLNode<E>{
        SLNode<E>[] links;
        E data;

        /** Create a node of level n */
        @SuppressWarnings("unchecked")
        public SLNode(int m,E data){
            links = (SLNode<E>[]) new SLNode[m];
            this.data = data;
        }

    }
}