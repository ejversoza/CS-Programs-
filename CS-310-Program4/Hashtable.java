package data_structures;

import java.util.ConcurrentModificationException;
import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 *  Program # 4
 *  creates and modifies a hashtable
 *  CS310-01
 *  04 May 2018
 *  @author  Emily Jean Versoza  cssc0760
 */


public class Hashtable<K extends Comparable<K>,V> implements DictionaryADT<K,V> {
	int elementAmount;
	int maxSize;
	int tableSize; 
	long modCounter;
	
	
	
	
	private linkedList<DictionaryNode<K,V>> [] list; 
	
	@SuppressWarnings("unchecked")
	public Hashtable(int x) { //constuctor 
		elementAmount = 0;
		maxSize = x;
		modCounter = 0;
		tableSize = (int) (maxSize * 1.3f);
		
		list = new linkedList[tableSize];
		for(int i = 0; i < tableSize; i++) {
			list[i] = new linkedList<DictionaryNode<K,V>>();
		}
	}
	
	@SuppressWarnings("hiding")
	private class DictionaryNode<K,V> implements Comparable<DictionaryNode<K,V>> { //DictionaryNode class
		K key;
		V value;
		
		public DictionaryNode(K key, V value) {
			this.key = key;
			this.value = value;
		}
		@SuppressWarnings("unchecked")
		@Override
		public int compareTo(DictionaryNode<K, V> node) {
			return ((Comparable<K>)key).compareTo((K)node.key);
		}
		
	}
	
	public class linkedList<E extends Comparable<E>> implements Iterable<E> { //uses linked list class for the methods down below 
		
		@SuppressWarnings("hiding")
		public class Node <E> {
			E data;
			Node<E> nxt;
			
			public Node(E obj) { //constructors 
				data = obj;
				nxt = null;
			}
		}
		
		Node<E> head = null;
		int elementAmount; 
		
		public boolean insert(E object) {
			Node<E> newElement = new Node<E>(object); //insets elements in order 
			
			if(isEmpty()) {
				
				head = newElement; //puts first element in 
				elementAmount++;
				return true;
			} 
			@SuppressWarnings("unused")
			Node<E> previous = null;
			Node<E> current = null;
			current = head;
			
			newElement.nxt = head;
			head = newElement;
			elementAmount++;
			return true;
			
		}
		
	public boolean delete(E obj) {
			
			if(isEmpty()) {
				return false;
			}
			
			
			Node<E> previous = null;
			Node<E> current = null;
			current = head;
			
			while(current != null) { 
				if(current.data.compareTo(obj) == 0) {
					if(previous == null) {
						head = head.nxt;
						current = head;
						elementAmount--;
					}
					if(current.nxt == null) {
						previous.nxt = null;
						current = null;
						elementAmount--;
					}
					else if(previous != null) {
						current = current.nxt;
						previous.nxt = current;
						elementAmount--;
					}
				}
				if((current != null) && (current.data.compareTo(obj) != 0)) {
					previous = current;
					current = current.nxt;
				}
			}
				
			return true;
		}
		
	public boolean contains(E obj) {
		
		
		if(isEmpty()) {
			return false;
		}
		
		Node<E> temporary = null;
		
		
		temporary = head;
		while(temporary != null) {
			if(temporary.data.compareTo(obj) == 0) {// scans to see if the object is there 
				return true;
			}
			temporary = temporary.nxt;
		}
		return false; 
	}

		public E get(E obj) {
			Node<E> temporary = null;
			
			temporary = head;
			
			while(temporary != null) {
				if(temporary.data.compareTo(obj) == 0) {
					return temporary.data;
					
				}
				temporary = temporary.nxt;
			}
			return null;
	}


	public int size() { //gives size
		return elementAmount;
	}


	public void clear() { //assigns null to everything to clear it
		Node<E> previous = null;
		Node<E> current = null;
		current = head;
		head = null;
		previous = null;
		current = null;
		elementAmount = 0;
		
	}


	public boolean isEmpty() {
		if(elementAmount == 0) { //checks if its empty
			return true;
		}
		return false;
	}


	public boolean isFull() { //checks if it s full
		return false;
	}
		

		
		public Iterator<E> iterator() {
			
			return new LLIteratorHelper();
		}
		private class LLIteratorHelper implements Iterator<E> {
			Node<E> current;
			
			public LLIteratorHelper() {
				current = head;
			}

