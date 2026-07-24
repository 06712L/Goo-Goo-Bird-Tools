#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "calculate.h"

#define DECIMAL_MIN_NUMBER ((double)0.0000000001)
// clang-format off
#define ZERO {false, false, 0, 0}
// clang-format on

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

	// vvvv     integer
	if (x.negative || y.negative)
	{
		if (x.negative ^ y.negative)
		{
			if (y.negative)
			{
				y.negative = false;
				// x - (-y) == x + y
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
			if (x.integer > y.integer)
			{
				answer.negative = true;
			}
			else if (x.integer <= y.integer)
			{
				answer.negative = false;
			}
			answer.integer = (y.integer - x.integer);
		}
	}
	else
	{
		if (x.integer >= y.integer)
		{
			answer.negative = false;
			answer.integer = (x.integer - y.integer);
		}
		else if (x.integer < y.integer)
		{
			answer.negative = true;
			answer.integer = (y.integer - x.integer);
		}
	}

	// vvvv     decimal
	answer.have_decimal = (x.have_decimal || y.have_decimal);
	if (answer.have_decimal)
	{
		if (x.have_decimal ^ y.have_decimal)
		{
			if (x.have_decimal)
			{
				answer.decimal = x.decimal;
			}
			else
			{
				answer.decimal = (1 - y.decimal);
				if (!answer.integer)
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
			if (x.decimal > y.decimal)
			{
				answer.decimal = (x.decimal - y.decimal);
			}
			else if (x.decimal < y.decimal)
			{
				answer.decimal = (1 - (y.decimal - x.decimal));
				if (!answer.integer)
				{
					answer.negative = true;
				}
				if (answer.negative)
				{
					answer.integer += 1;
				}
				else
				{
					answer.integer -= 1;
				}
			}
			else
			{
				answer.have_decimal = false;
			}
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

	// vvvv     integer
	if (x.negative || y.negative)
	{
		if (x.negative ^ y.negative)
		{
			if (y.negative)
			{
				y.negative = false;
				return minus(x, y); // x + (-y) == x - y
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

	// vvvv     decimal
	answer.have_decimal = (x.have_decimal || y.have_decimal);
	if (answer.have_decimal)
	{
		if (x.have_decimal ^ y.have_decimal)
		{
			if (x.have_decimal)
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
			if (answer.decimal > (1 - DECIMAL_MIN_NUMBER))
			{
				uint16_t tmp = (uint16_t)answer.decimal;
				answer.integer += tmp;
				answer.decimal -= tmp;
			}
		}
	}

	return answer;
}

// vvvv 	times

static uint64_t extract_the_decimal_part(const num num_var)
{
	enum
	{
		before_decimal_point_size = 2
	};
	uint64_t decimal_part = 0;
	char *tmp = malloc(before_decimal_point_size + DECIMAL_PRECISION + 1); // "0." + decimal + '\0'
	if (!tmp)
	{
		return decimal_part;
	}
	sprintf(tmp, "%lf", num_var.decimal);
	char *ptr_tmp = (tmp + before_decimal_point_size);
	/* move the pointer to the first decimal place
	 * 0.xxxx
	 *   ^    */
	decimal_part = atoi(ptr_tmp);
	free(tmp);
	tmp = NULL;
	ptr_tmp = NULL;
	return decimal_part;
}

/**
 * @brief      Multiplication operation
 *
 * @param[in]  x     multiplicand
 * @param[in]  y     multiplier
 *
 * @return     Product
 *
 * @todo       Continue fixing until the answer is correct
 */
num times(num x, num y)
{
	num answer = ZERO;

	// vvvv 	negative
	answer.negative = (x.negative ^ y.negative);

	// vvvv 	calculate
	answer.integer = (x.integer * y.integer);
	if (x.have_decimal || y.have_decimal)
	{
		uint64_t x_decimal = extract_the_decimal_part(x);
		uint64_t y_decimal = extract_the_decimal_part(y);
		uint64_t answer_decimal = (x_decimal * y_decimal);
		answer.integer *= answer_decimal;
		answer_decimal *= answer.integer;
	}

	return answer;
}
