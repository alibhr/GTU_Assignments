package GTUCargoAutomation;

/**
 * Represents a cargo packet.
 * @author Ali Bahar
 * @author 171044066
 */
public class CargoPackets {

    String AboutSender;
    Customer Receiver;
    String StatusOfPacket;

    /**
     *Creates a new Branch
     * @param NewReceiver information about receiver.
     * @param NewAboutSender information about sender.
     */
    public CargoPackets(Customer NewReceiver,String NewAboutSender){
        this.Receiver = NewReceiver;
        this.AboutSender = NewAboutSender;
        this.StatusOfPacket = "in branch";
    }

    /**
     * Sets the status of the packet.
     * @param statusOfPacket new status of packet.
     */
    public void setStatusOfPacket(String statusOfPacket) {
        StatusOfPacket = statusOfPacket;
    }

    /**
     * Gets information about sender.
     * @return information about sender.
     */
    public String getAboutSender() {
        return AboutSender;
    }

    /**
     * gets status of the packet
     * @return status of the packet as String.
     */
    public String getStatusOfPacket() {
        return StatusOfPacket;
    }

    /**
     * Gets Receiver Name.
     * @return Receiver Name.
     */
    public String getReceiverName(){
        return Receiver.getName();
    }

    /**
     * Gets Receiver Surname.
     * @return Receiver Surname.
     */
    public String getReceiverSurname(){
        return Receiver.getSurname();
    }
}