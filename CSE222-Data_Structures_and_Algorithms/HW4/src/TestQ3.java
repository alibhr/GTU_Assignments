import java.util.Arrays;
import java.util.EmptyStackException;

import static DataStructure_HW4_Q3.Q3RecursiveFunctions.*;

public class TestQ3 {
    public static void main(String[] args){
        testQ3_1();
        System.out.print("\n");

        testQ3_2();
        System.out.print("\n");

        testQ3_3();
        System.out.print("\n");

        testQ3_4();
        System.out.print("\n");

        testQ3_5();
        System.out.print("\n");

        testQ3_6();
        System.out.print("\n");
    }

    private static void testQ3_1(){
        System.out.println("Test Q3.1.1");
        testQ3_1("This function writes the sentence in reverse");

        System.out.println("Test Q3.1.2");
        testQ3_1("A computer is like air conditioning it becomes useless when you open windows (LinusTorvalds)");

        System.out.println("Test Q3.1.3");
        testQ3_1("oneWord");

        System.out.println("Test Q3.1.4(empty string)");
        testQ3_1("");
    }
    private static void testQ3_1(String sentence){
        System.out.println("Original string was : " + sentence);
        System.out.println("After reversing : " + reverseSentence(sentence));
        System.out.print("\n");
    }

    private static void testQ3_2(){
        System.out.println("Test Q3.2.1");
        testQ3_2("whiteleaf");

        System.out.println("Test Q3.2.2");
        testQ3_2("tasteful");

        System.out.println("Test Q3.2.3");
        testQ3_2("unfriendly");

        System.out.println("Test Q3.2.4");
        testQ3_2("waffles");

        System.out.println("Test Q3.2.5(Empty String)");
        testQ3_2("");

        System.out.println("Test Q3.2.6");
        testQ3_2("eeeeellllllll");

        System.out.println("Test Q3.2.7");
        testQ3_2("fffeee");

        System.out.println("Test Q3.2.8");
        testQ3_2("full");
    }
    private static void testQ3_2(String theWord){
        System.out.println("The word : " + theWord);
        System.out.println("isElfish : "+isElfish(theWord,"elf"));
        System.out.print("\n");
    }

    private static void testQ3_3(){
        Integer[] intArr = {100,50,25,12,6,3,1,0,-1,-3,-6,-12,-25};
        String[] strArr = {"zzz","zyz","zyy","aaa"};

        System.out.println("Test Q3.3.1");
        System.out.println("(Integer)The array was : " + Arrays.toString(intArr));
        selectionSort(intArr,0);
        System.out.println("(Integer)After sort method : " + Arrays.toString(intArr));
        System.out.print("\n");

        System.out.println("Test Q3.3.2");
        System.out.println("(String)The array was : " + Arrays.toString(strArr));
        selectionSort(strArr,0);
        System.out.println("(String)After sort method : " + Arrays.toString(strArr));
        System.out.print("\n");

        Integer[] intArr1 = {10,-2,21,34,-6,0,12,12,1,-1,100,-100};
        String[] strArr1 = {"Ali","Bahar","GTU","171044066"};

        System.out.println("Test Q3.3.3");
        System.out.println("(Integer)The array was : " + Arrays.toString(intArr1));
        selectionSort(intArr,0);
        System.out.println("(Integer)After sort method : " + Arrays.toString(intArr1));
        System.out.print("\n");

        System.out.println("Test Q3.3.4");
        System.out.println("(String)The array was : " + Arrays.toString(strArr1));
        selectionSort(strArr,0);
        System.out.println("(String)After sort method : " + Arrays.toString(strArr1));
        System.out.print("\n");
    }

    private static void testQ3_4(){
        System.out.println("Test Q3.4.1");
        testQ3_4("+ 10 + / - 20 * 4 2 6 - 11 / 14 7");

        System.out.println("Test Q3.4.2");
        testQ3_4("- - 2000 55 40");

        System.out.println("Test Q3.4.3 (This example throws an exception)");
        testQ3_4("- - + 2000 55 40");

        System.out.println("Test Q3.4.4 (Empty String)(This example throws an exception)");
        testQ3_4(" ");
    }
    private static void testQ3_4(String prefix) {
        System.out.println("The prefix expression was : " + prefix);
        try {
            System.out.println("Answer : " + prefixEvaluate(prefix));

        }catch (EmptyStackException e){
            System.err.println("There is a Syntax ERROR of prefix expression !");
            //e.printStackTrace();
        }
        System.out.print("\n");
    }

    private static void testQ3_5(){
        System.out.println("Test Q3.5.1");
        testQ3_5("10 20 4 2 * - 6 / + 11 + 14 7 / -");

        System.out.println("Test Q3.5.2");
        testQ3_5("2000 55 - 40 -");

        System.out.println("Test Q3.5.3 (This example throws an exception)");
        testQ3_5("2000 55 - 40 - +");

        System.out.println("Test Q3.5.4 (Empty String)(This example throws an exception)");
        testQ3_5(" ");
    }
    private static void testQ3_5(String postfix){
        System.out.println("The postfix expression was : " + postfix);
        try {
            System.out.println("Answer : " + postfixEvaluate(postfix));

        }catch (EmptyStackException e){
            System.err.println("There is a Syntax ERROR of postfix expression !");
            //e.printStackTrace();
        }
        System.out.print("\n");
    }

    private static void testQ3_6(){
        int[][] arr1 = new int[5][4];
        for(int i=0;i<5 ; ++i)
            for(int j=0 ; j<4 ; ++j)
                arr1[i][j] = i*4 + j + 1;

        System.out.println("Test Q3.6.1");
        testQ3_6(arr1,5,4);

        int[][] arr2 = {{1},{2},{3},{4},{5},{6},{7}};
        System.out.println("Test Q3.6.2(There is just one column)");
        testQ3_6(arr2,7,1);

        int[][] arr3 = {{1,2,3,4,5}};
        System.out.println("Test Q3.6.3(There is just one row)");
        testQ3_6(arr3,1,5);

        int[][] arr4 = new int[0][0];
        System.out.println("Test Q3.6.4(Empty Array)");
        testQ3_6(arr4,0,0);

        int[][] arr5 = {{1,2,3,4,5},{12,13,14,15,6},{11,10,9,8,7}};
        System.out.println("Test Q3.6.5");
        testQ3_6(arr5,3,5);
    }
    private static void testQ3_6(int[][] arr,int row,int column){
        System.out.println("The actual Array : ");
        for(int i=0;i<row ; ++i){
            for(int j=0 ; j<column ; ++j)
                System.out.print(arr[i][j] + "\t");
            System.out.print("\n");
        }
        System.out.println("Output : ");
        printArray(arr,row,column);
        System.out.print("\n\n");
    }
}
