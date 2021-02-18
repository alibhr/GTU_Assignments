package GTU_DataStructure_HW3_Q3;

public class WordLinkedList {

    private Node head;
    private String theWord;
    boolean direction;//if true direction will be horizontal.

    public WordLinkedList(String firstWord){
        theWord = firstWord;
        direction = true;
        if(firstWord.length() != 0 ) {
            head = new Node(firstWord.charAt(0), null, null);
            Node tempRef = head;
            for (int i = 1; i < firstWord.length(); ++i) {
                tempRef.next = new Node(firstWord.charAt(i),null,tempRef);
                tempRef = tempRef.next;
            }
        }

    }

    public int length(){ return theWord.length(); }

    public void addCross(String newWord,int indexOfNewWord,int index){
        this.addCross(new WordLinkedList(newWord),indexOfNewWord,index);
    }

    public void addCross(WordLinkedList newWord,int indexOfNewWord,int index){
        Node tempRef = this.head;
        Node newWordRef = newWord.head;
        newWord.direction = !this.direction;

        for(int i=0 ; i<index ; ++i)
            tempRef = tempRef.next;

        for(int i=0 ; i<indexOfNewWord ; ++i)
            newWordRef = newWordRef.next;

        if(tempRef.getData() != newWordRef.getData()){
            System.err.println("This indexes doesn't have same letters.");
        }

        tempRef.crossPrev = newWordRef.prev;
        if(tempRef.crossPrev != null)
            tempRef.crossPrev.next = tempRef;

        tempRef.crossNext = newWordRef.next;

        if(tempRef.crossNext !=null)
            tempRef.crossNext.prev = tempRef;

    }

    public void removeCross(int index){
        Node tempRef = head;
        for(int i=0 ; i<index ; ++i){
            tempRef = tempRef.next;
        }

        if(tempRef.hasCrossed()){
            tempRef.crossNext = null;
            tempRef.crossPrev = null;
        }
        else{
            System.err.println("There is no crossed word in this index!");
        }
    }

    public void print(){

        Node tempRef = head;
        System.out.print("The Word is : ");
        for(int i=0 ; i<this.length() ; ++i){
            System.out.print(tempRef.getData());
            if(direction)
                tempRef = tempRef.next;
            else{
                if(tempRef.hasCrossed()){
                    tempRef = tempRef.crossNext;
                }
                else {
                    tempRef = tempRef.next;
                }
            }
        }
        System.out.print("\n");

        tempRef = head;
        for(int i=0 ; i<this.length() ; ++i){
            if(tempRef.hasCrossed()){

                System.out.print("index : " + i + " : ");

                if(tempRef.crossPrev != null && direction)
                    tempRef = tempRef.crossPrev;
                else if(tempRef.prev != null){
                    tempRef = tempRef.prev;
                }

                while(tempRef.prev != null){
                    tempRef = tempRef.prev;
                }

                while(tempRef.next != null){
                    if(tempRef.next.hasCrossed() && direction){
                        System.out.print(tempRef.getData());
                        tempRef = tempRef.next;

                    }

                    System.out.print(tempRef.getData());

                    if(tempRef.hasCrossed()) {
                        if (direction && tempRef.crossNext != null){
                            tempRef = tempRef.crossNext;
                        }
                        else if (tempRef.next != null) {
                            tempRef = tempRef.next;
                        } else{
                            break;
                        }
                    }
                    else{
                        tempRef = tempRef.next;
                    }
                }

                System.out.print(tempRef.getData() + "\n");

                while(!tempRef.hasCrossed()){
                    tempRef=tempRef.prev;
                }

            }

            tempRef=tempRef.next;
            if(tempRef == null)
                break;
        }

    }

    private static class Node{
        private char data;
        Node next;
        Node prev;
        Node crossNext;
        Node crossPrev;

        private Node(char newData, Node newNext, Node newPrev){
            data = newData;
            next = newNext;
            prev = newPrev;
            crossNext = null;
            crossPrev = null;
        }

        private char getData() {
            return data;
        }

        boolean hasCrossed(){
            return (crossNext!=null || crossPrev !=null);
        }
    }
}