import DataStructureHW7_Q2.SkipListGTU;

import java.util.Random;

public class TestQ2 {
    public static void main(String[] args) {
        Random random = new Random();
        SkipListGTU<Integer> list = new SkipListGTU<>(4,2);

        list.add(100);
        list.add(50);
        list.add(150);
        list.add(125);
        list.add(25);
        list.add(15);
        list.add(10);
        list.add(-1);
        list.add(30);
        list.add(130);
        list.add(151);
        list.add(192);
        list.add(-34);
        list.add(123);
        list.add(152);
        list.add(-152);

        System.out.println(list);

    }
}
