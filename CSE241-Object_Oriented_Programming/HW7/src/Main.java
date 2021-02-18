import GTU_Board.*;

import java.io.File;
import java.io.IOException;
import java.util.Random;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        TestStatic();
        Test1D();
        Test2D();
    }

    public static void Test1D(){
        System.out.println("---------------------------Test1D---------------------------");
        BoardArray1D test1D = new BoardArray1D();

        test1D.readFromFile("readFromFile.txt");

        System.out.println("readFromFile : \n" + test1D);

        if(test1D.isSolved())
            System.out.println("This is a solved puzzle.");

        test1D.move('L');

        if(!test1D.isSolved())
            System.out.println("This is not a solved puzzle");

        for(int i=0;i<20;++i){
            moveRandom(test1D);
        }

        System.out.println("numberOfMoves : " + test1D.numberOfMoves());

        test1D.writeToFile("Test1D.txt");

        test1D.setsize(4,5);
        System.out.println("\n\nAfter set size : \n" + test1D);


        BoardArray1D test1DD = new BoardArray1D(test1D);
        if(test1D.equals(test1DD)) {
            System.out.println("they are equal");
        }
        System.out.println("-------------------------------------------------------------");
    }

    public static void Test2D(){
        System.out.println("---------------------------Test2D---------------------------");
        BoardArray2D test2D = new BoardArray2D();

        test2D.readFromFile("readFromFile.txt");

        System.out.println("readFromFile : \n" + test2D);

        if(test2D.isSolved())
            System.out.println("This is a solved puzzle.");

        test2D.move('L');

        if(!test2D.isSolved())
            System.out.println("This is not a solved puzzle");

        for(int i=0;i<20;++i){
            moveRandom(test2D);
        }

        System.out.println("numberOfMoves : " + test2D.numberOfMoves());

        test2D.writeToFile("Test2D.txt");

        test2D.setsize(4,5);
        System.out.println("\n\nAfter set size : \n" + test2D);

        BoardArray2D test1DD = new BoardArray2D(test2D);
        if(test2D.equals(test1DD)) {
            System.out.println("they are equal");
        }
        System.out.println("-------------------------------------------------------------");
    }

    public static void TestStatic(){
        System.out.println("-------------------------TestStataic-------------------------");
        BoardArray1D A1=new BoardArray1D(),A2=new BoardArray1D(),A3 = new BoardArray1D();
        BoardArray1D A4=new BoardArray1D(),A5=new BoardArray1D(),A6 = new BoardArray1D();
        BoardArray2D B1=new BoardArray2D(),B2=new BoardArray2D(),B3 = new BoardArray2D();
        BoardArray2D B4=new BoardArray2D(),B5=new BoardArray2D();

        AbstractBoard[] TestSequence = new AbstractBoard[]{A1, B1, A2, B2, A3, B3, A4, B4, A5, B5, A6};

        try{
            Scanner s = new Scanner(new File("path1/lastmoves.txt"));
            char m = 'x';
            String filename = "path1/element";
            for (int i = 0; i < 11; ++i) {
                m = s.next().charAt(0);
                filename = filename + (i + 1) + ".txt";
                TestSequence[i].readFromFile(filename);
                TestSequence[i].setLastMove(m);
                filename = "path1/element";
            }

            System.out.println("The sequence which will be tested");
            for(int i=0;i<TestSequence[0].numberOfBoard();++i){
                System.out.printf("%s",TestSequence[i]);
                System.out.println("Last move : " + TestSequence[i].lastMove());
                System.out.println("x : " + TestSequence[i].getEmptyCellX() + " ||| y : " + TestSequence[i].getEmptyCellY() + '\n');
            }
            System.out.println("\n\n");
            if(AbstractBoard.isit_ValidSequence(TestSequence))
                System.out.println("Valid sequence");
            else
                System.out.println("invalid sequence");

            System.out.println("Number of Board : " + ((BoardArray1D)TestSequence[0]).numberOfBoard());

        }catch (IOException e){
            e.printStackTrace();
        }
        System.out.println("------------------------------------------------------------");
    }

    public static char moveRandom(AbstractBoard o){
        Random rand = new Random();

        int u = rand.nextInt() % 4;

        if(u == 0){         o.move('R');    return 'R'; }
        else if (u == 1){   o.move('L');    return 'L'; }
        else if (u == 2){   o.move('U');    return 'U'; }
        else if (u == 3){   o.move('D');    return 'D'; }

        return '0';
    }
}
