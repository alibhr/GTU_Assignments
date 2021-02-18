package DataStructure_HW4_Q3;

import java.util.Stack;

/**
 * A class which has static recursive methods.
 * @author Ali
 * @author 171044066
 */
public class Q3RecursiveFunctions {

    /**
     * Returns the reversed form of the given sentence;
     * @param sentence the sentence which will be reversed.
     * @return the reversed form of the given sentence;
     */
    public static String reverseSentence(String sentence){
        return reverseSentence(sentence,0);
    }
    private static String reverseSentence(String sentence,int index){
        StringBuilder sb = new StringBuilder();
        if(index == sentence.length()){
            return "";
        }

        if(sentence.charAt(index) == ' '){
            return "";
        }

        sb.append(sentence.charAt(index)).append(reverseSentence(sentence,index+1));

        if(sb.toString().length() < sentence.length() && index == 0){
            sb.insert(0,reverseSentence(sentence.substring(sb.toString().length()+1),0) + " ");
        }

        return sb.toString();
    }

    /**
     * Determines whether a word is elfish or not.
     * @param word the word which will be considered.
     * @param letters the letters to search inside the word.
     * @return true if the word has this letters in any order : e,l,f
     */
    public static boolean isElfish(String word,String letters){
        if(letters.length() == 0) {
            return true;
        }

        if(word.length() == 0){
            return false;
        }

        int index;
        if((index=lookFor(word,letters.charAt(0))) != -1){
            return isElfish(word.substring(0,index) + word.substring(index+1,word.length()),letters.substring(1));
        }
        else{
            return false;
        }
    }
    private static int lookFor(String word, char letter) {
        if(word.length() == 0){
            return  -1;
        }

        if(word.charAt(0) == letter){
            return 0;
        }

        int index=lookFor(word.substring(1),letter);
        if(index != -1)
            return 1+index;
        else
            return -1;
    }

    /**
     * Sorts an array of elements using selection sort algorithm.
     * @param arr the array which will be sorted.
     * @param index This array elements which is after this index will be sorted.
     * @param <E> type of elements.
     */
    public static <E extends Comparable <E>> void selectionSort(E[] arr,int index){
        if(index == arr.length)
            return;

        int smallestIndex = findSmallest(arr,index);

        //swap
        E temp = arr[index];
        arr[index] = arr[smallestIndex];
        arr[smallestIndex] = temp;

        selectionSort(arr,index+1);
    }
    private static <E extends Comparable <E>> int findSmallest(E[] arr,int index){
        if(index == arr.length){
            return index-1;
        }

        int smallest = findSmallest(arr,index+1);

        if(arr[index].compareTo(arr[smallest]) > 0){
            return smallest;
        }
        else{
            return index;
        }
    }

    /**
     * Evaluating a Prefix expression
     * @param prefix prefix expression.
     * @return the result of the expression
     */
    public static int prefixEvaluate(String prefix){
        String[] tokens = prefix.split("\\s+");
        return prefixEvaluate(tokens,tokens.length-1,new Stack<>());
    }
    private static int prefixEvaluate(String[] token,int index, Stack<Integer> stack){
        if(index < 0){
            return stack.pop();
        }
        if(!isOperator(token[index])){
            stack.push(Integer.parseInt(token[index]));
        }
        else{
            stack.push(evaluate(token[index],stack.pop(),stack.pop()));
        }
        return prefixEvaluate(token,index-1,stack);
    }

    /**
     * Evaluating a Postfix expression.
     * @param postfix Postfix expression.
     * @return the result of the expression
     */
    public static int postfixEvaluate(String postfix){
        String[] tokens = postfix.split("\\s+");
        return postfixEvaluate(tokens,0,new Stack<>());
    }
    private static int postfixEvaluate(String[] token,int index, Stack<Integer> stack){
        if(index == token.length){
            return stack.pop();
        }
        if(!isOperator(token[index])){
            stack.push(Integer.parseInt(token[index]));
        }
        else{
            int first = stack.pop();
            int second = stack.pop();
            stack.push(evaluate(token[index],second,first));
        }
        return postfixEvaluate(token,index+1,stack);
    }
    private static int evaluate(String operator,int operand1,int operand2){
        //System.out.println(operator +" "+ operand1+" "+operand2);
        switch (operator){
            case "+":
                return operand1 + operand2;
            case "-":
                return operand1 - operand2;
            case "*":
                return operand1 * operand2;
            case "/" :
                return operand1 / operand2;
            default:
                return 0;
        }
    }
    private static boolean isOperator(String o){
        switch (o){
            case "+":
            case "-":
            case "*":
            case "/":
                return true;
            default:
                return false;
        }
    }

    /**
     * Prints the given array in spiral form.
     * @param arr The array.
     * @param row row number of array.
     * @param column column number of the array.
     */
    public static void printArray(int[][] arr,int row,int column){
        printArray(arr,0,0,row,column,0);
    }
    private static void printArray(int[][] arr,int i,int j,int row,int column,int depth){
        if(row<0 || column<0)
            return;

        if(i==depth && j<column+depth && column>0){
            System.out.print(arr[i][j] + " ");
            printArray(arr,i,j+1,row,column,depth);
        }
        else if(j==column+depth && i<row-1+depth && column>0){
            System.out.print(arr[i+1][j-1]+ " ");
            printArray(arr,i+1,j,row,column,depth);
        }
        else if(i==row-1+depth && j-1>depth && row>1){
            System.out.print(arr[i][j-2] + " ");
            printArray(arr,i,j-1,row,column,depth);
        }
        else if(j-1==depth && i>depth && row>1 && column>1){
            if(i==depth+1){
                return;
            }
            System.out.print(arr[i-1][j-1] + " ");
            printArray(arr,i-1,j,row,column,depth);
        }

        if(i==depth && j==depth){
            printArray(arr,i+1,depth+1,row-2,column-2,depth+1);
        }
    }
}