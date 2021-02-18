package DataStructureHW7_Q3;

/**
 * for a class that implements the binary search tree.
 * @param <E> data type.
 * @author Ali Bahar 171044066
 */
public interface SearchTree<E> {
    /**
     * Inserts item where it belongs int tree.
     * @param item item to be added.
     * @return true if item is inserted; false if it isn't (already in tree)
     */
    boolean add(E item);

    /**
     * Returns true if target is found in tree.
     * @param target element to be searched.
     * @return true if target is found in tree.
     */
    boolean contains(E target);

    /**
     * Returns a reference to the data in the node that is equal to target. If no such node s found, returns null.
     * @param target element to be searched.
     * @return a reference to the data in the node that is equal to target. If no such node s found, returns null.
     */
    E find(E target);

    /**
     * Removes target(if found) from tree and returns it; otherwise, returns null.
     * @param target element to be removed.
     * @return if target founds, returns it; otherwise, returns null
     */
    E delete(E target);

    /**
     * Removes target (if found) from tree and returns true; otherwise, returns false.
     * @param target to be removed.
     * @return if target founds, returns true; otherwise, returns false.
     */
    boolean remove(E  target);
}