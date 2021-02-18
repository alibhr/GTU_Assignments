package DataStructureHW7_Q3;


/**
 * Self-balancing binary search tree using the algorithm defined
 * by Adelson-Velskii and Landis.
 * @author Koffman and Wolfgang
 * @param <E> generic data type
 */
public class AVLTree<E extends Comparable<E>> extends BinarySearchTreeWithRotate<E>{

    /** Flag to indicate that height of tree has increased. */
    private boolean increase;

    /**
     * add starter method.
     * @param item The item being inserted.
     * @return true if the object is inserted; false
     *         if the object already exists in the tree
     * @throws ClassCastException if item is not Comparable
     */
    @Override
    public boolean add(E item) {
        increase = false;
        root = add((AVLNode<E>)root,item);
        return addReturn;
    }


    /**
     * Recursive add method. Inserts the given object into the tree.
     * @param localRoot The local root of the subtree
     * @param item The object to be inserted
     * @return The new local root of the subtree with the item
     *         inserted
     */
    private AVLNode<E> add(AVLNode<E> localRoot,E item){
        if(localRoot == null){
            addReturn = true;
            increase = true;
            return new AVLNode<>(item);
        }

        int compResult = item.compareTo(localRoot.getData());

        if(compResult == 0){
            addReturn = false;
            return localRoot;
        }
        else if(compResult < 0){
            localRoot.left = add((AVLNode<E>)localRoot.left,item);
            if(increase){
                decrementBalance(localRoot);
                if(localRoot.balance < AVLNode.LEFT_HEAVY){
                    increase = false;
                    return rebalanceLeft(localRoot);
                }
            }
            return localRoot;
        }
        else{
            localRoot.right = add((AVLNode<E>)localRoot.right,item);
            if(increase){
                incrementBalance(localRoot);
                if(localRoot.balance > AVLNode.RIGHT_HEAVY){
                    increase = false;
                    return rebalanceRight(localRoot);
                }
            }
            return localRoot;
        }
    }

    /**
     * Method to decrement the balance field and to reset the value of increase.
     * @param node The AVL node whose balance is to be incremented
     */
    private void decrementBalance(AVLNode<E> node){
        --node.balance;
        if(node.balance == AVLNode.BALANCED){
            increase = false;
        }
    }

    /**
     * Method to rebalance left.
     * @param localRoot Root of the AVL subtree
     *        that needs rebalancing
     * @return a new localRoot
     */
    private AVLNode<E> rebalanceLeft(AVLNode<E> localRoot){
        AVLNode<E> leftChild = (AVLNode<E>) localRoot.left;

        //Left-Right
        if(leftChild.balance > AVLNode.BALANCED){
            AVLNode<E> leftRightChild = (AVLNode<E>) leftChild.right;
            if(leftRightChild.balance < AVLNode.BALANCED){
                leftChild.balance = AVLNode.BALANCED;
                leftRightChild.balance = AVLNode.BALANCED;
                localRoot.balance = AVLNode.RIGHT_HEAVY;
            }
            else if (leftRightChild.balance > AVLNode.BALANCED){
                leftChild.balance = AVLNode.LEFT_HEAVY;
                leftRightChild.balance = AVLNode.BALANCED;
                localRoot.balance = AVLNode.BALANCED;
            }
            else{
                leftChild.balance = AVLNode.BALANCED;
                localRoot.balance = AVLNode.BALANCED;
            }
            localRoot.left = rotateLeft(leftChild);
        }
        //Left-Left
        else{
            leftChild.balance = AVLNode.BALANCED;
            localRoot.balance = AVLNode.BALANCED;
        }

        return (AVLNode<E>) rotateRight(localRoot);
    }

    /**
     * Method to increment the balance field and to reset the value of decrease.
     * @param node The AVL node whose balance is to be decremented.
     */
    private void incrementBalance(AVLNode<E> node){
        ++node.balance;
        if(node.balance == AVLNode.BALANCED){
            increase = false;
        }
    }

    /**
     * Method to rebalance right.
     * @param localRoot Root of the AVL subtree
     *        that needs rebalancing
     * @return a new localRoot
     */
    private AVLNode<E> rebalanceRight(AVLNode<E> localRoot){
        AVLNode<E> rightChild = (AVLNode<E>) localRoot.right;
        if(rightChild.balance < AVLNode.BALANCED){
            AVLNode<E> rightLeftChild = (AVLNode<E>) rightChild.left;
            if(rightLeftChild.balance < AVLNode.BALANCED){
                rightChild.balance = AVLNode.RIGHT_HEAVY;
                rightLeftChild.balance = AVLNode.BALANCED;
                localRoot.balance = AVLNode.BALANCED;
            }
            else if(rightLeftChild.balance > AVLNode.BALANCED){
                rightChild.balance = AVLNode.BALANCED;
                rightLeftChild.balance = AVLNode.BALANCED;
                localRoot.balance = AVLNode.LEFT_HEAVY;
            }
            else{
                rightChild.balance = AVLNode.BALANCED;
                localRoot.balance = AVLNode.BALANCED;
            }
            localRoot.right = rotateRight(rightChild);
        }
        else{
            rightChild.balance = AVLNode.BALANCED;
            localRoot.balance = AVLNode.BALANCED;
        }

        return (AVLNode<E>) rotateLeft(localRoot);
    }


    //TODO delete


    /** Class to represent an AVL Node. It extends the
     * BinaryTree.Node by adding the balance field.
     * @param <E> generic data type
     */
    private static class AVLNode<E> extends Node<E>{

        /** Constant to indicate left-heavy */
        public static final int LEFT_HEAVY = -1;

        /** Constant to indicate balanced */
        public static final int BALANCED = 0;

        /** Constant to indicate right-heavy */
        public static final int RIGHT_HEAVY = 1;

        /** balance is right subtree height - left subtree height */
        private int balance;

        /**
         * Construct a node with the given item as the data field.
         * @param item The data field
         */
        public AVLNode(E item){
            super(item);
            balance = BALANCED;
        }

        /**
         * Return a string representation of this object.
         * The balance value is appended to the contents.
         * @return String representation of this object
         */
        @Override
        public String toString() {
            return balance + " :  " + super.toString();
        }
    }
}