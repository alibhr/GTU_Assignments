package DataStructureHW5_Q2;

import java.util.Scanner;

/**
 * Implementation of ExpressionTree class of arithmetic operations.
 * @author Ali Bahar 171044066
 */
public class ExpressionTree extends BinaryTree<String>{

    /**
     * initialize the tree structure with the given expression string.
     * @param expression the given expression string.
     */
    public ExpressionTree(String expression){
        Scanner scanner = new Scanner(expression);;

        BinaryTree<String> exp = readBinaryTree(scanner);
        if(exp != null)
            this.root = exp.root;
        else
            root = null;
    }

    /**
     * creates an expression tree by reading both prefix and postfix expressions.
     * @param scan Scanner object that have prefix or postfix expression.
     * @return expression tree
     */
    public static BinaryTree<String> readBinaryTree(Scanner scan){
        if(!scan.hasNext())
            return null;
        String s = scan.next();
        StringBuilder sb = new StringBuilder();
        sb.append(s).append(" ");

        if(!isOperator(s)){
            while(scan.hasNext())
                sb.insert(0," ").insert(0,scan.next());
            return read1(new Scanner(sb.toString()));
        }
        else{
            return new BinaryTree<>(s,read(scan),read(scan));
        }
    }
    private static BinaryTree<String> read(Scanner scan){
        if(!scan.hasNext()){
            return null;
        }
        String data = scan.next();
        if(isOperator(data)){
            return new BinaryTree<>(data,
                    read(scan),
                    read(scan)
            );
        }
        else{
            return new BinaryTree<>(data,null,null);
        }
    }
    private static BinaryTree<String> read1(Scanner scan){
        if(!scan.hasNext()){
            return null;
        }
        String data = scan.next();
        if(isOperator(data)){

            BinaryTree<String> first = read1(scan);
            BinaryTree<String> second = read1(scan);
            return new BinaryTree<>(data,
                    second,
                    first
            );
        }
        else{
            return new BinaryTree<>(data,null,null);
        }
    }

    private static boolean isOperator(String data) {
        switch (data){
            case "+" :
            case "-" :
            case "/" :
            case "*" :
                return true;
        }
        return false;
    }

    /**
     * evaluates the expression.
     * @return the result of evaluation as double.
     */
    public double eval(){ return eval(this.root); }
    private double eval(Node<String> localRoot){
        if(!isOperator(localRoot.getData())){
            return Double.parseDouble(localRoot.getData());
        }
        else{
            return evaluate(localRoot.getData(),
                    eval(localRoot.getLeft()),
                    eval(localRoot.getRight())
            );
        }
    }
    private double evaluate(String operator,double operand1,double operand2){
        switch (operator){
            case "+":
                return operand1 + operand2;
            case "-":
                return operand1 - operand2;
            case "*":
                return operand1 * operand2;
            case "/":
                return operand1 / operand2;
            default:
                throw new NullPointerException("invalid operator!!!");
        }
    }

    /**
     * Returns a string representation of the tree(preOrderTraverse).
     * @return a string representation of the tree.
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        preOrderTraverse(this.root,0,sb);
        return sb.toString();
    }
    private void preOrderTraverse(Node<String> node,int depth,StringBuilder sb){
        if(node == null){
            return;
        }

        sb.append(node.toString()).append(" ");
        preOrderTraverse(node.left,depth+1,sb);
        preOrderTraverse(node.right,depth+1,sb);
    }

    /**
     * Returns a string representation of the tree(postOrderTraverse).
     * @return a string representation of the tree.
     */
    @Override
    public String toString2() {
        StringBuilder sb = new StringBuilder();
        postOrderTraverse(this.root,0,sb);
        return sb.toString();
    }
    private void postOrderTraverse(Node<String> node,int depth,StringBuilder sb){
        if(node == null){
            return;
        }

        postOrderTraverse(node.left,depth+1,sb);
        postOrderTraverse(node.right,depth+1,sb);
        sb.append(node.toString()).append(" ");
    }
}