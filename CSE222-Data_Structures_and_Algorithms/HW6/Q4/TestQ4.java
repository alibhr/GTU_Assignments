import DataStructureHW6_Q4.*;

import java.util.Random;
public class TestQ4 {
    public static void main(String[] args) {

        HashTableChainGTU<Integer,Integer> o1 = new HashTableChainGTU<>();

        test(o1,10000);
        test(o1,20000);
        test(o1,30000);
        test(o1,40000);
        test(o1,50000);

    }

    private static void test(HashTableChainGTU<Integer, Integer> o1,int problemSize) {
        Random random = new Random();
        long start = System.currentTimeMillis();
        for(int i=0 ; i<problemSize ; ++i){
            o1.put(random.nextInt()%problemSize,random.nextInt()%problemSize);
        }
        long end = System.currentTimeMillis();
        System.out.println(problemSize + " elements have been added to HashTableChainGTU " + (end-start) + " ms\n");


        int counter=0;
        Integer found;
        start = System.currentTimeMillis();
        for(int i=0 ; i<problemSize ; ++i){
            found = o1.get(random.nextInt()%problemSize);
            if(found != null){
                ++counter;
            }
        }
        end = System.currentTimeMillis();
        System.out.println(counter + " element have been got randomly (HashTableChainGTU)" + (end-start) + " ms\n");


        Integer removed;
        counter = 0;
        start = System.currentTimeMillis();
        for(int i=0 ; i<problemSize ; ++i){
            removed = o1.remove(random.nextInt()%problemSize);
            if(removed != null){
                ++counter;
            }
        }
        end = System.currentTimeMillis();
        System.out.println(counter + " element have been removed randomly(HashTableChainGTU)" + (end-start) + " ms\n");
    }
}