			public void remove() {
				throw new UnsupportedOperationException();
			}
			
			
			public boolean hasNext() {
				return current != null;
			}

			
			public E next() {
				if (!hasNext()) {
					throw new NoSuchElementException();
				}
				E temporary = current.data;
				current = current.nxt;
				return temporary;
			}
			
			
		}
		

	}


	
	public boolean contains(K key) { //checks to see if it contains the key
		
		return list[getHashCode(key)].contains(new DictionaryNode<K,V>(key,null));
	}
	private int getHashCode(K key) {
		return (key.hashCode() & 0x7FFFFFFF) % tableSize; //calculates the hashcode
	}

	
	public boolean add(K key, V value) { //adds to the hashtable
		if(isFull()) {
			return false;
		}
		if(list[getHashCode(key)].contains(new DictionaryNode<K,V>(key,null))) {
			return false;
		}
		
		list[getHashCode(key)].insert(new DictionaryNode<K,V>(key,value)); 
		elementAmount++;
		modCounter++;
		return true;
		
	}

	
	public boolean delete(K key) { //deletes at a certain key 
		
		if(list[getHashCode(key)].delete(new DictionaryNode<K,V>(key,null))) {
			elementAmount--;
			modCounter++;
			return true;
		}
		return false;
	}

	
	public V getValue(K key) { //gets the value
		DictionaryNode<K,V> temporary = list[getHashCode(key)].get(new DictionaryNode<K,V>(key,null));
		if(temporary == null) {
			return null;
		}
		return temporary.value;
	}

	
	public K getKey(V value) { //gets the key 
		for(int i = 0; i < tableSize; ++i) {
			for(DictionaryNode<K,V> V : list[i] ) {
				if( ((Comparable<V>) V.value).compareTo(value) == 0) {
					return V.key;
				}
				
			}
		}
		return null;
	}

	
	public int size() {
		return elementAmount;
	}

	
	public boolean isFull() {
		if(elementAmount == maxSize) {
			return true;
		}
		return false;
	}

	
	public boolean isEmpty() {
		if(elementAmount == 0) {
			return true;
		}
		return false;
	}

	
	public void clear() {
		for(int i = 0; i < elementAmount; ++i) {
			list[i] = null;
		}
		elementAmount = 0;
		modCounter++;
	}

	
	public Iterator<K> keys() {
		return new KeyIteratorHelper();
	}

	
	public Iterator<V> values() {
		
		return new ValueIteratorHelper();
	}
	
	
	abstract class IteratorHelper<E> implements Iterator<E> {
		protected DictionaryNode<K,V> [] node;
		protected int index;
		protected long modCheck;
		
		public IteratorHelper() {
			node = new DictionaryNode[elementAmount];
			index = 0;
			int x = 0;
			modCheck = modCounter;
			for(int i = 0; i < tableSize; ++i) {
				for(DictionaryNode k : list[i]) {
					node[x++] = k;			
				}
			
			}
			node = (DictionaryNode<K,V>[]) shellSort(node);
		}
		
		public boolean hasNext() {
			if(modCheck != modCounter) {
				throw new ConcurrentModificationException();
			}
			return index < elementAmount;
		}
		
		public abstract E next();
		
		DictionaryNode<K,V> [] shellSort(DictionaryNode<K,V> [] node) {
			DictionaryNode<K,V> [] sortArray = node;
			int in; 
			int out;
			int h = 1;
			DictionaryNode<K,V> temp;
			int size = sortArray.length;
			
			while(h <= size/3) {
				h = h * 3 +1;
			}
			while (h > 0) {
				for(out = h; out < size; out++) {
					temp = sortArray[out];
					in = out;
					while(in > h-1 && sortArray[in - h].compareTo(temp) > 0) {
						sortArray[in] = sortArray[in - h];
						in -= h; 
					}
					sortArray[in] = temp;
				}
				h = (h - 1) / 3;
			}
			return sortArray;
		}
		
		public void remove() {
			throw new UnsupportedOperationException();
		}
		
 	}
	
	private class KeyIteratorHelper<K> extends IteratorHelper<K> {
		
		public KeyIteratorHelper() {
			super();
		}

		
		public K next() {
			if(!hasNext()) {
				throw new NoSuchElementException();
				
			}
			return (K) node[index++].key;
		}
		
	}
	
	private class ValueIteratorHelper<V> extends IteratorHelper<V> {
		public ValueIteratorHelper() {
			super();
		}
		
		public V next() {
			if(!hasNext()) {
				throw new NoSuchElementException();
				
			}
			return (V) node[index++].value;
			
		}
	}



}
