package GTUCargoAutomation;

import java.util.ArrayList;

/**
 * Represents a customer.
 * @author Ali Bahar
 * @author 171044066
 */
public class Customer extends User implements CanLogin{

    private ArrayList<CargoPackets> AllPackets;

    /**
     * Creates a new Customer with name,surname,Password and ID.
     * @param name Customer's name.
     * @param surname Customer's surname.
     * @param password Customer's password.
     * @param ID Customer's ID.
     */
    public Customer(String name,String surname,String password,String ID){
        super(name,surname,password,ID);
        AllPackets = new ArrayList<>();
    }

    /**
     * Gets All packets.
     * @return All packets.
     */
    public ArrayList<CargoPackets> getAllPackets() {
        return AllPackets;
    }

    /**
     * Adds a new packet.
     * @param aPackets The packet which will be added.
     */
    public void addAPacket(CargoPackets aPackets) {
        AllPackets.add(aPackets);
    }

    /**
     * Shows All Info about All packets.
     */
    public void ShowInfoOfAllPackets(){
        System.out.printf("%-15s %-15s %-15s %-15s\n","index","Receiver","Sender","Status");
        for (int i=0 ; i<AllPackets.size() ; ++i) {
            System.out.printf("%-15d %-15s %-15s %-15s\n",i, AllPackets.get(i).getReceiverName() + " " +
                            AllPackets.get(i).getReceiverSurname(),
                            AllPackets.get(i).getAboutSender(),
                            AllPackets.get(i).getStatusOfPacket()
            );
        }
    }

    /**
     * longins to system.
     * @param trackingID compares this trackingID and real trackingID.
     * @return if Password correct, this method will return true.
     */
    @Override
    public boolean login(String trackingID) {
        return false;
    }

    /**
     * gets the name of the class.
     * @return name of the class.
     */
    @Override
    public String getClassName() {
        return "Customer";
    }
}