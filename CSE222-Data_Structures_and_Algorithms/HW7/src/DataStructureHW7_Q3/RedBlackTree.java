package DataStructureHW7_Q3;

/**
 * RedBlackTree.java
 * Implements a Red-Black binary search tree
 * Red-Black trees were invented by Bayer with refinments
 * (the color convention) introduced by Guibas and Sedgewick.
 * @author Koffman and Wolfgang
 * @param <E> generic data type
 */
public class RedBlackTree<E extends Comparable<E>> extends BinarySearchTreeWithRotate<E> {

    private boolean blackNodeRemoved;
    private E largestElementSearch;


    /**
     * Insert an item into the tree. This is the starter method of a recursive process.
     * @param item - The item to be inserted
     * @return true if item inserted, false if item already in the tree.
     */
    @Override
    public boolean add(E item) {
        if(root == null){
            root = new RedBlackNode<>(item);
            ((RedBlackNode<E>)root).isRed = false;
            return true;
        }
        else{
            root = add((RedBlackNode<E>)root,item);
            ((RedBlackNode<E>)root).isRed = false;
            return addReturn;
        }
    }

    /**
     * Recursive add method.
     * @param localRoot - The root of the subtree
     * @param item - The item to be inserted
     * @return  updated local root of the subtree
     */
    private RedBlackNode<E> add(RedBlackNode<E> localRoot, E item){
        int compResult = item.compareTo(localRoot.data);

        if(compResult == 0){
            addReturn = false;
            return localRoot;
        }
        else if(compResult < 0){
            if(localRoot.left == null){
                localRoot.left = new RedBlackNode<>(item);
                addReturn = true;
                return localRoot;
            }
            else{
                moveBlackDown(localRoot);

                localRoot.left = add((RedBlackNode<E>)localRoot.left,item);

                if(((RedBlackNode<E>)localRoot.left).isRed){
                    if( localRoot.left.left != null && ((RedBlackNode<E>)localRoot.left.left).isRed){
                        ((RedBlackNode<E>)localRoot.left).isRed = false;
                        localRoot.isRed = true;
                        return (RedBlackNode<E>) rotateRight(localRoot);
                    }
                    else if( localRoot.left.right != null && ((RedBlackNode<E>)localRoot.left.right).isRed){
                        localRoot.left = rotateLeft(localRoot.left);
                        ((RedBlackNode<E>)localRoot.left).isRed = false;
                        localRoot.isRed = true;
                        return (RedBlackNode<E>) rotateRight(localRoot);
                    }
                }
                return localRoot;
            }
        }
        else {

            if(localRoot.right == null){
                localRoot.right = new RedBlackNode<>(item);
                addReturn=true;
                return localRoot;
            }

            moveBlackDown(localRoot);

            localRoot.right = add((RedBlackNode<E>)localRoot.right,item);

            if(((RedBlackNode<E>)localRoot.right).isRed){
                if(localRoot.right.right != null && ((RedBlackNode<E>)localRoot.right.right).isRed){
                    ((RedBlackNode<E>)localRoot.right).isRed = false;
                    localRoot.isRed = true;
                    return (RedBlackNode<E>) rotateLeft(localRoot);
                }
                else if(localRoot.right.left != null && ((RedBlackNode<E>)localRoot.right.left).isRed){
                    localRoot.right = rotateRight(localRoot.right);
                    ((RedBlackNode<E>)localRoot.right).isRed = false;
                    localRoot.isRed = true;
                    return (RedBlackNode<E>) rotateLeft(localRoot);
                }
            }
            return localRoot;
        }
    }

