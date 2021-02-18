package DataStructureHW5_Q4;

import DataStructureHW5_Q3.AgeData;
import java.util.Comparator;

/**
 * Comparator class for AgeData. Compares the number of people of the objects.
 * @author Ali Bahar 171044066
 */
public class compareWithNumberOfPeople implements Comparator<AgeData> {

    /**
     * Compares two AgeData.
     * @param o1 first object to e compared.
     * @param o2 other object to e compared.
     * @return subtraction of the number of people of objects.
     */
    @Override
    public int compare(AgeData o1, AgeData o2) {
        return o1.getNumberOfPeople() - o2.getNumberOfPeople();
    }
}