/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Arrays;
import java.util.Scanner;

class Data<T> {

    public T first;
    public T second;
    public int count = 0;
    public boolean isSet = false;

    public Data(T t1, T t2) {
        first = t1;
        second = t2;
    }

    public Data() {
        super();
        first = null;
        second = null;
        count = 0;
        isSet = false;
    }

    @Override
    public int hashCode() {
        String str = ((String) first) + ((String) second);
        int ascii = 0;
        for (int i = 0; i < str.length(); i++) {
            ascii += (int) str.charAt(i);
        }
        return ascii;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == this) {
            return true;
        }
        Data p = (Data) obj;
      
        return (first.equals(p.first)) && second.equals(p.second);
    }


    @Override
    public String toString() {
        return first + " - " + second + " : " + count;
    }

}

/**
 *
 * @author segilmez
 * @param <T>
 */
public class BigramDyn<T> implements Bigram<T> {

    private int dataType;
    private int size = 0;
    private String[] datas;
    private Data[] bigrams;

    public BigramDyn(int type) throws Exception {
        this.bigrams = new Data[1];
        this.datas = new String[1];
        dataType = type;
        if (dataType < 1 || dataType > 3) {
            throw new Exception("Data type must be 1,2 or 3. ");
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
            int i = 1;
            while (scanner.hasNext()) {
                datas[i - 1] = scanner.next();
                datas = Arrays.copyOf(datas, i + 1);
                size++;
                i++;
            }
           
        } catch (FileNotFoundException e) {
            throw new Exception("Unable open file");
        }
        
        bigrams = Arrays.copyOf(bigrams, size-1);

        for (int i = 0; i < size-1 ; i++) {
            Data dt = new Data();
            bigrams[i] = dt;
        }
        T t1 = null, t2 = null;
        for (int i = 0; i < size -1; i++) {
            if ((dataType == 1 && isInteger((String) datas[i]))
                    || (dataType == 3 && isDouble((String) datas[i]))
                    || dataType == 2) {
                Data d = new Data();
                d.first = (T) datas[i];
                d.second = (T) datas[i + 1];
                setBg(d);
            } else {
                throw new Exception("Data not acceptable.");
            }
        }

        return true;
    }

    private boolean setBg(Data d) {
        for (int i = 0; i < size -1; i++) {
            if (bigrams[i].isSet) {
                if (bigrams[i].equals(d)) {
                    bigrams[i].count = (bigrams[i].count + 1);
                    return true;
                }
            } else {
                bigrams[i].first = d.first;
                bigrams[i].second = d.second;
                bigrams[i].count = 1;
                bigrams[i].isSet = true;
                return true;
            }
        }

        return false;
    }

    private int contains(Data d) {
        for (int i = 0; i < size -1; i++) {
            if (bigrams[i].equals(d)) {
                return i;
            }
        }
        return -1;
    }

    @Override
    public int numGrams() {
        return size - 1;
    }

    @Override
    public int numOfGrams(T elem1, T elem2) {
        int i = 0;
        if ((i = contains(new Data(elem1, elem2))) >= 0) {
            return bigrams[i].count;
        } else {
            return 0;
        }
    }

    @Override
    public String toString() {
        int num = size -1;
        String str = "";
        while (num > 0) {
            for (Data d : bigrams) {
                if (d.count == num) {
                    str += d.toString() + "  |  ";
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
    /*
    public static void main(String[] args) throws IOException, Exception {
        BigramDyn bg = new BigramDyn(1);
        bg.readFile("t1.txt");
        System.out.println(bg.numGrams());
        System.out.println(bg.numOfGrams("qwe", "asd"));
        System.out.println(bg);
    }
*/
}
