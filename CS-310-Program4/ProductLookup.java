package data_structures;


import data_structures.*;
import java.util.Iterator;

/**
 *  Program # 4
 *  Gives description of the item wanting to be looked up. can also delete and add items 
 *  CS310-01
 *  04 May 2018
 *  @author  Emily Jean Versoza cssc0760
 */

public class ProductLookup {
	private DictionaryADT<String, StockItem> productStorage;
   
    // Constructor.  There is no argument-less constructor, or default size
    public ProductLookup(int maxSize) {
    		productStorage = //new Hashtable<String, StockItem>(maxSize);
    						 //new BinarySearchTree<String, StockItem>();
    						new BalancedTree<String, StockItem>();
    }
       
    // Adds a new StockItem to the dictionary
    public void addItem(String SKU, StockItem item) {
    		productStorage.add(SKU, item);
    }

    // Returns the StockItem associated with the given SKU, if it is
    // in the ProductLookup, null if it is not.
    public StockItem getItem(String SKU) {
       if(productStorage.getValue(SKU) == null) {
    	   		return null; 
    	   	
       }
       return productStorage.getValue(SKU);
    }
    // Returns the retail price associated with the given SKU value.
    // -.01 if the item is not in the dictionary
    public float getRetail(String SKU) {
    		if(productStorage.isEmpty() || productStorage.getValue(SKU) == null) {
    			return (float) -.01;
    		}
    		StockItem temporary = (StockItem) productStorage.getValue(SKU);
    		
    		return temporary.getRetail();
    }
    
    // Returns the cost price associated with the given SKU value.
    // -.01 if the item is not in the dictionary
    public float getCost(String SKU) {
    		if(productStorage.isEmpty() || productStorage.getValue(SKU) == null) {
			return (float) -.01;
		}
		StockItem temporary = (StockItem) productStorage.getValue(SKU);
		
		return temporary.getCost();
    }
    
    // Returns the description of the item, null if not in the dictionary.
    public String getDescription(String SKU) {
    		if(productStorage.isEmpty() || productStorage.getValue(SKU) == null) {
			return null;
		}
		StockItem temporary = (StockItem) productStorage.getValue(SKU);
		
		return temporary.getDescription();
    	
    }
       
    // Deletes the StockItem associated with the SKU if it is
    // in the ProductLookup.  Returns true if it was found and
    // deleted, otherwise false.  
    public boolean deleteItem(String SKU){
    	
    		return productStorage.delete(SKU); 
    }
       
    // Prints a directory of all StockItems with their associated
    // price, in sorted order (ordered by SKU).
    public void printAll() {
    		Iterator<StockItem> val = productStorage.values();
    		while(val.hasNext()) {
    			System.out.println(val.next());
    		}
    		return;
    }
    
    // Prints a directory of all StockItems from the given vendor, 
    // in sorted order (ordered by SKU).
    public void print(String vendor) {
    		Iterator<StockItem> val = productStorage.values();
    		StockItem placeHolder;
    		
    		while(val.hasNext()) {
    			placeHolder = val.next();
    			if((placeHolder.getVendor().compareTo(vendor) == 0)) {
    				System.out.println(placeHolder);
    			}
    		}
    	
    		return;
    }
    
    // An iterator of the SKU keys.
    public Iterator<String> keys() {
    		return productStorage.keys();
    	
    }
    
    // An iterator of the StockItem values.    
    public Iterator<StockItem> values(){ 
    		return productStorage.values();
    	
    }
}