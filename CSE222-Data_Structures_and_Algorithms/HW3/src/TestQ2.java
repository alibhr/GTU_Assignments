import GTU_DataStructure_HW3_Q2.*;

import java.io.FileWriter;
import java.util.Random;
import java.io.IOException;
import java.util.logging.FileHandler;
import java.util.logging.Logger;
import java.util.logging.SimpleFormatter;

public class TestQ2 {
    public static void main(String[] args) {

        //ArrayList
        SimpleTextEditor editor40char = new SimpleTextEditor("Char40.txt");
        //SimpleTextEditor editor200char = new SimpleTextEditor("Char200.txt");
        //SimpleTextEditor editor600char = new SimpleTextEditor("Char600.txt");

        //LinkedList
        SimpleTextEditor _editor40char_ = new SimpleTextEditor("Char_40.txt",true);
        //SimpleTextEditor _editor200char_ = new SimpleTextEditor("Char_200.txt",true);
        //SimpleTextEditor _editor600char_ = new SimpleTextEditor("Char_600.txt",true);

        try{

            Logger logger = Logger.getLogger("LogFile");
            FileHandler fh = new FileHandler("LogFile.log");
            logger.addHandler(fh);
            SimpleFormatter formatter = new SimpleFormatter();
            fh.setFormatter(formatter);

            FileWriter fw = new FileWriter("runningTimes.txt");
            fw.write("By using ArrayList\n");
            fw.write("Without iterator:\tadd\t\t\tread\t\t\tfind\t\t\treplace\n");

            test(editor40char,40,logger,fw);
            //test(editor200char,200,logger,fw);
            //test(editor600char,600,logger,fw);

            editor40char.deleteAllChar();
            //editor200char.deleteAllChar();
            //editor600char.deleteAllChar();

            fw.write("\n\nWith iterator\t:\tadd\t\t\tread\t\t\tfind\t\t\treplace\n");
            testWithIter(editor40char,40,logger,fw);
            //testWithIter(editor200char,200,logger,fw);
            //testWithIter(editor600char,600,logger,fw);

            fw.write("\n\n");

            fw.write("By using LinkedList\n");
            fw.write("Without iterator:\tadd\t\t\tread\t\t\tfind\t\t\treplace\n");

            test(_editor40char_,40,logger,fw);
            //test(_editor200char_,200,logger,fw);
            //test(_editor600char_,600,logger,fw);

            _editor40char_.deleteAllChar();
            //_editor200char_.deleteAllChar();
            //_editor600char_.deleteAllChar();

            fw.write("\n\nWith iterator\t:\tadd\t\t\tread\t\t\tfind\t\t\treplace\n");
            testWithIter(_editor40char_,40,logger,fw);
            //testWithIter(_editor200char_,200,logger,fw);
            //testWithIter(_editor600char_,600,logger,fw);

            fw.close();

            SimpleTextEditor log = new SimpleTextEditor("runningTimes.txt");
            log.read();
            System.out.println(log);

            System.out.println("\nEach method of the SimpleTextEditor class has been tested.\n" +
                    "Readable log file of the test has been created .");

        }catch (IOException e){
            e.printStackTrace();
        }

    }

    private static void test(SimpleTextEditor editor,int charNumber,Logger logger,FileWriter fw)throws IOException{
        long startTime = System.currentTimeMillis();
        testAdd(editor,charNumber);
        long time = (System.currentTimeMillis() - startTime);
        logger.info(charNumber + " character add method without iterator :" + time + "ms");
        fw.write(charNumber + " character\t:\t" + time + "ms\t\t");

        startTime = System.nanoTime();
        editor.read();
        time = (System.nanoTime() - startTime);
        logger.info(charNumber + " character read method without iterator :" + time + "ns");
        fw.write(time + "ns\t\t");

        startTime = System.nanoTime();
        int index = editor.find("toFind");
        time = (System.nanoTime() - startTime);
        logger.info(charNumber + " character find method without iterator :" + time + "ns");
        fw.write(time + "ns\t\t");

        System.out.println("Before replace:\n"+editor);

        startTime = System.nanoTime();
        editor.replace(' ','.');
        time = (System.nanoTime() - startTime);
        logger.info(charNumber + " character replace method without iterator :" + time + "ns\n");
        fw.write(time + "ns\n");

        System.out.println("add method worked\n" +
                "read method worked\n" +
                "the string(toFind) found at " + index +"th \n" +
                "replace method turned all ' ' to '.' \n" +
                "after replace : \n" + editor + "\n\n");
    }

    private static void testWithIter(SimpleTextEditor editor, int charNumber,Logger logger,FileWriter fw) throws IOException {
        long startTime = System.currentTimeMillis();
        testAddWithIter(editor,charNumber);
        long time = (System.currentTimeMillis() - startTime);
        logger.info(charNumber + " character add method with iterator:" + time + "ms");
        fw.write(charNumber + " character\t:\t" + time + "ms\t\t");

        startTime = System.nanoTime();
        editor.readWithIter();
        time = (System.nanoTime() - startTime);
        logger.info(charNumber + " character read method with iterator:" + time + "ns");
        fw.write(time + "ns\t\t");

        startTime = System.nanoTime();
        int index = editor.findWithIter("toFind");
        time = (System.nanoTime() - startTime);
        logger.info(charNumber + " character find method with iterator:"+ time + "ns");
        fw.write(time + "ns\t\t");

        System.out.println("Before replace:\n"+editor);

        startTime = System.nanoTime();
        editor.replaceWithIter(' ','.');
        time = (System.nanoTime() - startTime);
        logger.info(charNumber + " character replace method with iterator:"+ time + "ns\n");
        fw.write(time + "ns\n");

        System.out.println("add method worked\n" +
                "read method worked\n" +
                "the string(toFind) found at " + index +"th \n" +
                "replace method turned all ' ' to '.' \n" +
                "after replace : \n" + editor + "\n\n");
    }

    private static void testAdd(SimpleTextEditor editor,int charNumber) throws IOException {
        Random rand = new Random();
        int index = 0;

        for(int j=0 ; j<charNumber/40 ; ++j) {
            for (int i = 0; i < 10; ++i) {
                editor.add(index, " ");
                ++index;
            }
            for (int i = 0; i < 29; ++i) {
                char randomChar = (char) (rand.nextInt(26) + 'a');
                editor.add(index, Character.toString(randomChar));
                ++index;
            }
            editor.add(index,"\n");
            ++index;
        }

        editor.add(index,"toFind");
    }

    private static void testAddWithIter(SimpleTextEditor editor,int charNumber) throws IOException {
        Random rand = new Random();
        int index = 0;

        for(int j=0 ; j<charNumber/40 ; ++j) {
            for (int i = 0; i < 10; ++i) {
                editor.addWithIter(index, " ");
                ++index;
            }
            for (int i = 0; i < 29; ++i) {
                char randomChar = (char) (rand.nextInt(26) + 'a');
                editor.addWithIter(index, Character.toString(randomChar));
                ++index;
            }
            editor.addWithIter(index,"\n");
            ++index;
        }

        editor.addWithIter(index,"toFind");
    }
}