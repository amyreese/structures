/**
 * Copyright (c) 2011 John Reese
 * Licensed under the MIT license
 */

#ifndef __JREESE_BIGNUM__
#define __JREESE_BIGNUM__

#define uint unsigned int

class Bignum
{
	public:
		/**
		 * Initialize a new Bignum instance with a given starting value.
		 *
		 * @param Initial value
		 */
		Bignum(uint value=0)
		{
			id = nextid++;
			//printf("ID %u: uint(%u) constructor\n", id, value);

			count = 0;
			size = 0;
			base = 10;
			buffer = NULL;
			resize(2000);

			uint i = 0;
			while (value > 0)
			{
				buffer[i++] = (value % base);
				value /= base;
			}

			count = i;
		}
		Bignum(const Bignum& copy)
		{
			id = nextid++;
			//printf("ID %u: Copy(%u) constructor\n", id, copy.id);

			count = 0;
			size = 0;
			base = 10;
			buffer = NULL;
			resize(copy.size);

			for (uint i = 0; i < copy.count; i++)
			{
				buffer[i] = copy.buffer[i];
			}
			count = copy.count;
		}
		~Bignum()
		{
			if (buffer != NULL)
			{
				//printf("ID %u: Destructor\n", id);
				free(buffer);
			}
		}

		/**
		 * Assignment/copy operator.
		 *
		 * @param Bignum instance to copy from
		 * @return Reference to this Bignum instance
		 */
		Bignum& operator= (const Bignum& copy)
		{
			//printf("ID %u: Copy(%u) operator\n", id, copy.id);
			if (buffer != NULL)
			{
				free(buffer);
			}

			count = 0;
			size = 0;
			base = 10;
			buffer = NULL;
			resize(copy.size);

			for (uint i = 0; i < copy.count; i++)
			{
				buffer[i] = copy.buffer[i];
			}
			count = copy.count;

			return *this;
		}

		/**
		 * Return the number of digits for the currently stored value.
		 *
		 * @return String length
		 */
		uint length()
		{
			return count;
		}

		/**
		 * Add a second value to the current value.
		 *
		 * @param Integer value to add
		 */
		void add(uint value)
		{
			uint i = 0;
			bool carry = false;
			uint digit;
			uint result;

			while (value > 0)
			{
				digit = value % base;
				result = digit + buffer[i];

				//printf("%u %u %u %d\n", value, digit, result, carry);

				if (carry)
				{
					result += 1;
					carry = false;
				}

				if (result >= base)
				{
					carry = true;
					result = result % base;
				}

				//printf("%u %u %u %d\n", value, digit, result, carry);
				buffer[i++] = result;
				value /= base;
			}

			while (carry)
			{
				result = 1 + buffer[i];
				carry = false;

				if (result >= base)
				{
					carry = true;
					result = 0;
				}

				buffer[i++] = result;
			}

			count = i > count ? i : count;
		}

		/**
		 * Output a null-terminated string representation of the large number
		 * to a target string buffer.
		 *
		 * @param Target buffer
		 * @param Buffer size
		 * @return Zero if larger than buffer, length of new string otherwise
		 */
		uint str(char* target, uint size)
		{
			uint i = 0;
			uint c = count - 1;
			uint l = count + 1;

			if (l > size)
			{
				return 0;
			}

			if (count == 0)
			{
				target[i++] = '0';
			}

			for (; i < count; i++)
			{
				target[i] = buffer[c-i] + '0';
			}

			target[i] = 0;

			return l;
		}

	private:
		static uint nextid;
		uint id;
		char* buffer;
		uint base;
		uint count;
		uint size;

		/**
		 * Resize the internal buffer to a new given size.
		 * TODO: Handle downsizing
		 *
		 * @param New buffer size
		 */
		void resize(uint newsize)
		{
			uint i;
			char* newbuffer = (char*) malloc(newsize * sizeof(char));

			for (i = 0; i < count; i++)
			{
				newbuffer[i] = buffer[i];
			}

			for (; i < newsize; i++)
			{
				newbuffer[i] = 0;
			}

			if (buffer != NULL)
			{
				free(buffer);
			}

			size = newsize;
			buffer = newbuffer;
		}
};

uint Bignum::nextid = 1;

#endif
