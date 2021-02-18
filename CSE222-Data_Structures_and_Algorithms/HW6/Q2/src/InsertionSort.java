import java.util.Arrays;

public class InsertionSort {
    public static <E extends Comparable<E>> E[] insertionSort(E[] Arr){
        for(int i=1 ; i<Arr.length ; ++i){


            //insertion
            int j;
            E value = Arr[i];
            for(j=i;j>0 && value.compareTo(Arr[j-1]) < 0 ; --j){
                Arr[j]=Arr[j-1];
            }
            Arr[j] = value;

        }
        return Arr;
    }
}