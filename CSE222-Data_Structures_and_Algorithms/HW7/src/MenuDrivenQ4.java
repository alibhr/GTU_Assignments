import DataStructureHW7_Q3.BinarySearchTree;
import DataStructureHW7_Q4.Software;
import DataStructureHW7_Q4.SoftwareStore;

import java.util.Scanner;

public class MenuDrivenQ4 {

    private static boolean quit = false;
    private static Scanner in = new Scanner(System.in);
    private static SoftwareStore myStore = new SoftwareStore(new BinarySearchTree<Software>());

    public static void main(String[] args) {

        myStore.addSoftware(new Software("AdobePhotoshop6.0",1,100));
        myStore.addSoftware(new Software("AdobePhotoshop6.2",1,101));
        myStore.addSoftware(new Software("Norton4.5",1,102));
        myStore.addSoftware(new Software("Norton5.5",1,103));
        myStore.addSoftware(new Software("AdobeFlash3.3",1,104));
        myStore.addSoftware(new Software("AdobeFlash4.0",1,105));

        while(!quit){
            System.out.println("Software Store System" +
                    "\n1) Login to system as admin"+
                    "\n2) Search Book by name"+
                    "\n0) Quit\n");
            String input = in.next();
            switch (input){
                case "1":
                    System.out.print("Password : ");
                    input = in.next();
                    if(myStore.loginToSystem(input)){
                        adminInterface();
                    }
                    else{
                        System.out.println("login fail");
                    }
                    break;
                case "2" :
                    System.out.println("Enter the name of the software");
                    input = in.next();
                    System.out.println(myStore.softwareSearch(input) + "\n");
                    break;
                case "0":
                    quit = true;
                    break;
            }
        }
    }

    private static void adminInterface(){
        System.out.println("Login success "+
                "\nAdmin Interface"+
                "\n1) add software"+
                "\n2) delete software"+
                "\n3) update software");
        String input = in.next();
        switch (input){
            case "1":
                System.out.println("Enter the name of the new software to be added");
                String softwareName = in.next();

                System.out.println("Enter the price of the new software to be added");
                int softwarePrice = in.nextInt();

                myStore.addSoftware(new Software(softwareName,1,softwarePrice));

                break;
            case "2":
                System.out.println("Enter the name of the new software to be removed");
                String name = in.next();
                myStore.removeSoftware(name);
                break;
            case "3":
                System.out.println("Enter the name of the software to be updated");
                name = in.next();

                System.out.println("Enter the new name");
                softwareName = in.next();

                System.out.println("Enter the new price");
                softwarePrice = in.nextInt();

                myStore.updateSoftware(name,new Software(softwareName,1,softwarePrice));
                break;
        }
    }

}