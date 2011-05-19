/**
 * Copyright (c) 2011 John Reese
 * Licensed under the MIT license
 */

/**
 * List node.
 */
template <class T>
class ListNode {
	public:

		ListNode();

		ListNode<T>* next;
		ListNode<T>* prev;
		T element;

};

/**
 * Linked list structure.
 */
template <class T>
class List {
	public:

		/**
		 * Create a new, empty list.
		 */
		List();

		/**
		 * Number of elements currently in the list.
		 *
		 * @return List length
		 */
		int length();

		/**
		 * Retrieve an element at the given position.
		 *
		 * @param Position of the requested element
		 * @return Requested element, or null if not found
		 */
		T get(int);

		/**
		 * Insert an element into the list.
		 *
		 * @param Element to insert
		 */
		void insert(T);

		/**
		 * Insert an element into the list at a given position.
		 *
		 * @param Element to insert
		 * @param Position to insert element at
		 */
		void insert(T, int);

	private:

		int count;
		
		ListNode<T>* list;
		
};

