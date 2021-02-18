package DataStructureHW6_Q4;

/**
 * Hash table.
 * @param <K> key type
 * @param <V> value type
 */
public class HashTableOpen <K,V> implements KWHashMap<K,V>{

    /**
     * The has table array
     */
    protected Entry<K,V>[] table;

    /**
     * the initial capacity
     */
    protected static final int START_CAPACITY = 1;

    /**
     * A special object to indicate that an entry has been deleted
     */
    protected final Entry<K,V> DELETED = new Entry<>(null,null);

    /**
     * the maximum load factor
     */
    protected double LOAD_THRESHOLD = 0.75;

    /**
     * the number of the key
     */
    protected int numKeys;

    /**
     * the number of deleted keys
     */
    protected int numDeletes;

    /**
     * creates a new hash table.
     */
    public HashTableOpen(){
        table = new Entry[START_CAPACITY];
        numKeys = 0;
        numDeletes = 0 ;
    }

    /**
     * Associates the specified value with the specified key.
     * @param key the key
     * @param value the value
     * @return previous value associated with the specified key or null if there was no mapping for the key.
     */
    @Override
    public V put(K key, V value) {
        int index = find(key);
        if(table[index] == null){
            ++numKeys;
            table[index] = new Entry<>(key,value);

            double loadFactor = (double)((numKeys+numDeletes)/table.length);

            if(loadFactor > LOAD_THRESHOLD){
                reHash();
            }
            return null;
        }

        V oldValue = table[index].getValue();
        table[index].setValue(value);
        return oldValue;
    }

    /**
     * returns the value associated with key.
     * @param key the key
     * @return null if the key is not present.
     */
    @SuppressWarnings("unchecked")
    @Override
    public V get(Object key) {
        int index = find((K) key);

        if(table[index] != null)
            return table[index].value;

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
        int index = find((K) key);
        if(table[index] == null){
            return null;
        }

        Entry<K,V> temp = table[index];
        table[index] = DELETED;
        --numKeys;
        ++numDeletes;

        return temp.getValue();
    }

    /**
     * returns the index of specified key if present in the table
     * @param key the key
     * @return the index of specified key if present in the table
     */
    protected int find(K key){
        int index = key.hashCode() % table.length;
        if(index < 0)
            index += table.length;

        while(table[index] != null && !table[index].getKey().equals(key)){
            ++index;
            if(index >= table.length || index < 0)
                index = 0;
        }
        return index;
    }

    /**
     * Expands the table size
     */
    private void reHash(){
        Entry<K,V>[] oldTable = table;
        table = new Entry[2 * oldTable.length + 1];

        numKeys = 0;
        numDeletes = 0;

        for (Entry<K, V> kvEntry : oldTable) {
            if ((kvEntry != null) && (kvEntry != DELETED)) {
                put(kvEntry.key, kvEntry.value);
            }
        }
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
     * contains key-value pairs for a hash table.
     * @param <K> key type
     * @param <V> value type
     */
    protected static class Entry<K,V>{
        /**
         * the key
         */
        protected K key;

        /**
         * the value
         */
        protected V value;

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
    }
}