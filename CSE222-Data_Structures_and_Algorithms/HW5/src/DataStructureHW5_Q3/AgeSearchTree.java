package DataStructureHW5_Q3;

/**
 * records the number of people in each age for a population.
 * @param <E> type of the data which extends AgeDataInterface.
 * @author Ali Bahar 171044066
 */
public class AgeSearchTree<E extends AgeDataInterface<E>> extends BinarySearchTree<E>{

    /**
     * Constructs a new empty AgeSearchTree.
     */
    public AgeSearchTree(){ super(); }

    /**
     * Adds a new data to AgeSearchTree.
     * @param item item to be added.
     * @return true.
     */
    @Override
    public boolean add(E item) {
        this.root = add(this.root,item);
        addReturn = true;
        return true;
    }
    private Node<E> add(Node<E> localRoot,E item){
        if(localRoot == null){
            return new Node<E>(item);
        }

        int compResult = item.compareTo(localRoot.getData());

        if(compResult == 0){
            localRoot.getData().setNumberOfPeople(localRoot.getData().getNumberOfPeople()+item.getNumberOfPeople());
        }
        else if (compResult < 0){
            localRoot.setLeft(add(localRoot.getLeft(),item));
        }
        else{
            localRoot.setRight(add(localRoot.getRight(),item));
        }

        return localRoot;
    }

    /**
     * returns the number of people younger than an age.
     * @param anAge an age to compare.
     * @return the number of people younger than an age.
     */
    public int youngerThan(int anAge){ return youngerThan(this.root,anAge); }
    private int youngerThan(Node<E> localRoot,int anAge){
        if(localRoot == null){ return 0; }

        if(localRoot.getData().getAge() < anAge){
            return localRoot.getData().getNumberOfPeople()  +
                    youngerThan(localRoot.getLeft(),anAge)  +
                    youngerThan(localRoot.getRight(),anAge);
        }

        return youngerThan(localRoot.getLeft(),anAge);
    }

    /**
     * returns number of people older than an age.
     * @param anAge an age to compare.
     * @return number of people older than an age.
     */
    public int olderThan(int anAge){ return olderThan(this.root,anAge); }
    private int olderThan(Node<E> localRoot,int anAge){
        if(localRoot == null){ return 0; }

        if(localRoot.getData().getAge() > anAge){
            return localRoot.getData().getNumberOfPeople()  +
                    olderThan(localRoot.getLeft(),anAge)    +
                    olderThan(localRoot.getRight(),anAge);
        }

        return olderThan(localRoot.getRight(),anAge);
    }

    /**
     * first check if a node with that age exists.
     * If it exists and the number of people field of this node’s AgeData object is greater than 1,
     * it will decrease the number of people field 1. If the number of people field is 1, it will remove the node.
     * @param target target value to be removed.
     * @return true if target has been remove, returns false otherwise.
     */
    @Override
    public boolean remove(E target) {
        E found = find(target);
        if(found != null && found.getNumberOfPeople() > 1){
            found.decrementNumberOfPeople();
            return true;
        }
        else if(found == null){
            return false;
        }
        else{
            delete(target);
            return true;
        }
    }

    /**
     * Returns a string representation of the AgeSearchTree(preOrderTraverse).
     * @return a string representation of the AgeSearchTree.
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        preOrderTraverse(this.root,sb);
        return sb.toString();
    }
    private void preOrderTraverse(Node<E> node,StringBuilder sb){
        if(node == null){
            sb.append("null\n");
            return;
        }

        sb.append(node.toString()).append("\n");
        preOrderTraverse(node.getLeft(),sb);
        preOrderTraverse(node.getRight(),sb);
    }
}