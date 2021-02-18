package GTUCargoAutomation;

import java.util.ArrayList;

/**
 * Represents a Branch.
 * @author Ali Bahar
 * @author 171044066
 */
public class Branch {

    String BranchName;
    Administrator AdminOfBranch;
    ArrayList<BranchEmployee> AllBranchEmployees;
    ArrayList<TransportationPersonnel> AllTransportationPersonnel;

    /**
     * Creates a new Branch with a name and an admin.
     * @param NewBranchName The name of the new Branch.
     * @param NewAdmin The Admin of this branch.
     */
    public Branch(String NewBranchName,Administrator NewAdmin){
        this.BranchName = NewBranchName;
        this.AdminOfBranch = NewAdmin;
        AllBranchEmployees = new ArrayList<>();
        AllTransportationPersonnel = new ArrayList<>();
    }

    /**
     * Gets Branch Name.
     * @return Branch Name as a string.
     */
    public String getBranchName() {
        return BranchName;
    }

    /**
     * Gets All branch employees
     * @return branch employees as ArrayList.
     */
    public ArrayList<BranchEmployee> getAllBranchEmployees() {
        return AllBranchEmployees;
    }

    /**
     * Gets All Transportation Personnel.
     * @return Transportation Personnel as ArrayList.
     */
    public ArrayList<TransportationPersonnel> getAllTransportationPersonnel() {
        return AllTransportationPersonnel;
    }

    /**
     * Gets a Branch Employee.
     * @param ID to find the correct Branch Employee.
     * @return a Branch Employee
     */
    public BranchEmployee getBranchEmployeeByID(String ID){
        for (BranchEmployee aBranchEmployee : AllBranchEmployees) {
            if (aBranchEmployee.getID().equals(ID))
                return aBranchEmployee;
        }
        return null;
    }

    /**
     * Gets a Transportation Personal.
     * @param ID to find the correct Transportation Personal.
     * @return a Transportation Personal.
     */
    public TransportationPersonnel getTransportationEmployeeByID(String ID){
        for (TransportationPersonnel aTransportationEmployee : AllTransportationPersonnel) {
            if (aTransportationEmployee.getID().equals(ID))
                return aTransportationEmployee;
        }
        return null;
    }
}