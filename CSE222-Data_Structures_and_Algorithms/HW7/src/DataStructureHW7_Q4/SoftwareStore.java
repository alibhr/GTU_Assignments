package DataStructureHW7_Q4;

import DataStructureHW7_Q3.SearchTree;

/**
 * Simple software store.
 */
public class SoftwareStore {

    /**
     * All software in the software store.
     */
    private SearchTree<Software> allSoftware;

    /**
     * password of the store.
     */
    private String password;

    /**
     * indicates the login is success or not.
     */
    private boolean isLogin;

    /**
     * constructs a new software store.
     * @param software to determine the tree type.
     */
    public SoftwareStore(SearchTree<Software> software){
        allSoftware = software;
        password = "171044066";
        isLogin = false;
    }

    /**
     * login to system.
     * @param password password which comes from user.
     * @return true if login is success, otherwise returns false.
     */
    public boolean loginToSystem(String password){
        if(password.equals(this.password)){
            isLogin = true;
            return true;
        }
        return false;
    }

    /**
     * adds a ne software to system.
     * @param newSoftware new software
     * @return true if add is success, otherwise returns false.
     */
    public boolean addSoftware(Software newSoftware){
        return allSoftware.add(newSoftware);
    }

    /**
     * removes a software
     * @param softwareName software name to be removed.
     * @return true if remove is success, otherwise returns false.
     */
    public boolean removeSoftware(String softwareName){
        return allSoftware.remove(new Software(softwareName,1,1));
    }

    /**
     * updates the software
     * @param softwareName software name to be updated.
     * @param newSoftware new software.
     * @return true if update is success, otherwise returns false.
     */
    public boolean updateSoftware(String softwareName,Software newSoftware){
        if(removeSoftware(softwareName)){
            addSoftware(newSoftware);
            return true;
        }
        return false;
    }

    /**
     * returns the software by searching its name.
     * @param softwareName name of the software to be searched.
     * @return the software if it exists in this system.
     */
    public Software softwareSearch(String softwareName){
        return allSoftware.find(new Software(softwareName,1,1));
    }
}