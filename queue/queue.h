/**
 * Copyright (c) 2011 John Reese
 * Licensed under the MIT license
 */

#ifndef __JREESE_QUEUE__
#define __JREESE_QUEUE__

#include <math.h>
#include <stdlib.h>

#include "vector.h"

/**
 * Priority queue using an unsigned integer to represent the priority level.
 * Backed by a vector of vectors.
 */
template <class T>
class Queue
{
	public:

		/**
		 * Create an empty queue, with an optional size hint.
		 *
		 * @param Size hint
		 */
		Queue(unsigned int size) : queues(size)
		{
			count = 0;
		}

		/**
		 * Push a new element to the queue with the given priority.
		 *
		 * @param Element to push
		 * @param Priority of element
		 */
		void push(T element, unsigned int prio=0)
		{
			for (unsigned int i = queues.length(); i <= prio; i++)
			{
				Vector<T>* v = new Vector<T>();
				queues.push(v);
			}

			count++;
			Vector<T>* q = queues[prio];
			q->push(element);
		}

		/**
		 * Get the next element in the queue by priority.
		 *
		 * @return Next element
		 */
		T shift()
		{
			if (count < 1)
			{
				throw 0;
			}

			Vector<T>* q;

			for (unsigned int i = 0; i <= queues.length(); i++)
			{
				q = queues[i];
				if (q->length())
				{
					count--;
					return q->shift();
				}
			}

			throw 1;
		}

		/**
		 * Get the number of elements still in the queue.
		 *
		 * @return Queue length
		 */
		unsigned int length()
		{
			return count;
		}

	private:

		Vector<Vector<T>*> queues;
		unsigned int count;
};

#endif

