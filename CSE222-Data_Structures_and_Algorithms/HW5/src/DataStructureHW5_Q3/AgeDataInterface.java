package DataStructureHW5_Q3;

/**
 * for the class that represents AgeData class.
 * @param <E> type of the data.
 * @author Ali Bahar 171044066
 */
public interface AgeDataInterface<E> extends Comparable<E> {
    /**
     * returns the age.
     * @return the age.
     */
    int getAge();

    /**
     * returns the number of people.
     * @return the number of people.
     */
    int getNumberOfPeople();

    /**
     * sets the age to given age.
     * @param age the given age.
     */
    void setAge(int age);

    /**
     * sets the number of the people to given number of people.
     * @param numberOfPeople the given number of the people.
     */
    void setNumberOfPeople(int numberOfPeople);

    /**
     * decreases the number of people by one.
     */
    void decrementNumberOfPeople();
}
