package GTUCargoAutomation;

import java.util.Scanner;

/**
 * Represent a Transportation personnel.
 * @author Ali Bahar
 * @author 171044066
 */
public class TransportationPersonnel extends User implements CanLogin{
    Branch TheBranch;
    private static Scanner input = new Scanner(System.in);

    /**
     * Creates a new Transportation Personal with new user and customers.
     * @param NewName name of Transportation Personal
     * @param NewSurname surname of Transportation Personal
     * @param NewPassword password of Transportation Personal
     * @param NewID ID of Transportation Personal
     * @param branch branch of Transportation Personal
     */
    public TransportationPersonnel(String NewName,String NewSurname,String NewPassword,String NewID,Branch branch){
        super(NewName,NewSurname,NewPassword,NewID);
        this.TheBranch = branch;
    }

    /**
     * Sets status of a packet.
     * @param automationOfMyCompany Sets the packet by finding the packet from this ArrayList.
     */
    public void setPacketStatus(CargoAutomation automationOfMyCompany) {
        if(automationOfMyCompany == null){
            throw  new NullPointerException();
        }

        System.out.print("Enter the Customer ID : ");
        String CustomerID = input.next();

        Customer aCustomer = automationOfMyCompany.getCustomerByID(CustomerID);
        if(aCustomer != null){
            aCustomer.ShowInfoOfAllPackets();

            System.out.println("Enter the index of the packet to change status:");
            int index = input.nextInt();
            aCustomer.getAllPackets().get(index).setStatusOfPacket("Delivered");
            System.out.println("The status changed to Delivered.");
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
            System.out.println("invalid Transportation Employee password");
            return false;
        }
        return true;
    }

    /**
     * gets the name of the class.
     * @return name of the class.
     */
    @Override
    public String getClassName() {
        return "TransportationPersonnel";
    }
}