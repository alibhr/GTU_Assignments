import java.util.Arrays;

public class HeapSort {
    public static <E extends Comparable<E>> E[] heapSort(E[] arr){

        buildHeap(arr);

        shrinkHeap(arr);

        return arr;
    }

    private static <E extends Comparable<E>> void buildHeap(E[] arr) {
        int child = 0;
        int parent = 0;

        for(int i=0 ; i<arr.length-1 ; ++i){
            child = i+1;
            parent = (child-1)/2;
            while(parent >= 0 && arr[parent].compareTo(arr[child])<0){
                swap(arr,parent,child);
                child = parent;
                parent = (child-1)/2;
            }
        }


        /*
        int i=1;
        int child = 0;
        int parent = 0;

        while(i < arr.length){
            ++i;
            child = i-1;
            parent = (child-1)/2 ;
            while(parent >= 0 && arr[parent].compareTo(arr[child]) < 0){
                swap(arr,parent,child);
                child = parent;
                parent = (child-1)/2 ;
            }
        }
        */
    }

    private static <E extends Comparable<E>> void swap(E[] arr, int index1, int index2) {
        E temp = arr[index1];
        arr[index1]=arr[index2];
        arr[index2] = temp;
    }

    private static <E extends Comparable<E>> void shrinkHeap(E[] arr) {
        for(int i=arr.length-1 ; i>0 ; --i){
            swap(arr,0,i);
            int parent = 0;

            int leftChild  = 1;
            int rightChild = 2;

            while(leftChild < i){

                int maxChild = leftChild;

                if(rightChild < i && arr[rightChild].compareTo(arr[leftChild]) > 0){
                    maxChild = rightChild;
                }

                leftChild = 2 * parent + 1;
                rightChild = leftChild + 1;

                if(arr[parent].compareTo(arr[maxChild]) < 0){
                    swap(arr,parent,maxChild);
                    parent = maxChild;
                }
                else{
                    leftChild = i; // break;
                }
            }
        }

        /*
        int n = arr.length;
        while(n > 0){
            --n;
            swap(arr,0,n);

            int parent = 0;
            while(true){
                int leftChild = 2 * parent + 1;
                if(leftChild >= n){
                    break;
                }
                int rightChild = leftChild + 1;

                int maxChild = leftChild;

                if(rightChild < n && arr[leftChild].compareTo(arr[rightChild]) < 0){
                    maxChild = rightChild;
                }
                if(arr[parent].compareTo(arr[maxChild]) < 0){
                    swap(arr,parent,maxChild);
                    parent = maxChild;
                }
                else{
                    break;
                }
            }
        }
        */
    }
}