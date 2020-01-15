/**
       *  Program # 7a
       *  Generic methods that shuffle, find the max element, and removes duplicates in an array and arraylist
       *  CS108-2 
       *  11/28/17
       *  @author  Emily Jean Versoza
       */

import java.awt.List;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedList;
import java.util.Random;
import java.util.Scanner;

public class GenMethods {
	
	public static String getIdentificationString() {
		return "Program 7a, Emily Jean Versoza";
	}
	public static <E> ArrayList<E> removeDuplicates(ArrayList<E> list) { 
		ArrayList<E> NewArrayList = new ArrayList<>(list.size());
		for (int i = 0; i < list.size(); ++i) { //goes through the new array to check if it contains the same elements as list
			if (!NewArrayList.contains(list.get(i))) { //if it doesnt contain it then it adds the element
				NewArrayList.add(list.get(i));
			}
		}
		return NewArrayList;
	}
	public static <E> void shuffle(ArrayList<E> list) {
		int size = list.size();
		Random rand = new Random(340L);
		for(int i = 0; i < 30; ++i) { //shuffles 30 times
			int spot1 = rand.nextInt(size); //gets are two indexes using the random generator
			int spot2 = rand.nextInt(size);
			Collections.swap(list, spot1, spot2);// swaps it
		
		}
			
			
		
		
		
		
		
		
	}
	public static <E extends Comparable<E>> E max(ArrayList<E> list) {
			E Maximum = list.get(0);
			for(int i = 1; i < list.size(); ++i) { //finds the max number by comparing elements
				if (Maximum.compareTo(list.get(i)) == -1) {
					Maximum = list.get(i);
				}
			}
			
		return Maximum;
		
	}
	public static <E extends Comparable<E>> int linearSearch(E[] list, E key) {
		for(int i = 0; i < list.length; ++i) { //uses the linear search algorithm to find position 
			if(list[i] == key) {
				return i;
			}
		}
		return -1;
	}
	
	public static <E extends Comparable<E>> E max(E[] list) {
		E Maximum = list[0];
		
		for(int i = 1; i < list.length; ++i) {
			if (Maximum.compareTo(list[i]) == -1) { //finds the max number by comparing elements
				Maximum = list[i];
			}
		}
		return Maximum;
	}
	
	public static <E extends Comparable<E>> E max(E[][] list) {
		E Maximum = list[0][0];
		
		for(int i = 0; i < list.length; ++i) {
			for(int j = 0; j < list[i].length; j++) {
				if(Maximum.compareTo(list[i][j]) == -1) { //finds the max number by comparing elements
					Maximum = list[i][j];
				}
			}
		}
		return Maximum;
	}
	
	public static void main(String [] args) {
		Scanner scnr = new Scanner(System.in);
		
		final int ELEMENTS = scnr.nextInt();
		Integer [] list = new Integer [ELEMENTS];
		LinkedList<Integer> linked = new LinkedList<Integer>();
		
		for(int i = 0; i < ELEMENTS; ++i) { //fills linked and with elements from user 
			list[i] = scnr.nextInt();
			linked.add(list[i]);
			
		}
		
		System.out.println(Arrays.toString(list));
		System.out.println(linked);
		
		int k = scnr.nextInt();
		int searchResult = linearSearch(list, k);
		
		if(searchResult != -1) { //output varies depending on if the position was found
			System.out.println("Key " + k + " was found at position " + searchResult);
		}
		else {
			System.out.println("Key " + k + " was not found");
		}
		
		int maxResult = max(list);
		System.out.println(maxResult + " is the max element");
		
		int m = scnr.nextInt();
		int p = scnr.nextInt();
		Integer [][] list2 = new Integer [m][p]; // creates 2D array
		
		for(int i = 0; i < list2.length; ++i) {
			for(int j = 0; j < list2[i].length; ++j) {
				list2[i][j] = scnr.nextInt();
			}
		}
		
		for(int i = 0; i < list2.length; ++i) {
			for(int j = 0; j < list2[i].length; ++j) {
				System.out.print(list2[i][j] + " ");
			}
			System.out.println();
		}
		System.out.println();
		
		int maxResult2 = max(list2);
		System.out.println(maxResult2 + " is the max element");
		
		ArrayList<Integer> alist = new ArrayList<>(); 
		for(int i = 0; i < linked.size(); ++i) { //alist gets filled with elements from list
			alist.add(linked.get(i));
		}
		System.out.println(alist);
		alist = removeDuplicates(alist);
		System.out.println(alist);
		
		shuffle(alist); //shuffles alist
		System.out.println(alist);
		
		int maxResult3 = max(alist);
		System.out.println(maxResult3 + " is the max element");
		
	}
	
}


