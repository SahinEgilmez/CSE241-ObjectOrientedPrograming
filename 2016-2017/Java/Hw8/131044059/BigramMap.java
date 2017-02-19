/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
//package hw8;

import com.oracle.jrockit.jfr.DataType;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author segilmez
 * @param <T>
 */
public class BigramMap<T> implements Bigram<T> {

    private int dataType;
    private ArrayList datas = new ArrayList<>();

    private Map<Pair, Integer> bigrams = new HashMap();

    public BigramMap(int type) throws Exception {
        dataType = type;
        if (dataType < 1 || dataType > 3) {
            throw new Exception("Data type must be 1,2 or 3. ");
        }
    }

    private class Pair {

        public T first;
        public T second;

        public Pair(T t1, T t2) {
            first = t1;
            second = t2;
        }

        public Pair() {
            first = null;
            second = null;
        }

        @Override
        public int hashCode() {
            int ascii = 0;
            if (first instanceof String) {
                String str = ((String) first) + ((String) second);
                for (int i = 0; i < str.length(); i++) {
                    ascii += (int) str.charAt(i);
                }
            } else if (first instanceof Integer || first instanceof Double) {
                ascii = (Integer) first + (Integer) second;
            }

            return ascii;
        }

        @Override
        public boolean equals(Object obj) {

            if (obj == this) {
                return true;
            }
            Pair p = (Pair) obj;
            return (first.equals(p.first)) && second.equals(p.second);
        }

        @Override
        public String toString() {
            return first + " - " + second;
        }

    }

    /**
     *
     * @param fileName
     * @return
     * @throws Exception
     */
    @Override
    public boolean readFile(String fileName) throws Exception {
        try {
            Scanner scanner = new Scanner(new File(fileName));
            while (scanner.hasNext()) {
                datas.add(scanner.next());
            }
        } catch (Exception e) {
            throw new Exception("Unable open file");
        }

        T t1 = null, t2 = null;

        for (int i = 0; i < datas.size() - 1; i++) {
            if ((dataType == 1 && isInteger((String) datas.get(i)))
                    || (dataType == 3 && isDouble((String) datas.get(i)))
                    || dataType == 2) {
                Pair p = new Pair(t1, t2);
                p.first = (T) datas.get(i);
                p.second = (T) datas.get(i + 1);
                if (bigrams.containsKey(p)) {
                    bigrams.put(p, bigrams.get(p) + 1);
                } else {
                    bigrams.put(p, 1);
                }
            } else {
                throw new Exception("Data not acceptable.");
            }
        }

        return true;
    }

    @Override
    public int numGrams() {
        return datas.size() - 1;
    }

    @Override
    public int numOfGrams(T elem1, T elem2) {
        /*
        for(Pair p : bigrams.keySet()){
            System.out.println(p.first);
            if(p.first == elem1 || p.second == elem2)
                return bigrams.get(p);
        }
         */

        if (bigrams.containsKey(new Pair(elem1, elem2))) {
            return bigrams.get(new Pair(elem1, elem2));
        } else {
            return 0;
        }
    }

    @Override
    public String toString() {
        int num = datas.size();
        String str = "";
        while (num > 0) {
            for (Pair key : bigrams.keySet()) {
                if (bigrams.get(key) == num) {
                    str += key.toString() + " : " + num + "  |  ";
                }
            }

            num--;
        }
        return str;
    }

    public static boolean isInteger(String s) {
        try {
            Integer.parseInt(s);
        } catch (NumberFormatException | NullPointerException e) {
            return false;
        }
        return true;
    }

    public static boolean isDouble(String s) {
        try {
            Double.parseDouble(s);
        } catch (NumberFormatException | NullPointerException e) {
            return false;
        }
        return true;
    }

    public static void main(String[] args) throws IOException, Exception {
        BigramMap bg = new BigramMap(1);
        bg.readFile("t1.txt");
        System.out.println(bg.numGrams());
        System.out.println(bg.numOfGrams(1, 4));
        System.out.println(bg);
    }

}
