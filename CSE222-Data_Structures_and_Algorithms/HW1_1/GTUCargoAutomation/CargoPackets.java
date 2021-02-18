package GTUCargoAutomation;

/**
 * Represents a cargo packet.
 * @author Ali Bahar
 * @author 171044066
 */
public class CargoPackets {

    private static int ObjectCounter = 0;

    private User Sender;
    private User Receiver;
    private String StatusOfPacket;
    private int PacketID;

    /**
     * Creates a new cargo packet with sender,receiver and status.
     * @param NewSender Sender of the packet.
     * @param NewReceiver Receiver of the packet.
     * @param NewStatus Status of the packet.
     */
    public CargoPackets(User NewSender,User NewReceiver,String NewStatus){
        this.setReceiver(NewReceiver);
        this.setSender(NewSender);
        this.setStatusOfPacket(NewStatus);
        PacketID = ObjectCounter;
        ++ObjectCounter;
    }

    /**
     * Gets status of the packet.
     * @return status of the packet as String.
     */
    public String getStatusOfPacket() { return StatusOfPacket; }

    /**
     * Gets receiver of the packet.
     * @return Receiver of the packet as User.
     */
    public User getReceiver() { return Receiver; }

    /**
     * Gets Sender of the packet.
     * @return Sender of the packet as User.
     */
    public User getSender() { return Sender; }

    /**
     * Gets ID of the packet.
     * @return ID of the packet as integer.
     */
    public int getPacketID(){ return PacketID; }

    /**
     * Gets Receiver ID of the packet.
     * @return Receiver ID of the packet as String.
     */
    public String getReceiverID(){ return Receiver.getID(); }

    /**
     * Sets status of packet.
     * @param statusOfPacket new status of the packet.
     */
    public void setStatusOfPacket(String statusOfPacket) { StatusOfPacket = statusOfPacket; }

    /**
     * Sets the receiver of the packet.
     * @param receiver new receiver of the packet.
     */
    public void setReceiver(User receiver) { Receiver = receiver; }

    /**
     * Sets the Sender of the packet.
     * @param sender new sender of the packet.
     */
    public void setSender(User sender) { Sender = sender; }

    /**
     * Creates a string which has sender name,sender surname,receiver name,receiver surname and packet ID.
     * @return a string which has sender name,sender surname,receiver name,receiver surname and packet ID.
     */
    @Override
    public String toString() {
        return "Sender Name : " + Sender.getName() +
                "\nSender Surname : " + Sender.getSurname() +
                "\nReceiver Name : " + Receiver.getName() +
                "\nReceiver Surname : " + Receiver.getSurname() +
                "\nPacket ID : " + PacketID  + "\n";
    }
}