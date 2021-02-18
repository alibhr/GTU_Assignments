package DataStructureHW5_Q3;

/**
 * to handle both age and number of people at that age values.
 * @author Ali Bahar 171044066
 */
public class AgeData implements AgeDataInterface<AgeData>{

    /**
     * the age of the people.
     */
    private int age;

    /**
     * the number of people at that age values.
     */
    private int numberOfPeople;

    /**
     * Constructs a new age data object with given age and number of people.
     * @param age the age of the people.
     * @param numberOfPeople the number of people at that age values.
     */
    public AgeData(int age,int numberOfPeople){
        this.age = age;
        this.numberOfPeople = numberOfPeople;
    }

    /**
     * Constructs a new age data object with given age. number of people will be 1.
     * @param age the age of the people.
     */
    public AgeData(int age){ this(age,1); }

    /**
     * Constructs a new age data object with given AgeData object.
     * @param o the AgeData object.
     */
    public AgeData(AgeData o){ this(o.age,o.numberOfPeople); }

    /**
     * returns the age.
     * @return the age.
     */
    public int getAge() { return age; }

    /**
     * returns number of the people.
     * @return number of the people.
     */
    public int getNumberOfPeople() { return numberOfPeople; }

    /**
     * sets the age to given age.
     * @param age the given age.
     */
    public void setAge(int age) { this.age = age; }

    /**
     * sets the number of the people to given number.
     * @param numberOfPeople the given new number.
     */
    public void setNumberOfPeople(int numberOfPeople) { this.numberOfPeople = numberOfPeople; }

    /**
     * decrease by one the value of the number of the people.
     */
    public void decrementNumberOfPeople(){ --numberOfPeople; }

    /**
     * compares two AgeData object by considering the age values.
     * @param o the other AgeData object to compare.
     * @return returns 0 if the objects are equal, returns negative if age of the this object smaller than age of the other object.
     */
    @Override
    public int compareTo(AgeData o) { return this.age - o.age; }

    /**
     * returns string representation of the node.
     * @return string representation of the node.
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(age).append(" - ").append(numberOfPeople);
        return sb.toString();
    }
}