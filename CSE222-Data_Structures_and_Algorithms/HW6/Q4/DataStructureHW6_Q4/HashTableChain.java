package DataStructureHW6_Q4;

import java.util.LinkedList;

/**
 * Hash table with chain technique.
 * @param <K> key type
 * @param <V> value type
 */
public class HashTableChain<K,V> implements KWHashMap<K,V>{

    /**
     * The has table array
     */
    private LinkedList<Entry<K,V>>[] table;

    /**
     * the number of the key
     */
    private int numKeys;

    /**
     * the capacity
     */
    private static final int CAPACITY = 101;

    /**
     * the maximum load factor
     */
    private static final double LOAD_THRESHOLD = 3.0;


    /**
     * creates a new hash table.
     */
    public HashTableChain(){
        table = new LinkedList[CAPACITY];
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
        int index = key.hashCode() % table.length;
        if(index < 0){
            index += table.length;
        }
        if(table[index] == null){
            table[index] = new LinkedList<Entry<K,V>>();
        }
        for(Entry<K,V> nextItem : table[index]){
            if(nextItem.key.equals(key)){
                V oldValue = nextItem.value;
                nextItem.setValue(value);
                return oldValue;
            }
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
        LinkedList<Entry<K,V>>[] oldTable = table;
        table = new LinkedList[2 * oldTable.length + 1];
        for(int i=0 ; i<oldTable.length ; ++i) {
            while(oldTable[i] != null && !oldTable[i].isEmpty()){
                Entry<K,V> temp = oldTable[i].poll();
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
    @Override
    public V get(Object key) {
        int index = key.hashCode() % table.length;
        if(index < 0){
            index += table.length;
        }
        if(table[index] == null){
            return  null;
        }

        for(Entry<K, V> nextItem : table[index]){
            if(nextItem.key.equals(key)){
                return nextItem.value;
            }
        }
        return null;
    }

    /**
     * removes the mapping for this key from this table if it is present.
     * @param key the key
     * @return the previous value associated with specified key,or null if there was no mapping
     */
    @Override
    public V remove(Object key) {
        int index = key.hashCode() % table.length;
        if(index < 0)
            index += table.length;

        if(table[index] == null)
            return null;

        int i=0;
        for(Entry<K,V> nextItem : table[index]){
            if(key.equals(nextItem.key)){
                V temp= nextItem.value;
                table[index].remove(i);
                if(table[index].isEmpty()){
                    table[index] = null;
                }
                return temp;
            }
            ++i;
        }

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
     * contains key-value pairs for a hash table.
     * @param <K> key type
     * @param <V> value type
     */
    private static class Entry<K,V>{
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
    }
}