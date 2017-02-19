/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
//package hw8;

import java.io.IOException;

/**
 *
 * @author segilmez
 */
public interface Bigram<T> {
    /*read file and set data */
    public boolean readFile(String filename) throws Exception;
    /*return count of numbers*/
    public int numGrams();
    /*return maximum Bigram pair*/
    public int numOfGrams(T elem1, T elem2);
    @Override
    public String toString();
    
    
}
