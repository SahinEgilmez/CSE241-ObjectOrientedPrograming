/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package polynomial;

/**
 *
 * @author sahin
 */
public class Polynomial {

    private double[] coefficients;  // coefficients
    private int degree;     // degree of polynomial 

    //constructor take a double array for coffecients(ax^2 + bx+ c etc.)
    public Polynomial(double[] coefs) {
        this.coefficients = new double[coefs.length];
        System.arraycopy(coefs, 0, this.coefficients, 0, coefs.length);
        this.degree = (coefs.length - 1);
    }

    // constructor for a * x^b
    public Polynomial(int a, int x) {
        coefficients = new double[x + 1];
        coefficients[x] = a;
        degree = x;
    }

    // return the Degree of this polynomial 
    public int getDegree() {
        int deg = 0, n = 0;

        for (int i = coefficients.length - 1; i >= 0; --i) {
            if (coefficients[i] != 0) {
                deg = n;
            }
            n++;
        }
        return deg;
    }

    //return the Coefficients array this polynomial
    public double[] getCoefficients() {
        return this.coefficients;
    }

    // return p3 = p1 + p2
    public Polynomial add(Polynomial p2) {
        Polynomial p1 = this;
        Polynomial p3 = new Polynomial(0, Math.max(p1.degree, p2.degree));
        int n = p3.degree;
        for (int i = p1.degree; i >= 0; --i) {
            p3.coefficients[n] += p1.coefficients[i];
            n--;
        }
        n = p3.degree;
        for (int i = p2.degree; i >= 0; --i) {
            p3.coefficients[n] += p2.coefficients[i];
            n--;
        }
        return p3;
    }

    // return p3 = p1 - p2
    public Polynomial substract(Polynomial p2) {
        Polynomial p1 = this;
        Polynomial p3 = new Polynomial(0, Math.max(p1.degree, p2.degree));
        int n = p3.degree;
        for (int i = p1.degree; i >= 0; --i) {
            p3.coefficients[n] += p1.coefficients[i];
            n--;
        }
        n = p3.degree;
        for (int i = p2.degree; i >= 0; --i) {
            p3.coefficients[n] -= p2.coefficients[i];
            n--;
        }
        return p3;
    }

    // return p3 = p1 * p2
    public Polynomial multiply(Polynomial p2) {
        Polynomial p1 = this;
        Polynomial p3 = new Polynomial(0, p1.degree + p2.degree);
        for (int i = 0; i <= p1.degree; i++) {
            for (int j = 0; j <= p2.degree; j++) {
                p3.coefficients[i + j] += (p1.coefficients[i] * p2.coefficients[j]);
            }
        }
        return p3;
    }

    //set coefficient by exponent value
    public void setCoef(int coef, int exponent) {
        if (this.coefficients.length > exponent) {
            this.coefficients[(this.coefficients.length - 1) - exponent] = coef;
        } else {
            double[] arr = new double[exponent + 1];
            int n = arr.length - 1;
            for (int i = this.coefficients.length - 1; i >= 0; --i) {
                arr[n] = this.coefficients[i];
                n--;
            }
            arr[arr.length - exponent - 1] = coef;
            this.coefficients = arr;
            this.degree = exponent;
        }
    }

    //return coefficient by exponent value
    public double getCoef(int exponent) {
        if (this.coefficients.length > exponent) {
            return this.coefficients[this.coefficients.length - 1 - exponent];
        } else {
            return 0;
        }
    }

    //evaluate polynom for valX
    public double evaluate(int valX) {
        double total = 0;
        for (int i = this.coefficients.length - 1; i >= 0; --i) {
            total += this.coefficients[i] * (Math.pow(valX, this.coefficients.length - i - 1));
        }
        return total;
    }

