import DataStructure_HW4_Q2.GTUDeque;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class TestQ2 {
    public static void main(String[] args) {

        //1
        GTUDeque<String> footballers = new GTUDeque<>();
        System.out.println("First initialization of deque : " + footballers);
        System.out.print("\n");

        //2
        testAddFirst(footballers);

        //3
        try{
            testRemoveFirst(footballers);
        }catch (NoSuchElementException e){
            System.err.println("There is NoSuchElementException, because i tried to remove more element than this deque has.(testRemoveFirst)");
            e.printStackTrace();
        }

        System.out.print("\n");
        System.out.println("After removing all elements from this deque : "+ footballers);
        System.out.print("\n");

        //4
        testAddLast(footballers);

        //5
        try{
            testRemoveLast(footballers);
        }catch (NoSuchElementException e){
            System.err.println("There is NoSuchElementException, because i tried to remove more element than this deque has.(testRemoveLast)");
            e.printStackTrace();
        }

        System.out.print("\n");
        System.out.println("After removing all elements from this deque : "+ footballers);
        System.out.print("\n");

        //6
        testOfferFirst(footballers);

        //7
        tesPollFirst(footballers);

        //8
        testOfferLast(footballers);

        //9
        testPollLast(footballers);

        //10
        testAdd(footballers);

        //11
        try{
            testRemove(footballers);
        }catch (NoSuchElementException e){
            System.err.println("There is NoSuchElementException, because i tried to remove more element than this deque has.(testRemove)");
            e.printStackTrace();
        }

        System.out.print("\n");
        System.out.println("After removing all elements from this deque : "+ footballers);
        System.out.print("\n");

        //12
        testPush(footballers);

        //13
        try{
            testPop(footballers);
        }catch (NoSuchElementException e){
            System.err.println("There is NoSuchElementException, because i tried to remove more element than this deque has.(testPop)");
            e.printStackTrace();
        }

        System.out.print("\n");
        System.out.println("After removing all elements from this deque : "+ footballers);
        System.out.print("\n");

        //14
        testOffer(footballers);

        //15
        testPoll(footballers);


        footballers.add("Inan");
        footballers.add("Amrabat");
        footballers.add("Bruma");
        footballers.add("Kaya");
        footballers.add("Inan");
        footballers.add("Ujfalusi");
        footballers.add("Riera");
        footballers.add("Elmander");
        footballers.add("Inan");
        footballers.add("Baros");
        System.out.println("Deque\t\t: " + footballers);
        //16
        System.out.println("getFirst\t: " + footballers.getFirst());
        //17
        System.out.println("getLast\t\t: " + footballers.getLast());
        //18
        System.out.println("peekFirst\t: " + footballers.peekFirst());
        //19
        System.out.println("peekLast\t: " + footballers.peekLast());
        //20
        System.out.println("element\t\t: " + footballers.element());
        //21
        System.out.println("peek\t\t: " + footballers.peek());

        System.out.print("\n\n");

        GTUDeque<Integer> empty = new GTUDeque<>();
        System.out.println("Deque\t\t: " + empty);
        //22
        try{
            System.out.println("getFirst\t: " + empty.getFirst());
        }catch(NoSuchElementException e){
            System.err.println("getFirst method threw an exception because the deque was empty.");
            e.printStackTrace();
        }
        //23
        try{
            System.out.println("getLast\t\t: " + empty.getLast());
        }catch(NoSuchElementException e){
            System.err.println("getLast method threw an exception because the deque was empty.");
            e.printStackTrace();
        }
        //24
        System.out.println("peekFirst\t: " + empty.peekFirst());
        //25
        System.out.println("peekLast\t: " + empty.peekLast());
        //26
        try{
            System.out.println("element\t\t: " + empty.element());
        }catch(NoSuchElementException e){
            System.err.println("element method threw an exception because the deque was empty.");
            e.printStackTrace();
        }
        //27
        System.out.println("peek\t\t: " + empty.peek());


        System.out.println("\n\nDeque: " + footballers);
        //28
        System.out.println("contains(\"Ali\") : " + footballers.contains("Ali"));
        //29
        System.out.println("contains(\"Inan\") : " + footballers.contains("Inan"));
        System.out.println("contains(\"Bahar\") : " + footballers.contains("Bahar"));
        System.out.println("contains(\"Ujfalusi\") : " + footballers.contains("Ujfalusi"));
        System.out.println("contains(\"Bruma\") : " + footballers.contains("Bruma"));

        System.out.println("\n\nDeque: " + footballers);
        //30
        System.out.println("removeFirstOccurrence(\"Inan\") : " + footballers.removeFirstOccurrence("Inan"));
        System.out.println("after removeFirstOccurrence(\"Inan\") : " + footballers);
        //31
        System.out.println("removeFirstOccurrence(\"Ali\") : " + footballers.removeFirstOccurrence("Ali"));
        System.out.println("after removeFirstOccurrence(\"Ali\") : " + footballers);
        System.out.println("removeFirstOccurrence(\"Kaya\") : " + footballers.removeFirstOccurrence("Kaya"));
        System.out.println("after removeFirstOccurrence(\"Kaya\") : " + footballers);

        System.out.println("\n\nDeque: " + footballers);
        //32
        System.out.println("removeLastOccurrence(\"Inan\") : " + footballers.removeLastOccurrence("Inan"));
        System.out.println("after removeLastOccurrence(\"Inan\") : " + footballers);
        //33
        System.out.println("removeLastOccurrence(\"Ali\") : " + footballers.removeLastOccurrence("Ali"));
        System.out.println("after removeLastOccurrence(\"Ali\") : " + footballers);
        System.out.println("removeLastOccurrence(\"Riera\") : " + footballers.removeLastOccurrence("Riera"));
        System.out.println("after removeLastOccurrence(\"Riera\") : " + footballers);

        System.out.println("\n\nDeque: " + footballers);
        //34
        System.out.println("remove(\"Inan\") : " + footballers.removeLastOccurrence("Inan"));
        System.out.println("after remove(\"Inan\") : " + footballers);
        //35
        System.out.println("remove(\"Ali\") : " + footballers.remove("Ali"));
        System.out.println("after remove(\"Ali\") : " + footballers);

        //36
        System.out.println("\n\nDeque: " + footballers);
        for (String footballer : footballers) {
            System.out.println(footballer);
        }
        System.out.println("All elements of the deque has printed with enhanced for loop.");

        //37
        System.out.println("\n\nDeque: " + footballers);
        Iterator<String> iter = footballers.descendingIterator();
        while(iter.hasNext()){
            System.out.println(iter.next());
        }
        System.out.println("All elements of the deque has printed with descending iterator methods(next,hasNext).\n\n");


        System.out.println("\n\n\t**************End of the Test**************\n\n");
    }

    private static void testAddFirst(GTUDeque<String> footballers) {
        footballers.addFirst("Muslera");
        System.out.println("First element has been added by using addFirst method\t: " + footballers);

        footballers.addFirst("Falcao");
        System.out.println("Second element has been added by using addFirst method\t: " + footballers);

        footballers.addFirst("Melo");
        System.out.println("third element has been added by using addFirst method\t: " + footballers);

        footballers.addFirst("Drogba");
        System.out.println("fourth element has been added by using addFirst method\t: " + footballers);

        System.out.println("There is " + footballers.size() + " element inside this deque.\n\n");
    }

    private static void testRemoveFirst(GTUDeque<String> footballers) {
        for(int i=0 ; i<100 ; ++i){
            System.out.println(footballers.removeFirst() + " has been removed (removeFirst)");
            System.out.println("Deque : " + footballers);
        }
    }

    private static void testAddLast(GTUDeque<String> footballers) {
        footballers.addLast("Hazard");
        System.out.println("First element has been added by using addLast method\t: " + footballers);

        footballers.addLast("Ramos");
        System.out.println("Second element has been added by using addLast method\t: " + footballers);

        footballers.addLast("Casemiro");
        System.out.println("Third element has been added by using addLast method\t: " + footballers);

        footballers.addLast("Modric");
        System.out.println("Fourth element has been added by using addLast method\t: " + footballers);

        footballers.addLast("Marcelo");
        System.out.println("Fifth element has been added by using addLast method\t: " + footballers);

        System.out.println("There is " + footballers.size() + " element inside this deque.\n\n");
    }

    private static void testRemoveLast(GTUDeque<String> footballers) {
        for(int i=0 ; i<100 ; ++i){
            System.out.println(footballers.removeLast() + " has been removed (removeLast)");
            System.out.println("Deque : " + footballers);
        }
    }

    private static void testOfferFirst(GTUDeque<String> footballers) {
        footballers.offerFirst("Messi");
        System.out.println("First element has been added by using offerFirst method\t: " + footballers);

        footballers.offerFirst("Suarez");
        System.out.println("Second element has been added by using offerFirst method\t: " + footballers);

        footballers.offerFirst("Griezmann");
        System.out.println("third element has been added by using offerFirst method\t: " + footballers);

        footballers.offerFirst("Dembele");
        System.out.println("fourth element has been added by using offerFirst method\t: " + footballers);

        System.out.println("There is " + footballers.size() + " element inside this deque.\n\n");
    }

    private static void tesPollFirst(GTUDeque<String> footballers) {
        for(int i=0 ; i<10 ; ++i){
            String temp = footballers.pollFirst();
            if(temp == null){
                System.out.println("pollFirst has returned null");
                break;
            }
            System.out.println(temp + " has been removed (pollFirst)");
            System.out.println("Deque : " + footballers);
        }
        System.out.print("\n\n");
    }

    private static void testOfferLast(GTUDeque<String> footballers) {
        footballers.offerLast("Rodallega");
        System.out.println("First element has been added by using offerLast method\t: " + footballers);

        footballers.offerLast("Barrow");
        System.out.println("Second element has been added by using offerLast method\t: " + footballers);

        footballers.offerLast("Recep");
        System.out.println("Third element has been added by using offerLast method\t: " + footballers);

        footballers.offerLast("Stachowiak");
        System.out.println("Fourth element has been added by using offerLast method\t: " + footballers);

        footballers.offerLast("Zeki");
        System.out.println("Fifth element has been added by using offerLast method\t: " + footballers);

        System.out.println("There is " + footballers.size() + " element inside this deque.\n\n");
    }

    private static void testPollLast(GTUDeque<String> footballers) {
        for(int i=0 ; i<10 ; ++i){
            String temp = footballers.pollLast();
            if(temp == null){
                System.out.println("pollLast has returned null");
                break;
            }
            System.out.println(temp + " has been removed (pollLast)");
            System.out.println("Deque : " + footballers);
        }
        System.out.print("\n\n");
    }

    private static void testAdd(GTUDeque<String> footballers) {
        footballers.add("Merih");
        System.out.println("First element has been added by using add method\t: " + footballers);

        footballers.add("Caglar");
        System.out.println("Second element has been added by using add method\t: " + footballers);

        footballers.add("Cengiz");
        System.out.println("Third element has been added by using add method\t: " + footballers);

        footballers.add("Ozan");
        System.out.println("Fourth element has been added by using add method\t: " + footballers);

        footballers.add("Yusuf");
        System.out.println("Fifth element has been added by using add method\t: " + footballers);

        System.out.println("There is " + footballers.size() + " element inside this deque.\n\n");
    }

    private static void testRemove(GTUDeque<String> footballers) {
        for(int i=0 ; i<100 ; ++i){
            System.out.println(footballers.removeFirst() + " has been removed (remove)");
            System.out.println("Deque : " + footballers);
        }
    }

    private static void testPush(GTUDeque<String> footballers) {
        footballers.push("Cenk");
        System.out.println("First element has been added by using push method\t: " + footballers);

        footballers.push("Dorukhan");
        System.out.println("Second element has been added by using push method\t: " + footballers);

        footballers.push("Omer");
        System.out.println("third element has been added by using push method\t: " + footballers);

        footballers.push("Irfan");
        System.out.println("fourth element has been added by using push method\t: " + footballers);

        System.out.println("There is " + footballers.size() + " element inside this deque.\n\n");
    }

    private static void testPop(GTUDeque<String> footballers) {
        for(int i=0 ; i<100 ; ++i){
            System.out.println(footballers.removeLast() + " has been removed (pop)");
            System.out.println("Deque : " + footballers);
        }
    }

    private static void testOffer(GTUDeque<String> footballers) {
        footballers.offer("Rodallega");
        System.out.println("First element has been added by using offer method\t: " + footballers);

        footballers.offer("Barrow");
        System.out.println("Second element has been added by using offer method\t: " + footballers);

        footballers.offer("Recep");
        System.out.println("Third element has been added by using offer method\t: " + footballers);

        footballers.offer("Stachowiak");
        System.out.println("Fourth element has been added by using offer method\t: " + footballers);

        footballers.offer("Zeki");
        System.out.println("Fifth element has been added by using offer method\t: " + footballers);

        System.out.println("There is " + footballers.size() + " element inside this deque.\n\n");
    }

    private static void testPoll(GTUDeque<String> footballers) {
        for(int i=0 ; i<10 ; ++i){
            String temp = footballers.poll();
            if(temp == null){
                System.out.println("poll has returned null");
                break;
            }
            System.out.println(temp + " has been removed (poll)");
            System.out.println("Deque : " + footballers);
        }
        System.out.print("\n\n");
    }
}