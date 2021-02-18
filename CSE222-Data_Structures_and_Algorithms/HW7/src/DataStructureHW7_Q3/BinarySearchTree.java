package DataStructureHW7_Q3;

/**
 * Binary search tree implementation.
 * @param <E> type of the data.
 * @author Ali Bahar 171044066
 */
public class BinarySearchTree <E extends Comparable<E>> extends BinaryTree<E> implements SearchTree<E>{

    /**
     * Stores a second return value from the recursive add method that indicates whether the item has been inserted.
     */
    protected boolean addReturn;

    /**
     * Stores a second return value from the recursive delete method that references the item that was stored int the tree.
     */
    protected E deleteReturn;

    /**
     * Constructs a new empty binary search tree.
     */
    public BinarySearchTree(){ super (); }

    /**
     * adds a new item to binary search tree.
     * @param item item to be added.
     * @return true if the item has been added,returns false otherwise.
     */
    @Override
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
     * @return true if the target is found,returns false otherwise.
     */
    @Override
    public boolean contains(E target) {
        return contains(this.root,target);
    }
    private boolean contains(Node<E> localRoot,E target){
        if(localRoot == null){ return false; }

        int compResult = target.compareTo(localRoot.getData());

        if(compResult == 0){ return true; }
        else if(compResult < 0 ){ return contains(localRoot.getLeft(),target); }
        else{ return contains(localRoot.getRight(),target);}
    }


    /**
     * Searches the target element inside this tree.
     * @param target element to be searched.
     * @return the the object if the target is found, returns null otherwise.
     */
    @Override
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
    @Override
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
     * Removes the target inside this tree.
     * @param target lement to be removed.
     * @return the removed object if the target is found, returns null otherwise.
     */
    @Override
    public boolean remove(E target) { return delete(target) != null; }
}