    /*// delete method doesn't work properly.
    public E delete (E item){
        blackNodeRemoved = false;
        if(root == null)
            return null;

        root = delete((RedBlackNode<E>) root,item);

        if(root != null)
            ((RedBlackNode<E>)root).isRed = false;

        return deleteReturn;
    }

    private RedBlackNode<E> delete(RedBlackNode<E> localRoot,E item){
        if(localRoot == null)
            return null;

        int compResult = item.compareTo(localRoot.data);

        if(compResult < 0){
            localRoot.left = delete((RedBlackNode<E>)localRoot.left,item);
            if(blackNodeRemoved){
                localRoot = rightFix(localRoot);
                blackNodeRemoved = false;
            }
            return localRoot;

        }
        else if(compResult > 0){
            localRoot.right = delete((RedBlackNode<E>)localRoot.right,item);
            if(blackNodeRemoved){
                localRoot = leftFix(localRoot);
                blackNodeRemoved = false;
            }
            return localRoot;
        }
        else{
            deleteReturn = localRoot.data;

            if(localRoot.left == null){
                if(localRoot.right != null){
                    ((RedBlackNode<E>)localRoot.right).isRed = false;
                }
                else if(!localRoot.isRed){
                    blackNodeRemoved = true;
                }
                return (RedBlackNode<E>) localRoot.right;
            }
            else if(localRoot.right == null){
                ((RedBlackNode<E>)localRoot.left).isRed = false;
                return (RedBlackNode<E>) localRoot.left;
            }
            else{
                if(localRoot.left.right == null){
                    if(!((RedBlackNode<E>)localRoot.left).isRed){
                        if(localRoot.left.left != null){
                            ((RedBlackNode<E>)localRoot.left.left).isRed = false;
                        }
                    }
                    localRoot.data = localRoot.left.data;
                    localRoot.left = localRoot.left.left;
                }
                else{
                    findLargestChild((RedBlackNode<E>) localRoot.left);
                    localRoot.data = largestElementSearch;
                    if(blackNodeRemoved){
                        localRoot.left = leftFix((RedBlackNode<E>) localRoot.left);
                        blackNodeRemoved = false;
                    }
                }
                return localRoot;
            }
        }
    }

    protected RedBlackNode<E> findLargestChild(RedBlackNode<E> parent){
        if(parent.right.right == null){
            if(!((RedBlackNode<E>)parent.right).isRed){
                blackNodeRemoved = true;
            }
            largestElementSearch = parent.right.data;
            parent.right = parent.right.left;
            return parent;
        }

        parent = findLargestChild((RedBlackNode<E>)parent.right);

        if(blackNodeRemoved){
            parent = leftFix(parent);
            blackNodeRemoved = false;
        }
        return parent;
    }

    private RedBlackNode<E> leftFix(RedBlackNode<E> parent){

        if( parent.left!=null && parent.left.left != null && parent.left.right != null){
            if(!parent.isRed && ((RedBlackNode<E>)parent.left).isRed && !((RedBlackNode<E>)parent.left.left).isRed && !((RedBlackNode<E>)parent.left.right).isRed){
                parent.isRed = true;
                ((RedBlackNode<E>)parent.left).isRed = false;
                return (RedBlackNode<E>) rotateRight(parent);
            }
            else if(!((RedBlackNode<E>)parent.left).isRed && !((RedBlackNode<E>)parent.left.left).isRed && !((RedBlackNode<E>)parent.left.right).isRed){
                ((RedBlackNode<E>)parent.left).isRed = true;
            }
        }

        else if(parent.left!=null && !((RedBlackNode<E>)parent.left).isRed){
            if(parent.left.right!=null && ((RedBlackNode<E>)parent.left.right).isRed){
                ((RedBlackNode<E>)parent.left).isRed = true;
                ((RedBlackNode<E>)parent.left.right).isRed = false;
                parent.left = rotateLeft(parent.left);
            }
            else if(parent.left.left!=null && ((RedBlackNode<E>)parent.left.left).isRed){
                parent.isRed = false;
                ((RedBlackNode<E>)parent.left).isRed = true;
                ((RedBlackNode<E>)parent.left.left).isRed = false;
                return (RedBlackNode<E>) rotateRight(parent);
            }
        }

        return parent;
    }

    private RedBlackNode<E> rightFix(RedBlackNode<E> parent){
        if(!parent.isRed){
            if(((RedBlackNode<E>)parent.right).isRed && !((RedBlackNode<E>)parent.right.right).isRed && !((RedBlackNode<E>)parent.right.left).isRed){
                parent.isRed = true;
                ((RedBlackNode<E>)parent.right).isRed = false;
                return (RedBlackNode<E>) rotateLeft(parent);
            }
        }

        else if(!((RedBlackNode<E>)parent.right).isRed && !((RedBlackNode<E>)parent.right.left).isRed && !((RedBlackNode<E>)parent.right.right).isRed){
            ((RedBlackNode<E>)parent.right).isRed = true;
        }

        else if(!((RedBlackNode<E>)parent.right).isRed){
            if(((RedBlackNode<E>)parent.right.right).isRed){
                ((RedBlackNode<E>)parent.right).isRed = true;
                ((RedBlackNode<E>)parent.right.right).isRed = false;
                parent.right = rotateRight(parent.right);
            }
            else if(((RedBlackNode<E>)parent.right.left).isRed){
                parent.isRed = false;
                ((RedBlackNode<E>)parent.right.left).isRed = false;
                return (RedBlackNode<E>) rotateLeft(parent);
            }
        }
        return parent;
    }
    */

    /**
     * Check to see whether both children of the given node are red.
     * If so, make them black and change the localRoot's color to red.
     * @param localRoot The node to check whether both children are red or not
     */
    private void moveBlackDown(RedBlackNode<E> localRoot){
        if(localRoot.left == null ||localRoot.right == null){
            return;
        }

        if(((RedBlackNode<E>)localRoot.left).isRed && ((RedBlackNode<E>)localRoot.right).isRed){
            ((RedBlackNode<E>)localRoot.left).isRed = false;
            ((RedBlackNode<E>)localRoot.right).isRed = false;
            localRoot.isRed = true;
        }
    }

    /**
     * Nested class to represent a Red-Black node.
     * @param <E> generic data type
     */
    private static class RedBlackNode<E> extends Node<E>{

        /** Color indicator. True if red, false if black. */
        private boolean isRed;

        /**
         * Create a RedBlackNode with the default color of red
         * and the given data field.
         * @param item The data field
         */
        public RedBlackNode(E item){
            super(item);
            isRed = true;
        }

        /**
         * Return a string representation of this object.
         * The color (red or black) is appended to the
         * node's contents.
         * @return String representation of this object
         */
        @Override
        public String toString() {
            if(isRed)
                return "Red :  " + super.toString();
            else
                return "Black :  " + super.toString();
        }
    }
}