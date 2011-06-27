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
		Bignum& operator= (const uint value)
		{
			//printf("ID %u: Assignment(%u) operator\n", id, value);
			count = 0;
			resize(size);

			uint i = 0;
			uint v = value;
			while (v > 0)
			{
				buffer[i++] = (v % base);
				v /= base;
			}

			count = i;

			return *this;
		}
		Bignum& operator= (const Bignum& copy)
		{
			//printf("ID %u: Copy(%u) operator\n", id, copy.id);
			if (id == copy.id)
			{
				return *this;
			}

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
		 * Addition operators.
		 *
		 * @param Value to add
		 * @return Reference to current Bignum
		 */
		Bignum operator+ (const uint value)
		{
			//printf("ID %u: Add(%u) operator\n", id, value);
			Bignum n = *this;
			n.add(value);

			return n;
		}
		Bignum operator+ (const Bignum& value)
		{
			//printf("ID %u: AddBignum(%u) operator\n", id, value.id);
			Bignum n = *this;
			n.add(value);

			return n;
		}

		/**
		 * In-place addition operators.
		 *
		 * @param Value to add
		 * @return Reference to current Bignum
		 */
		Bignum& operator+= (const uint value)
		{
			//printf("ID %u: AddEq(%u) operator\n", id, value);
			add(value);

			return *this;
		}
		Bignum& operator+= (const Bignum& value)
		{
			//printf("ID %u: AddEqBignum(%u) operator\n", id, value.id);
			add(value);

			return *this;
		}

		/**
		 * Multiplication operators.
		 *
		 * @param Value to multiply
		 * @return Reference to current Bignum
		 */
		Bignum operator* (const uint value)
		{
			//printf("ID %u: Mul(%u) operator\n", id, value);
			Bignum n = *this;
			n.mul(value);

			return n;
		}
		Bignum operator* (const Bignum& value)
		{
			//printf("ID %u: MulBignum(%u) operator\n", id, value.id);
			Bignum n = *this;
			n.mul(value);

			return n;
		}

		/**
		 * In-place multiplication operators.
		 *
		 * @param Value to multiply
		 * @return Reference to current Bignum
		 */
		Bignum& operator*= (const uint value)
		{
			//printf("ID %u: MulEq(%u) operator\n", id, value);
			mul(value);

			return *this;
		}
		Bignum& operator*= (const Bignum& value)
		{
			//printf("ID %u: MulEqBignum(%u) operator\n", id, value.id);
			mul(value);

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
		 * Add a second Bignum value to the current value.
		 *
		 * @param Bignum value to add
		 */
		void add(const Bignum& value)
		{
			uint i = 0;
			bool carry = false;
			uint digit;
			uint result;

			while (i < value.count)
			{
				digit = value.buffer[i];
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
		 * Multiple by the given value. Converts to Bignum before multiplying.
		 *
		 * @param Value to multiply
		 */
		void mul(const uint value)
		{
			Bignum v(value);
			mul(v);
		}

		/**
		 * Multiple by the given Bignum value.
		 *
		 * @param Bignum value to multiply
		 */
		void mul(const Bignum& value)
		{
			uint i, k;
			uint p, q, r;
			Bignum result;
			Bignum total;

			for (i = 0; i < count; i++)
			{
				p = buffer[i];

				for (k = 0; k < value.count; k++)
				{
					q = value.buffer[k];
					result = p * q;
					r = i + k;

					if (r > 0)
					{
						result.buffer[r+1] = result.buffer[1];
						result.buffer[1] = 0;
						result.buffer[r] = result.buffer[0];
						result.buffer[0] = 0;
						result.count += r;
					}

					total += result;
				}
			}

			for (uint i = 0; i < total.count; i++)
			{
				buffer[i] = total.buffer[i];
			}
			count = total.count;
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

