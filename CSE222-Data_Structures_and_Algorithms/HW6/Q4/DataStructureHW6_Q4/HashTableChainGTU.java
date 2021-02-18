package DataStructureHW6_Q4;

/**
 * Hash table.
 * @param <K> key type
 * @param <V> value type
 */
public class HashTableChainGTU<K extends Comparable<K>,V> implements KWHashMap<K,V> {

    /**
     * The has table array
     */
    BinarySearchTree<Entry<K,V>>[] table;

    /**
     * the capacity
     */
    private static final int CAPACITY = 2;

    /**
     * the maximum load factor
     */
    private static final double LOAD_THRESHOLD = 3.0;

    /**
     * the number of the key
     */
    private int numKeys;

    /**
     * creates a new hash table.
     */
    public HashTableChainGTU(){
        table = new BinarySearchTree[CAPACITY];
        numKeys = 0;
    }

    /**
     * Associates the specified value with the specified key.
     * @param key the key
     * @param value the value
     * @return previous value associated with the specified key or null if there was no mapping for the key.
     */
    @Override
    public V put(K key, V value) {
        int index = hash(key);
        if(index < 0){
            index += table.length;
        }
        if(table[index] == null){
            table[index] = new BinarySearchTree<Entry<K,V>>();
        }
        if(!table[index].add(new Entry<K,V>(key,value))){
            return table[index].getReplaced().getValue();
        }
        ++numKeys;

        if(numKeys > (LOAD_THRESHOLD * table.length)){
            reHash();
        }

        return null;
    }

    /**
     * Expands the table size
     */
    private void reHash(){
        numKeys = 0;
        BinarySearchTree<Entry<K,V>>[] oldTable = table;
        table = new BinarySearchTree[2 * oldTable.length + 1];
        for(int i=0 ; i<oldTable.length ; ++i) {
            while(oldTable[i] != null && !oldTable[i].isEmpty()){
                Entry<K,V> temp = oldTable[i].popFromRoot();
                if(temp != null)
                    put(temp.getKey(),temp.getValue());
            }
        }
    }

    /**
     * returns the value associated with key.
     * @param key the key
     * @return null if the key is not present.
     */
    @SuppressWarnings("unchecked")
    @Override
    public V get(Object key) {
        int index = hash(key);
        if(index < 0){
            index += table.length;
        }
        if(table[index] == null){
            return null;
        }

        Entry<K,V> temp = table[index].find(new Entry<K,V>((K) key,null));

        if(temp != null)
            return temp.getValue();
        else
            return null;
    }

    /**
     * removes the mapping for this key from this table if it is present.
     * @param key the key
     * @return the previous value associated with specified key,or null if there was no mapping
     */
    @SuppressWarnings("unchecked")
    @Override
    public V remove(Object key) {
        int index = hash(key);
        if(index < 0){
            index += table.length;
        }
        if(table[index] == null){
            return null;
        }

        Entry<K,V> temp = table[index].delete(new Entry<K,V>((K) key,null));

        if(temp != null){
            --numKeys;
            return temp.getValue();
        }
        else
            return null;
    }

    /**
     * returns true if this table contains no key-value mappings.
     * @return true if this table contains no key-value mappings.
     */
    @Override
    public boolean isEmpty() {
        return numKeys == 0;
    }

    /**
     * returns the size of the table
     * @return the size of the table
     */
    @Override
    public int size() {
        return numKeys;
    }

    /**
     * calculates an index
     * @param key the key to calculate the index
     * @param <K> key type
     * @return an index
     */
    public <K> int hash(K key){
        if(key == null){
            return 0;
        }
        return key.hashCode() % table.length;
    }

    /**
     * contains key-value pairs for a hash table.
     * @param <K> key type
     * @param <V> value type
     */
    private static class Entry<K extends Comparable<K>,V> implements Comparable<Entry<K,V>>{
        /**
         * the key
         */
        private K key;

        /**
         * the value
         */
        private V value;

        /**
         * creates a new key-value pair
         * @param key the key
         * @param value the value
         */
        public Entry(K key, V value){
            this.key = key;
            this.value = value;
        }

        /**
         * gets the key
         * @return key
         */
        public K getKey() { return key; }

        /**
         * gets the value
         * @return value
         */
        public V getValue() { return value; }

        /**
         * sets the value
         * @param val new value
         * @return old value
         */
        public V setValue(V val) {
            V oldValue = value;
            this.value = val;
            return oldValue;
        }

        /**
         * compares two Entry objects
         * @param o the other object to be compared
         * @return difference between keys
         */
        @Override
        public int compareTo(Entry<K, V> o) {
            if(o == null){
                throw new NullPointerException();
            }
            return this.key.compareTo(o.key);
        }
    }
}