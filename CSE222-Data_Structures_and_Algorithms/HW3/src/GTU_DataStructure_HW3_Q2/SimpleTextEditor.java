package GTU_DataStructure_HW3_Q2;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;
import java.io.File;

/**
 * provides the some of the edit functionality of a text editor.
 */
public class SimpleTextEditor {
    /**
     * keeps the all data as Characters.
     */
    private List<Character> text;

    /**
     * keeps the file name.
     */
    private String fileName;

    /**
     * keeps the file.
     */
    private File file;

    /**
     * creates a new SimpleText editor which use ArrayList.
     * @param theFileName Name of the file
     */
    public SimpleTextEditor(String theFileName){
        fileName = theFileName;
        file = new File(fileName);
        text = new ArrayList<>();
    }

    /**
     * creates a new SimpleText editor which use LinkedList.
     * @param theFileName Name of the file.
     * @param ignoreMe indicates to LinkedList.
     */
    public SimpleTextEditor(String theFileName,boolean ignoreMe){
        fileName = theFileName;
        file = new File(fileName);
        text = new LinkedList<>();
    }

    /**
     * reads a text file and construct the text.
     * @throws IOException Signals that an I/O exception of some sort has occurred.
     */
    public void read() throws IOException {

        FileReader fr = new FileReader(fileName);
        text.clear();
        int ch;
        while((ch = fr.read()) != -1){
            text.add((char)ch);
        }

        fr.close();

    }

    /**
     * reads a text file and construct the text by using iterator.
     * @throws IOException Signals that an I/O exception of some sort has occurred.
     */
    public void readWithIter() throws IOException {

        FileReader fr = new FileReader(fileName);
        text.clear();
        ListIterator<Character> iter = text.listIterator();
        int ch;
        while((ch = fr.read()) != -1){
            iter.add((char)ch);
        }

        fr.close();
    }

    /**
     * adds one or more characters (given as a string) at the specified position.
     * @param index index at which the specified element is to be inserted.
     * @param toInsert String to be inserted.
     * @throws IOException Signals that an I/O exception of some sort has occurred.
     */
    public void add(int index,String toInsert) throws IOException {

        FileWriter fw = new FileWriter(file);

        for(int i=0 ; i<toInsert.length() ; ++i)
            text.add(index+i,toInsert.charAt(i));

        for (Character character : text) {
            fw.write(character);
        }
        fw.close();

    }

    /**
     * adds one or more characters (given as a string) at the specified position by using iterator.
     * @param index index at which the specified element is to be inserted.
     * @param toInsert Signals that an I/O exception of some sort has occurred.
     * @throws IOException Signals that an I/O exception of some sort has occurred.
     */
    public void addWithIter(int index,String toInsert) throws IOException {

        FileWriter fw = new FileWriter(file);

        ListIterator<Character> iter = text.listIterator(index);

        for(int i=0 ; i<toInsert.length() ; ++i)
            iter.add(toInsert.charAt(i));

        for (Character character : text) {
            fw.write(character);
        }
        fw.close();
    }

    /**
     * returns the start index of the first occurrence of the searched group of characters.
     * @param toSearch group of characters to search in text.
     * @return the start index of the first occurrence of the searched group of characters.
     */
    public int find(String toSearch){

        boolean found;

        for(int i=0 ; i<text.size() ; ++i){

            found = true;
            for(int j=0 ; j<toSearch.length() ; ++j)
                if(toSearch.charAt(j) != text.get(i+j))
                    found = false;

            if(found)
                return i;

        }
        return -1;
    }

    /**
     * returns the start index of the first occurrence of the searched group of characters by using iterator.
     * @param toSearch group of characters to search in text.
     * @return the start index of the first occurrence of the searched group of characters.
     */
    public int findWithIter(String toSearch){
        ListIterator<Character> iter = text.listIterator();
        boolean found;


        for(int i=0;iter.hasNext();++i){

            found = true;

            int j;
            for(j=0 ; j<toSearch.length() ; ++j){
                if(!iter.hasNext()){
                    break;
                }

                if(toSearch.charAt(j) != iter.next())
                    found = false;
            }
            if(j != toSearch.length()){
                return -1;
            }

            if(found)
                return i;

            for(j=0 ; j<toSearch.length()-1 ; ++j)
                iter.previous();
        }

        return -1;
    }

    /**
     * replaces all occurrences of a character with another character.
     * @param aLetter the character which will be removed.
     * @param newLetter the character which is replaced with it.
     * @throws IOException Signals that an I/O exception of some sort has occurred.
     */
    public void replace(char aLetter,char newLetter) throws IOException {

        FileWriter fw = new FileWriter(file);

        for(int i=0 ; i<text.size() ; ++i){
            if(aLetter == text.get(i)){
                text.set(i,newLetter);
            }
        }

        for (Character character : text) {
            fw.write(character);
        }
        fw.close();

    }

    /**
     * replaces all occurrences of a character with another character by using iterator.
     * @param aLetter the character which will be removed.
     * @param newLetter the character which is replaced with it.
     * @throws IOException Signals that an I/O exception of some sort has occurred.
     */
    public void replaceWithIter(char aLetter,char newLetter) throws IOException {
        ListIterator<Character> iter = text.listIterator();

        FileWriter fw = new FileWriter(file);

        while(iter.hasNext()){
            if(aLetter == iter.next()){
                iter.set(newLetter);
            }
        }

        for (Character character : text) {
            fw.write(character);
        }
        fw.close();
    }

    /**
     * deletes the all characters in the text.
     * @throws IOException Signals that an I/O exception of some sort has occurred.
     */
    public void deleteAllChar() throws IOException {
        text.clear();

        FileWriter fw = new FileWriter(file);
        fw.write("");
        fw.close();
    }

    /**
     * returns the whole text as a string.
     * @return the whole text as a string.
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (Character character : text) {
            sb.append(character);
        }
        return sb.toString();
    }
}