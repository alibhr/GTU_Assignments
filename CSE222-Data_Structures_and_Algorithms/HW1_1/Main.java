import GTUCargoAutomation.*;

import java.util.Scanner;

public class Main {
	
	public static Scanner in = new Scanner(System.in);
	
    public static void main(String[] args) {

        CargoAutomation AutomationOfMyCompany = new CargoAutomation(new Administrator("Ali","Bahar","true","true"));

        boolean quit = false;
        while(!quit){
            FirstScreen();
            String selection = in.next();
            switch (selection){
                case "0":
                    quit = true;
                    break;
                case "1":
                    AdminLogin(AutomationOfMyCompany);
                    break;
                case "2":
                    BranchEmployeeLogin(AutomationOfMyCompany);
                    break;
                case "3":
                    TransportationPersonnelLogin(AutomationOfMyCompany);
                    break;
                case "4":
                    CustomerLogin(AutomationOfMyCompany);
                    break;

            }
        }
    }

    private static void FirstScreen(){
        System.out.print("\n\nCargo Automation Login screen.\n" +
                "1) Login as a Admin." +
                "\n2) Login as a Branch Employee." +
                "\n3) Login as a Transportation Personnel." +
                "\n4) Login as a Customer." +
                "\n0) to quit from automation." +
                "\nchoice : "
        );
    }

    private static void AdminLogin(CargoAutomation AutomationOfMyCompany){
        if( AutomationOfMyCompany == null)
            throw new NullPointerException();

        System.out.print(
                "\nDefault ID : true" +
                "\nDefault password : true" +
                "\nAfter Login you can add a new Admin\n"
        );

        System.out.print("Enter Admin ID : ");
        String SearchID = in.next();

        System.out.print("Enter Admin Password : ");
        String AdminPassword = in.next();

        Administrator anAdmin = AutomationOfMyCompany.getAdmin(SearchID);
        if (anAdmin == null)
            System.out.println("invalid ID");
        else if (anAdmin.login(AdminPassword))
            AdminsMethods(anAdmin,AutomationOfMyCompany);

    }

    private static void AdminsMethods(Administrator anAdmin,CargoAutomation AutomationOfMyCompany) {

        boolean quit = false;
        while(!quit){
            System.out.print(" \n\nAdmin Panel" +
                    "\n1) Add Branch." +
                    "\n2) Add BranchEmployee." +
                    "\n3) Add Transportation Personnel." +
                    "\n4) Add Admin." +
                    "\n5) remove Branch." +
                    "\n6) remove Branch Employee." +
                    "\n7) remove Transportation Personnel." +
                    "\n8) remove Admin." +
                    "\n0) back." +
                    "\nchoice : ");
            String selection = in.next();
            switch (selection){
                case "0":
                    quit=true;
                    break;
                case "1":
                    anAdmin.addBranch(AutomationOfMyCompany.getAllBranchEmployee());
                    break;
                case "2":
                    anAdmin.addBranchEmployee(AutomationOfMyCompany.getAllBranchEmployee(),AutomationOfMyCompany.getAllCustomers());
                    break;
                case "3":
                    anAdmin.addTransportationPersonnel(AutomationOfMyCompany.getAllTransportationPersonnel(),AutomationOfMyCompany.getAllCustomers());
                    break;
                case "4":
                    anAdmin.addAdmin(AutomationOfMyCompany.getAllAdmins(),anAdmin.getBranches());
                    break;
                case "5":
                    anAdmin.removeBranch();
                    break;
                case "6":
                    anAdmin.removeBranchEmployee(AutomationOfMyCompany.getAllBranchEmployee());
                    break;
                case "7":
                    anAdmin.removeTransportationPersonnel(AutomationOfMyCompany.getAllTransportationPersonnel());
                    break;
                case "8":
                    anAdmin.removeAdmin(AutomationOfMyCompany.getAllAdmins());
                    break;
            }
        }
    }

    private static void CustomerLogin(CargoAutomation AutomationOfMyCompany) {

        System.out.print("Enter your Tracking Number : ");
        String TrackingNumber = in.next();

        Customer aCustomer = AutomationOfMyCompany.getCustomerByID(TrackingNumber);
        if(aCustomer != null){
            GTUArray<CargoPackets> ThePackets = aCustomer.getPackets();
            for(int i=0 ; i<ThePackets.getUsed() ; ++i)
                if(ThePackets.getData(i).getReceiverID().equals(aCustomer.getID()))
                    System.out.println(ThePackets.getData(i).toString() + "\n");
        }
        else{
            System.out.println("Couldn't be found");
        }
    }

    private static void BranchEmployeeLogin(CargoAutomation automationOfMyCompany) {

        System.out.println("Enter Your Branch Employee ID : ");
        String ID = in.next();

        System.out.println("Enter Your Branch Employee Password : ");
        String password = in.next();

        BranchEmployee aBranchEmployee = automationOfMyCompany.getBranchEmploeeByID(ID);
        if(aBranchEmployee == null){
            System.out.println("This ID Doesn't exist.");
        }
        else if(aBranchEmployee.login(password)){
            BranchEmployeesMethods(aBranchEmployee);
        }

    }

    private static void BranchEmployeesMethods(BranchEmployee aBranchEmployee){
        boolean quit = false;
        while(!quit){
            System.out.print("1) Add Customer." +
                    "\n2) Add packet." +
                    "\n3) erase packet." +
                    "\n4) Set packet status." +
                    "\n0) Quit\n");
            String selection = in.next();
            switch (selection){
                case "0":
                    quit=true;
                    break;
                case "1":
                    aBranchEmployee.AddCustomer();
                    break;
                case "2":
                    aBranchEmployee.AddPacket();
                    break;
                case "3":
                    aBranchEmployee.erasePacket();
                    break;
                case "4":
                    String NewStatus = SelectNewStatus();
                    if(NewStatus!=null)
                        aBranchEmployee.setPacketStatus(NewStatus);
                    break;
            }
        }
    }

    private static String SelectNewStatus(){
        while(true){
            System.out.println("1) in branch" +
                    "\n2) in Transportation" +
                    "\n0) quit");
            String  selection = in.next();

            switch (selection){
                case "1":
                    return "in branch";
                case "2":
                    return "in Transportation";
                case "0":
                    return null;
                default:
                    System.out.println("invalid input,try again.");
            }
        }
    }

    private static void TransportationPersonnelLogin(CargoAutomation automationOfMyCompany) {
        if(automationOfMyCompany == null)
            throw new NullPointerException();

        System.out.println("Enter Your Transportation Personnel ID : ");
        String ID = in.next();

        System.out.println("Enter Your Transportation Personnel Password : ");
        String password = in.next();

        TransportationPersonnel aTransportationPersonnel = automationOfMyCompany.getTransportationPersonnelByID(ID);
        if(aTransportationPersonnel == null)
            System.out.println("This ID Doesn't exist.");
        else if(aTransportationPersonnel.login(password)){
            System.out.println("1) Turn Status to Delivered." +
                    "\n0) quit");

            String selection = in.next();

            if(selection.equals("1"))
                aTransportationPersonnel.setPacketStatus("Delivered");
            else{
                System.out.println("The Status didn't change.");
            }
        }
    }
}