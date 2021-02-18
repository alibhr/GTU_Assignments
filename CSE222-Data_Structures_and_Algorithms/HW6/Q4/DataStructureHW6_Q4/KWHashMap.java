package DataStructureHW6_Q4;

/**
 * A hash table stores key-value pairs.
 * @param <K> key type
 * @param <V> value type
 */
public interface KWHashMap<K, V> {
    /**
     * Associates the specified value with the specified key.
     * @param key the key
     * @param value the value
     * @return previous value associated with the specified key or null if there was no mapping for the key.
     */
    V put(K key, V value);

    /**
     * returns the value associated with key.
     * @param key the key
     * @return null if the key is not present.
     */
    V get(Object key);

    /**
     * removes the mapping for this key from this table if it is present.
     * @param key the key
     * @return the previous value associated with specified key,or null if there was no mapping
     */
    V remove(Object key);

    /**
     * returns true if this table contains no key-value mappings.
     * @return true if this table contains no key-value mappings.
     */
    boolean isEmpty();

    /**
     * returns the size of the table
     * @return the size of the table
     */
    int size();
}