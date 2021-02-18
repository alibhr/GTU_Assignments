package GTUCargoAutomation;

import java.util.Scanner;

/**
 * Represent a Transportation personnel.
 * @author Ali Bahar
 * @author 171044066
 */
public class TransportationPersonnel extends User{
	
	private static Scanner in = new Scanner(System.in);
	
    private GTUArray<Customer> Customers;

    /**
     * Creates a new Transportation Personnel with the specified name,surname,password and ID.
     * @param NewName Transportation Personnel's name.
     * @param NewSurname Transportation Personnel's surname.
     * @param NewPassword Transportation Personnel's password.
     * @param NewID Transportation Personnel's ID.
     * @param NewCustomers The customers.
     */
    public TransportationPersonnel(String NewName, String NewSurname, String NewPassword,String NewID,GTUArray<Customer> NewCustomers) {
        super(NewName, NewSurname, NewPassword,NewID);
        Customers = NewCustomers;
    }

    /**
     * sets the packet status.
     * @param NewStatus The new status of packet.
     */
    public void setPacketStatus(String NewStatus){

        System.out.print("Enter the Customer ID : ");
        String CustomerID = in.next();

        int index = FindCustomerByID(CustomerID);
        if(index != -1){
            for(int i=0 ; i<Customers.getData(index).getPacketNumber() ; ++i)
                System.out.println(Customers.getData(index).getPacket(i));

            System.out.print("Enter Packet ID : ");
            int PacketID = in.nextInt();

            for(int i=0 ; i<Customers.getData(index).getPacketNumber() ; ++i){
                if(Customers.getData(index).getPacket(i).getPacketID() == PacketID)
                    Customers.getData(index).getPacket(i).setStatusOfPacket(NewStatus);
            }
        }
        else{
            System.out.println("The customer couldn't be found");
        }
    }

    /**
     * search a customer with their ID.
     * @param CustomerID Customer ID which will be searched.
     * @return if the Customer can be found returns index.if the Customer can't be found returns -1.
     */
    public int FindCustomerByID(String CustomerID){
        for(int i=0 ; i<Customers.getUsed() ; ++i)
            if(Customers.getData(i).getID().equals(CustomerID))
                return i;
        return -1;
    }
}