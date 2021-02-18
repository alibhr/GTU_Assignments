import GTU_DataStructure_HW3_Q1.LinkedArrayList;
import java.util.ListIterator;

public class TestQ1 {
    public static void main(String[] args) {
        LinkedArrayList<String> names = new LinkedArrayList<>();
        LinkedArrayList<Character> alphabet = new LinkedArrayList<>();

        System.out.println("First initialization : ");
        System.out.print("list of names : ");
        System.out.println(names);
        System.out.print("list of alphabet : ");
        System.out.println(alphabet);
        System.out.print("\n\n");

        testAddMethod(names,alphabet);
        System.out.println("After add some element to list : ");
        System.out.print("list of alphabet : ");
        System.out.println(alphabet);
        System.out.print("list of names : ");
        System.out.println(names);
        System.out.print("\n\n");

        testAddWithIndex(names,alphabet);
        System.out.println("After add some element to list with index : ");
        System.out.print("list of alphabet : ");
        System.out.println(alphabet);
        System.out.print("list of names : ");
        System.out.println(names);
        System.out.print("\n\n");

        testRemove(names,alphabet);
        System.out.println("After remove some element from list : ");
        System.out.print("list of alphabet : ");
        System.out.println(alphabet);
        System.out.print("list of names : ");
        System.out.println(names);
        System.out.print("\n\n");

        testSet(alphabet);
        System.out.println("All character in alphabet list have setted to 'u' ");
        System.out.println("All character in alphabet list have printed by using get() method ");
        testGet(alphabet);
        System.out.print("\n\n");

        testIterator(names,alphabet);

        alphabet.clear();
        names.clear();

        names.add("Ali");
        names.add("Ali");
        names.add("Ali");
        names.add("Ali");


        try{
            alphabet.remove(1);
        }catch (ArrayIndexOutOfBoundsException e){
            e.printStackTrace();
        }

        try{
            names.remove(15);
        }catch (ArrayIndexOutOfBoundsException e){
            e.printStackTrace();
        }

        try{
            ListIterator<String> iter = names.listIterator();
            iter.remove();
        }catch (IllegalStateException e){
            e.printStackTrace();
        }

        try{
            ListIterator<String> iter = names.listIterator();
            iter.set("yenisi");
        }catch (IllegalStateException e){
            e.printStackTrace();
        }

        try{
            names.add(-1,"yenisi");
        }catch (ArrayIndexOutOfBoundsException e){
            e.printStackTrace();
        }

        System.out.println("All exceptions have been handled (They wew just test)");

    }

    private static void testAddMethod(LinkedArrayList<String> names, LinkedArrayList<Character> alphabet) {

        for(char i = 'A' ; i <= 'Z' ; ++i){
            alphabet.add(i);
        }

        names.add("Ali");
        names.add("Bahar");
        names.add("17");
        names.add("1044");
        names.add("066");
        names.add("GTU");
        names.add("Gebze");
        names.add("Denizli");
        names.add("Acipayam");
        names.add("Pamukkale");
        names.add("Horoz");
    }

    private static void testAddWithIndex(LinkedArrayList<String> names, LinkedArrayList<Character> alphabet) {
        alphabet.add(0,'i');
        alphabet.add(alphabet.size()-1,'i');
        if(alphabet.size()>4)
            alphabet.add(4,'i');

        if(alphabet.size()>11)
            alphabet.add(11,'i');

        if(alphabet.size()>9)
            alphabet.add(9,'i');


        names.add(0,"first");
        names.add(names.size(),"last");
        if(names.size()>4)
            names.add(4,"inserted");

        if(names.size()>8)
            names.add(8,"inserted");

        if(names.size()>9)
            names.add(9,"inserted");
    }

    private static void testRemove(LinkedArrayList<String> names, LinkedArrayList<Character> alphabet) {
        alphabet.remove(0);

        if(alphabet.size()>3)
            alphabet.remove(3);

        if(alphabet.size()>7)
            alphabet.remove(7);

        if(alphabet.size()>9)
            alphabet.remove(9);

        if(alphabet.size()>25)
            alphabet.remove(25);


        if(names.size()>9)
            names.remove(9);

        if(names.size()>8) {
            names.remove(8);
        }

        if(names.size()>4) {
            names.remove(4);
        }

        names.remove(0);
        names.remove(names.size()-1);

    }

    private static void testSet(LinkedArrayList<Character> alphabet) {
        for(int i=0 ; i<alphabet.size() ; ++i){
            alphabet.set(i,'u');
        }
    }

    private static void testGet(LinkedArrayList<Character> alphabet) {
        for (Character character : alphabet) {
            System.out.printf("%c ", character);
        }
        System.out.print("\n");
    }

    private static void testIterator(LinkedArrayList<String> names, LinkedArrayList<Character> alphabet) {

        ListIterator<Character> iterAlphabet = alphabet.listIterator();
        while(iterAlphabet.hasNext()){
            iterAlphabet.next();
            iterAlphabet.remove();
        }
        System.out.println("All elements of alphabet list has been removed by using iterator methods(remove,next,hasNext)");
        System.out.print("list of alphabet : ");
        System.out.println(alphabet);
        System.out.print("\n\n");


        System.out.print("list of names : ");
        ListIterator<String> iterNames = names.listIterator();
        while(iterNames.hasNext()){
            System.out.print(iterNames.next() + ' ');
        }
        System.out.println("\nAll elements of names list has been printed by using iterator methods(hasNext,next)\n");


        System.out.print("list of names : ");
        while(iterNames.hasPrevious()){
            System.out.print(iterNames.previous() + ' ');
        }
        System.out.println("\nAll elements of names list has been printed by using iterator methods(hasPrevious,previous)\n\n");


        while(iterNames.hasNext()){
            iterNames.next();
            iterNames.set("setted");
        }
        System.out.println("All elements of names list setted to \"setted\" ");
        System.out.print("list of names : ");
        System.out.println(names);
        System.out.print("\n\n");


        iterAlphabet = alphabet.listIterator();
        for(char i='a' ; i<='z' ; ++i){
            iterAlphabet.add(i);
        }

        System.out.println("Alphabet filled with characters by using iterator add method.");
        System.out.print("list of alphabet : ");
        System.out.println(alphabet);
        System.out.print("\n\n");


        iterAlphabet = alphabet.listIterator(alphabet.size());
        while(iterAlphabet.hasPrevious()){
            System.out.printf("%c ",iterAlphabet.previous());
            iterAlphabet.remove();
        }
        System.out.println("\nAll element of alphabet is removed by using iterator remove method");
        System.out.print("list of alphabet : ");
        System.out.println(alphabet);
        System.out.print("\n\n");


        iterNames = names.listIterator(names.size());
        while(iterNames.hasPrevious()){
            System.out.printf("%s ",iterNames.previous());
            iterNames.remove();
        }
        System.out.println("\nAll element of names is removed by using iterator remove method");
        System.out.print("list of names : ");
        System.out.println(names);
        System.out.print("\n\n");
    }
}