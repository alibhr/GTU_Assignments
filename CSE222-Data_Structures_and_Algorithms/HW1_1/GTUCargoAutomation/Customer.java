package GTUCargoAutomation;

/**
 * Represents a customer.
 * @author Ali Bahar
 * @author 171044066
 */
public class Customer extends User {

    private GTUArray<CargoPackets> packets;

    /**
     * Creates a new Customer with name,surname,Password and ID.
     * @param NewName Customer's Name.
     * @param NewSurname Customer's Surname.
     * @param NewPassword Customer's password.
     * @param NewID Customer's ID.
     */
    public Customer(String NewName, String NewSurname, String NewPassword,String NewID) {
        super(NewName, NewSurname, NewPassword,NewID);
        packets = new GTUArray<>();
    }

    /**
     * Adds a new packet.
     * @param NewPacket The new packet which will be added.
     */
    public void addPacket(CargoPackets NewPacket){
        packets.addData(NewPacket);
    }

    /**
     * erases the packet.
     * @param toDelete The packet which will be removed.
     */
    public void erasePacket(CargoPackets toDelete){
        int indexToDelete = packets.find(toDelete);
        if(indexToDelete != -1)
            packets.eraseData(indexToDelete);
        else
            System.out.println("Couldn't erased the packet !");
    }

    /**
     * gets a packet.
     * @param index index of packet which will be got.
     * @return The packet in the given index.
     */
    public CargoPackets getPacket(int index){ return packets.getData(index); }

    /**
     * gets the all packets.
     * @return All packets as GTUArray.
     */
    public GTUArray<CargoPackets> getPackets(){ return packets; }

    /**
     * Gets How many packet there are.
     * @return packet number as integer.
     */
    public int getPacketNumber(){ return packets.getUsed(); }
}