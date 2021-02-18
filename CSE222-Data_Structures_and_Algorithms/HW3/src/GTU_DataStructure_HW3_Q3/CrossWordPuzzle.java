package GTU_DataStructure_HW3_Q3;

import java.util.ArrayList;

public class CrossWordPuzzle {
    private ArrayList<WordLinkedList> words;

    public CrossWordPuzzle(){
        words = new ArrayList<>();
    }

    public void addWord(WordLinkedList newWord){
        words.add(newWord);
    }

    public void addWord(String newWord,int toWhichWord,int fromIndex,int toIndex){
        this.addWord(new WordLinkedList(newWord),toWhichWord,fromIndex,toIndex);
    }

    public void addWord(WordLinkedList newWord,int toWhichWord,int fromIndex,int toIndex){
        words.get(toWhichWord).addCross(newWord,fromIndex,toIndex);
        words.add(newWord);
    }

    public void removeWord(int index){
        words.remove(index);
    }

    public void print(){
        for (WordLinkedList word : words) {
            word.print();
            System.out.print("\n");
        }
    }
}