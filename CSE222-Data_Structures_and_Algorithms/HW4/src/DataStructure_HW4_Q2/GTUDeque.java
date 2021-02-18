package DataStructure_HW4_Q2;

import java.util.AbstractCollection;
import java.util.Deque;
import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * It is a data structure which allows operations from both ends(front and rear).
 * @param <E> the type of elements
 * @author Ali BAHAR
 * @author 171044066
 */
public class GTUDeque<E> extends AbstractCollection<E> implements Deque<E> {

    /**
     * first node of the liked list.
     */
    private Node<E> head;

    /**
     * last element of the linked list.
     */
    private Node<E> tail;

    /**
     * Element number of this deque.
     */
    private int size;

    /**
     * the nodes which can be allocated again.
     */
    private Node<E> available;

    /**
     * Constructs a new empty deque.
     */
    public GTUDeque(){
        head = null;
        tail = null;
        available = null;
        size = 0;
    }

    /**
     * Inserts item at the front of the deque.
     * @param element element to added.
     */
    @Override
    public void addFirst(E element) {

        boolean isItFirst = false;

        if(head == null)
            isItFirst = true;

        if(available != null){

            head = getAvailableNode(element,head,null);

            if(head.next != null)
                head.next.prev = head;

        }else{
            head = new Node<>(element,head,null);
        }

        if(isItFirst)
            tail = head;

        ++size;
    }

    /**
     * Inserts item at the rear of the deque.
     * @param element element to added.
     */
    @Override
    public void addLast(E element) {
        if(tail == null){
            addFirst(element);
        }
        else if(available != null){
            tail.next = getAvailableNode(element,null,tail);
            tail = tail.next;
            ++size;
        }
        else{
            tail.next = new Node<>(element,null,tail);
            tail = tail.next;
            ++size;
        }
    }

    /**
     * Inserts item at the front of the deque.
     * @param element item to added.
     * @return false if the item couldn't be iserted.
     */
    @Override
    public boolean offerFirst(E element) {
        addFirst(element);
        return true;
    }

    /**
     * Inserts item at the rear of the deque.
     * @param element item to added.
     * @return false if the item couldn't be inserted.
     */
    @Override
    public boolean offerLast(E element) {
        addLast(element);
        return true;
    }

    /**
     * Removes the entry at the front of the deque.
     * @return the entry which is removed.
     * @throws NoSuchElementException if the deque is empty.
     */
    @Override
    public E removeFirst() {
        if(head == null)
            throw new NoSuchElementException();

        Node<E> temp = head;
        head = head.next;
        if(head != null)
            head.prev = null;

        addAvailableNode(temp);

        if(head == null){
            tail = null;
        }

        --size;
        return temp.getData();
    }

    /**
     * Removes the item at the rear of the deque.
     * @return the item which is removed.
     * @throws NoSuchElementException if the deque is empty.
     */
    @Override
    public E removeLast() {
        if(tail == null)
            throw new NoSuchElementException();

        Node<E> temp = tail;
        tail = tail.prev;
        if(tail !=null){
            tail.next = null;
        }

        addAvailableNode(temp);

        if(tail == null)
            head = null;

        --size;
        return temp.getData();
    }

    /**
     * Removes the entry at the front of the deque.
     * @return null if the deque is empty otherwise returns the element which is removed.
     */
    @Override
    public E pollFirst() {
        if(head == null){
            return null;
        }

        return removeFirst();
    }

    /**
     * Removes the entry at the rear of the deque.
     * @return null if the deque is empty otherwise returns the element which is removed.
     */
    @Override
    public E pollLast() {
        if(tail == null){
            return null;
        }

        return removeLast();
    }

    /**
     * Returns the entry at the front of the deque without removing.
     * @return the entry at the front of the deque.
     * @throws NoSuchElementException if the deque is empty.
     */
    @Override
    public E getFirst() {
        if(head == null)
            throw new NoSuchElementException();

        return head.getData();
    }

    /**
     * Returns the entry at the rear of the deque without removing.
     * @return the entry at the rear of the deque.
     * @throws NoSuchElementException if the deque is empty.
     */
    @Override
    public E getLast() {
        if(tail == null)
            throw new NoSuchElementException();

        return tail.getData();
    }

    /**
     * Returns the entry at the front of the deque without removing.
     * @return null if the deque is empty otherwise returns the entry at the front of the deque.
     */
    @Override
    public E peekFirst() {
        if(head == null)
            return null;

        return head.getData();
    }

