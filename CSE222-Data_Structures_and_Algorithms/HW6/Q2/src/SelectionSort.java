import java.util.Arrays;

public class SelectionSort {
    public static <E extends Comparable<E>> E[] selectionSort(E[] Arr){
        for(int i=0 ; i<Arr.length ; ++i){
            E temp = Arr[i];
            int smallest = findSmallest(Arr,i);
            Arr[i] = Arr[smallest];
            Arr[smallest] = temp;
        }

        return Arr;
    }
    private static <E extends Comparable<E>> int findSmallest(E[] Arr,int index){
        int smallest = index;
        for(int i=index ; i<Arr.length ;++i){
            if(Arr[smallest].compareTo(Arr[i]) > 0){
                smallest = i;
            }
        }
        return smallest;
    }
}
