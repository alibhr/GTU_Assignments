package GTU_DataStructure_HW3_Q1;

import java.util.AbstractList;
import java.util.List;
import java.util.ListIterator;
import java.util.NoSuchElementException;

/**
 * Doubly-Linked list implementation which keeps partially filled arrays in its nodes.
 * @param <E> to keep generic data in LinkedArrayList.
 */
public class LinkedArrayList<E>  extends AbstractList<E> implements List<E>{

    /**
     * first node of the liked list.
     */
    private Node<E> head;

    /**
     * last element of the linked list.
     */
    private Node<E> tail;

    /**
     * Size of LinkedArrayList.
     */
    private int size;

    /**
     * Constructs an empty LinkedArrayList.
     */
    public LinkedArrayList(){
        head = null;
        tail = null;
        size = 0;
    }

    /**
     * Appends the specified element to the end of this LinkedArrayList.
     * @param element element to be appended to this LinkedArrayList.
     * @return true.
     */
    @Override
    public boolean add(E element) {
        if(tail == null){
            head = new Node<>(null,null);
            tail = head;
            head.data.addElement(element);
            ++size;
            return true;
        }

        else if(tail.data.isFull()){
            tail.next = new Node<>(null,tail);
            tail = tail.next;
            tail.data.addElement(element);
            ++size;
            return true;
        }

        else {
            tail.data.addElement(element);
            ++size;
            return true;
        }
    }

    /**
     * Inserts the specified element at the specified position in this LinkedArrayList.
     * @param index index at which the specified element is to be inserted.
     * @param element element to be inserted.
     */
    @Override
    public void add(int index, E element) {
        ListIterator<E> iter = this.listIterator(index);
        iter.add(element);
    }

    /**
     * Removes the element at the specified position in this LinkedArrayList.
     * @param index the index of the element to be removed.
     * @return the element that was removed from the LinkedArrayList.
     */
    @Override
    public E remove(int index) {
        if(index < 0 || index >= size)
            throw new ArrayIndexOutOfBoundsException("size : " + size + "   index : " + index);

        Node<E> tempRef = head;
        while(index >= tempRef.data.getUsed()){
            index -= tempRef.data.getUsed();
            tempRef = tempRef.next;
        }

        E toReturn = tempRef.data.getData(index);
        tempRef.data.removeAnElement(index);

        if(tempRef.data.isEmpty()){

            if(tempRef == head && tempRef == tail){
                head = null;
                tail = null;
            }

            else if(tempRef == head){
                head = head.next;
                head.prev = null;
            }
            else if (tempRef == tail){
                tail = tail.prev;
                tail.next = null;
            }
            else{
                tempRef.prev.next = tempRef.next;
                tempRef.next.prev = tempRef.prev;
                tempRef.next = null;
                tempRef.prev = null;
            }
        }

        --size;
        return  toReturn;
    }

    /**
     * Replaces the element at the specified position in this LinkedArrayList with the specified element.
     * @param index index of the element to replace.
     * @param element element to be stored at the specified position.
     * @return the element previously at the specified position.
     */
    @Override
    public E set(int index, E element) {

        Node<E> tempRef = head;
        while(index >= tempRef.data.getUsed()){
            index -= tempRef.data.getUsed();
            tempRef = tempRef.next;
        }

        E toReturn = tempRef.data.getData(index);

        tempRef.data.setData(index,element);

        return toReturn;
    }

    /**
     * Returns the element at the specified position in this LinkedArrayList.
     * @param index index of the element to return.
     * @return the element at the specified position in this LinkedArrayList.
     */
    @Override
    public E get(int index) {

        Node<E> tempRef = head;
        while(index >= tempRef.data.getUsed()){
            index -= tempRef.data.getUsed();
            tempRef = tempRef.next;
        }

        return tempRef.data.getData(index);
    }

    /**
     * Returns the number of elements in this LinkedArrayList.
     * @return the number of elements in this LinkedArrayList.
     */
    @Override
    public int size() {
        return this.size;
    }

    /**
     * Returns a list iterator of the beginning of this LinkedArrayList.
     * @return a list iterator of the beginning of this LinkedArrayList.
     */
    @Override
    public ListIterator<E> listIterator() {
        return new Iterator(head,0,0);
    }

