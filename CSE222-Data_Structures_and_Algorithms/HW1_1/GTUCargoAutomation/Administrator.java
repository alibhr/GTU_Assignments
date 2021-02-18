package GTUCargoAutomation;

import java.util.Scanner;

/**
 * Represents an admin.
 * Administrators manage the system.
 * @author Ali Bahar
 * @author 171044066
 */
public class Administrator extends User{
	
	private static Scanner in = new Scanner(System.in);

    private GTUArray<Branch> Branches;

    /**
     *Creates a new Admin with the specified name,surname,password and ID.
     * @param NewName Admin's Name.
     * @param NewSurname Admin's Surname.
     * @param NewPassword Admin's Password.
     * @param NewID Admins' ID.
     */
    public Administrator(String NewName,String NewSurname,String NewPassword,String NewID){
        super(NewName,NewSurname,NewPassword,NewID);
        Branches = new GTUArray<>();
    }

    /**
     * Creates a new admin with default name,surname,password and ID.
     */
    public Administrator(){
        this("AdminName","AdminSurname","AdminPassword","AdminID");
    }

    /**
     * creates a string that have Admin name,surname and ID.
     * @return a string that have Admin name,surname and ID.
     */
    @Override
    public String toString() {
        return "Admin name : " + super.getName() +
                "\nAdmin Surname : " + super.getSurname() +
                "\nAdmin ID : " + super.getID() +
                "\n";
    }

    /**
     * creates a hashcode.
     * @return hashcode from super class.
     */
    @Override
    public int hashCode() {
        return super.hashCode();
    }

    /**
     * Adding a new branches.
     * @param AllBranchEmployee The new branch is gonna be added to this GTUArray.
     */
    public void addBranch(GTUArray<BranchEmployee>AllBranchEmployee){

        System.out.print("Enter the name of new branch : ");
        String NewName = in.next();

        Branches.addData(new Branch(NewName,AllBranchEmployee));

    }

    /**
     * adding a new Branch employee.
     * @param AllBranchEmployees The new branch employee is gonna be added to this GTUArray.
     * @param AllCustomers to create a new Branch employee.
     */
    public void addBranchEmployee(GTUArray<BranchEmployee> AllBranchEmployees,GTUArray<Customer> AllCustomers){

        System.out.print("Enter the name of the new branch employee : ");
        String NewName = in.next();

        System.out.print("Enter the surname of the new branch employee : ");
        String NewSurname = in.next();

        System.out.print("Enter the ID of the new branch employee : ");
        String ID = in.next();

        System.out.print("Enter the password of the new branch employee : ");
        String NewPassword = in.next();

        BranchEmployee NewBranchEmployee = new BranchEmployee(new User(NewName,NewSurname,NewPassword,ID),AllCustomers);

        AllBranchEmployees.addData(NewBranchEmployee);

    }

    /**
     * adding a new Transportation employee.
     * @param TransportEmployees The new Transport employee is gonna be added to this GTUArray.
     * @param AllCustomers to create a new Transportation employee.
     */
    public void addTransportationPersonnel(GTUArray<TransportationPersonnel> TransportEmployees,GTUArray<Customer> AllCustomers){

        System.out.print("Enter the name of the new Transportation personnel  : ");
        String NewName = in.next();

        System.out.print("Enter the surname of the new Transportation personnel : ");
        String NewSurname = in.next();

        System.out.print("Enter the ID of the new Transportation personnel : ");
        String ID = in.next();

        System.out.print("Enter the password of the new Transportation personnel : ");
        String NewPassword = in.next();

        TransportEmployees.addData(new TransportationPersonnel(NewName,NewSurname,NewPassword,ID,AllCustomers));

    }

    /**
     * adding a new admin.
     * @param AllAdmins The new Admin is gonna be added to this GTUArray
     * @param AllBranches to create a new Admin.
     */
    public void addAdmin(GTUArray<Administrator> AllAdmins,GTUArray<Branch> AllBranches){

        System.out.print("Enter the name of the new Admin : ");
        String NewName = in.next();

        System.out.print("Enter the surname of the new Admin : ");
        String NewSurname = in.next();

        System.out.print("Enter the ID of the new Admin : ");
        String ID = in.next();

        System.out.print("Enter the password of the new Admin : ");
        String NewPassword = in.next();

        Administrator newAdmin = new Administrator(NewName,NewSurname,NewPassword,ID);
        newAdmin.setBranches(AllBranches);

        AllAdmins.addData(newAdmin);
    }

    /**
     * removes a branch.
     */
    public void removeBranch(){

        System.out.print("Branch Name : ");
        String name = in.next();

        int index = findBranchByName(name);
        if(index != -1)
            Branches.eraseData(index);
        else{
            System.out.println("this name couldn't be found");
        }
    }

    /**
     * removes a branch employee.
     * @param AllBranchEmployees removes a branch employee from this parameter.
     */
    public void removeBranchEmployee(GTUArray<BranchEmployee> AllBranchEmployees){

        System.out.print("Branch Employee ID : ");
        String ID = in.next();

        int index = -1;
        for(int i=0 ; i<AllBranchEmployees.getUsed() ; ++i)
            if(AllBranchEmployees.getData(i).getID().equals(ID))
                index = i;

        if(index != -1)
            AllBranchEmployees.eraseData(index);
        else
            System.out.println("The branch employee couldn't be found");
    }

    /**
     * removes a transportation personnel.
     * @param AllTransportationPersonnel removes a transportation personnel from this parameter
     */
    public void removeTransportationPersonnel(GTUArray<TransportationPersonnel> AllTransportationPersonnel){

        System.out.print("Transportation personnel ID : ");
        String ID = in.next();

        int index = -1;
        for(int i=0 ; i<AllTransportationPersonnel.getUsed() ; ++i)
            if(AllTransportationPersonnel.getData(i).getID().equals(ID))
                index = i;

        if(index != -1)
            AllTransportationPersonnel.eraseData(index);
        else
            System.out.println("The Transportation personnel couldn't be found");
    }

    /**
     * removes a admin.
     * @param AllAdmins removes a admin from this parameter.
     */
    public void removeAdmin(GTUArray<Administrator> AllAdmins){

        System.out.print("Admin personnel ID : ");
        String ID = in.next();

        int index = -1;
        for(int i=0 ; i<AllAdmins.getUsed() ; ++i)
            if(AllAdmins.getData(i).getID().equals(ID))
                index = i;

        if(index != -1)
            AllAdmins.eraseData(index);
        else
            System.out.println("The Admin couldn't be found");

    }

    /**
     * get the all branches.
     * @return the All Branches as GTUArray.
     */
    public GTUArray<Branch> getBranches(){
        return Branches;
    }

    /**
     * changes the branches.
     * @param NewBranches a GTUArray which contains the new branches.
     */
    public void setBranches(GTUArray<Branch> NewBranches){
        Branches = NewBranches;
    }

    /**
     * search a customer with their ID.
     * @param BranchName Branch Name which will be searched.
     * @return if the branch can be found returns index.if the branch can't be found return -1.
     */
    public int findBranchByName(String BranchName){
        for(int i=0 ; i<Branches.getUsed() ; ++i){
            if(Branches.getData(i).getBranchName().equals(BranchName))
                return i;
        }
        return -1;
    }
}