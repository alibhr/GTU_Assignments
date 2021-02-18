package DataStructureHW6_Q3;

/**
 * The admin class to manage ethe automation system
 */
public class Administrator extends User{

    /**
     * password to login to system
     */
    private String password;

    /**
     * indicates whether the login success or not.
     */
    private boolean login;

    /**
     * creates a new admin
     * @param name name of the admin
     * @param surname surname of the admin
     * @param password password of the admin
     */
    public Administrator(String name, String surname, String password){
        super(name,surname);
        setPassword(password);
        login = false;
    }

    /**
     * setter method
     * @param password the new password
     */
    public void setPassword(String password) { this.password = password; }

    /**
     * getter method
     * @return the password
     */
    public String getPassword() { return password; }

    /**
     * to log in to system
     * @param thePassword a password to compare with actual password
     * @return true if log in success
     */
    public boolean login(String thePassword){
        login = this.getPassword().equals(thePassword);
        return login;
    }

    /**
     * check whether the login or not.
     * @return whether login is success
     */
    public boolean isLogin(){
        return login;
    }
}