    /**
     * Returns a list-iterator of the elements in this LinkedArrayList.
     * @param index index of the element.
     * @return a list-iterator of the elements in this LinkedArrayList.
     */
    @Override
    public ListIterator<E> listIterator(int index) {
        int tempIndex = index;

        if(index > size)
            throw new ArrayIndexOutOfBoundsException("index : " + index + "  size : " + size);

        if(index == size){
            return new Iterator(null,0,size);
        }

        Node<E> tempRef = head;
        while(index >= tempRef.data.getUsed()){
            index -= tempRef.data.getUsed();
            tempRef = tempRef.next;
        }

        return new Iterator(tempRef,index,tempIndex);
    }

    /**
     * returns the LinkedArrayList as string.
     * @return the LinkedArrayList as string.
     */
    @Override
    public String toString() {
        if(head == null){
            return "{}";
        }

        StringBuilder sB = new StringBuilder();
        Node<E> tempRef = head;

        sB.append("{ ");
        while(tempRef.next != null){

            sB.append(tempRef.data.toString());
            sB.append(" <--> ");
            tempRef = tempRef.next;
        }

        sB.append(tempRef.data.toString());
        sB.append(" }");

        return sB.toString();
    }

    /**
     * Creates a generic node for a double linked list.
     * @param <E> to keep generic data in a node.
     */
    private static class Node<E>{

        /**
         *The data.
         */
        private PFArrayGTU<E> data;

        /**
         * The link to the next node.
         */
        private Node<E> next;

        /**
         * The link to the previous node.
         */
        private Node<E> prev;

        /**
         * Creates a node which has an array with const capacity.
         */
        private Node(){
            this(PFArrayGTU.getConstCapacity());
        }

        /**
         * Creates a node which has an array with a different capacity.
         * @param newCapacity capacity of the array in the node.
         */
        private Node(int newCapacity){
            data = new PFArrayGTU<>(newCapacity);
            next = null;
            prev = null;
        }

        /**
         * Creates a node which has an array with const capacity.
         * @param nodeRefNext The link to the next node.
         * @param nodeRefPrev The link to the previous node.
         */
        private Node(Node<E> nodeRefNext, Node<E> nodeRefPrev){
            data = new PFArrayGTU<>();
            next = nodeRefNext;
            prev = nodeRefPrev;
        }

    }

    /**
     * Inner class to implement the ListIterator interface.
     */
    private class Iterator implements ListIterator<E>{

        /**
         * A reference to the next item.
         */
        private Node<E> nodRef;
        /**
         * index of the next item for the node.
         */
        private int indexOfArray;


        /**
         *A reference of the last item returned.
         */
        private Node<E> lastItemReturned;
        /**
         * index of the last item returned for the node.
         */
        private int lastItemIndex;


        /**
         * total index of the next item.
         */
        private int indexOfContainer;

        /**
         * Construct a Iterator that will reference the i'th element.
         * @param newNodRef the reference of the node to be referenced.
         * @param newIndexOfArray the index for a node to be referenced.
         * @param newIndexOfContainer the total index to be referenced.
         */
        public Iterator(Node<E> newNodRef,int newIndexOfArray,int newIndexOfContainer){
            nodRef = newNodRef;
            indexOfArray = newIndexOfArray;

            lastItemReturned = null;
            lastItemIndex = -1;

            indexOfContainer=newIndexOfContainer;
        }

        /**
         * Indicate whether movement forward is defined.
         * @return true if call to next will not throw an exception.
         */
        @Override
        public boolean hasNext() {
            if(nodRef == null){
                return false;
            }
            if(indexOfArray + 1 <= nodRef.data.getUsed())
                return true;
            else
                return nodRef != null;
        }

        /**
         *Move the iterator forward and return the next item.
         * @return the next item in the list.
         * @throws NoSuchElementException if there is no such object.
         */
        @Override
        public E next() {
            if(!hasNext()){
                throw new NoSuchElementException();
            }

            lastItemIndex = indexOfArray;
            lastItemReturned = nodRef;

            if(indexOfArray + 1 < nodRef.data.getUsed()){
                ++indexOfArray;
            }
            else{
                nodRef = nodRef.next;
                indexOfArray = 0;
            }

            ++indexOfContainer;

            return lastItemReturned.data.getData(lastItemIndex);
        }

        /**
         * Indicate whether movement backward is defined.
         * @return true if call to previous will not throw exception.
         */
        @Override
        public boolean hasPrevious() {
            if(nodRef == null)
                return size != 0;

            else if(indexOfArray > 0)
                return true;

            else{
                return nodRef.prev != null;
            }
        }

