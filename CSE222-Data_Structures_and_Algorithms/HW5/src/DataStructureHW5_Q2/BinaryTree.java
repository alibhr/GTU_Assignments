package DataStructureHW5_Q2;

import java.io.Serializable;
import java.util.Scanner;

/**
 * A special type of tree which has at most two child at every node.
 * @param <E> type of the data.
 * @author Ali Bahar 171044066
 */
public class BinaryTree<E> implements Serializable{

    /**
     * Reference to the root of the tree.
     */
    protected Node<E> root;

    /**
     * Constructs an empty binary tree.
     */
    public BinaryTree(){ this.root = null; }

    /**
     * Constructs a new binary tree with given node as the root.
     * @param root the given node as the root.
     */
    protected BinaryTree(Node<E> root){ this.root = root; }

    /**
     * Constructs a new binary tree with the given data at the root and two given subtrees.
     * @param data the given data for root of the tree.
     * @param leftTree the given subtree for left subtree.
     * @param rightTree the given subtree for right subtree.
     */
    public BinaryTree(E data,BinaryTree<E> leftTree,BinaryTree<E> rightTree){
        this.root = new Node<>(data);

        if(rightTree != null) root.right = rightTree.root;
        else this.root.right = null;

        if(leftTree != null) root.left = leftTree.root;
        else this.root.left = null;
    }

    /**
     * returns the left subtree.
     * @return the left subtree.
     */
    public BinaryTree<E> getLeftSubtree(){
        if(this.root != null && root.left != null)
            return new BinaryTree<>(root.left);
        return null;
    }

    /**
     * returns the right subtree.
     * @return the right subtree.
     */
    public BinaryTree<E> getRightSubtree(){
        if(this.root != null && root.right != null)
            return new BinaryTree<>(root.right);
        return null;
    }

    /**
     * returns the data at the root.
     * @return the data at the root.
     */
    public E getData(){
        if(root != null)
            return this.root.data;
        return null;
    }

    /**
     * return true if this tree is a leaf, false otherwise.
     * @return true if this tree is a leaf, false otherwise.
     */
    public boolean isLeaf(){
        if(root != null)
            return root.left==null && root.right==null;
        return false;
    }

    /**
     * Returns a string representation of the tree(preOrderTraverse).
     * @return a string representation of the tree.
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        preOrderTraverse(this.root,0,sb);
        return sb.toString();
    }

    /**
     * Performs a pre order traversal of the subtree whose root is node.
     * @param node the root of the tree.
     * @param depth depth of the tree.
     * @param sb to build a string representation of the tree.
     */
    private void preOrderTraverse(Node<E> node,int depth,StringBuilder sb){
        for(int i=0 ; i<depth ; ++i){
		sb.append("\t");	
	}

        if(node == null){
            sb.append("null\n");
            return;
        }

        sb.append(node.toString()).append("\n");
        preOrderTraverse(node.left,depth+1,sb);
        preOrderTraverse(node.right,depth+1,sb);
    }

    /**
     * Returns a string representation of the tree(postOrderTraverse).
     * @return a string representation of the tree.
     */
    public String toString2(){
        StringBuilder sb = new StringBuilder();
        postOrderTraverse(this.root,0,sb);
        return sb.toString();
    }

    /**
     * Performs a post order traversal of the subtree whose root is node.
     * @param node the root of the tree.
     * @param depth depth of the tree.
     * @param sb to build a string representation of the tree.
     */
    private void postOrderTraverse(Node<E> node,int depth,StringBuilder sb){
        for(int i=0 ; i<depth ; ++i){
		sb.append("\t");	
	}

        if(node == null){
            sb.append("null\n");
            return;
        }

        postOrderTraverse(node.left,depth+1,sb);
        postOrderTraverse(node.right,depth+1,sb);
        sb.append(node.toString()).append("\n");
    }

    /**
     * Constructs a binary tree by reading its data using Scanner scan.
     * @param scan the Scanner
     * @return the binary tree which has constructed by this method.
     */
    public static BinaryTree<String> readBinaryTree(Scanner scan){
        String data = scan.next();

        if(data.equals("null")){
            return null;
        }

        BinaryTree<String> leftTree = readBinaryTree(scan);
        BinaryTree<String> rightTree = readBinaryTree(scan);
        return new BinaryTree<>(data,leftTree,rightTree);
    }

    /**
     * Binary tree  node representation.
     * @param <E> type of the data.
     */
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
