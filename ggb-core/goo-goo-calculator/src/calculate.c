#include <stdint.h>
#include <stdbool.h>

#include "calculate.h"

#define DECIMAL_MIN_NUMBER ((double)0.0000000001)
#define DECIMAL_MIN 10
#define ZERO {false, false, 0, 0}

/**
 * @brief      Subtraction operation
 *
 * @param[in]  x     minuend
 * @param[in]  y     subtrahend
 *
 * @return     Difference
 */
num minus(num x, num y)
{
	num answer = ZERO;

	//vvvv     integer
	if(x.negative || y.negative)
	{
		if(x.negative ^ y.negative)
		{
			if(y.negative)
			{
				y.negative = false;
				//x - (-y) == x + y
			}
			else
			{
				y.negative = true;
				//(-x) - y == -(x + y)
			}
			return plus(x, y);
		}
		else //(-x) - (-y) == (-x) + y == y - x
		{
			if(x.integer > y.integer)
			{
				answer.negative = true;
			}
			else if(x.integer <= y.integer)
			{
				answer.negative = false;
			}
			answer.integer = (y.integer - x.integer);
		}
	}
	else
	{
		if(x.integer >= y.integer)
		{
			answer.negative = false;
			answer.integer = (x.integer - y.integer);
		}
		else if(x.integer < y.integer)
		{
			answer.negative = true;
			answer.integer = (y.integer - x.integer);
		}
	}


	//vvvv     decimal
	answer.have_decimal = (x.have_decimal || y.have_decimal);
	if(answer.have_decimal)
	{
		if(x.have_decimal ^ y.have_decimal)
		{
			if(x.have_decimal)
			{
				answer.decimal = x.decimal;
			}
			else
			{
				answer.decimal = (1 - y.decimal);
				if(!answer.integer)
				{
					answer.negative = true;
					answer.integer += 1;
				}
				else
				{
					answer.integer -= 1;
				}
			}
		}
		else
		{
			if(x.decimal > y.decimal) answer.decimal = (x.decimal - y.decimal);
			else if(x.decimal < y.decimal)
			{
				answer.decimal = (1 - (y.decimal - x.decimal));
				if(!answer.integer) answer.negative = true;
				if(answer.negative) answer.integer += 1;
				else answer.integer -= 1;
			}
			else answer.have_decimal = false;
		}
	}

	return answer;
}


/**
 * @brief      Addition operation
 *
 * @param[in]  x     augend
 * @param[in]  y     addend
 *
 * @return     sum
 */
num plus(num x, num y)
{
	num answer = ZERO;

	//vvvv     integer
	if(x.negative || y.negative)
	{
		if(x.negative ^ y.negative)
		{
			if(y.negative)
			{
				y.negative = false;
				return minus(x, y); //x + (-y) == x - y
			}
			else
			{
				x.negative = false;
				return minus(y, x); //(-x) + y == y - x
			}
		}
		else
		{
			answer.negative = true;
			answer.integer = (x.integer + y.integer); //(-x) + (-y) == -(x + y)
		}
	}

	else
	{
		answer.integer = (x.integer + y.integer);
	}


	//vvvv     decimal
	answer.have_decimal = (x.have_decimal || y.have_decimal);
	if(answer.have_decimal)
	{
		if(x.have_decimal ^ y.have_decimal)
		{
			if(x.have_decimal)
			{
				answer.decimal = x.decimal;
			}
			else
			{
				answer.decimal = y.decimal;
			}
		}

		else
		{
			answer.decimal = (x.decimal + y.decimal);
			if(answer.decimal > (1 - DECIMAL_MIN_NUMBER))
			{
				uint16_t tmp = (uint16_t)answer.decimal;
				answer.integer += tmp;
				answer.decimal -= tmp;
			}
		}
	}

	return answer;
}
