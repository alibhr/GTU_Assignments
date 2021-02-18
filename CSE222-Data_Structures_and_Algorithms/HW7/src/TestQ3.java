import DataStructureHW7_Q2.SkipListGTU;
import DataStructureHW7_Q3.*;

import java.util.Random;
import java.util.TreeSet;
import java.util.concurrent.ConcurrentSkipListSet;

public class TestQ3 {

    private static final int instanceNumber = 10;
    private static long totalInsertionTime;
    private static long totalRemoveTime;

    public static void main(String[] args) {
        //Test 1
        binarySearchTreeTest();

        //Test 2
        redBlackTest();

        //Test 3
        treeSetTest();

        //Test 4
        bTreeTest();

        //Test 5
        skipListTest();

        //Test 6
        concurrentSkipListTest();

        //Test 7
        skipListQ2Test();
    }

    private static void binarySearchTreeTest(){
        binarySearchTreeTest(10000);
        binarySearchTreeTest(20000);
        binarySearchTreeTest(40000);
        binarySearchTreeTest(80000);
    }
    private static void binarySearchTreeTest(int problemSize){
        totalInsertionTime = 0;
        totalRemoveTime = 0;
        for(int j=0 ; j<instanceNumber ; ++j){
            BinarySearchTree<Integer> binarySearchTree = new BinarySearchTree<>();

            searchTreeTest(binarySearchTree,problemSize);
        }
        System.out.println("(Regular Binary Search Tree) " +
                "\nproblem size : "+ problemSize +
                "\nAverage running time (insertion): " + (totalInsertionTime/10) + "ns" +
                "\nAverage running time (remove): " + (totalRemoveTime/10) + "ns\n");
    }

    private static void redBlackTest(){
        redBlackTest(10000);
        redBlackTest(20000);
        redBlackTest(40000);
        redBlackTest(80000);
    }
    private static void redBlackTest(int problemSize){
        totalInsertionTime = 0;
        totalRemoveTime = 0;
        for(int j=0 ; j<instanceNumber ; ++j){
            RedBlackTree<Integer> redBlackTree = new RedBlackTree<>();
            Random random = new Random();
            for(int i=0 ; i<problemSize ; ++i){
                redBlackTree.add(random.nextInt(problemSize));
            }

            //TODO verify that data structure are built correctly.

            long start = System.nanoTime();
            for(int i=0 ; i<10 ; ++i){
                redBlackTree.add(random.nextInt(problemSize));
            }
            totalInsertionTime += (System.nanoTime()-start);

            //TODO Remove test

        }
        System.out.println("(Red black tree implementation in the book) " +
                "\nproblem size : "+ problemSize +
                "\nAverage running time (insertion): " + (totalInsertionTime/10) + "ns\n");
    }

    private static void treeSetTest() {
        treeSetTest(10000);
        treeSetTest(20000);
        treeSetTest(40000);
        treeSetTest(80000);
    }
    private static void treeSetTest(int problemSize){
        totalInsertionTime = 0;
        totalRemoveTime = 0;
        for(int j=0 ; j<instanceNumber ; ++j){
            TreeSet<Integer> treeSet = new TreeSet<>();
            Random random = new Random();
            for(int i=0 ; i<problemSize ; ++i){
                treeSet.add(random.nextInt(problemSize));
            }

            //TODO verify that data structure are built correctly.

            long start = System.nanoTime();
            for(int i=0 ; i<10 ; ++i){
                treeSet.add(random.nextInt(problemSize));
            }
            totalInsertionTime += (System.nanoTime()-start);

            start = System.nanoTime();
            for(int i=0 ; i<10 ; ++i){
                if(!treeSet.remove(random.nextInt(problemSize))){
                    --i;
                }
            }
            totalRemoveTime +=(System.nanoTime()-start);
        }
        System.out.println("(Tree set(Red black tree implementation in java)) " +
                "\nproblem size : "+ problemSize +
                "\nAverage running time (insertion): " + (totalInsertionTime/10) + "ns" +
                "\nAverage running time (remove): " + (totalRemoveTime/10) + "ns\n");
    }

    private static void bTreeTest(){
        bTreeTest(10000);
        bTreeTest(20000);
        bTreeTest(40000);
        bTreeTest(80000);
    }
    private static void bTreeTest(int problemSize){
        totalInsertionTime = 0;
        totalRemoveTime = 0;
        for(int j=0 ; j<instanceNumber ; ++j){
            BTree<Integer> bTree = new BTree<>(5);
            Random random = new Random();
            for(int i=0 ; i<problemSize ; ++i){
                bTree.add(random.nextInt(problemSize));
            }

            //TODO verify that data structure are built correctly.

            long start = System.nanoTime();
            for(int i=0 ; i<10 ; ++i){
                bTree.add(random.nextInt(problemSize));
            }
            totalInsertionTime += (System.nanoTime()-start);
        }
        System.out.println("BTree" +
                "\nproblem size : "+ problemSize +
                "\nAverage running time (insertion): " + (totalInsertionTime/10) + "ns\n");

        //TODO remove test
    }

