package GTUCargoAutomation;

/**
 * Represents a User.
 * @author Ali Bahar
 * @author 171044066
 */
public abstract class User {

    String ID;
    String Password;
    String Name;
    String Surname;

    /**
     * Creates a new User with default name,surname,password and ID.
     */
    public User(){
        this(
                "non",
                "non",
                "non",
                "non"
        );
    }

    /**
     * Creates a new user with given parameters.
     * @param NewName User's Name.
     * @param NewSurname User's Surname.
     * @param NewPassword User's Password.
     * @param NewID User's ID.
     */
    public User(String NewName,String NewSurname,String NewPassword,String NewID){
        this.Name = NewName;
        this.Surname = NewSurname;
        this.Password = NewPassword;
        this.ID = NewID;
    }

    public abstract String getClassName();

    /**
     * Gets User's Name.
     * @return User's Name as String
     */
    public String getName(){ return Name; }

    /**
     * Gets Users's Surname.
     * @return User's Surname as String.
     */
    public String getSurname(){ return Surname; }

    /**
     * Gets User's password.
     * @return User's password as String.
     */
    public String getPassword(){ return Password; }

    /**
     * Gets User's ID.
     * @return User's ID as String.
     */
    public String getID(){ return ID; }

    /**
     * Sets User's ID.
     * @param ID User's new ID.
     */
    public void setID(String ID) { this.ID = ID; }

    /**
     * Sets User's name.
     * @param name User's new name.
     */
    public void setName(String name) { Name = name; }

    /**
     * Sets User's password.
     * @param password User's new password.
     */
    public void setPassword(String password) { Password = password; }

    /**
     * Sets User's surname.
     * @param surname User's new surname.
     */
    public void setSurname(String surname) { Surname = surname; }

    /**
     * Creates a string which has name,surname and ID.
     * @return a string which has name,surname and ID.
     */
    @Override
    public String toString() {
        return "Name : " + Name + "\nSurname : " + Surname + "\nID : " + ID;
    }

    /**
     * compare the name,surname and ID if they are same returns true.
     * @param obj other object to compare.
     * @return compare the name,surname and ID if they are same returns true.
     */
    @Override
    public boolean equals(Object obj) {
        if(obj == null)
            return false;
        if(obj == this)
            return true;
        if(obj.getClass() != this.getClass())
            return false;

        return (this.Name.equals(((User)obj).Name)) &&
                (this.Surname.equals(((User)obj).Surname)) &&
                (this.ID.equals(((User)obj).ID));
    }

    /**
     * Creates a hashcode.
     * @return hashcode from Object class.
     */
    @Override
    public int hashCode() {
        return super.hashCode();
    }

}