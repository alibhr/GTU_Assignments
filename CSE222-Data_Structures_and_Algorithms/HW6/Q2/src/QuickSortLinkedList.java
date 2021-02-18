import java.util.Iterator;
import java.util.LinkedList;
import java.util.ListIterator;

public class QuickSortLinkedList {
    static int c = 0;
    public static void main(String[] args) {
        LinkedList<Integer> linkedList1 = new LinkedList<>();
        linkedList1.add(5);
        linkedList1.add(2);
        linkedList1.add(13);
        linkedList1.add(9);
        linkedList1.add(1);
        linkedList1.add(7);
        linkedList1.add(6);
        linkedList1.add(8);
        linkedList1.add(1);
        linkedList1.add(15);
        linkedList1.add(4);
        linkedList1.add(11);



        quickSortLinkedList(linkedList1);
        System.out.println(linkedList1);

    }

    public static <E extends Comparable<E>> void quickSortLinkedList(LinkedList<E> linkedList){
        quickSortLinkedList(linkedList,0,linkedList.size()-1);
    }

    private static <E extends Comparable<E>> void quickSortLinkedList(LinkedList<E> linkedList, int first, int last){
        if(first < last){
            int pivIndex = partitionLinkedList(linkedList,first,last);

            quickSortLinkedList(linkedList,first,pivIndex-1);

            quickSortLinkedList(linkedList,pivIndex+1,last);
        }
    }

    private static <E extends Comparable<E>> int partitionLinkedList(LinkedList<E> linkedList, int first, int last){
        E pivot = linkedList.get(first);
        if(pivot == null){
            System.out.println("pivot null !!");
            return 0;
        }

        int up = first;
        int down = last;

        do{
            while( (up < last) && linkedList.get(up).compareTo(pivot) <= 0){ ++up; }

            while( linkedList.get(down).compareTo(pivot) > 0 ){ --down; }

            if(up < down){
                E temp = linkedList.get(up);
                linkedList.set(up,linkedList.get(down));
                linkedList.set(down,temp);
            }
        }while(up < down);

        E temp1 = linkedList.get(first);
        linkedList.set(first,linkedList.get(down));
        linkedList.set(down,temp1);

        return down;
    }
}
