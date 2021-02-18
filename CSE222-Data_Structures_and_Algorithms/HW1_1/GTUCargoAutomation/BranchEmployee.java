package GTUCargoAutomation;

import java.util.Scanner;

/**
 * Represents a Branch Employee.
 * @author Ali Bahar
 * @author 171044066
 */
public class BranchEmployee extends User{

	private static Scanner in = new Scanner(System.in);
	
    private GTUArray<Customer> Customers;

    /**
     * Creates a new Branch Employee with new user and customers.
     * @param NewUser Branch employee is a user.
     * @param NewCustomers Branch employee has customers.
     */
    public BranchEmployee(User NewUser , GTUArray<Customer> NewCustomers){
        super(NewUser.getName(),NewUser.getSurname(),NewUser.getPassword(),NewUser.getID());
        this.Customers = NewCustomers;
    }

    /**
     * Creates and Adds a new customer.
     */
    public void AddCustomer(){
        System.out.print("Enter customer name : ");

        String NewName = in.next();
        System.out.print("Enter customer surname : ");

        String NewSurname = in.next();
        System.out.print("Enter tracking number : ");

        String NewTrackingNumber = in.next();
        Customers.addData(new Customer(NewName,NewSurname,NewTrackingNumber,NewTrackingNumber));
    }

    /**
     * Creates and adds a new packet.
     */
    public void AddPacket(){
        User Sender = new User();
        User receiver = new User();

        System.out.print("Enter the customer Tracking Number : ");
        String IDtoAdd = in.next();

        System.out.print("Enter sender name : ");
        Sender.setName(in.next());

        System.out.print("Enter sender surname : ");
        Sender.setSurname(in.next());

        System.out.print("Enter receiver name : ");
        receiver.setName(in.next());

        System.out.print("Enter receiver surname : ");
        receiver.setSurname(in.next());


        String status = "";
        boolean quit = false;
        while(!quit){
            System.out.println("1) in branch" +
                    "\n2) in Transportation");
            System.out.print("Enter the status of the packet : ");

            status = in.next();

            switch (status){
                case "1":
                    status =  "in branch";
                    quit = true;
                    break;
                case "2":
                    status = "in Transportation";
                    quit = true;
                    break;
                default:
                    System.out.println("invalid input,try again.");
            }
        }

        int index = FindCustomerByID(IDtoAdd);
        if(index == -1)
            System.out.println("invalid tracking number : " + index);
        else{
            receiver.setID(IDtoAdd);
            Sender.setID(IDtoAdd);
            Customers.getData(index).addPacket(new CargoPackets(Sender,receiver,status));
        }
    }

    /**
     * Erases a packet which determined by user.
     */
    public void erasePacket(){

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
                    Customers.getData(index).erasePacket(Customers.getData(index).getPacket(i));
            }
        }
        else{
            System.out.println("Customer couldn't found.");
        }
    }

    /**
     * Changes the status of the packet.
     * @param NewStatus The new status of the packet.
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
            System.out.println("Customer couldn't found.");
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