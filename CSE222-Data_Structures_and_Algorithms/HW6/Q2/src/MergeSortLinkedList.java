import java.util.Iterator;
import java.util.LinkedList;
import java.util.Random;


public class MergeSortLinkedList <E>{
    public static <E extends Comparable<E>> void mergeSortLinkedList(LinkedList<E> linkedList) {
        int fullSize = linkedList.size();

        if(fullSize > 1){
            LinkedList<E> leftList  = new LinkedList<>();
            for(int i=0 ; i< (fullSize+1)/2 ; ++i){
                leftList.add(linkedList.poll());
            }

            LinkedList<E> rightList = new LinkedList<>();
            for(int i=0 ; i< fullSize/2 ; ++i){
                rightList.add(linkedList.poll());
            }

            mergeSortLinkedList(leftList);
            mergeSortLinkedList(rightList);

            mergeLinkedList(linkedList,leftList,rightList);
        }
    }
    private static <E extends Comparable<E>> void mergeLinkedList(LinkedList<E> linkedList,LinkedList<E> left,LinkedList<E> right){
        int i = 0;
        int j = 0;

        Iterator<E> leftIter = left.iterator();
        Iterator<E> rightIter = right.iterator();

        while(i < left.size() && j < right.size()){
            if(left.get(i).compareTo(right.get(j)) < 0){
                linkedList.add(leftIter.next());
                ++i;
            }
            else{
                linkedList.add(rightIter.next());
                ++j;
            }
        }

        while (i < left.size()){
            linkedList.add(leftIter.next());
            ++i;
        }
        while (j < right.size()){
            linkedList.add(rightIter.next());
            ++j;
        }
    }
}