        /**
         * Move the iterator backward and return the previous item.
         * @return the previous item in the list.
         * @throws NoSuchElementException if there is no such object.
         */
        @Override
        public E previous() {
            if(!hasPrevious())
                throw new NoSuchElementException();

            if(nodRef == null){
                nodRef = tail;
                indexOfArray = nodRef.data.getUsed() - 1;
            }
            else if (indexOfArray > 0){
                --indexOfArray;
            }
            else{
                nodRef = nodRef.prev;
                indexOfArray = nodRef.data.getUsed() - 1 ;
            }

            lastItemReturned = nodRef;
            lastItemIndex = indexOfArray;

            --indexOfContainer;

            return lastItemReturned.data.getData(lastItemIndex);
        }

        /**
         * return the next index of the iterator.
         * @return the next index of the iterator.
         */
        @Override
        public int nextIndex() {
            return indexOfContainer;
        }

        /**
         * return the previous index of the iterator.
         * @return the previous index of the iterator.
         */
        @Override
        public int previousIndex() {
            return indexOfContainer - 1;
        }

        /**
         * Removes from the list the last element that was returned by next() or previous().
         * This call can only be made once per call to next or previous.
         * It can be made only if add(E) has not been called after the last call to next or previous.
         * @throws IllegalStateException if neither next nor previous have been called,
         * or remove or add have been called after the last call to next or previous
         */
        @Override
        public void remove() {
            if(lastItemReturned == null || lastItemIndex < 0) {
                throw new IllegalStateException();
            }

            if(lastItemIndex != lastItemReturned.data.getUsed()-1) {
                --indexOfArray;
                if(indexOfArray < 0){
                    indexOfArray = 0;
                }
            }
            lastItemReturned.data.removeAnElement(lastItemIndex);

            if(lastItemReturned.data.isEmpty()){
                boolean c1 = lastItemReturned.prev == null;
                boolean c2 = lastItemReturned.next == null;
                if(c1 && c2){
                    head = null;
                    tail = null;
                }
                else if(c1){
                    head = head.next;
                    head.prev = null;
                }
                else if(c2){
                    tail = tail.prev;
                    tail.next = null;
                }
                else{
                    lastItemReturned.prev.next = lastItemReturned.next;
                    lastItemReturned.next.prev = lastItemReturned.prev;
                }

            }

            lastItemReturned = null;
            lastItemIndex = -1;

            --size;
        }

        /**
         * Replaces the last element returned by next() or previous() with the specified element.
         * @param e the element with which to replace the last element returned by next or previous.
         * @throws IllegalStateException if neither next nor previous have been called.
         */
        @Override
        public void set(E e) {
            if(lastItemReturned == null || lastItemIndex < 0)
                throw new IllegalStateException();

            lastItemReturned.data.setData(lastItemIndex,e);
        }

        /**
         * Inserts the specified element into the list.
         * @param e the element to insert
         */
        @Override
        public void add(E e) {

            if(nodRef == null){
                if(head== null){
                    head = new Node<>();
                    tail = head;
                    size = 0;
                }
                if(tail.data.isFull()){
                    tail.next = new Node<>(null,tail);
                    tail = tail.next;
                }
                indexOfArray = tail.data.getUsed();
                tail.data.insertElement(indexOfArray,e);
                nodRef = tail;
            }

            else if(nodRef.data.isFull()) {

                E temp = nodRef.data.getData(nodRef.data.getUsed()-1);
                nodRef.data.removeAnElement(nodRef.data.getUsed()-1);

                if(nodRef.next == null){
                    tail.next = new Node<>(null,tail);
                    tail = tail.next;

                    nodRef.data.insertElement(indexOfArray,e);

                    tail.data.addElement(temp);
                }
                else{
                    Node<E> newNode = new Node<>(nodRef.next,nodRef);
                    newNode.next.prev = newNode;
                    nodRef.next = newNode ;

                    nodRef.data.insertElement(indexOfArray,e);

                    newNode.data.addElement(temp);
                }
            }

            else{
                nodRef.data.insertElement(indexOfArray,e);
            }


            if(indexOfArray == nodRef.data.getUsed()-1){
                indexOfArray = 0;
                nodRef = nodRef.next;
            }
            else{
                ++indexOfArray;
            }

            ++size;
        }
    }
}