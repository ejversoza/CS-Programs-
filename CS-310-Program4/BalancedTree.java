package data_structures;

import java.util.Iterator;
import java.util.TreeMap;

/**
 *  Program # 4
 *  creates and modifies a red and black tree using the treemap api
 *  CS310-01
 *  04 May 2018
 *  @author  Emily Jean Versoza cssc0760
 */

public class BalancedTree<K extends Comparable<K>,V> implements DictionaryADT<K,V>{
	private TreeMap<K,V> map;
	private K keyFind;
	
	
	public BalancedTree() { //construtor 
		map = new TreeMap<K,V>();
		
		
	}

	
	public boolean contains(K key) { //sees if it contains the key 
		return map.containsKey(key);
	}

	
	public boolean add(K key, V value) { //adds to the tree
		if(contains(key)) {
			return false;
		}
		map.put(key, value);
		
		return true;
	}

	
	public boolean delete(K key) { //deletes at a certain key 
		if(map.remove(key) != null) {
			return true;
		}
		return false;
	}

	
	public V getValue(K key) { //gets the value 
		return map.get(key);
	}


	public K getKey(V value) { //uses both the value and the key iterator to get the key 
		Iterator<V> val = values();
		Iterator<K> keyIt = keys();
		while(val.hasNext()) {
			if((((Comparable<V>)val.next()).compareTo(value) == 0)) {
				keyFind = keyIt.next();
				return keyFind;
			}
			keyFind = keyIt.next();
			
		}
		return null;
	}

	@Override
	public int size() {
		return map.size();
	}

	
	public boolean isFull() {
		return false;
	}

	
	public boolean isEmpty() {
		if(map.size() == 0) {
			return true;
		}
		return false;
	}

	
	public void clear() {
		map.clear();
		
	}

	
	public Iterator<K> keys() {
		return map.keySet().iterator();
	}


	public Iterator<V> values() {
		return map.values().iterator();
	}

}
