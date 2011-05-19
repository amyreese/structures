/**
 * Linked list implementation.
 *
 * Copyright (c) 2011 John Reese
 * Licensed under the MIT license
 */

#include <stdlib.h>

#include "list.h"

template <class T>
List<T>::List()
{
	count = 0;
	list = NULL;
}

template <class T>
int List<T>::length()
{
	return count;
}

template <class T>
T List<T>::get(int position)
{
	return NULL;
}

template <class T>
void List<T>::insert(T element)
{
}

template <class T>
void List<T>::insert(T element, int position)
{
}

template <class T>
ListNode<T>::ListNode()
{
	next = NULL;
	prev = NULL;
}

