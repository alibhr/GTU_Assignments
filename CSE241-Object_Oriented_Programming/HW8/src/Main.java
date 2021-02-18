import _GTU__HW_8_.*;

import javax.naming.SizeLimitExceededException;
@SuppressWarnings("unchecked")
public class Main {
    public static void main(String[] args) {

        try{

            GTUVector<String> TestVector = new GTUVector<String>();
            TestVector.insert("AAA");
            TestVector.insert("BBB");
            GTUIterator<String> it = TestVector.insert("CCC");
            TestVector.insert("DDD");
            TestVector.insert("EEE");

            TestVector.insert(it,"FFF");

            GTUIterator<String> iterator = TestVector.iterator();

            System.out.println("--------hasNext(),next()--------");
            while(iterator.hasNext())
                System.out.printf("%s ",iterator.next());
            System.out.printf("\n");


            TestVector.erase(it);
            TestVector.erase(it);
            TestVector.erase(it);
            iterator = TestVector.iterator();
            System.out.println("--------erase(iterator)--------");
            while(iterator.hasNext())
                System.out.printf("%s ",iterator.next());
            System.out.printf("\n");

            GTUIterator<String> it1 = TestVector.insert("GGG");
            TestVector.insert("FFF");
            GTUIterator<String> it2 = TestVector.insert("HHH");
            TestVector.insert("III");
            iterator = TestVector.iterator();
            System.out.println("--------insert()--------");
            while(iterator.hasNext())
                System.out.printf("%s ",iterator.next());
            System.out.printf("\n");


            TestVector.erase(it1,it2);
            iterator = TestVector.iterator();
            System.out.println("--------erase(iterator,iterator)--------");
            while(iterator.hasNext())
                System.out.printf("%s ",iterator.next());
            System.out.printf("\n");

            System.out.println("--------empty()--------");
            while(!TestVector.empty()){
                System.out.println(TestVector);
                TestVector.erase(iterator);
            }

            System.out.println("--------clear()--------");
            TestVector.insert("AAA");
            TestVector.insert("BBB");
            TestVector.insert("CCC");
            TestVector.insert("DDD");
            TestVector.insert("EEE");
            TestVector.clear();
            iterator = TestVector.iterator();
            if(!iterator.hasNext())
                System.out.println("Empty");

            System.out.println("--------contains(object)--------");
            TestVector.insert("AAA");
            TestVector.insert("BBB");
            GTUIterator<String> temp = TestVector.insert("CCC");
            TestVector.insert("DDD");
            TestVector.insert("EEE");
            System.out.println("TestVector : "+TestVector);
            if(TestVector.contains("AAA"))
                System.out.println("TestVector contains AAA ");
            else
                System.out.println("TestVector doesn't contains AAA ");

            if(TestVector.contains("TTT"))
                System.out.println("TestVector contains TTT ");
            else
                System.out.println("TestVector doesn't contain TTT ");

            System.out.println("--------clone()--------");
            GTUVector<String> TestVectorClone = (GTUVector<String>) TestVector.clone();
            iterator = TestVectorClone.iterator();
            TestVectorClone.erase(iterator);
            TestVectorClone.erase(iterator);
            iterator = TestVector.iterator();
            TestVector.erase(iterator);
            System.out.println("After erase");
            System.out.println("TestVector : " + TestVector);
            System.out.println("TestVectorClone : " + TestVectorClone);
            System.out.println("TestVector : " + TestVector);
        }catch (CloneNotSupportedException | SizeLimitExceededException
                | IllegalArgumentException | NullPointerException e){
            e.printStackTrace();
        }


        try{
            GTUSet<String> TestSet = new GTUSet<String>();
            TestSet.insert("A");
            TestSet.insert("B");
            GTUIterator<String> it = TestSet.insert("C");
            TestSet.insert("D");
            TestSet.insert("E");

            TestSet.insert(it,"F");

            GTUIterator<String> iterator = TestSet.iterator();

            System.out.println("--------hasNext(),next()--------");
            while(iterator.hasNext())
                System.out.printf("%s ",iterator.next());
            System.out.printf("\n");


            TestSet.erase(it);
            TestSet.erase(it);
            TestSet.erase(it);
            iterator = TestSet.iterator();
            System.out.println("--------erase(iterator)--------");
            while(iterator.hasNext())
                System.out.printf("%s ",iterator.next());
            System.out.printf("\n");

            GTUIterator<String> it1 = TestSet.insert("G");
            TestSet.insert("F");
            GTUIterator<String> it2 = TestSet.insert("H");
            TestSet.insert("I");
            iterator = TestSet.iterator();
            System.out.println("--------insert()--------");
            while(iterator.hasNext())
                System.out.printf("%s ",iterator.next());
            System.out.printf("\n");


            TestSet.erase(it1,it2);
            iterator = TestSet.iterator();
            System.out.println("--------erase(iterator,iterator)--------");
            while(iterator.hasNext())
                System.out.printf("%s ",iterator.next());
            System.out.printf("\n");

            System.out.println("--------empty()--------");
            while(!TestSet.empty()){
                System.out.println(TestSet);
                TestSet.erase(iterator);
            }

            System.out.println("--------clear()--------");
            TestSet.insert("A");
            TestSet.insert("B");
            TestSet.insert("C");
            TestSet.insert("D");
            TestSet.insert("E");
            TestSet.clear();
            iterator = TestSet.iterator();
            if(!iterator.hasNext())
                System.out.println("Empty");

            System.out.println("--------contains(object)--------");
            TestSet.insert("A");
            TestSet.insert("B");
            GTUIterator<String> temp = TestSet.insert("C");
            TestSet.insert("D");
            TestSet.insert("E");
            System.out.println("TestVector : "+TestSet);
            if(TestSet.contains("A"))
                System.out.println("TestVector contains A ");
            else
                System.out.println("TestVector doesn't contains A ");

            if(TestSet.contains("T"))
                System.out.println("TestVector contains T ");
            else
                System.out.println("TestVector doesn't contain T ");

            System.out.println("--------clone()--------");
            GTUVector<String> TestVectorClone = (GTUVector<String>) TestSet.clone();
            iterator = TestVectorClone.iterator();
            TestVectorClone.erase(iterator);
            TestVectorClone.erase(iterator);
            iterator = TestSet.iterator();
            TestSet.erase(iterator);
            System.out.println("After erase");
            System.out.println("TestVector : " + TestSet);
            System.out.println("TestVectorClone : " + TestVectorClone);
            System.out.println("TestVector : " + TestSet);
        }catch (CloneNotSupportedException | SizeLimitExceededException
                | IllegalArgumentException | NullPointerException e){
            e.printStackTrace();
        }
    }
}
