package DataStructureHW6_Q4;
/**
 * Binary search tree implementation.
 * @param <E> type of the data.
 * @author Ali Bahar 171044066
 */
public class BinarySearchTree<E extends Comparable<E>> {
    /**
     * Reference to the root of the tree.
     */
    protected Node<E> root;

    /**
     * Stores a second return value from the recursive add method that indicates whether the item has been inserted.
     */
    protected boolean addReturn;

    /**
     * Stores a second return value from the recursive delete method that references the item that was stored int the tree.
     */
    protected E deleteReturn;

    /**
     * if there is a replacement..
     */
    protected E replaced;

    /**
     * Constructs a new empty binary search tree.
     */
    public BinarySearchTree(){ this.root = null; }

    /**
     * adds a new item to binary search tree.
     * @param item item to be added.
     * @return true if the item has been added,returns false otherwise.
     */
    public boolean add(E item) {
        this.root = add(this.root,item);
        return addReturn;
    }
    private Node<E> add(Node<E> localRoot, E item){
        if(localRoot == null){
            addReturn = true;
            return new Node<>(item);
        }
        int compResult = item.compareTo(localRoot.getData());
        if(compResult == 0){
            addReturn = false;
            replaced = item;
            localRoot.setData(item);
            return localRoot;
        }
        else if(compResult < 0){
            localRoot.setLeft(add(localRoot.getLeft(),item));
            return localRoot;
        }
        else{
            localRoot.setRight(add(localRoot.getRight(),item));
            return localRoot;
        }
    }

    /**
     * Searches the target element inside this tree.
     * @param target element to be searched.
     * @return the the object if the target is found, returns null otherwise.
     */
    public E find(E target) { return find(this.root,target); }
    private E find(Node<E> localRoot, E target){
        if(localRoot == null){
            return null;
        }

        int compResult = target.compareTo(localRoot.getData());
        if(compResult == 0){
            return localRoot.getData();
        }
        else if(compResult < 0){
            return find(localRoot.getLeft(),target);
        }
        else{
            return find(localRoot.getRight(),target);
        }
    }

    /**
     * Deletes the target inside this tree.
     * @param target element to be removed.
     * @return the deleted object if the target is found, returns null otherwise.
     */
    public E delete(E target) {
        root = delete(this.root,target);
        return deleteReturn;
    }
    private Node<E> delete(Node<E> localRoot, E target){
        if(localRoot == null){
            deleteReturn = null;
            return null;
        }

        int compResult = target.compareTo(localRoot.getData());

        if(compResult < 0){
            localRoot.setLeft(delete(localRoot.getLeft(),target));
            return localRoot;
        }
        else if(compResult > 0){
            localRoot.setRight(delete(localRoot.getRight(),target));
            return localRoot;
        }
        else{
            deleteReturn = localRoot.getData();

            if(localRoot.getLeft() == null){
                return localRoot.getRight();
            }
            else if(localRoot.getRight() == null){
                return localRoot.getLeft();
            }
            else{
                if(localRoot.getLeft().getRight() == null){
                    localRoot.setData(localRoot.getLeft().getData());
                    localRoot.setLeft(localRoot.getLeft().getLeft());
                }
                else{
                    localRoot.setData(findLargestChild(localRoot.getLeft()));
                }
                return localRoot;
            }
        }
    }
    protected E findLargestChild(Node<E> parent){
        if(parent == null){ return null; }

        if(parent.getRight().getRight() == null){
            E temp = parent.getRight().getData();
            parent.setRight(parent.getRight().getLeft());
            return temp;
        }
        else{
            return findLargestChild(parent.getRight());
        }
    }

    /**
     * gets the last replaced item
     * @return last replaced item
     */
    public E getReplaced() {
        return replaced;
    }

    /**
     * removes the root of the tree
     * @return value of the root.
     */
    public E popFromRoot(){
        if(root == null){
            return null;
        }
        return delete(root.data);
    }

    /**
     * checked whether the tree empty or not
     * @return true if the tree is empty
     */
    public boolean isEmpty(){
        return root == null;
    }

    protected static class Node<E>{

        /**
         * the data at the node.
         */
        protected E data;

        /**
         * Right child of the node.
         */
        protected Node<E> right;

        /**
         * Left child of the node.
         */
        protected Node<E> left;

        /**
         * Constructs a new node with given data.
         * @param newData the given data.
         */
        public Node(E newData){ this(newData,null,null); }

        /**
         * Constructs a new node with given data and given subtrees.
         * @param newData the given data.
         * @param newLeft the given left subtree.
         * @param newRight the given right subtree.
         */
        public Node(E newData,Node<E> newLeft,Node<E> newRight){
            this.data = newData;
            this.right = newRight;
            this.left = newLeft;
        }

        /**
         * returns string representation of the node.
         * @return string representation of the node.
         */
        @Override
        public String toString() { return this.data.toString(); }

        /**
         * returns the data of the node.
         * @return the data of the node.
         */
        public E getData() {
            return data;
        }

        /**
         * returns right child of the node.
         * @return right child of the node.
         */
        public Node<E> getRight() {
            return right;
        }

        /**
         * returns left child of the node.
         * @return left child of the node.
         */
        public Node<E> getLeft() {
            return left;
        }

        /**
         * sets the data at this node
         * @param data the new data.
         */
        public void setData(E data) {
            this.data = data;
        }

        /**
         * sets the left child of this node.
         * @param left the new left child.
         */
        public void setLeft(Node<E> left) {
            this.left = left;
        }

        /**
         * sets the left child of right node.
         * @param right the new right child.
         */
        public void setRight(Node<E> right) {
            this.right = right;
        }
    }
}