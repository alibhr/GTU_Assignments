package GTUCargoAutomation;

import java.util.ArrayList;
import java.util.Scanner;

/**
 * Represents an admin.
 * Administrators manage the system.
 * @author Ali Bahar
 * @author 171044066
 */
public class Administrator extends User implements CanLogin{
    private static Scanner input = new Scanner(System.in);

    /**
     *Creates a new Admin with the specified name,surname,password and ID.
     * @param NewName Admin's Name.
     * @param NewSurname Admin's Surname.
     * @param NewPassword Admin's Password.
     * @param NewID Admins' ID.
     */
    public Administrator(String NewName,String NewSurname,String NewPassword,String NewID){
        super(NewName,NewSurname,NewPassword,NewID);
    }

    /**
     * Adding a new branches.
     * @param AllBranches The new branch is gonna be added to this ArrayList.
     */
    public void addBranch(ArrayList<Branch> AllBranches){
        if(AllBranches == null)
            throw new NullPointerException();
        System.out.print("Enter the name of new branch : ");
        String BranchName = input.next();

        boolean found = false;
        for(Branch aBranch : AllBranches){
            if(aBranch.getBranchName().equals(BranchName)){
                found = true;
            }
        }

        if(!found)
            AllBranches.add(new Branch(BranchName,this));
        else{
            System.out.println("This name has been already taken");
        }
    }

    /**
     * Removes a branch
     * @param AllBranches Branch will be removed from that ArrayList;
     */
    public void removeBranch(ArrayList<Branch> AllBranches){
        if(AllBranches == null)
            throw new NullPointerException();

        System.out.println("Enter The name of the branch to remove : ");
        String NameOfBranch = input.next();

        boolean found = false;
        for(int i=0;i<AllBranches.size();++i){
            if (AllBranches.get(i).getBranchName().equals(NameOfBranch)){
                AllBranches.remove(i);
                i=AllBranches.size();
                found = true;
            }
        }

        if(found){
            System.out.println("Removed");
        }
        else{
            System.out.println("couldn't Removed");
        }
    }


    /**
     * Adding a new Branch employee.
     * @param AllBranches Branch employee is gonna be added by finding the correct branch from this list.
     */
    public void addBranchEmployee(ArrayList<Branch> AllBranches){
        if(AllBranches == null)
            throw  new NullPointerException();
        System.out.print("Enter the name of the branch to be able to add a new branch employee. : ");
        String BranchName = input.next();
        Branch branch = null;
        for (Branch allBranch : AllBranches) {
            if (allBranch.getBranchName().equals(BranchName))
                branch = allBranch;
        }
        if(branch == null){
            System.out.println("There is no branch that has the entered name.");
        }
        else{
            System.out.print("Enter the name of the new branch employee : ");
            String NewName = input.next();

            System.out.print("Enter the surname of the new branch employee : ");
            String NewSurname = input.next();

            System.out.print("Enter the ID of the new branch employee : ");
            String NewID = input.next();

            System.out.print("Enter the password of the new branch employee : ");
            String NewPassword = input.next();

            boolean found = false;
            ArrayList<BranchEmployee> All = branch.getAllBranchEmployees();
            for(BranchEmployee aBranchEmployee : All){
                if(aBranchEmployee.getID().equals(NewID))
                    found = true;
            }
            if(!found)
                branch.getAllBranchEmployees().add(new BranchEmployee(NewName,NewSurname,NewPassword,NewID,branch));
            else{
                System.out.print("This ID has been already added.");
            }
        }
    }

    /**
     * Removes Branch Employee
     * @param AllBranches To find the branch employee to remove.
     */
    public void removeBranchEmployee(ArrayList<Branch> AllBranches){
        if(AllBranches == null){
            throw new NullPointerException();
        }
        System.out.println("Enter the Branch Employee ID : ");
        String ID = input.next();

        boolean found = false;
        for(int i=0 ; i<AllBranches.size() ; ++i){
            ArrayList<BranchEmployee> branchEmployees = AllBranches.get(i).getAllBranchEmployees();
            for(int j=0 ; j<branchEmployees.size() ; ++j){
                if(branchEmployees.get(j).getID().equals(ID)){
                    branchEmployees.remove(j);
                    j=branchEmployees.size();
                    i=AllBranches.size();
                    found = true;
                }
            }
        }
        if(!found){
            System.out.println("The branch employee couldn't be found.");
        }
        else{
            System.out.println("The branch employee has been removed.");
        }

    }

    private static boolean doesItContain(ArrayList<User> users,String ID){
        if(users == null)
            return false;

        for(int j=0 ; j<users.size() ; ++j){
            if(users.get(j).getID().equals(ID)){
                users.remove(j);
                j=users.size();
                return true;
            }
        }
        return false;
    }

