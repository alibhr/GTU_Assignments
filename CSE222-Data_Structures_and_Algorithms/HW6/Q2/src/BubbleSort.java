import java.util.Arrays;

public class BubbleSort {
    public static <E extends Comparable<E>> E[] bubbleSort(E[] Arr){
        boolean stop = true;
        for(int i=0 ; i<Arr.length ; ++i){
            for(int j=0 ; j<Arr.length-i-1 ; ++j){
                if(Arr[j].compareTo(Arr[j+1]) > 0){
                    E temp = Arr[j];
                    Arr[j] = Arr[j+1];
                    Arr[j+1] = temp;
                    stop = false;
                }
            }
            if(stop) i = Arr.length;
            stop = true;
        }

        return Arr;
    }
}
