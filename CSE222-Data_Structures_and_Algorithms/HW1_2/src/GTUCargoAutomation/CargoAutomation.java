package GTUCargoAutomation;

import java.util.ArrayList;


/**Represents a cargo automation.
 * The automation system for a cargo company has users such as administrators, branch
 * employees, transportation personnel and customers.
 * @author Ali Bahar
 * @author 171044066
 */
public class CargoAutomation {
    String CompanyName;
    ArrayList <Administrator> AllAdmins;
    ArrayList <Branch> AllBranches;
    ArrayList <Customer> AllCustomers;

    /**
     *Creates an automation with default Admin.
     */
    public CargoAutomation(){
        this(new Administrator(
                "default",
                "default",
                "default",
                "default"
        ));
    }

    /**
     * Creates an automation with given Admin.
     * @param NewAdmin The first admin of the automation.
     */
    public CargoAutomation(Administrator NewAdmin){
        AllAdmins = new ArrayList<>();
        AllBranches = new ArrayList<>();
        AllCustomers = new ArrayList<>();

        this.AllAdmins.add(NewAdmin);
    }

    /**
     * gets an admin.
     * @param SearchID The ID of the admin which will be got.
     * @return The admin who has the ID which given as parameter.
     */
    public Administrator getAdminByID(String SearchID){
        for (Administrator allAdmin : AllAdmins) {
            if (SearchID.equals(allAdmin.getID())) {
                return allAdmin;
            }
        }
        return null;
    }

    /**
     * gets a customer.
     * @param ID The ID of the customer which will be got.
     * @return The customer who has the ID which given as parameter.
     */
    public Customer getCustomerByID(String ID){
        for (Customer allCustomer : AllCustomers) {
            if (ID.equals(allCustomer.getID())) {
                return allCustomer;
            }
        }
        return null;
    }

    /**
     * Gets a Branch
     * @param Name Name of the branch which will be got.
     * @return The Branch who has the ID which given as parameter.
     */
    public Branch getBranchByName(String Name){
        for (Branch allBranch : AllBranches) {
            if (Name.equals(allBranch.getBranchName()))
                return allBranch;
        }
        return null;
    }

    /**
     * gets All Branches.
     * @return All Branches.
     */
    public ArrayList<Branch> getAllBranches() {
        return AllBranches;
    }

    /**
     * Gets All Admins.
     * @return All Admins.
     */
    public ArrayList<Administrator> getAllAdmins(){
        return AllAdmins;
    }

    /**
     * Gets All AllCustomers.
     * @return All Customers.
     */
    public ArrayList<Customer> getAllCustomers(){
        return AllCustomers;
    }

    /**
     * gets a Branch Employee.
     * @param ID The ID of the Branch Employee which will be got.
     * @return The Branch Employee who has the ID which given as parameter.
     */
    public BranchEmployee getBranchEmployeeByID(String ID){
        for(Branch allBranches : AllBranches){
            if(allBranches.getBranchEmployeeByID(ID) != null)
                return allBranches.getBranchEmployeeByID(ID);
        }
        return null;
    }

    /**
     * gets a Transportation personal.
     * @param ID The ID of the Branch Employee which will be got
     * @return a Transportation personal.
     */
    public TransportationPersonnel getTransportationPersonnelByID(String ID){
        for(Branch aBranch : AllBranches){
            if(aBranch.getTransportationEmployeeByID(ID) != null)
                return aBranch.getTransportationEmployeeByID(ID);
        }
        return null;
    }
}