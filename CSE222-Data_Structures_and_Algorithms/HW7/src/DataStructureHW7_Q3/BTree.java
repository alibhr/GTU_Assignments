package DataStructureHW7_Q3;

/**
 * An implementation of the B-tree. A B-tree is a
 * search tree in which each node contains n data items where
 * n is between N/2 and N. (For the root, n may be between 1
 * and N. Other than leaves there are n+1 children.  The tree
 * is always balanced in that all leaves are on the same level,
 * i.e., the length of the path  from the root to a leaf is
 * constant.
 * @author Koffman and Wolfgang
 * @param <E> generic data type
 */
public class BTree<E extends Comparable<E>> {

    /** The reference to the root. */
    private Node<E> root;

    /** The right half of a split node returned from insert */
    private Node<E> newChild;

    /** The parent of a split node returned from insert */
    private E newParent;

    /** The maximum number of children of a node */
    private int order;

    /** The last deleted element */
    private E deleteReturn;

    /**
     * Construct a B-tree with a specified order
     * @param order - the size of a node
     * @throws IllegalArgumentException if order less than 3
     */
    public BTree(int order){
        if(order<3){
            throw new IllegalArgumentException();
        }
        root = null;
        newChild = null;
        this.order = order;
    }

    /**
     * Insert an Object into the tree.  Inserted item
     * must implement the Comparable interface
     * @param item The object to be inserted
     * @return true if the item was inserted
     */
    public boolean add(E item){
        if (root == null) {
            root = new Node<>(order);
            root.data[0] = item;
            root.size = 1;
            return true;
        }
        newChild = null;
        boolean result = insert(root,item);
        if(newChild != null){
            Node<E> newRoot = new Node<E>(order);
            newRoot.child[0] = root;
            newRoot.child[1] = newChild;
            newRoot.data[0] = newParent;
            newRoot.size = 1;
            root = newRoot;
        }

        return result;
    }

    /**
     * Recursive insert an Object into the Tree. Inserted
     * item must implement the Comparable interface
     * @param root - The local root
     * @param item - The item to be inserted
     * @return true if the item was inserted, false
     *         if the item is already in the tree
     */
    private boolean insert(Node<E> root, E item){
        int index = binarySearch(item, root.data, 0, root.size);

        if(index != root.size && item.compareTo(root.data[index]) == 0){ return false ; }

        if(root.child[index] == null){
            if(root.size < order-1){
                insertIntoNode(root,index,item,null);
                newChild = null;
            }
            else{
                splitNode(root,index,item,null);
            }
            return true;
        }
        else{
            boolean result = insert(root.child[index],item);
            if(newChild != null){
                if(root.size < order -1){
                    insertIntoNode(root,index,newParent,newChild);
                    newChild = null;
                }
                else{
                    splitNode(root,index,newParent,newChild);
                }
            }
            return result;
        }
    }

    /**
     * Method to insert a new value into a node
     * @param node The node to insert the value into
     * @param index The index where the inserted item is to be placed
     * @param obj The value to be inserted
     * @param child The right child if the value
     */
    private void insertIntoNode(Node<E> node,int index,E obj,Node<E> child){
        for(int i=node.size ; i > index ;--i){
            node.data[i] = node.data[i-1];
            node.child[i+1] = node.child[i];
        }
        node.data[index] = obj;
        node.child[index+1] = child;
        ++node.size;
    }

    /**
     * Method to split a node
     * @param node - The node to be split
     * @param index - The index where the new item is to be inserted
     * @param item - The item to be inserted
     * @param child - Reference to the subtree containing items greater than item
     */
    private void splitNode(Node<E> node ,int index,E item,Node<E> child){
        newChild = new Node<>(order);

        int numToMove = (order - 1) - ((order-1)/2);

        if(index > (order-1)/2){
            --numToMove;
        }

        System.arraycopy(node.data,order-numToMove-1,newChild.data,0,numToMove);
        System.arraycopy(node.child,order-numToMove,newChild.child,0,numToMove);
        node.size = order-numToMove-1;
        newChild.size = numToMove;

        if(index == ((order-1)/2)){
            newParent = item;
            newChild.child[0] = child;
        }
        else{
            if(index < ((order-1)/2)){
                insertIntoNode(node,index,item,child);
            }
            else{
                insertIntoNode(newChild,index - ((order-1)/2)-1 , item,child);
            }
            newParent = node.data[node.size-1];
            newChild.child[0] = node.child[node.size];
            --node.size;
        }
        for(int i=node.size ; i<node.data.length ; ++i){
            node.data[i] = null;
            node.child[i+1] = null;
        }
    }

