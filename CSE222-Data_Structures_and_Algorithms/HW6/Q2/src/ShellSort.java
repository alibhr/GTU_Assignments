//Better insertion sort
public class ShellSort {

    public static <E extends Comparable<E>> E[] shellSort(E[] Arr){
        int gap = Arr.length/2;
        while(gap > 0){
            for(int i=gap ; i<Arr.length ; ++i){

                int j;
                E value = Arr[i];
                for(j=i ; j>=gap && value.compareTo(Arr[j-gap])<0 ; j-=gap){
                    Arr[j] = Arr[j-gap];
                }
                Arr[j] = value;

            }
            if(gap == 2)
                gap = 1;
            else
                gap =(int)(gap / 2);
        }

        return Arr;
    }
}