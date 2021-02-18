package GTUCargoAutomation;

import java.util.ArrayList;
import java.util.Scanner;

/**
 * Represents a Branch Employee.
 * @author Ali Bahar
 * @author 171044066
 */
public class BranchEmployee extends User implements CanLogin{

    private Branch TheBranch;


    private static Scanner input = new Scanner(System.in);

    /**
     * Creates a new Branch Employee with new user and customers.
     * @param NewName name of Branch Employee
     * @param NewSurname surname of Branch Employee
     * @param NewPassword password of Branch Employee
     * @param NewID ID of Branch Employee
     * @param branch branch of Branch Employee
     */
    public BranchEmployee(String NewName,String NewSurname,String NewPassword,String NewID,Branch branch){
        super(NewName,NewSurname,NewPassword,NewID);
        this.TheBranch = branch;
    }

    /**
     * gets the branch.
     * @return the branch.
     */
    public Branch getTheBranch() {
        return TheBranch;
    }

    /**
     * sets the branch.
     * @param theBranch new branch.
     */
    public void setTheBranch(Branch theBranch) {
        TheBranch = theBranch;
    }

    /**
     * Adds a new customer
     * @param AllCustomers Adds a new customer to this ArrayList.
     */
    public void AddCustomer(ArrayList<Customer> AllCustomers){
        if(AllCustomers == null){
            throw new NullPointerException();
        }

        System.out.print("Enter customer name : ");
        String NewName = input.next();

        System.out.print("Enter customer surname : ");
        String NewSurname = input.next();

        System.out.print("Enter tracking number : ");
        String NewTrackingNumber = input.next();

        boolean found = false;

        for(Customer aCustomer : AllCustomers){
            if(aCustomer.getID().equals(NewTrackingNumber))
                found = true;
        }
        if(!found)
            AllCustomers.add(new Customer(NewName,NewSurname,NewTrackingNumber,NewTrackingNumber));
        else{
            System.out.println("This ID has been already added.");
        }
    }

    /**
     * Adds a new packet
     * @param automationOfMyCompany Adds a new packet by finding the correct customer from this ArrayList
     */
    public void AddPacket(CargoAutomation automationOfMyCompany){
        if(automationOfMyCompany == null){
            throw new NullPointerException();
        }

        System.out.print("Enter the customer Tracking Number : ");
        String IDtoAdd = input.next();

        System.out.print("Enter sender name : ");
        String SenderName = input.next();

        System.out.print("Enter sender surname : ");
        String SenderSurName = input.next();

        Customer aCustomer = automationOfMyCompany.getCustomerByID(IDtoAdd);
        if(aCustomer == null){
            System.out.println("this customer doesn't exist.");
        }
        else{
            String status = SelectNewStatus();

            if(status != null){
                CargoPackets NewPacket = new CargoPackets(aCustomer,SenderName + " " + SenderSurName);
                NewPacket.setStatusOfPacket(status);
                aCustomer.addAPacket(NewPacket);
            }
            else {
                System.out.println("Couldn't be added .");
            }
        }
    }

    private static String SelectNewStatus(){
        while(true){
            System.out.println("1) in branch" +
                    "\n2) in Transportation" +
                    "\n0) quit");
            String  selection = input.next();
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

    /**
     * erases a packet.
     * @param automationOfMyCompany erases a packet by finding the correct packet which will be removed.
     */
    public void erasePacket(CargoAutomation automationOfMyCompany){
        if(automationOfMyCompany == null){
            throw new NullPointerException();
        }

        System.out.println("Enter the tracking ID of customer : ");
        String ID = input.next();

        Customer aCustomer = automationOfMyCompany.getCustomerByID(ID);
        if(aCustomer != null){
            aCustomer.ShowInfoOfAllPackets();

            System.out.println("Enter the index of the packet to remove:");
            int index = input.nextInt();
            aCustomer.getAllPackets().remove(index);
        }
        else{
            System.out.println("This Customer couldn't be found.");
        }
    }

    /**
     * Sets status of a packet.
     * @param automationOfMyCompany Sets the packet by finding the packet from this ArrayList.
     */
    public void setPacketStatus(CargoAutomation automationOfMyCompany){
        if(automationOfMyCompany == null){
            throw new NullPointerException();
        }
        System.out.println("Enter the tracking ID of customer : ");
        String ID = input.next();

        Customer aCustomer = automationOfMyCompany.getCustomerByID(ID);
        if(aCustomer != null){
            aCustomer.ShowInfoOfAllPackets();

            System.out.println("Enter the index of the packet to change status:");
            int index = input.nextInt();
            String NewStatus = SelectNewStatus();
            aCustomer.getAllPackets().get(index).setStatusOfPacket(NewStatus);
        }
        else{
            System.out.println("This Customer couldn't be found.");
        }
    }

    /**
     * longins to system.
     * @param Password compares this password and real password
     * @return if Password correct, this method will return true.
     */
    @Override
    public boolean login(String Password) {
        if(Password == null)
            throw new NullPointerException();
        if( ! Password.equals(this.getPassword())){
            System.out.println("invalid Branch employee password");
            return false;
        }
        return true;
    }

    /**
     * Says the name of the class.
     * @return name of the class.
     */
    @Override
    public String getClassName() {
        return "BranchEmployee";
    }
}