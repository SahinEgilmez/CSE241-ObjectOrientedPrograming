/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.io.*;

/**
 *
 * @author akay
 */
public class _mainTester {

    static <T> void testFunc(Bigram<T> bg, String filename, T p1, T p2) throws Exception {
	//////////////////////////////////////////////////////////////////////////
        //readFile
        bg.readFile(filename);

        //numGrams
        System.out.println(bg.numGrams());

        //numOfGrams	         
        System.out.println(bg.numOfGrams(p1, p2));

        //to string
        System.out.println(bg.toString());

	//////////////////////////////////////////////////////////////////////////
    }

    static void testManMap(int dataType, String filename) throws Exception {

        if (1 == dataType) {

            BigramMap<Integer> myBg = new BigramMap<>(dataType);
            _mainTester.<Integer>testFunc(myBg, filename, 1, 4);		
	}
	
	else if (2 == dataType) {

            BigramMap<String> myBg = new BigramMap<>(dataType);
            _mainTester.<String>testFunc( myBg, filename, "qwe", "asd");
	}
	else if (3 == dataType) {

            BigramMap<Double> myBg = new BigramMap<>(dataType);
            _mainTester.<Double>testFunc(myBg, filename, 3.0, 4.0);	
	}
}


	static void testManDyn(int dataType, String filename) throws Exception {
                  
        if (1 == dataType) {

            BigramDyn<Integer> myBg = new BigramDyn<>(dataType);


            _mainTester.<Integer>testFunc(myBg, filename, 1, 4);		
	}
	
	else if (2 == dataType) {

            BigramDyn<String> myBg = new BigramDyn<>(dataType);
            _mainTester.<String>testFunc( myBg, filename, "qwe", "asd");
	}
	else if (3 == dataType) {
                      

            BigramDyn<Double> myBg = new BigramDyn<>(dataType);
            _mainTester.<Double>testFunc(myBg, filename, 3.0, 4.0);	
	}        
}
    
    
    public static void main(String[] args) {

	//////////////////////////////////////////////////////////////////////////
        //command line parameters
        String filename = args[0];
        int dataType = Integer.parseInt(args[1]);
        int classType = Integer.parseInt(args[2]);
	//////////////////////////////////////////////////////////////////////////             

	
	
	
        try {
		//////////////////////////////////////////////////////////////////////////
            //Testing class BigramMap
            if (classType == 1) {
                testManMap(dataType, filename);
            } else {

                testManDyn(dataType, filename);
            }
            //////////////////////////////////////////////////////////////////////////
        } catch (Exception e) {
            System.out.println("Exception caught: " + e);
        }

    }
}
