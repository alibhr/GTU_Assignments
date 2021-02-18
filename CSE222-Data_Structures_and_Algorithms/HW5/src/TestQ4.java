import DataStructureHW5_Q3.AgeData;
import DataStructureHW5_Q4.*;

public class TestQ4 {
    public static void main(String[] args) {
        //Create an empty heap
        MaxHeap<AgeData> heap = new MaxHeap<AgeData>();

        testAdd(heap);

        testToString(heap);

        testYoungerThan(heap);

        testOlderThan(heap);

        testFind(heap);

        testRemove(heap);
    }

    private static void testAdd(MaxHeap<AgeData> heap) {
        //Add nodes
        //Test 1
        heap.add(new AgeData(10));
        heap.add(new AgeData(20));
        heap.add(new AgeData(30));
        heap.add(new AgeData(40));
        heap.add(new AgeData(50));
        heap.add(new AgeData(60));
        heap.add(new AgeData(70));

        heap.add(new AgeData(10));
        heap.add(new AgeData(20));
        heap.add(new AgeData(30));
        heap.add(new AgeData(40));

        heap.add(new AgeData(10));
        heap.add(new AgeData(40));
        System.out.println("Some element has added to heap.\n");
    }

    private static void testToString(MaxHeap<AgeData> heap) {
        //Test 2
        System.out.println("String representation of the heap : ");
        System.out.println(heap);
    }

    private static void testYoungerThan(MaxHeap<AgeData> heap) {
        //Test 3
        System.out.print("The number of people younger than 15 : ");
        System.out.println(heap.youngerThan(15));

        System.out.print("The number of people younger than 5 : ");
        System.out.println(heap.youngerThan(5));

        System.out.print("The number of people younger than 80 : ");
        System.out.println(heap.youngerThan(80));

        System.out.print("The number of people younger than 40 : ");
        System.out.println(heap.youngerThan(40));

        System.out.print("The number of people younger than 45 : ");
        System.out.println(heap.youngerThan(45));

        System.out.print("\n");
    }

    private static void testOlderThan(MaxHeap<AgeData> heap) {
        //Test 4
        System.out.print("The number of people older than 15 : ");
        System.out.println(heap.olderThan(15));

        System.out.print("The number of people older than 80 : ");
        System.out.println(heap.olderThan(80));

        System.out.print("The number of people older than 5 : ");
        System.out.println(heap.olderThan(5));

        System.out.print("The number of people older than 15 : ");
        System.out.println(heap.olderThan(40));

        System.out.print("The number of people older than 45 : ");
        System.out.println(heap.olderThan(45));

        System.out.print("\n");
    }

    private static void testFind(MaxHeap<AgeData> heap) {
        //Test 5
        System.out.print("find the number of people at 30 : ");
        System.out.println(heap.find(new AgeData(30)).toString());

        System.out.print("find the number of people at 70 : ");
        System.out.println(heap.find(new AgeData(70)).toString());

        try{
            System.out.print("find the number of people at 100 : ");
            System.out.println(heap.find(new AgeData(100)).toString());
        }catch (NullPointerException e){
            System.err.println("NullPointerException has been thrown because find method returned null.");
        }
        System.out.print("\n\n");
    }

    private static void testRemove(MaxHeap<AgeData> heap) {
        //Test 6
        boolean deleted = false;
        deleted = heap.remove(new AgeData(7));
        if(deleted) System.out.println("7 is removed.");
        else        System.out.println("7 is not removed.");

        deleted = heap.remove(new AgeData(50));
        if(deleted) System.out.println("50 is removed.");
        else        System.out.println("50 is not removed.");
        System.out.println("The heap after remove :");
        System.out.print(heap);
        System.out.print("\n");

        for(int i=0 ; i<4 ; ++i){
            deleted = heap.remove(new AgeData(10));
            if(deleted) System.out.println("10 is removed.");
            else        System.out.println("10 is not removed.");
            System.out.println("The heap after remove :");
            System.out.print(heap);
            System.out.print("\n");
        }

        deleted = heap.remove(new AgeData(40));
        if(deleted) System.out.println("40 is removed.");
        else        System.out.println("40 is not removed.");
        System.out.println("The heap after remove :");
        System.out.print(heap);
        System.out.print("\n");

        deleted = heap.remove(new AgeData(35));
        if(deleted) System.out.println("35 is removed.");
        else        System.out.println("35 is not removed.");

        deleted = heap.remove(new AgeData(0));
        if(deleted) System.out.println("0 is removed.");
        else        System.out.println("0 is not removed.");
        System.out.println("The heap after remove :");
        System.out.print(heap);
        System.out.print("\n");
    }
}