    /**
     * Binary search
     * @param item the item to be searched.
     * @param data the array.
     * @param firstIndex first index of the array to search.
     * @param size the size of the array
     * @return if element is found ,returns the index of the element otherwise it returns an index of empty cell.
     */
    private int binarySearch(E item, E[] data, int firstIndex, int size){
        if(firstIndex < size){
            int mid = (size + firstIndex) / 2;
            int compResult = item.compareTo(data[mid]);
            if(compResult == 0){
                return mid;
            }
            else if(compResult < 0){
                return binarySearch(item,data,firstIndex,mid);
            }
            else{
                return binarySearch(item,data,mid+1,size);
            }
        }

        //return -1
        return size;
    }

    /* // it doesn't work properly.
    public boolean remove(E item){
        root = remove(this.root,item);
        return deleteReturn != null;
    }
    private Node<E> remove(Node<E> localRoot,E target){

        if(localRoot == null){
            deleteReturn = null;
            return localRoot;
        }

        for(int i=0 ; i<localRoot.size ; ++i){
            int compResult = target.compareTo(localRoot.data[i]);
            if(compResult < 0){
                localRoot.child[i]=remove(localRoot.child[i],target);
            }
            else if(compResult > 0){
                localRoot.child[i+1]=remove(localRoot.child[i+1],target);
            }
            else{
                deleteReturn = localRoot.data[i];
                if(localRoot.isLeaf()){
                    localRoot.remove(i);
                    return localRoot;
                }
                else{

                }
            }
        }

        return localRoot;
    }
    */

    /**
     * Return a pre-order traversal as the string
     * representation of the tree
     * @return a string representation of the tree
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        preOrderTraverse(this.root,0,sb);
        return sb.toString();
    }

    /**
     * Perform a pre-order traversal
     * @param node - The local root
     * @param depth - The depth
     * @param sb - The string buffer to put the output
     */
    private void preOrderTraverse(Node<E> node, int depth, StringBuilder sb){
        for(int i=0 ; i<depth ; ++i){
            sb.append("\t");
        }

        if(node == null){
            sb.append("null\n");
            return;
        }

        sb.append(node.toString()).append("\n");

        for(int i=0 ; i<=node.size ; ++i){
            preOrderTraverse(node.child[i],depth+1,sb);
        }
    }

    /** A Node represents a node in a B-tree tree.
     * @param <E> generic data type
     */
    private static class Node<E>{

        /** The number of data items in this node */
        private int size;

        /** The information */
        private E[] data;

        /** The links to the children. child[i] refers to
         *  the subtree of children < data[i] for i < size
         *  and to the subtree of children > data[size-1]
         *  for i == size  */
        private Node<E>[] child;

        /**
         * Create an empty node of size nn
         * @param order - The size of a node
         */
        @SuppressWarnings("unchecked")
        public Node(int order){
            data = (E[]) new Comparable[order-1];
            child = (Node<E>[]) new Node[order];
            size = 0;
        }

        /**
         * checks whether this node is leaf.
         * @return true if this node is a leaf.
         */
        public boolean isLeaf(){
            for(int i=0 ; i<size ; ++i){
                if(child[i] != null){
                    return false;
                }
            }
            return true;
        }

        /**
         * remove an element from node.
         * @param index index of the element to be removed.
         */
        public void remove(int index){
            if(index >= size){
                //throw new IndexOutOfBoundsException();
                System.err.println("IndexOutOfBoundsException");
                return;
            }
            for(int i=index ; i<size-1 ; ++i){
                data[i]=data[i+1];
            }
            --size;
        }

        /**
         * Return a String representation of this node
         * @return a String representation of this node
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