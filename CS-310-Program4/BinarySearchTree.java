package data_structures;

import java.util.ConcurrentModificationException;
import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 *  Program # 4
 *  Creates and modifies a binary search tree.
 *  CS310-01
 *  04 May 2018
 *  @author  Emily Jean Versoza cssc0760
 */

public class BinarySearchTree<K extends Comparable<K>, V> implements DictionaryADT<K, V> {

	private class Node<K, V> { // node class
		private K key;
		private V value;
		private Node<K, V> leftC;
		private Node<K, V> rightC;

		private Node(K k, V v) {
			key = k;
			value = v;
			leftC = rightC = null;
		}
	}

	private Node<K, V> root;
	private int elementAmount;
	protected long modCounter;
	private K keyFind;

	public BinarySearchTree() { //constructor 
		root = null;
		elementAmount = 0;
	}

	public boolean contains(K key) { //checks to see if the BST has the key 
		if (findV(key, root) == null) {
			return false;
		}
		return true;
	}

	public boolean add(K key, V value) {
		if (contains(key)) {
			return false;
		}
		if (root == null) {
			root = new Node<K, V>(key, value); //if tree is empty then gets assigned to the root 
		} else {
			insert(key, value, root, null, false); //finds the position it needs to be inserted 
		}
		elementAmount++;
		modCounter++;
		return true;
	}

	private void insert(K key, V value, Node<K, V> n, Node<K, V> parent, boolean wasleft) { //helper method helps find position 
		if (n == null) {
			if (wasleft)
				parent.leftC = new Node<K, V>(key, value);
			else
				parent.rightC = new Node<K, V>(key, value);
		} else if (key.compareTo((K) n.key) < 0) {
			insert(key, value, n.leftC, n, true);
		} else {
			insert(key, value, n.rightC, n, false);
		}
	}

	public boolean delete(K key) {
		Node<K,V> temp;
		if (root == null) { //checks if the tree is empty 
			return false;
		}
		if (!contains(key)) { //if it doesn't contain key then return false.
			return false;
		}
		if(elementAmount == 1 && root.key.compareTo(key) == 0) { //if the root is the one needed to remove then removes it and tree is empty 
			root = null;
			elementAmount--;
			modCounter++;
			return true;
		}
		else {
			root = deleteHelper(key, root); //calls the helper method
			elementAmount--;
			modCounter++; 
			return true;
		}
		
	}

	private Node<K,V> deleteHelper(K key, Node<K, V> n) {
		if(key.compareTo(n.key) > 0) {
			n.rightC = deleteHelper(key, n.rightC);  //goes through the tree
		}
		else if(key.compareTo(n.key) < 0) {
			n.leftC = deleteHelper(key, n.leftC); 
		}
		else {
			if(n.leftC == null && n.rightC == null) { //zero children 
				n = null; 
				return n;
			}
			else if(n.leftC == null) {  //one right child 
				return n.rightC;
				
			}
			else if(n.rightC == null) { // one left child
				return n.leftC;
			}
			else {
				Node<K,V> successorNode = getInorderSuccessor(n); //two children 
				n.key = successorNode.key;
				n.rightC = deleteHelper(n.key, n.rightC);
			}
		}
		return n;
	}
	private Node<K,V> getInorderSuccessor(Node<K,V> n) { //finds the successor node 
		if(n == null) {
			return null; 
		}
		
		if(n.rightC != null) {
			return findMin(n.rightC);
		}
		else {
			return n.rightC;
		}
	}
	private Node<K,V> findMin(Node<K, V> n) { //finds the leftmost node 
		Node<K,V> temp = n;
		
		while(temp.leftC != null) {
			temp = temp.leftC;
		}
		return temp; 
	}

	public V getValue(K key) { //get value
		return findV(key, root);
	}

	private V findV(K key, Node<K, V> n) { //find the value 
		if (n == null) {
			return null;
		}
		if (key.compareTo(n.key) < 0) {
			return findV(key, n.leftC);
		} else if (key.compareTo(n.key) > 0) {
			return findV(key, n.rightC);
		} else {
			return (V) n.value;
		}

	}

	public K getKey(V value) { //gets key
		findK(root, value);
		return keyFind;

	}

	private void findK(Node<K, V> n, V value) { //finds key 
		if (n == null) {
			return;
		}
		if (n != null) {
			if (((Comparable<V>) value).compareTo(n.value) == 0) {
				keyFind = n.key; //finds first iteration 
				return;

			}
			findK(n.leftC, value);
			findK(n.rightC, value);

		}

	}

	public int size() {
		return elementAmount;
	}

	public boolean isFull() {
		return false;
	}

	public boolean isEmpty() {
		if (elementAmount == 0) {
			return true;
		}
		return false;
	}

	public void clear() {
		elementAmount = 0;
		root = null;
		modCounter++;

	}

	public Iterator<K> keys() {
		return new KeyIteratorHelper();
	}

	public Iterator<V> values() {
		return new ValueIteratorHelper();
	}

	abstract class IteratorHelper<E> implements Iterator<E> {
		protected Node<K, V>[] node;
		protected int index;
		protected long modCheck;

		public IteratorHelper() {
			index = 0;
			modCheck = modCounter;
			node = new Node[elementAmount];
			iter(root);
			index = 0; // Reset index to 0
		}

		public boolean hasNext() {
			if (modCheck != modCounter) {
				throw new ConcurrentModificationException();
			}
			return index < elementAmount;
		}

		abstract public E next();

		private void iter(Node<K, V> n) {
			if (n != null) {
				iter(n.leftC);
				node[index++] = n;
				iter(n.rightC);
			}
		}
	}

	class KeyIteratorHelper<K> extends IteratorHelper<K> {

		public KeyIteratorHelper() {
			super();
		}

		@Override
		public K next() {
			if (!hasNext()) {
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
			if (!hasNext()) {
				throw new NoSuchElementException();

			}
			return (V) node[index++].value;

		}
	}

}
