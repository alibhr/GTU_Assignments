package GTUCargoAutomation;

/**
 * Represents a Branch.
 * @author Ali Bahar
 * @author 171044066
 */
public class Branch {
    private String BranchName;
    private GTUArray<BranchEmployee> BranchEmployees;

    /**
     * Creates a new Branch with a name and branch employees.
     * @param NewBranchName The name of the new Branch.
     * @param NewBranchEmployee The employees of the name branch.
     */
    public Branch(String NewBranchName,GTUArray<BranchEmployee>NewBranchEmployee){
        this.BranchName = NewBranchName;
        this.BranchEmployees = NewBranchEmployee;
    }

    /**
     * Get the name of the Branch.
     * @return return the name of the branch as a string.
     */
    public String getBranchName(){ return BranchName; }

    /**
     * Adds branch employee.
     * @param NewBranchEmployee the branch employee which will be added.
     */
    public void AddBranchEmployee(BranchEmployee NewBranchEmployee){
        this.BranchEmployees.addData(NewBranchEmployee);
    }

    /**
     * gets a branch employee.
     * @param index index of the branch employee which will be got.
     * @return a branch employee.
     */
    public BranchEmployee getBranchEmployee(int index){
        return this.BranchEmployees.getData(index);
    }

    /**
     * returns how many employees there are.
     * @return how many employees there are.
     */
    public int getBranchEmployeeNumber(){
        return BranchEmployees.getUsed();
    }
}