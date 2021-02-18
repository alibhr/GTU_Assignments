import DataStructureHW5_Q2.ExpressionTree;

public class TestQ2 {
    public static void main(String[] args) {
        //Test-1
        ExpressionTree expTree1 = new ExpressionTree("+ + 10 * 5 15 20");
        ExpressionTree expTree2 = new ExpressionTree("10 5 15 * + 20 +");
        ExpressionTree expTree3 = new ExpressionTree("* + * 40 3 / 42 6 / - 67 37 + 2 0");
        ExpressionTree expTree4 = new ExpressionTree("40 3 * 42 6 / + 67 37 - 2 0 + / *");
        System.out.println("four different Expression tree object has been created.\n");

        //Test-2
        System.out.println("expTree1.toString() : " + expTree1.toString());
        System.out.println("expTree2.toString() : " + expTree2.toString());
        System.out.println("expTree3.toString() : " + expTree3.toString());
        System.out.println("expTree4.toString() : " + expTree4.toString());
        System.out.print("\n");

        //Test-3
        System.out.println("expTree1.toString2() : " + expTree1.toString2());
        System.out.println("expTree2.toString2() : " + expTree2.toString2());
        System.out.println("expTree3.toString2() : " + expTree3.toString2());
        System.out.println("expTree4.toString2() : " + expTree4.toString2());
        System.out.print("\n");

        //Test-4
        System.out.println("Evaluation of expTree1 : " + expTree1.eval());
        System.out.println("Evaluation of expTree2 : " + expTree2.eval());
        System.out.println("Evaluation of expTree3 : " + expTree3.eval());
        System.out.println("Evaluation of expTree4 : " + expTree4.eval());
    }
}