    /**
     * adding a new Transportation employee.
     * @param AllBranches Transportation Employee is gonna be added by finding the correct branch from this list.
     */
    public void addTransportationPersonnel(ArrayList<Branch> AllBranches){
        if(AllBranches == null)
            throw  new NullPointerException();
        System.out.print("Enter the name of the branch to be able to add a new Transportation Personnel : ");
        String BranchName = input.next();
        Branch branch = null;
        for (Branch aBranch : AllBranches) {
            if (aBranch.getBranchName().equals(BranchName))
                branch = aBranch;
        }
        if(branch == null){
            System.out.println("There is no branch that has the entered name.");
        }
        else{
            System.out.print("Enter the name of the new  Transportation Personnel : ");
            String NewName = input.next();

            System.out.print("Enter the surname of the new Transportation Personnel : ");
            String NewSurname = input.next();

            System.out.print("Enter the ID of the new Transportation Personnel : ");
            String NewID = input.next();

            System.out.print("Enter the password of the new Transportation Personnel : ");
            String NewPassword = input.next();

            boolean found = false;
            ArrayList<TransportationPersonnel> All = branch.getAllTransportationPersonnel();
            for (TransportationPersonnel transportationPersonnel : All) {
                if (transportationPersonnel.getID().equals(NewID))
                    found = true;
            }

            if(!found)
                branch.getAllTransportationPersonnel().add(new TransportationPersonnel(NewName,NewSurname,NewPassword,NewID,branch));
            else{
                System.out.println("This ID has been already added.");
            }
        }

    }

    /**
     * Removes a Transportation personnel.
     * @param AllBranches ArrayList that personal removed from.   To find the Transportation personnel to remove.
     */
    public void removeTransportationPersonnel(ArrayList<Branch> AllBranches){
        if(AllBranches == null){
            throw new NullPointerException();
        }
        System.out.println("Enter the Transportation Personnel ID : ");
        String ID = input.next();

        boolean found = false;
        for(int i=0 ; i<AllBranches.size() ; ++i){
            ArrayList<TransportationPersonnel> transportationPersonnel = AllBranches.get(i).getAllTransportationPersonnel();
            for(int j=0 ; j<transportationPersonnel.size() ; ++j){
                if(transportationPersonnel.get(j).getID().equals(ID)){
                    transportationPersonnel.remove(j);
                    j=transportationPersonnel.size();
                    i=AllBranches.size();
                    found = true;
                }
            }
        }

        if(!found){
            System.out.println("The Transportation personnel couldn't be found.");
        }
        else{
            System.out.println("The Transportation personnel has been removed.");
        }
    }

    /**
     * adding a new admin.
     * @param AllAdmins The new Admin is gonna be added to this ArrayList.
     */
    public void addAdmin(ArrayList<Administrator> AllAdmins){
        if (AllAdmins == null)
            throw new NullPointerException();
        System.out.print("Enter the name of the new Admin : ");
        String NewName = input.next();

        System.out.print("Enter the surname of the new Admin : ");
        String NewSurname = input.next();

        System.out.print("Enter the ID of the new Admin : ");
        String ID = input.next();

        System.out.print("Enter the password of the new Admin : ");
        String NewPassword = input.next();

        boolean found = false;
        for (Administrator allAdmin : AllAdmins) {
            if (allAdmin.getID().equals(ID)) {
                found = true;
            }
        }
        if(!found)
            AllAdmins.add(new Administrator(NewName,NewSurname,NewPassword,ID));
        else{
            System.out.println("This ID has been already added.");
        }
    }


    /**
     * removes a admin.
     * @param AllAdmins removes a admin from this ArrayList.
     */
    public void removeAdmin(ArrayList<Administrator> AllAdmins){
        if(AllAdmins == null)
            throw new NullPointerException();

        System.out.println("Enter the ID of the admin to remove : ");
        String ID = input.next();

        boolean found = false;
        for(int i=0 ; i<AllAdmins.size() ; ++i){
            if(AllAdmins.get(i).getID().equals(ID)){
                AllAdmins.remove(i);
                i = AllAdmins.size();
                found = true;
            }
        }
        if(!found){
            System.out.println("The Admin couldn't found.");
        }
        else{
            System.out.println("The admin has been removed.");
        }
    }

    /**
     * longins to system.
     * @param Password compares this password and real password
     * @return if Password correct, this method will return true.
     */
    @Override
    public boolean login(String Password) {
        if(Password == null)
            throw new NullPointerException();
        if( ! Password.equals(this.getPassword())){
            System.out.println("invalid Admin password");
            return false;
        }
        return true;
    }

    /**
     * Says the name of the class.
     * @return name of the class.
     */
    @Override
    public String getClassName() {
        return "Administrator";
    }
}