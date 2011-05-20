/**
 * Copyright (c) 2011 John Reese
 * Licensed under the MIT license
 */

#ifndef __JREESE_VECTOR__
#define __JREESE_VECTOR__

#include <math.h>
#include <stdlib.h>

template <class T>
class Vector
{
	public:

		/**
		 * Create an empty vector, with an optional size hint.
		 *
		 * @param Initial size hint
		 */
		Vector(unsigned int s=128)
		{
			size = s;
			start = size / 10;
			count = 0;

			back = 1;
			front = 1;

			data = new T[size];
		}

		/**
		 * Get the element at the given position.
		 *
		 * @param Element position
		 * @return Element
		 */
		T& operator[](unsigned int position)
		{
			if (position >= count)
			{
				throw 0;
			}

			return data[start+position];
		}

		/**
		 * Get the number of elements in the vector.
		 *
		 * @return Element count
		 */
		unsigned int length()
		{
			return count;
		}

		/**
		 * Get the total size of the vector, including used and unused elements.
		 *
		 * @return Vector size
		 */
		unsigned int space()
		{
			return size;
		}

		/**
		 * Add a new element to the end of the vector.
		 *
		 * @param Element to add
		 */
		void push(T element)
		{
			back++;

			if (start + count >= size)
			{
				resize();
			}

			data[start + count++] = element;
		}

		/**
		 * Remove and return the last element from the vector.
		 *
		 * @return Removed element
		 */
		T pop()
		{
			if (count < 1)
			{
				return (T) NULL;
			}

			back--;
			return data[start + --count];
		}

		/**
		 * Add a new element to the front of the vector.
		 *
		 * @param Element to add
		 */
		void unshift(T element)
		{
			front++;

			if (start < 1)
			{
				resize();
			}

			data[start--] = element;
			count++;
		}

		/**
		 * Remove and return the first element from the vector.
		 *
		 * @return Removed element
		 */
		T shift()
		{
			if (count < 1)
			{
				return (T) NULL;
			}

			front--;
			count--;
			return data[start++];
		}

		/**
		 * Resize the vector.
		 *
		 * @param New vector size, or 0 for automatic
		 */
		void resize(unsigned int nsize=0)
		{
			// Try to semi-intelligently resize at a growing rate
			if (nsize == 0 || nsize <= size)
			{
				if (count < size / 2)
				{
					nsize = size;
				}
				else if (size >= 16384)
				{
					nsize = size + size / 4;
				}
				else
				{
					nsize = size * 2;
				}
			}

			T* ndata = new T[nsize];

			// Try to semi-intelligently pick a new start position based on a history
			// how many elements were added on front or back since last resize
			float percent = (float) front / (float) (front + back);
			float diff = nsize - count;
			float buffer = diff * 0.10f;
			float pool = diff * 0.80f;
			unsigned int nstart = floor(buffer + percent * pool);

			printf("Resizing vector from %d to %d, count %d, front %f%%, starting at %d...\n", size, nsize, count, percent, nstart);
			
			for (unsigned int i = 0; i < count; i++)
			{
				ndata[nstart+i] = data[start+i];
			}

			delete[] data;

			data = ndata;
			size = nsize;
			start = nstart;

			back = 1;
			front = 1;
		}

	private:
		T* data;	
		unsigned int size;
		unsigned int start;
		unsigned int count;

		unsigned int back;
		unsigned int front;
};

#endif