    /**
     * Returns the item at the rear of the deque without removing.
     * @return null if the deque is empty otherwise returns the item at the rear of the deque.
     */
    @Override
    public E peekLast() {
        if(tail == null)
            return null;

        return tail.getData();
    }

    /**
     * Removes the first occurrence of the item in the deque.
     * @param o element to be removed from this deque.
     * @return true if an element was removed as a result of this call
     */
    @Override
    public boolean removeFirstOccurrence(Object o) {
        Node<E> tempRef = head;
        while(tempRef != null){
            if(tempRef.getData().equals(o)){
                removeHelper(tempRef);
                return true;
            }
            tempRef = tempRef.next;
        }

        return false;
    }

    /**
     * Removes the last occurrence of the item in the deque.
     * @param o element to be removed from this deque.
     * @return true if an element was removed as a result of this call
     */
    @Override
    public boolean removeLastOccurrence(Object o) {
        Node<E> tempRef = tail;
        while(tempRef != null){
            if(tempRef.getData().equals(o)){
                removeHelper(tempRef);
                return true;
            }
            tempRef = tempRef.prev;
        }

        return false;
    }

    /**
     * Inserts the specified element into the queue represented by this deque (in other words, at the tail of this deque)
     * @param element item to added.
     * @return true.
     */
    @Override
    public boolean add(E element) {
        addLast(element);
        return true;
    }

    /**
     * Inserts the specified element into the queue represented by this deque (in other words, at the tail of this deque)
     * @param element item to added.
     * @return true.
     */
    @Override
    public boolean offer(E element) {
        return offerLast(element);
    }

    /**
     * Retrieves and removes the head of the queue represented by this deque.
     * @return the head of the queue.
     */
    @Override
    public E remove() {
        return removeFirst();
    }

    /**
     * Retrieves and removes the head of the queue
     * @return the first element of this deque, or null if this deque is empty
     */
    @Override
    public E poll() {
        return pollFirst();
    }

    /**
     * Retrieves, but does not remove, the head of the queue.
     * @return the head of the queue.
     * @throws NoSuchElementException if the deque is empty.
     */
    @Override
    public E element() {
        if(head == null)
            throw new NoSuchElementException();
        return head.getData();
    }

    /**
     * Retrieves, but does not remove, the head of the queue.
     * @return the head of the queue or null if this deque is empty.
     */
    @Override
    public E peek() {
        if(head == null)
            return null;
        return head.getData();
    }

    /**
     * Pushes an element onto the stack.
     * @param e  the element to push
     */
    @Override
    public void push(E e) {
        addFirst(e);
    }

    /**
     * Pops an element from the stack.
     * @return the element at the front of this deque.
     * @throws NoSuchElementException if the deque is empty.
     */
    @Override
    public E pop() {
        return removeLast();
    }

    /**
     * Returns the number of elements in this deque.
     * @return the number of elements in this deque.
     */
    @Override
    public int size() {
        return size;
    }

    /**
     * Returns true if this deque contains the specified element.
     * @param o element whose existence in this deque is to be tested
     * @return true if this deque contains the specified element.
     */
    @Override
    public boolean contains(Object o) {
        Node<E> tempRef = head;
        while(tempRef != null){
            if(tempRef.getData().equals(o)){
                return true;
            }
            tempRef = tempRef.next;
        }

        return false;
    }

    /**
     * Removes the first occurrence of the specified element from this deque.
     * @param o element to be removed from this deque.
     * @return true if an element was removed as a result of this call.
     */
    @Override
    public boolean remove(Object o) {
        return removeFirstOccurrence(o);
    }

    /**
     * Returns an iterator over the elements in this deque in proper sequence. The elements will be returned in order from first (head) to last (tail).
     * @return an iterator over the elements in this deque in proper sequence. The elements will be returned in order from first (head) to last (tail).
     */
    @Override
    public Iterator<E> iterator() {
        return new Iter(head);
    }

    /**
     * Returns an iterator over the elements in this deque in reverse sequential order. The elements will be returned in order from last (tail) to first (head).
     * @return an iterator over the elements in this deque in reverse sequential order. The elements will be returned in order from last (tail) to first (head).
     */
    @Override
    public Iterator<E> descendingIterator() {
        return new DescendingIter(tail);
    }

