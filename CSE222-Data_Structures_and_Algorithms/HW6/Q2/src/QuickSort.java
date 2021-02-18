import java.util.Arrays;
import java.util.Random;

public class QuickSort {

    public static <E extends Comparable<E>> E[] quickSort(E[] arr){

        quickSort(arr,0,arr.length-1);

        return arr;
    }

    private static <E extends Comparable<E>> void quickSort(E[] arr,int first,int last){
        if(first < last){
            int pivIndex = partition(arr,first,last);

            quickSort(arr,first,pivIndex-1);

            quickSort(arr,pivIndex+1,last);
        }
    }

    /*
    private static <E extends Comparable<E>> int partition(E[] arr,int first,int last){
        E pivot = arr[first];

        int up = first;
        int down = last;

        do{

            while( (up < last) && arr[up].compareTo(pivot) <= 0){ ++up; }

            while( arr[down].compareTo(pivot) > 0 ){ --down; }

            if(up < down){
                swap(arr,up,down);
            }

        }while(up < down);

        swap(arr,first,down);

        return down;
    }
    */

    private static <E extends Comparable<E>> int partition(E[] arr,int first,int last){
        bubbleSort3(arr,first,last);
        swap(arr,first,(first+last)/2);

        E pivot = arr[first];

        int up = first;
        int down = last;

        do{

            while( (up < last) && arr[up].compareTo(pivot) <= 0){ ++up; }

            while( arr[down].compareTo(pivot) > 0 ){ --down; }

            if(up < down){
                swap(arr,up,down);
            }

        }while(up < down);

        swap(arr,first,down);

        return down;
    }

    private static <E extends Comparable<E>> void swap(E[] arr, int index1, int index2) {
        E temp = arr[index1];
        arr[index1]=arr[index2];
        arr[index2] = temp;
    }

    private static <E extends Comparable<E>> void bubbleSort3(E[] arr, int first, int last) {
        int middle = (first + last) / 2 ;

        if(arr[first].compareTo(arr[middle]) > 0){
            swap(arr,first,middle);
        }

        if(arr[middle].compareTo(arr[last]) > 0){
            swap(arr,middle,last);
        }

        if(arr[first].compareTo(arr[middle]) > 0){
            swap(arr,first,middle);
        }
    }
}