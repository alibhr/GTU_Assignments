import java.util.LinkedList;
import java.util.Random;

public class Main {
    
    static final int repeat = 1;
    static final boolean elementNumber10  = true;
    static final boolean elementNumber40  = true;
    static final boolean elementNumber100 = true;
    static final boolean elementNumber150 = true;
    static final boolean elementNumber180 = true;

    public static void main(String[] args) {

        System.out.println("Bubble Sort ...");
        test(BubbleSort::bubbleSort);

        System.out.println("Heap Sort ...");
        test(HeapSort::heapSort);

        System.out.println("insertion Sort ...");
        test(InsertionSort::insertionSort);

        System.out.println("Merge Sort ...");
        test(MergeSort::mergeSort);

        System.out.println("Quick Sort ...");
        test(QuickSort::quickSort);

        System.out.println("selection Sort ...");
        test(SelectionSort::selectionSort);

        System.out.println("shell Sort ...");
        test(ShellSort::shellSort);

        System.out.println("merge Sort (Linked List) ...");
        linkedTest(MergeSortLinkedList::mergeSortLinkedList);

        System.out.println("Quick Sort (Linked List) ...");
        linkedTest(QuickSortLinkedList::quickSortLinkedList);
    }

    private static <E> void test(Tester<Integer> tester){
        long start = 0;
        long end = 0;
        long total = 0;

        if(elementNumber10){
            for(int j=0 ; j<repeat ; ++j){
                start = System.currentTimeMillis();
                tester.execute(createRandomArray(10000));
                end = System.currentTimeMillis();
                System.out.println("10000 element has been sorted in "+ (end-start) + "ms");
                total += (end-start);
            }
            System.out.println("average time "+ (total/repeat) + "ms");
            total=0;

            start = System.currentTimeMillis();
            tester.execute(createSortedArray(10000));
            end = System.currentTimeMillis();
            System.out.println("10000 sorted array test " + (end-start) + "ms");
        }

        if(elementNumber40){
            for(int j=0 ; j<repeat ; ++j){
                start = System.currentTimeMillis();
                tester.execute(createRandomArray(40000));
                end = System.currentTimeMillis();
                System.out.println("40000 element has been sorted in "+ (end-start) + "ms");
                total += (end-start);
            }
            System.out.println("average time "+ (total/repeat) + "ms");
            total=0;

            start = System.currentTimeMillis();
            tester.execute(createSortedArray(40000));
            end = System.currentTimeMillis();
            System.out.println("40000 sorted array test " + (end-start) + "ms");
        }

        if(elementNumber100){
            for(int j=0 ; j<repeat ; ++j){
                start = System.currentTimeMillis();
                tester.execute(createRandomArray(100000));
                end = System.currentTimeMillis();
                System.out.println("100000 element has been sorted in "+ (end-start) + "ms");
                total += (end-start);
            }
            System.out.println("average time "+ (total/repeat) + "ms");
            total=0;

            start = System.currentTimeMillis();
            tester.execute(createSortedArray(100000));
            end = System.currentTimeMillis();
            System.out.println("100000 sorted array test " + (end-start) + "ms");
        }

        if(elementNumber150){
            for(int j=0 ; j<repeat ; ++j){
                start = System.currentTimeMillis();
                tester.execute(createRandomArray(150000));
                end = System.currentTimeMillis();
                System.out.println("150000 element has been sorted in "+ (end-start) + "ms");
                total += (end-start);
            }
            System.out.println("average time "+ (total/repeat) + "ms");
            total=0;

            start = System.currentTimeMillis();
            tester.execute(createSortedArray(150000));
            end = System.currentTimeMillis();
            System.out.println("150000 sorted array test " + (end-start) + "ms");
        }

        if(elementNumber180){
            for(int j=0 ; j<repeat ; ++j){
                start = System.currentTimeMillis();
                tester.execute(createRandomArray(180000));
                end = System.currentTimeMillis();
                System.out.println("180000 element has been sorted in "+ (end-start) + "ms");
                total += (end-start);
            }
            System.out.println("average time "+ (total/repeat) + "ms");

            start = System.currentTimeMillis();
            tester.execute(createSortedArray(180000));
            end = System.currentTimeMillis();
            System.out.println("180000 sorted array test " + (end-start) + "ms");
        }
    }
    private static Integer[] createRandomArray(int size){
        Random rand = new Random();
        Integer[] arr = new Integer[size];
        for(int i=0 ; i<size ; ++i){
            arr[i] = rand.nextInt(size);
        }
        return arr;
    }
    private static Integer[] createSortedArray(int size){
        Integer[] arr = new Integer[size];
        for(int i=0 ; i<size ; ++i){
            arr[i] = i;
        }
        return arr;
    }

