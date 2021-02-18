import GTUCargoAutomation.*;

import java.util.Scanner;
public class Main {

    private static Scanner input = new Scanner(System.in);

    public static void main(String[] args) {

        CargoAutomation AutomationOfMyCompany = new CargoAutomation(new Administrator("Ali", "Bahar", "tr", "tr"));

        boolean quit = false;
        while (!quit) {
            FirstScreen();
            String selection = input.next();
            switch (selection) {
                case "0":
                    input.close();
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
                "1) Login as an Admin." +
                "\n2) Login as a Branch Employee." +
                "\n3) Login as a Transportation Personnel." +
                "\n4) Login as a Customer." +
                "\n0) to quit from automation." +
                "\nchoice : "
        );
    }

    private static void AdminLogin(CargoAutomation automationOfMyCompany) {
        if( automationOfMyCompany == null)
            throw new NullPointerException();

        System.out.print(
                "\nDefault ID : tr" +
                        "\nDefault password : tr" +
                        "\nAfter Login you can add a new Admin\n"
        );

        System.out.print("Enter Admin ID : ");
        Scanner in = new Scanner(System.in);
        String SearchID = in.next();

        System.out.print("Enter Admin Password : ");
        String AdminPassword = in.next();

        Administrator anAdmin = automationOfMyCompany.getAdminByID(SearchID);
        if (anAdmin == null)
            System.out.println("invalid ID");
        else if (anAdmin.login(AdminPassword))
            AdminsMethods(anAdmin,automationOfMyCompany);

    }

    private static void showClassName(User aUser){
        if( aUser == null)
            throw new NullPointerException();
        System.out.println(aUser.getClassName());
    }

    private static void AdminsMethods(Administrator anAdmin, CargoAutomation automationOfMyCompany) {
        boolean quit = false;
        while(!quit){
            System.out.print(" \n\nAdmin Panel" +
                    "\n1) Add Branch." +
                    "\n2) Add  BranchEmployee." +
                    "\n3) Add Transportation Personnel." +
                    "\n4) Add Admin." +
                    "\n5) remove Branch." +
                    "\n6) remove Branch Employee." +
                    "\n7) remove Transportation Personnel." +
                    "\n8) remove Admin." +
                    "\n0) back." +
                    "\nchoice : ");
            String selection = input.next();
            switch (selection){
                case "0":
                    quit=true;
                    break;
                case "1":
                    anAdmin.addBranch(automationOfMyCompany.getAllBranches());
                    break;
                case "2":
                    anAdmin.addBranchEmployee(automationOfMyCompany.getAllBranches());
                    break;
                case "3":
                    anAdmin.addTransportationPersonnel(automationOfMyCompany.getAllBranches());
                    break;
                case "4":
                    anAdmin.addAdmin(automationOfMyCompany.getAllAdmins());
                    break;
                case "5":
                    anAdmin.removeBranch(automationOfMyCompany.getAllBranches());
                    break;
                case "6":
                    anAdmin.removeBranchEmployee(automationOfMyCompany.getAllBranches());
                    break;
                case "7":
                    anAdmin.removeTransportationPersonnel(automationOfMyCompany.getAllBranches());
                    break;
                case "8":
                    anAdmin.removeAdmin(automationOfMyCompany.getAllAdmins());
                    break;
            }
        }
    }

    private static void BranchEmployeeLogin(CargoAutomation automationOfMyCompany) {
        if(automationOfMyCompany == null){
            throw new NullPointerException();
        }

        System.out.println("Enter Your Branch Employee ID : ");
        String ID = input.next();

        System.out.println("Enter Your Branch Employee Password : ");
        String password = input.next();


        BranchEmployee aBranchEmployee = automationOfMyCompany.getBranchEmployeeByID(ID);
        if(aBranchEmployee == null){
            System.out.println("This ID Doesn't exist.");
        }
        else if(aBranchEmployee.login(password)){
            BranchEmployeesMethods(aBranchEmployee,automationOfMyCompany);
        }
    }

    private static void BranchEmployeesMethods(BranchEmployee aBranchEmployee, CargoAutomation automationOfMyCompany) {
        boolean quit = false;
        while(!quit){
            System.out.print("1) Add Customer." +
                    "\n2) Add packet." +
                    "\n3) erase packet." +
                    "\n4) Set packet status." +
                    "\n0) Quit\n");
            String selection = input.next();
            switch (selection){
                case "0":
                    quit=true;
                    break;
                case "1":
                    aBranchEmployee.AddCustomer(automationOfMyCompany.getAllCustomers());
                    break;
                case "2":
                    aBranchEmployee.AddPacket(automationOfMyCompany);
                    break;
                case "3":
                    aBranchEmployee.erasePacket(automationOfMyCompany);
                    break;
                case "4":
                    aBranchEmployee.setPacketStatus(automationOfMyCompany);
                    break;
            }
        }
    }

    private static void CustomerLogin(CargoAutomation automationOfMyCompany) {
        if(automationOfMyCompany == null)
            throw new NullPointerException();

        System.out.print("Enter your Tracking Number : ");
        String TrackingNumber = input.next();

        Customer aCustomer = automationOfMyCompany.getCustomerByID(TrackingNumber);
        if(aCustomer != null){
            aCustomer.ShowInfoOfAllPackets();
        }
        else{
            System.out.println("Couldn't be found");
        }
    }

    private static void TransportationPersonnelLogin(CargoAutomation automationOfMyCompany) {
        if(automationOfMyCompany == null){
            throw new NullPointerException();
        }

        System.out.println("Enter Your Transportation Personnel ID : ");
        String ID = input.next();

        System.out.println("Enter Your Transportation Personnel Password : ");
        String password = input.next();


        TransportationPersonnel aTransportationEmployee = automationOfMyCompany.getTransportationPersonnelByID(ID);
        if(aTransportationEmployee == null){
            System.out.println("This ID Doesn't exist.");
        }
        else if(aTransportationEmployee.login(password)){
            System.out.println("Do you want to change any packet status to Delivered" +
                    "\ny)yes" +
                    "\nn)no");
            String S = input.next();
            if(S.equals("y")){
                aTransportationEmployee.setPacketStatus(automationOfMyCompany);
            }
        }
    }
}