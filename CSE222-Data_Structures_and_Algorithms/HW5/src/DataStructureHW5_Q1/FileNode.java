package DataStructureHW5_Q1;

import java.util.ArrayList;

/**
 * File Node class to handle the nodes of the tree.
 * @author Ali Bahar 171044066
 */
public class FileNode {

    /**
     * name of the node.
     */
    private String name;

    /**
     * children nodes of this node.
     */
    private ArrayList<FileNode> children;

    /**
     * if this node represents a file this filed will be true,unless false.
     */
    private boolean isFile;

    /**
     * constructs a new node.
     * @param newName name of the node.
     * @param children children nodes of this node.
     * @param s it determines the type of the node file or directory
     */
    public FileNode(String newName,ArrayList<FileNode> children,boolean s){
        this.name = newName;
        this.children = children;
        this.isFile = s;
    }

    /**
     * constructs a new node. There is no children in this node.
     * @param newName name of the node.
     * @param s it determines the type of the node file or directory
     */
    public FileNode(String newName,boolean s){ this(newName,new ArrayList<FileNode>(),s); }

    /**
     * constructs a new node. There is no children in this node and type of node will be directory.
     * @param newName name of the node.
     */
    public FileNode(String newName){ this(newName,new ArrayList<FileNode>(),false); }

    /**
     * gets the name of the node.
     * @return the name of the node as string.
     */
    public String getName() { return name; }

    /**
     * returns the all children nodes.
     * @return the all children nodes.
     */
    public ArrayList<FileNode> getChildren() { return children; }

    /**
     * returns true if this node represents a file.
     * @return true if this node represents a file.
     */
    public boolean isFile(){ return isFile; }

    /**
     * returns the number of the child.
     * @return the number of the child.
     */
    public int childrenSize(){ return children.size(); }

    /**
     * adds a new child to this node.
     * @param newChild the new child to be added.
     */
    public void addChild(FileNode newChild){ children.add(newChild); }

    /**
     * Finds the specified node and return its index.
     * @param nameToSearch to be searched.
     * @return index of the node which is specified.
     */
    public int getIndex(String nameToSearch){
        for(int i=0 ; i<childrenSize() ; ++i){
            if(children.get(i).getName().equals(nameToSearch))
                return i;
        }
        return -1;
    }
}