    private static void skipListTest(){
        skipListTest(10000);
        skipListTest(20000);
        skipListTest(40000);
        skipListTest(80000);
    }
    private static void skipListTest(int problemSize){
        totalInsertionTime = 0;
        totalRemoveTime = 0;
        for(int j=0 ; j<instanceNumber ; ++j){
            SkipList<Integer> skipList = new SkipList<>();
            Random random = new Random();
            for(int i=0 ; i<problemSize ; ++i){
                skipList.add(random.nextInt(problemSize));
            }

            //TODO verify that data structure are built correctly.

            long start = System.nanoTime();
            for(int i=0 ; i<10 ; ++i){
                skipList.add(random.nextInt(problemSize));
            }
            totalInsertionTime += (System.nanoTime()-start);

            start = System.nanoTime();
            for(int i=0 ; i<10 ; ++i){
                if(!skipList.remove(random.nextInt(problemSize))){
                    --i;
                }
            }
            totalRemoveTime +=(System.nanoTime()-start);
        }
        System.out.println("Skip List " +
                "\nproblem size : "+ problemSize +
                "\nAverage running time (insertion): " + (totalInsertionTime/10) + "ns" +
                "\nAverage running time (remove): " + (totalRemoveTime/10) + "ns\n");
    }

    private static void concurrentSkipListTest(){
        concurrentSkipListTest(10000);
        concurrentSkipListTest(20000);
        concurrentSkipListTest(40000);
        concurrentSkipListTest(80000);
    }
    private static void concurrentSkipListTest(int problemSize){
        totalInsertionTime = 0;
        totalRemoveTime = 0;
        for(int j=0 ; j<instanceNumber ; ++j){
            ConcurrentSkipListSet<Integer> concurrentSkipListSet = new ConcurrentSkipListSet<>();
            Random random = new Random();
            for(int i=0 ; i<problemSize ; ++i){
                concurrentSkipListSet.add(random.nextInt(problemSize));
            }

            //TODO verify that data structure are built correctly.

            long start = System.nanoTime();
            for(int i=0 ; i<10 ; ++i){
                concurrentSkipListSet.add(random.nextInt(problemSize));
            }
            totalInsertionTime += (System.nanoTime()-start);

            start = System.nanoTime();
            for(int i=0 ; i<10 ; ++i){
                if(!concurrentSkipListSet.remove(random.nextInt(problemSize))){
                    --i;
                }
            }
            totalRemoveTime +=(System.nanoTime()-start);
        }
        System.out.println("concurrentSkipListSet(skip list implementation in java) " +
                "\nproblem size : "+ problemSize +
                "\nAverage running time (insertion): " + (totalInsertionTime/10) + "ns" +
                "\nAverage running time (remove): " + (totalRemoveTime/10) + "ns\n");
    }

    private static void skipListQ2Test(){
        skipListQ2Test(10000);
        skipListQ2Test(20000);
        //skipListQ2Test(40000);
        //skipListQ2Test(80000);
    }
    private static void skipListQ2Test(int problemSize){
        totalInsertionTime = 0;
        totalRemoveTime = 0;
        for(int j=0 ; j<instanceNumber ; ++j){
            SkipListGTU<Integer> skipListGTU = new SkipListGTU<>(4,2);
            Random random = new Random();
            for(int i=0 ; i<problemSize ; ++i){
                skipListGTU.add(random.nextInt(problemSize));
            }

            //TODO verify that data structure are built correctly.

            long start = System.nanoTime();
            for(int i=0 ; i<10 ; ++i){
                skipListGTU.add(random.nextInt(problemSize));
            }
            totalInsertionTime += (System.nanoTime()-start);

        }
        System.out.println("Skip list in Q2 " +
                "\nproblem size : "+ problemSize +
                "\nAverage running time (insertion): " + (totalInsertionTime/10) + "ns\n");
    }

    private static void searchTreeTest(SearchTree<Integer> tree,int problemSize){
        Random random = new Random();
        for(int i=0 ; i<problemSize ; ++i){
            tree.add(random.nextInt(problemSize));
        }

        //TODO verify that data structure are built correctly.

        long start = System.nanoTime();
        for(int i=0 ; i<10 ; ++i){
            tree.add(random.nextInt(problemSize));
        }
        totalInsertionTime += (System.nanoTime()-start);

        start = System.nanoTime();
        for(int i=0 ; i<10 ; ++i){
            if(!tree.remove(random.nextInt(problemSize))){
                --i;
            }
        }
        totalRemoveTime +=(System.nanoTime()-start);
    }
}