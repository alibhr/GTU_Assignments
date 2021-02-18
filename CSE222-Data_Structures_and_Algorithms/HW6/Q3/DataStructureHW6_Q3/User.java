package DataStructureHW6_Q3;

/**
 * The user that can use the system
 */
public class User {
    /**
     * name of the user
     */
    private String name;

    /**
     * surname of the user
     */
    private String surname;

    /**
     * creates a new user
     * @param name name of the user
     * @param surname surname of the user
     */
    public User(String name, String surname){
        setName(name);
        setSurname(surname);
    }

    /**
     * Sets the name
     * @param name new name
     */
    public void setName(String name) { this.name = name; }

    /**
     * sets the surname
     * @param surname new surname
     */
    public void setSurname(String surname) { this.surname = surname; }

    /**
     * gets the name
     * @return name
     */
    public String getName() { return name; }

    /**
     * gets surname
     * @return surname
     */
    public String getSurname() { return surname; }
}