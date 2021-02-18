package DataStructureHW6_Q4;

/**
 * Hash table.
 * @param <K> key type
 * @param <V> value type
 */
public class HashTableOpenGTU<K,V> extends HashTableOpen<K,V> implements KWHashMap<K,V>{

    public HashTableOpenGTU(){
        table = new Entry[START_CAPACITY];
        numKeys = 0;
        numDeletes = 0 ;
    }

    /**
     * returns the index of specified key if present in the table
     * @param key the key
     * @return the index of specified key if present in the table
     */
    @Override
    protected int find(K key){
        int index = hash(key);
        if(index < 0)
            index += table.length;

        int index2 = 0;
        if(table[index] != null){
            index2 = second_hash(key);
        }

        int newIndex = (index + index2) % table.length;

        if(newIndex < 0)
            newIndex += table.length;

        while(table[newIndex] != null && !table[newIndex].getKey().equals(key)){
            newIndex++;
            if(newIndex >= table.length) {
                newIndex = 0;
            }
        }
        return newIndex;
    }

    /**
     * calculates an index
     * @param key the key to calculate the index
     * @return an index
     */
    public int hash(K key){
        if(key == null){
            return 0;
        }
        return key.hashCode() % table.length;
    }

    /**
     * calculates an index
     * @param key the key to calculate the index
     * @return an index
     */
    public int second_hash(K key){
        if(key == null){
            return 0;
        }
        return (1);
    }
}