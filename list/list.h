/**
 * Copyright (c) 2011 John Reese
 * Licensed under the MIT license
 */

#ifndef __JREESE_LIST__
#define __JREESE_LIST__

#include <stdlib.h>

/**
 * List node.
 */
template <class T>
class ListNode
{
	public:

		/**
		 * Create an unconnected node containing the given value.
		 *
		 * @param Element to contain
		 */
		ListNode(T element)
		{
			next = NULL;
			prev = NULL;
			value = element;
		}

		ListNode<T>* next;
		ListNode<T>* prev;
		T value;

};

/**
 * Linked list implementation using doubly-linked nodes.
 */
template <class T>
class List
{
	public:

		/**
		 * Create a new, empty list.
		 */
		List()
		{
			count = 0;
			start = NULL;
			end = NULL;
		}

		/**
		 * Number of elements currently in the list.
		 *
		 * @return List length
		 */
		int length()
		{
			return count;
		}

		/**
		 * Find the position of the element with the given value.
		 *
		 * @param Element to search for
		 * @return Position of element, or -1 if not found
		 */
		int find(T element)
		{
			if (start == NULL)
			{
				return -1;
			}

			ListNode<T>* iter = start;

			for (unsigned int i = 0; i < count; i++)
			{
				if (iter->value == element)
				{
					return i;
				}

				iter = iter->next;
			}

			return -1;
		}

		/**
		 * Retrieve an element at the given position.
		 *
		 * @param Position of the requested element
		 * @return Requested element, or null if not found
		 */
		T get(unsigned int position)
		{
			ListNode<T>* iter = start;

			if (position >= count)
			{
				return (T) NULL;
			}

			for (unsigned int i = 0; i < position; i++)
			{
				iter = iter->next;
			}

			return iter->value;
		}

		/**
		 * Insert an element into the list.
		 *
		 * @param Element to insert
		 */
		void append(T element)
		{
			ListNode<T>* iter = new ListNode<T>(element);

			iter->prev = end;

			if (start == NULL)
			{
				start = iter;
			}
			if (end != NULL)
			{
				end->next = iter;
			}

			end = iter;

			count++;
		}

		/**
		 * Insert an element into the list at a given position.
		 *
		 * @param Element to insert
		 * @param Position to insert element at
		 */
		void insert(T element, unsigned int position)
		{
			if (position >= count)
			{
				return append(element);
			}

			ListNode<T>* node = new ListNode<T>(element);
			ListNode<T>* iter = start;
			ListNode<T>* last = NULL;

			for (unsigned int i = 0; i < position; i++)
			{
				if (iter->next == NULL)
				{
					break;
				}
				else
				{
					last = iter;
					iter = iter->next;
				}
			}

			if (last == NULL)
			{
				start = node;
			}
			else
			{
				last->next = node;
			}

			node->prev = iter->prev;
			iter->prev = node;
			node->next = iter;

			count++;
		}

		/**
		 * Remove an element from the list at a given position.
		 *
		 * @param Position to remove
		 * @return Removed element
		 */
		T remove(unsigned int position)
		{
			ListNode<T>* iter = start;
			ListNode<T>* last = NULL;

			if (position >= count)
			{
				return (T) NULL;
			}

			for (unsigned int i = 0; i < position; i++)
			{
				if (iter->next == NULL)
				{
					break;
				}
				else
				{
					last = iter;
					iter = iter->next;
				}
			}

			T value = iter->value;

			if (last != NULL)
			{
				last->next = iter->next;
			}

			if (iter->next == NULL)
			{
				end = last;
			}
			else
			{
				iter->next->prev = last;
			}

			count--;
			delete iter;

			return value;
		}

		ListNode<T>* start;
		ListNode<T>* end;

	protected:

		unsigned int count;
		
};

/**
 * List iterator.
 */
template <class T>
class ListIter
{
	public:

		/**
		 * Create a new iterator.
		 */
		ListIter()
		{
			position = NULL;
		}

		/**
		 * Create a new iterator pointing at the beginning of the given list.
		 */
		ListIter(List<T>& l)
		{
			position = l.start;
		}

		/**
		 * Set an iterator position to the given list node.
		 *
		 * @param Target node
		 */
		ListIter<T> operator=(const ListNode<T>* node)
		{
			position = node;
			return *this;
		}

		/**
		 * Get the current element pointed to.
		 *
		 * @return Current element
		 */
		T value()
		{
			if (position == NULL)
			{
				return (T) NULL;
			}

			return position->value;
		}

		/**
		 * Return the current element when dereferenced.
		 *
		 * @return Current element
		 */
		T operator*()
		{
			if (position == NULL)
			{
				return (T) NULL;
			}
			
			return position->value;
		}

		/**
		 * Prefix increment the iterator to the next list node.
		 */
		void operator++()
		{
			if (position != NULL)
			{
				position = position->next;
			}
		}

		/**
		 * Postfix increment the iterator to the next list node.
		 *
		 * @return Iterator pointing to the previous node
		 */
		ListIter<T> operator++(int)
		{
			ListIter<T> old;
			old.position = position;

			if (position != NULL)
			{
				position = position->next;
			}

			return old;
		}

		/**
		 * Check if the iterator points at the given node.
		 *
		 * @param Target node
		 * @return True if pointing at target
		 */
		bool operator==(ListNode<T>* node)
		{
			return position == node;
		}

		/**
		 * Check if the iterator points at the given node.
		 *
		 * @param Target node
		 * @return False if pointing at target
		 */
		bool operator!=(ListNode<T>* node)
		{
			return position != node;
		}

	private:

		ListNode<T>* position;

};

#endif

