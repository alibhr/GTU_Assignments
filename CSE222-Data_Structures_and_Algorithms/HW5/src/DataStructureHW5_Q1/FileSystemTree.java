package DataStructureHW5_Q1;

import java.util.Scanner;

/**
 * File System Tree class to handle a file system hierarchy in a general tree structure.
 * @author Ali Bahar 171044066
 */
public class FileSystemTree {

    /**
     * root node of the tree.
     */
    FileNode root;

    /**
     * creates a new tree with specified root name.
     * @param rootName the name of the root
     */
    public FileSystemTree(String rootName){ root = new FileNode(rootName); }

    /**
     * adds a new node as directory.
     * @param thePath the path of the new node.
     */
    public void addDir(String thePath){
        if(thePath == null)
            throw new NullPointerException("the root can not be null");
        String[] path = thePath.split("/");
        if(path.length>1)
            addHelper(path,root,0,false);
        else{
            System.out.print("Couldn't be added!");
        }
    }

    /**
     * to add a new node to tree with recursive calls.
     * @param path the path of the new node.
     * @param r root node.
     * @param index index of the path.
     * @param s it determines whether this node is file or directory.
     */
    private void addHelper(String[] path,FileNode r,int index,boolean s){
        if(!r.getName().equals(path[index])){ return ; }

        if(index==path.length-2){
            if(!r.isFile()){
                r.addChild(new FileNode(path[index+1],s));
                //System.out.println("Added : " + path[index+1]);
            }
            else{
                System.out.println("file can't have child.");
            }
        }
        else{
            for(int i=0 ; i<r.childrenSize() ; ++i){
                addHelper(path,r.getChildren().get(i),index+1,s);
            }
        }
    }

    /**
     * adds a new node as file.
     * @param thePath the path of the new node.
     */
    public void addFile(String thePath){
        if(thePath == null)
            throw new NullPointerException("the root can not be null");
        String[] path = thePath.split("/");
        if(path.length>1)
            addHelper(path,root,0,true);
        else{
            System.out.print("Couldn't be added!");
        }
    }

    /**
     * removes a node from tree.
     * @param thePath the path of the node which will be removed.
     */
    public void remove(String thePath){
        if(thePath == null)
            throw new NullPointerException();

        String[] path = thePath.split("/");
        if(path.length>1)
            remove(path,root,0);
        else{
            System.out.print("Couldn't be removed (the root can not be removed)");
        }
    }

    /**
     * to remove the specified node from tree with recursive calls.
     * @param path the path of the node which will be removed.
     * @param r root node.
     * @param index index of the path.
     */
    private void remove(String[] path,FileNode r,int index){
        if(!r.getName().equals(path[index])){ return ; }

        if(index==path.length-2){
            int j = r.getIndex(path[index+1]);
            if(j == -1){
                System.out.println("WARNING : path cannot be found.");
            }
            else if(r.getChildren().get(j).childrenSize()==0){
                System.out.println(r.getChildren().get(j).getName() + " is removed.");
                r.getChildren().remove(j);
            }
            else{
                System.out.print("Content of ");
                printFileSystem(r.getChildren().get(j),0);
                System.out.println("the directory includes some other directories (or files)\n" +
                        "Do you want to remove them also.(press y ,if you want to remove)");

                Scanner in = new Scanner(System.in);
                String yOrN = in.next();

                if(yOrN.equals("y")||yOrN.equals("Y")){
                    System.out.println(r.getChildren().get(j).getName() + " is removed with its content.");
                    r.getChildren().remove(j);
                }
                else{
                    System.out.print("the directory is not removed.");
                }
            }
        }
        else {
            for(int i=0 ; i<r.childrenSize() ; ++i){
                remove(path,r.getChildren().get(i),index+1);
            }
        }
    }

    /**
     * Finds all nodes which contains specified word.
     * @param theWord the word which will be searched inside tree.
     */
    public void search(String theWord){
        if(root == null){
            return;
        }

        if(root.getName().contains(theWord)){
            System.out.println("dir - " + root.getName());
        }

        for(int i=0 ; i<root.childrenSize() ; ++i){
            search(root.getChildren().get(i),theWord,root.getName());
        }
    }

    /**
     * Finds all nodes which contains specified word with recursive calls.
     * @param root the root of the tree.
     * @param theWord the word which will be searched inside tree.
     * @param path to show the path of the node which contains the specified word.
     */
    private void search(FileNode root,String theWord,String path){
        if(root == null){
            return;
        }

        if(root.getName().contains(theWord)){
            if(root.isFile()) System.out.print("file - ");
            else System.out.print("dir - ");
            System.out.println(path + "/" + root.getName());
        }

        for(int i=0 ; i<root.childrenSize() ; ++i){
            search(root.getChildren().get(i),theWord,path + "/" + root.getName());
        }
    }

    /**
     * Prints the all nodes with hierarchical form.
     */
    public void printFileSystem(){ printFileSystem(this.root,0); }

    /**
     * Prints the all nodes with hierarchical form by using recursive calls.
     * @param root root of the tree.
     * @param depth depth of the tree.
     */
    private void printFileSystem(FileNode root,int depth) {

        for(int i=0 ; i<depth ; ++i){
            System.out.print('\t');
        }

        if(root == null){
            return;
        }

        System.out.println(root.getName());

        for(int i=0 ; i<root.childrenSize() ; ++i)
            printFileSystem(root.getChildren().get(i),depth+1);

    }
}