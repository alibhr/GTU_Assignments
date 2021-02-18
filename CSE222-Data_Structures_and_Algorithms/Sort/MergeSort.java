import java.util.Arrays;

public class MergeSort {

    public static <E extends Comparable<E>> E[] mergeSort(E[] arr){
        mergeSort(arr,0,arr.length-1);
        return arr;
    }

    private static <E extends Comparable<E>> void mergeSort(E[] arr, int left, int right){
        if(left < right){
            int mid = (left + right)/2;

            mergeSort(arr,left,mid);
            mergeSort(arr,mid+1,right);

            merge(arr,left,mid,right);
        }
    }

    @SuppressWarnings("unchecked")
    private static <E extends Comparable<E>> void merge(E[] arr, int left, int mid, int right) {

        Object[] sortedArray = new Object[right-left+1];

        int i=left;//Index into the left input sequence.
        int j=mid+1;//Index into the right input sequence.
        int k=0;//into the output sequence.

        while(i <= mid && j <= right){
            if(arr[i].compareTo(arr[j]) < 0){
                sortedArray[k++] = arr[i++];
            }else{
                sortedArray[k++] = arr[j++];
            }
        }

        while(i <= mid){
            sortedArray[k++] = arr[i++];
        }

        while(j <= right){
            sortedArray[k++] = arr[j++];
        }
        j=0;
        for(i=left ; i<=right ; ++i){
            arr[i] = (E) sortedArray[j++];
        }
    }
}