    /**
     * it helps when a node is being removed.
     * @param nodRef a node reference to removed.
     */
    private void removeHelper(Node<E> nodRef){
        if(nodRef == head) {
            removeFirst();
        }

        else if(nodRef == tail){
            removeLast();
        }

        else{
            nodRef.prev.next = nodRef.next;
            nodRef.next.prev = nodRef.prev;
            addAvailableNode(nodRef);
            --size;
        }
    }

    /**
     * if there is a available node it returns a node to be used.
     * @param newData data of the node which will be returned.
     * @param newNext next of the node which will be returned.
     * @param newPrev prev of the node which will be returned.
     * @return a node which can be used which will be returned.
     */
    private Node<E> getAvailableNode(E newData,Node<E> newNext,Node<E> newPrev){
        if(available == null)
            throw new NullPointerException("getAvailableNode couldn't work.");

        Node<E> temp = available;

        available = available.next;
        if(available != null){
            available.prev = null;
        }

        temp.data = newData;
        temp.next = newNext;
        temp.prev = newPrev;

        return temp;
    }

    /**
     * adds the node to available nodes.
     * @param newNode the node which will be added.
     */
    private void addAvailableNode(Node<E> newNode){
        if(available == null){
            available = newNode;
            available.next = null;
            available.prev = null;
        }else{
            newNode.next = available;
            newNode.next.prev = newNode;
            newNode.prev = null;
            available = available.prev;
        }
    }

    /**
     * An iterator over GTUDeque collection.
     */
    private class Iter implements Iterator<E>{

        /**
         * A reference to the next item.
         */
        Node<E> nodRef;

        /**
         * A reference of the last item returned.
         */
        Node<E> lastReturned;

        /**
         * Construct a Iterator
         * @param newNodRef node reference of element which is in GTUDeque collection.
         */
        public Iter(Node<E> newNodRef){
            nodRef = newNodRef;
            lastReturned = null;
        }

        /**
         * Indicate whether movement forward is defined.
         * @return true if call to next will not throw an exception.
         */
        @Override
        public boolean hasNext() {
            return nodRef !=null;
        }

        /**
         * Move the iterator forward and return the next item.
         * @return the next item in the list.
         * @throws NoSuchElementException if there is no such object.
         */
        @Override
        public E next() {
            if(!hasNext()){
                throw new NoSuchElementException();
            }
            E temp = nodRef.getData();
            lastReturned = nodRef;
            nodRef = nodRef.next;
            return temp;
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
            if(lastReturned == null)
                throw new IllegalStateException();
            removeHelper(lastReturned);
            lastReturned = null;
        }
    }

    /**
     * An DescendingIter over GTUDeque collection.
     */
    private class DescendingIter implements Iterator<E>{

        /**
         * A reference to the previous item.
         */
        private Node<E> nodRef;

        /**
         * A reference of the last item returned.
         */
        private Node<E> lastReturned;

        /**
         * Construct a DescendingIter
         * @param newNodRef node reference of element which is in GTUDeque collection.
         */
        public DescendingIter(Node<E> newNodRef){
            nodRef = newNodRef;
            lastReturned = null;
        }

        /**
         * Indicate whether movement backward is defined.
         * @return true if call to next will not throw an exception.
         */
        @Override
        public boolean hasNext() {
            return nodRef != null;
        }

        /**
         * Move the iterator backward and return the previous item.
         * @return the next item in the list.
         * @throws NoSuchElementException if there is no such object.
         */
        @Override
        public E next() {
            if(!hasNext())
                throw new NoSuchElementException();
            E temp = nodRef.getData();
            lastReturned = nodRef;
            nodRef = nodRef.prev;
            return temp;
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
            if(lastReturned == null)
                throw new IllegalStateException();
            removeHelper(lastReturned);
            lastReturned = null;
        }
    }

    /**
     * Creates a generic node for a double linked list.
     * @param <E> data type to keep.
     */
    private static class Node<E>{
        /**
         * The data.
         */
        private E data;

        /**
         * The link to the next node.
         */
        private Node<E> next;

        /**
         * The link to the previous node.
         */
        private Node<E> prev;

        /**
         * Creates a node.
         * @param newData data of the node.
         * @param newNext next reference of the node.
         * @param newPrev previous reference of the node.
         */
        public Node(E newData,Node<E> newNext,Node<E> newPrev){
            data = newData;
            next = newNext;
            prev = newPrev;
        }

        /**
         * Returns the data of the node.
         * @return the data of the node.
         */
        public E getData() {
            return data;
        }
    }
}