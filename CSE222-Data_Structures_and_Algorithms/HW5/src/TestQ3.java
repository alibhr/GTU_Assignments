import DataStructureHW5_Q3.*;

public class TestQ3 {
    public static void main(String[] args) {

        //Create an empty age tree.
        AgeSearchTree<AgeData> ageTree = new AgeSearchTree<AgeData>();
        System.out.println("Empty Tree has created.\n");

        testAdd(ageTree);

        testToString(ageTree);

        testYoungerThan(ageTree);

        testOlderThan(ageTree);

        testFind(ageTree);

        testRemove(ageTree);
    }

    private static void testAdd(AgeSearchTree<AgeData> ageTree) {
        //Add nodes for some ages.
        //Test 1
        ageTree.add(new AgeData(10));
        ageTree.add(new AgeData(20));
        ageTree.add(new AgeData(5));
        ageTree.add(new AgeData(15));
        ageTree.add(new AgeData(10));
        ageTree.add(new AgeData(2));
        ageTree.add(new AgeData(7));
        ageTree.add(new AgeData(30));
        ageTree.add(new AgeData(2));
        ageTree.add(new AgeData(2));
        ageTree.add(new AgeData(30));
        ageTree.add(new AgeData(30));
        ageTree.add(new AgeData(30));
        System.out.println("Some element has added to tree.\n");
    }

    private static void testToString(AgeSearchTree<AgeData> ageTree) {
        //Create a string representing the tree and print it.
        //Test 2
        System.out.println("String representation of the tree : ");
        String treeStr = ageTree.toString();
        System.out.println(treeStr);
    }

    private static void testYoungerThan(AgeSearchTree<AgeData> ageTree) {
        //Test 3
        //Print the number of people younger than 15.
        System.out.print("The number of people younger than 15 : ");
        System.out.println(ageTree.youngerThan(15));

        //Print the number of people younger than 30.
        System.out.print("The number of people younger than 30 : ");
        System.out.println(ageTree.youngerThan(30));

        //Print the number of people younger than 35.
        System.out.print("The number of people younger than 35 : ");
        System.out.println(ageTree.youngerThan(35));

        //Print the number of people younger than 5.
        System.out.print("The number of people younger than 5 : ");
        System.out.println(ageTree.youngerThan(5));

        //Print the number of people younger than 1.
        System.out.print("The number of people younger than 1 : ");
        System.out.println(ageTree.youngerThan(1));
        System.out.print("\n");
    }

    private static void testOlderThan(AgeSearchTree<AgeData> ageTree) {
        //Test 4
        //Print the number of people older than 15.
        System.out.print("The number of people older than 15 : ");
        System.out.println(ageTree.olderThan(15));

        //Print the number of people older than 30.
        System.out.print("The number of people older than 30 : ");
        System.out.println(ageTree.olderThan(29));

        //Print the number of people older than 35.
        System.out.print("The number of people older than 35 : ");
        System.out.println(ageTree.olderThan(35));

        //Print the number of people older than 5.
        System.out.print("The number of people older than 5 : ");
        System.out.println(ageTree.olderThan(5));

        //Print the number of people older than 1.
        System.out.print("The number of people older than 1 : ");
        System.out.println(ageTree.olderThan(1));
        System.out.print("\n");
    }

    private static void testFind(AgeSearchTree<AgeData> ageTree) {
        //Test 5
        //Find the number of people at any age.
        System.out.print("find the number of people at 30 : ");
        System.out.println(ageTree.find(new AgeData(30)).toString());

        //Find the number of people at any age.
        System.out.print("find the number of people at 15 : ");
        System.out.println(ageTree.find(new AgeData(15)).toString());

        //Find the number of people at any age.
        try{
            System.out.print("find the number of people at 0 : ");
            System.out.println(ageTree.find(new AgeData(0)).toString());
        }catch (NullPointerException e){
            System.err.println("NullPointerException has been thrown because find method returned null.");
        }
        System.out.print("\n\n");
    }

    private static void testRemove(AgeSearchTree<AgeData> ageTree) {
        //Test 6
        //Remove some nodes.
        boolean deleted = false;
        deleted = ageTree.remove(new AgeData(7));
        if(deleted) System.out.println("7 is removed.");
        else        System.out.println("7 is not removed.");

        deleted = ageTree.remove(new AgeData(5));
        if(deleted) System.out.println("5 is removed.");
        else        System.out.println("5 is not removed.");

        deleted = ageTree.remove(new AgeData(7));
        if(deleted) System.out.println("7 is removed.");
        else        System.out.println("7 is not removed.");

        deleted = ageTree.remove(new AgeData(20));
        if(deleted) System.out.println("20 is removed.");
        else        System.out.println("20 is not removed.");

        deleted = ageTree.remove(new AgeData(10));
        if(deleted) System.out.println("10 is removed.");
        else        System.out.println("10 is not removed.");

        deleted = ageTree.remove(new AgeData(10));
        if(deleted) System.out.println("10 is removed.");
        else        System.out.println("10 is not removed.");

        deleted = ageTree.remove(new AgeData(30));
        if(deleted) System.out.println("30 is removed.");
        else        System.out.println("30 is not removed.");

        deleted = ageTree.remove(new AgeData(30));
        if(deleted) System.out.println("30 is removed.");
        else        System.out.println("30 is not removed.");

        deleted = ageTree.remove(new AgeData(100));
        if(deleted) System.out.println("100 is removed.");
        else        System.out.println("100 is not removed.");

        deleted = ageTree.remove(new AgeData(0));
        if(deleted) System.out.println("0 is removed.");
        else        System.out.println("0 is not removed.");

        System.out.print("\n");

        System.out.println("The last situation of the tree : ");
        String treeStr = ageTree.toString();
        System.out.println(treeStr);
    }
}