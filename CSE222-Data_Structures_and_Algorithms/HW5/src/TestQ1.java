import DataStructureHW5_Q1.FileSystemTree;

public class TestQ1 {
    public static void main(String[] args) {

        System.out.println("The tree is created to be tested.\n\n");
        //Test Q1.0
        FileSystemTree myFileSystem = new FileSystemTree("root");
            myFileSystem.addDir("root/dev");
                myFileSystem.addDir("root/dev/pts");
                    myFileSystem.addFile("root/dev/pts/file1.doc");
                    myFileSystem.addFile("root/dev/pts/file2.doc");
                myFileSystem.addDir("root/dev/fd");
                    myFileSystem.addFile("root/dev/fd/file1.c");
                    myFileSystem.addFile("root/dev/fd/file2.c");
                myFileSystem.addFile("root/dev/ttyS1.i");
                myFileSystem.addFile("root/dev/ttyS2.i");
                myFileSystem.addFile("root/dev/ttyS3.i");
            myFileSystem.addDir("root/home");
                myFileSystem.addDir("root/home/Ali");
                    myFileSystem.addDir("root/home/Ali/Desktop");
                        myFileSystem.addFile("root/home/Ali/Desktop/file0.desktop");
                        myFileSystem.addFile("root/home/Ali/Desktop/file1.desktop");
                        myFileSystem.addFile("root/home/Ali/Desktop/file2.desktop");
            myFileSystem.addDir("root/mnt");{}
                myFileSystem.addDir("root/mnt/c");
                    myFileSystem.addDir("root/mnt/c/ProgramFiles");
                        myFileSystem.addFile("root/mnt/c/ProgramFiles/programFile1.txt");
                        myFileSystem.addFile("root/mnt/c/ProgramFiles/programFile2.txt");
                        myFileSystem.addFile("root/mnt/c/ProgramFiles/programFile3.txt");
                        myFileSystem.addFile("root/mnt/c/ProgramFiles/programFile4.txt");


        //Test Q1.1
        System.out.println("The tree after created : ");
        myFileSystem.printFileSystem();
        System.out.print("\n\n");

        //Test Q1.2
        System.out.println("try to some invalid input for addFile and addDir methods.");
        myFileSystem.addFile("invalidROOT/mnt/c/ProgramFiles/programFile1.txt");
        myFileSystem.addDir("root/mnt/c/ProgramFiles/programFile3.txt/INVALID");
        myFileSystem.addFile("root/mnt/INVALID/ProgramFiles/programFile1.txt");
        System.out.println("After some invalid inputs : ");
        myFileSystem.printFileSystem();
        System.out.print("\n\n");

        //TestQ1.3
        System.out.println("The search method Tested (theWord = \"Pro\")");
        myFileSystem.search("File");
        System.out.print("\n");
        System.out.println("The search method Tested (theWord = \"A\")");
        myFileSystem.search("A");
        System.out.print("\n");
        System.out.println("The search method Tested (theWord = \"a\")");
        myFileSystem.search("a");
        System.out.print("\n");
        System.out.println("The search method Tested (theWord = \".\")");
        myFileSystem.search(".");
        System.out.print("\n\n");

        //TestQ1.4
        System.out.println("The search method Tested with invalid parameter(theWord = \"INVALID\")");
        myFileSystem.search("INVALID");
        System.out.println("The search method Tested with invalid parameter(theWord = \"ttys4\")");
        myFileSystem.search("ttys4");
        System.out.print("\n\n");

        //TestQ1.5
        System.out.println("Some files and directories has been removed :");
        System.out.println("try to remove root/dev/pts/file1.doc");
        myFileSystem.remove("root/dev/pts/file1.doc");
        System.out.println("try to remove root/dev/pts/file2.doc");
        myFileSystem.remove("root/dev/pts/file2.doc");
        System.out.println("try to remove root/dev/pts");
        myFileSystem.remove("root/dev/pts");
        System.out.println("After remove operation : ");
        myFileSystem.printFileSystem();
        System.out.print("\n\n");

        //TestQ1.6
        System.out.println("try to remove root/home/Ali");
        myFileSystem.remove("root/home/Ali");
        System.out.println("try to remove root/mnt/c");
        myFileSystem.remove("root/mnt/c");
        System.out.println("After remove operation : ");
        myFileSystem.printFileSystem();
        System.out.print("\n\n");

        //TestQ1.7
        System.out.println("try to remove root/INVALID");
        myFileSystem.remove("root/INVALID");
        System.out.println("try to remove root/home/Ali/Desktop/file0");
        myFileSystem.remove("root/home/Ali/Desktop/file0");
        System.out.print("\n\n");

        //TestQ1.8
        System.out.println("The tree after Test:");
        myFileSystem.printFileSystem();
        System.out.print("\n\n");
    }
}