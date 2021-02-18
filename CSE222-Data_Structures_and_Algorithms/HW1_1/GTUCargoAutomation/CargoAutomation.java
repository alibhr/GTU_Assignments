package GTUCargoAutomation;

/**Represents a cargo automation.
 * The automation system for a cargo company has users such as administrators, branch
 * employees, transportation personnel and customers.
 * @author Ali Bahar
 * @author 171044066
 */
public class CargoAutomation {
    private GTUArray<Administrator> Admins;
    private GTUArray<Customer> Customers;
    private GTUArray<BranchEmployee> BranchEmployees;
    private GTUArray<TransportationPersonnel> TransportEmployees;

    /**
     *Creates an automation with default Admin.
     */
    public CargoAutomation(){
        this(new Administrator(
                "DefaultName",
                "DefaultSurname",
                "DefaultPassword",
                "DefaultID"
        ));
    }

    /**
     * Creates an automation with given Admin.
     * @param Admin The first admin of the automation.
     */
    public CargoAutomation(Administrator Admin){
        Admins = new GTUArray<>();
        Admins.addData(Admin);

        Customers = new GTUArray<>();
        BranchEmployees = new GTUArray<>();
        TransportEmployees = new GTUArray<>();
    }

    /**
     * gets an admin.
     * @param SearchID The ID of the admin which will be get.
     * @return The admin who has the ID which given as parameter.
     */
    public Administrator getAdmin(String SearchID){
        for(int i = 0 ; i< Admins.getUsed() ; ++i){
            if(SearchID.equals(Admins.getData(i).getID())){
                return Admins.getData(i);
            }
        }
        return null;
    }

    /**
     * gets an customer.
     * @param ID The ID of the customer which will be get.
     * @return The customer who has the ID which given as parameter.
     */
    public Customer getCustomerByID(String ID){
        for(int i = 0 ; i< Customers.getUsed() ; ++i){
            if(ID.equals(Customers.getData(i).getID())){
                return Customers.getData(i);
            }
        }
        return null;
    }

    /**
     * gets an customer.
     * @param ID The ID of the Branch Employee which will be get.
     * @return The Branch Employee who has the ID which given as parameter.
     */
    public BranchEmployee getBranchEmploeeByID(String ID){
        for(int i=0 ; i<BranchEmployees.getUsed() ; ++i)
            if(ID.equals(BranchEmployees.getData(i).getID()))
                return BranchEmployees.getData(i);
        return null;
    }

    public TransportationPersonnel getTransportationPersonnelByID(String ID){
        for(int i=0 ; i<TransportEmployees.getUsed() ; ++i)
            if(ID.equals(TransportEmployees.getData(i).getID()))
                return TransportEmployees.getData(i);
        return null;
    }

    /**
     *gets All Branch Employees that this automation have.
     * @return Branch employees as a GTUArray.
     */
    public GTUArray<BranchEmployee> getAllBranchEmployee(){
        return BranchEmployees;
    }

    /**
     * gets All customer that this automation have.
     * @return Customers as a  GTUArray.
     */
    public GTUArray<Customer> getAllCustomers(){
        return Customers;
    }

    /**
     * gets All Transportation Personnel that this automation have.
     * @return Transportation Personnel as a  GTUArray.
     */
    public GTUArray<TransportationPersonnel> getAllTransportationPersonnel(){
        return TransportEmployees;
    }

    /**
     * gets All Admins that this automation have.
     * @return Admins as a  GTUArray.
     */
    public GTUArray<Administrator> getAllAdmins(){
        return Admins;
    }
}