    private static <E> void linkedTest(LinkedTester<Integer> tester){
        long start = 0;
        long end = 0;
        long total = 0;

        if(elementNumber10){
            for(int j=0 ; j<repeat ; ++j){
                start = System.currentTimeMillis();
                tester.execute(createRandomList(10000));
                end = System.currentTimeMillis();
                System.out.println("10000 element has been sorted in "+ (end-start) + "ms");
                total += (end-start);
            }
            System.out.println("average time "+ (total/repeat) + "ms");
            total=0;

            start = System.currentTimeMillis();
            tester.execute(createSortedList(10000));
            end = System.currentTimeMillis();
            System.out.println("10000 sorted array test " + (end-start) + "ms");
        }

        if(elementNumber40){
            for(int j=0 ; j<repeat ; ++j){
                start = System.currentTimeMillis();
                tester.execute(createRandomList(40000));
                end = System.currentTimeMillis();
                System.out.println("40000 element has been sorted in "+ (end-start) + "ms");
                total += (end-start);
            }
            System.out.println("average time "+ (total/repeat) + "ms");
            total=0;

            start = System.currentTimeMillis();
            tester.execute(createSortedList(40000));
            end = System.currentTimeMillis();
            System.out.println("40000 sorted array test " + (end-start) + "ms");
        }

        if(elementNumber100){
            for(int j=0 ; j<repeat ; ++j){
                start = System.currentTimeMillis();
                tester.execute(createRandomList(100000));
                end = System.currentTimeMillis();
                System.out.println("100000 element has been sorted in "+ (end-start) + "ms");
                total += (end-start);
            }
            System.out.println("average time "+ (total/repeat) + "ms");
            total=0;

            start = System.currentTimeMillis();
            tester.execute(createSortedList(100000));
            end = System.currentTimeMillis();
            System.out.println("100000 sorted array test " + (end-start) + "ms");
        }

        if (elementNumber150) {
            for(int j=0 ; j<repeat ; ++j){
                start = System.currentTimeMillis();
                tester.execute(createRandomList(150000));
                end = System.currentTimeMillis();
                System.out.println("150000 element has been sorted in "+ (end-start) + "ms");
                total += (end-start);
            }
            System.out.println("average time "+ (total/repeat) + "ms");
            total=0;

            start = System.currentTimeMillis();
            tester.execute(createSortedList(150000));
            end = System.currentTimeMillis();
            System.out.println("150000 sorted array test " + (end-start) + "ms");
        }

        if(elementNumber180){
            for(int j=0 ; j<repeat ; ++j){
                start = System.currentTimeMillis();
                tester.execute(createRandomList(180000));
                end = System.currentTimeMillis();
                System.out.println("180000 element has been sorted in "+ (end-start) + "ms");
                total += (end-start);
            }
            System.out.println("average time "+ (total/repeat) + "ms");

            start = System.currentTimeMillis();
            tester.execute(createSortedList(180000));
            end = System.currentTimeMillis();
            System.out.println("180000 sorted array test " + (end-start) + "ms");
        }
    }
    private static LinkedList<Integer> createRandomList(int size){
        Random rand = new Random();
        LinkedList<Integer> linkedList = new LinkedList<>();
        for(int i=0 ; i<size ; ++i){
            linkedList.add(rand.nextInt(size));
        }
        return linkedList;
    }
    private static LinkedList<Integer> createSortedList(int size){
        LinkedList<Integer> linkedList = new LinkedList<>();
        for(int i=0 ; i<size ; ++i){
            linkedList.add(i);
        }
        return linkedList;
    }
}

interface Tester<E>{
    void execute(E[] arr);
}

interface LinkedTester<E>{
    void execute(LinkedList<E> arr);
}
