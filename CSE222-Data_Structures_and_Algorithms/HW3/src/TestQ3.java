import GTU_DataStructure_HW3_Q3.CrossWordPuzzle;
import GTU_DataStructure_HW3_Q3.WordLinkedList;

public class TestQ3 {
    public static void main(String[] args) {
        WordLinkedList firstWord = new WordLinkedList("PUZZLES");
        WordLinkedList second = new WordLinkedList("FUN");
        WordLinkedList third = new WordLinkedList("CROSSWORD");

        CrossWordPuzzle puzzle = new CrossWordPuzzle();

        puzzle.addWord(firstWord);
        puzzle.addWord(second,0,1,1);
        puzzle.addWord(third,0,3,6);
        puzzle.addWord("PLAYP",0,4,0);

        puzzle.removeWord(3);

        puzzle.print();

    }
}
