package DataStructureHW7_Q4;

/**
 * To represents a software in a software store.
 */
public class Software implements Comparable<Software> {
    /** name of the software */
    private String nameWithVersion;

    /** quantity of the software */
    private int quantity;

    /** price of the software */
    private int price;

    /**
     * constructs a new software.
     * @param name name of the software
     * @param quantity quantity of the software
     * @param price price of the software
     */
    public Software(String name,int quantity,int price){
        setNameWithVersion(name);
        setQuantity(quantity);
        setPrice(price);
    }

    /**
     * sets the name
     * @param nameWithVersion name of the software
     */
    public void setNameWithVersion(String nameWithVersion) {
        this.nameWithVersion = nameWithVersion;
    }

    /**
     * sets the price
     * @param price price of the software
     */
    public void setPrice(int price) {
        this.price = price;
    }

    /**
     * sets the quantity
     * @param quantity quantity of the software
     */
    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }

    /**
     * gets the price
     * @return price
     */
    public int getPrice() {
        return price;
    }

    /**
     * gets the quantity
     * @return quantity
     */
    public int getQuantity() {
        return quantity;
    }

    /**
     * gets the name
     * @return name
     */
    public String getNameWithVersion() {
        return nameWithVersion;
    }

    /**
     * returns the string representation of the software.
     * @return the string representation of the software.
     */
    @Override
    public String toString() {
        return "Name : " + getNameWithVersion() +
                "\nquantity : " + getQuantity() +
                "\nprice : " + getPrice();
    }

    /**
     * compares two software object with their names.
     * @param o other object to compare
     * @return difference between the names.
     */
    @Override
    public int compareTo(Software o) {
        return this.nameWithVersion.compareTo(o.getNameWithVersion());
    }
}