    //represent Polynom as String
    public String toString() {
        String str = "";
        if (this.degree == 0) {
            str = str + this.coefficients[0];
        } else {
            if (this.coefficients[0] != 0) {
                str = str + this.coefficients[0] + "x^" + this.degree;
            }
            for (int i = 1; i < this.degree; ++i) {
                if (i == (this.degree - 1) && this.coefficients[i] != 0.0) {
                    if (this.coefficients[i] == 1.0) {
                        str = str + " + x ";
                    } else if (this.coefficients[i] == -1.0) {
                        str = str + " - x ";
                    } else if (this.coefficients[i] > 0.0) {
                        str = str + " + " + this.coefficients[i];
                    } else if (this.coefficients[i] < 0.0) {
                        str = str + " - " + Math.abs(this.coefficients[i]);
                    }
                } else if (this.coefficients[i] == 1.0) {
                    str = str + " + " + "x^" + (this.degree - i);
                } else if (this.coefficients[i] == -1.00) {
                    str = str + " - " + "x^" + (this.degree - i);
                } else if (this.coefficients[i] == 0.0) {
                } else if (this.coefficients[i] > 0.0) {
                    str = str + " + " + this.coefficients[i] + "x^" + (this.degree - i);
                } else {
                    str = str + " - " + Math.abs(this.coefficients[i]) + "x^" + (this.degree - i);
                }
            }
            if (this.coefficients[this.degree] > 0) {
                str = str + " + " + this.coefficients[degree];
            } else if (this.coefficients[this.degree] < 0) {
                str = str + " - " + Math.abs(this.coefficients[degree]);
            }
        }
        return str;
    }

    //check polynom which is equal to p2
    public boolean equals(Object other) {
        Polynomial p1 = this;
        if (other == null) {
            return false;
        }
        if (other == this) {
            return true;
        }
        if (!(other instanceof Polynomial)) {
            return false;
        }
        Polynomial p2 = (Polynomial) other;

        if (p1.getDegree() != p2.getDegree()) {
            return false;
        }

        int n1 = p1.coefficients.length - 1;
        int n2 = p2.coefficients.length - 1;
        for (int i = p1.getDegree(); i >= 0; --i) {
            if (p1.coefficients[n1] != p2.coefficients[n2]) {
                return false;
            }
            n1--;
            n2--;
        }
        return true;

    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        //Main for test
        double[] coef1 = {5, 0, 2,};//5x^2 + 2.
        double[] coef2 = {4, 2, 1, 7,};//4x^3 + 2x^2 + x + 7
        Polynomial p1 = new Polynomial(coef1);
        Polynomial p2 = new Polynomial(coef2);
        System.out.println("p1 = " + p1);
        System.out.println("p2 = " + p2);
        //Test equals function
        if (p2.equals(p1)) {
            System.out.println("These are equals!");
        } else {
            System.out.println("These are not equals");
        }
        //Test set coefficient function
        System.out.println("p1 before set ax^4 a=2 : " + p1);
        p1.setCoef(2, 4);
        System.out.println("After : " + p1);
        System.out.println("p2 before set ax^2 a=3 : " + p2);
        p2.setCoef(3, 2);
        System.out.println("After : " + p2);
        //Test get coefficient function
        System.out.println("p1's value that exponent is 2 : " + p1.getCoef(2));
        System.out.println("p2's value that exponent is 3 : " + p2.getCoef(3));
        //Test mathematical operation of Polynomial
        System.out.println("p1 = " + p1);
        System.out.println("p2 = " + p2);
        System.out.println("p1+p2 : " + p2.add(p1));
        System.out.println("p1-p2 : " + p2.substract(p1));
        System.out.println("p1*p2 : " + p2.multiply(p1));
        //Test get coefficients array function and print all elements
        System.out.println("These are p1 all coefficients : ");
        double[] arr = p1.getCoefficients();
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i] + " , ");
        }
        //Test for evaluate for x value
        System.out.println("\nTest for evaluating : ");
        System.out.println("p1 for x=2 : " + p1.evaluate(2));
        System.out.println("p2 for x=5 : " + p1.evaluate(5));

    }

}
