import DataStructureHW6_Q3.LibraryAutomationSystem;

public class TestQ3 {
    public static void main(String[] args) {
        //Test-1
        LibraryAutomationSystem myAutomation = new LibraryAutomationSystem();

        if(myAutomation.loginToSystemAsAdmin("171044066")){
            System.out.println("login success");
        }

        addBooks(myAutomation);

        testSearch(myAutomation);

        testDelete(myAutomation);
    }

    private static void addBooks(LibraryAutomationSystem myAutomation){
        //Test-2
        myAutomation.addBook("AAA","A_Book1","c0s0.1001");
        myAutomation.addBook("BBB","B_Book1","c1s1.1001");
        myAutomation.addBook("CCC","C_Book1","c2s2.1001");
        myAutomation.addBook("DDD","D_Book1","c3s3.1001");

        //Test-3
        myAutomation.addBook("AAA","A_Book2","c0s0.2001");
        myAutomation.addBook("AAA","A_Book3","c0s0.3001");
        myAutomation.addBook("AAA","A_Book4","c0s0.4001");
        myAutomation.addBook("CCC","C_Book2","c2s2.2001");
        myAutomation.addBook("CCC","C_Book3","c2s2.3001");

        //Test-4
        myAutomation.addBook("AAA","A_Book2","c0s0.2002");
        myAutomation.addBook("AAA","A_Book2","c0s0.2003");
        myAutomation.addBook("AAA","A_Book2","c0s0.2004");
        myAutomation.addBook("DDD","D_Book1","c3s3.1002");
        myAutomation.addBook("DDD","D_Book1","c3s3.1003");
    }

    private static void testSearch(LibraryAutomationSystem myAutomation){
        //test-5
        System.out.println("\nauthor \"AAA\" has this books :");
        myAutomation.searchByAuthorName("AAA");

        System.out.println("\nauthor \"BBB\"  has this books :");
        myAutomation.searchByAuthorName("BBB");

        System.out.println("\nauthor \"CCC\"  has this books :");
        myAutomation.searchByAuthorName("CCC");

        System.out.println("\nauthor \"DDD\"  has this books :");
        myAutomation.searchByAuthorName("DDD");

        System.out.println("\nauthor \"EEE\"  has this books :");
        myAutomation.searchByAuthorName("EEE");


        //Test-6
        System.out.println("\nlocations of \"A_Book2\"");
        myAutomation.displayTheLocations("AAA","A_Book2");

        System.out.println("\nlocations of \"D_Book1\"");
        myAutomation.displayTheLocations("DDD","D_Book1");

        System.out.println("\nlocations of \"C_Book1\"");
        myAutomation.displayTheLocations("CCC","C_Book1");

        System.out.println("\nlocations of \"B_Book1\"");
        myAutomation.displayTheLocations("BBB","B_Book1");


        //Test-7
        System.out.println("\nSome information about \"A_Book2\"");
        myAutomation.searchByBookTitle("A_Book2");

        System.out.println("\nSome information about \"D_Book1\"");
        myAutomation.searchByBookTitle("D_Book1");

        System.out.println("\nSome information about \"C_Book1\"");
        myAutomation.searchByBookTitle("C_Book1");

        System.out.println("\nSome information about \"B_Book1\"");
        myAutomation.searchByBookTitle("B_Book1");
    }

    private static void testDelete(LibraryAutomationSystem myAutomation){
        //Test-8
        System.out.println("\nlocations of \"A_Book2\" (before deletion)");
        myAutomation.displayTheLocations("AAA","A_Book2");

        myAutomation.deleteByLocation("c0s0.2002");
        myAutomation.deleteByLocation("c0s0.2003");
        myAutomation.deleteByLocation("c0s0.2004");

        System.out.println("\nlocations of \"A_Book2\" (after deletion)");
        myAutomation.displayTheLocations("AAA","A_Book2");

        //Test-9
        System.out.println("\nSome information about \"D_Book1\" (before deletion)");
        myAutomation.searchByBookTitle("D_Book1");

        myAutomation.deleteByTitle("D_Book1");

        System.out.println("\nSome information about \"D_Book1\" (after deletion)");
        myAutomation.searchByBookTitle("D_Book1");

        //Test-10
        System.out.println("\nauthor \"AAA\" has this books : (before deletion)");
        myAutomation.searchByAuthorName("AAA");

        myAutomation.deleteByAuthor("AAA");

        System.out.println("\nauthor \"AAA\" has this books : (after deletion)");
        myAutomation.searchByAuthorName("AAA");

    }
}