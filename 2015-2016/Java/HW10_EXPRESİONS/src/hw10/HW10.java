/* HW9_SAHIN_EGILMEZ_131044059
 * 
 * Author: sahin
 *
 * Created on 23 Aralık 2015 Çarşamba, 21:58
 */
package hw10;

import java.util.*;

/**
 *
 * @author sahin
 */
public class HW10 {

    //This class represent the one of operators(+,-,*,/)
    public static class Operator {

        private char operator;//take operator

        public Operator(char ch) {//the constructor
            if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
                this.operator = ch;
            }
        }

        //function perform operator's opertion
        public double operation(double a, double b) {
            if (this.operator == '+') {
                return (a + b);
            } else if (this.operator == '-') {
                return (a - b);
            } else if (this.operator == '*') {
                return (a * b);
            } else if (this.operator == '/') {
                return (a / b);
            } else {
                System.out.println("Wrong operator");
                return 0;
            }

        }

        //override equals method
        public boolean equals(Object other) {
            if (other == null) {
                return false;
            }
            if (other == this) {
                return true;
            }
            if (!(other instanceof Operator)) {
                return false;
            }
            Operator op = (Operator) other;
            return this.operator == op.operator;
        }

        //override toString method
        public String toString() {
            return "" + (this.operator);
        }
    }

    //This class represent the each operand 
    public static class Operand {

        private double operand;//take operand

        public Operand(double x) {//constructor
            this.operand = x;
        }

        public void setOperand(int x) {//setter of operand
            this.operand = x;
        }

        public double getOperand() {//getter of operand
            return this.operand;
        }

        //override equals method
        public boolean equals(Object other) {
            if (other == null) {
                return false;
            }
            if (other == this) {
                return true;
            }
            if (!(other instanceof Operand)) {
                return false;
            }

            Operand op = (Operand) other;
            return this.operand == op.operand;
        }

        //override toString method
        public String toString() {
            return "" + (this.operand);
        }
    }

    //This class represent the paranthesis
    public static class Paranthesis {

        private char Paranthesis;//take paranthesis

        public Paranthesis(char ch) {//constructor
            this.Paranthesis = ch;
        }

        public void setParanthesis(char ch) {//setter paranthesis
            this.Paranthesis = ch;
        }

        public char getParanthesis() {//getter of paranthesis
            return this.Paranthesis;
        }

        //override equals method
        public boolean equals(Object other) {
            if (other == null) {
                return false;
            }
            if (other == this) {
                return true;
            }
            if (!(other instanceof Paranthesis)) {
                return false;
            }
            Paranthesis p;
            p = (Paranthesis) other;
            return this.Paranthesis == p.Paranthesis;
        }

        //override toString method
        public String toString() {
            return "" + (this.Paranthesis);
        }
    }

    //this class represent expressions operation
    public static class Expression {

        private final ArrayList expressions;//take all expressions class

        public Expression() {//constructor
            this.expressions = new ArrayList();
        }

        //method perform the scan input and take for expression's Array.Then
        //call evaluate method and return result.
        public void play() {
            System.out.println("Enter your expression, after each operator or "
                    + "operand press enter, to end the expression press =");
            boolean finish = false, turnInt = true, turnChar = true;
            int unClosedParanthesis = 0;
            String str;
            Scanner input = new Scanner(System.in);
            while (finish != true) {

                if (turnInt == true) {
                    System.out.println("Enter your expression element ");
                    str = input.next();
                    if (str.charAt(0) == '(') {
                        unClosedParanthesis++;
                        Paranthesis p = new Paranthesis(str.charAt(0));
                        this.expressions.add(p);
                        turnChar = false;
                    } else {
                        try {
                            Operand operand = new Operand((double) Double.parseDouble(str));
                            this.expressions.add(operand);
                            turnChar = true;
                        } catch (NumberFormatException error) {
                            System.out.println("Please enter just number");
                            turnChar = false;
                        }
                    }
                }
                if (turnChar == true) {
                    System.out.println("Enter your expression element ");
                    do {
                        str = input.next();
                        if (str.charAt(0) == '=') {
                            if (unClosedParanthesis != 0) {
                                System.out.println("Please close last Paranthesis");
                            } else {
                                finish = true;
                                System.out.println("Result = "
                                        + this.evaluate(this.expressions));
                                break;
                            }
                        } else if ((str.charAt(0) == '+' || str.charAt(0) == '-'
                                || str.charAt(0) == '*' || str.charAt(0) == '/')
                                && str.length() == 1) {
                            System.out.println("girdi");
                            Operator operator = new Operator(str.charAt(0));
                            this.expressions.add(operator);
                            turnInt = true;
                            break;
                        } else if (str.charAt(0) == ')') {
                            unClosedParanthesis--;
                            Paranthesis paranthesis = new Paranthesis(str.charAt(0));
                            this.expressions.add(paranthesis);
                            turnInt = false;
                            break;
                        } else {
                            System.out.println("Please enter one of + , - , * , / "
                                    + "( , ) , = operators");
                        }
                    } while ((str.charAt(0) != '+' || str.charAt(0) != '-'
                            || str.charAt(0) != '*' || str.charAt(0) != '/'
                            || str.charAt(0) != '(' || str.charAt(0) != ')')
                            && str.length() != 1);
                }
            }
        }

        //this method perform all expression's operation and return result
        public double evaluate(ArrayList array) {
            ArrayList arr = (ArrayList) array.clone();
            double result = 0.0;
            boolean rec = false;
            ArrayList temp = new ArrayList();
            int m = 0;
            for (int i = 0; i < arr.size(); i++) {
                if (new Paranthesis('(').equals(arr.get(i))) {
                    rec = true;
                    arr.remove(i);
                    int num = 1;
                    while (num != 0) {
                        if ((new Paranthesis('(').equals(arr.get(i)))) {
                            num++;
                        } else if (new Paranthesis(')').equals(arr.get(i))) {
                            num--;
                        }
                        if (num != 0) {
                            temp.add(arr.get(i));
                        }
                        arr.remove(i);
                        m = i;
                    }
                    i--;
                    if (rec) {
                        result = this.evaluate(temp);
                        Operand op = new Operand(result);
                        arr.add(m, op);
                    }
                    temp.clear();
                }
            }

            for (int i = 0; i < arr.size(); i++) {
                if (new Operator('*').equals(arr.get(i)) || new Operator('/').equals(arr.get(i))) {
                    if ((arr.get(i - 1) instanceof Operand) && (arr.get(i + 1) instanceof Operand)) {
                        Operand a = (Operand) arr.get(i - 1);
                        Operand b = (Operand) arr.get(i + 1);
                        result = ((Operator) arr.get(i)).operation(a.getOperand(), b.getOperand());
                        Operand op = new Operand(result);
                        arr.remove(i + 1);
                        arr.remove(i);
                        arr.remove(i - 1);
                        i--;
                        arr.add(i, op);
                    }
                }
            }
            for (int i = 0; i < arr.size(); i++) {
                if (new Operator('+').equals(arr.get(i)) || new Operator('-').equals(arr.get(i))) {
                    if ((arr.get(i - 1) instanceof Operand) && (arr.get(i + 1) instanceof Operand)) {
                        Operand a = (Operand) arr.get(i - 1);
                        Operand b = (Operand) arr.get(i + 1);
                        result = ((Operator) arr.get(i)).operation(a.getOperand(), b.getOperand());
                        Operand op = new Operand(result);
                        arr.remove(i + 1);
                        arr.remove(i);
                        arr.remove(i - 1);
                        i--;
                        arr.add(i, op);
                    }
                }
            }
            return ((Operand) arr.get(0)).getOperand();
        }

        //override toString method
        public String toString() {
            String str = "";
            for (int i = 0; i < this.expressions.size(); i++) {
                str = str + this.expressions.get(i).toString() + " ";
            }
            return str;
        }

        public boolean equals(Object other) {
            if (other == null) {
                return false;
            }
            if (other == this) {
                return true;
            }
            if (!(other instanceof Expression)) {
                return false;
            }
            Expression exp;
            exp = (Expression) other;
            for (int i = 0; i < exp.expressions.size(); i++) {
                if (this.expressions.get(i) != exp.expressions.get(i)) {
                    return false;
                }
            }
            return true;
        }
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        Expression exp = new Expression();
        exp.play();
        System.out.print(exp);
    }

}
