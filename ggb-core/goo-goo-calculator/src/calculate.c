#include <stdint.h>
#include <stdbool.h>
/*
#include "calculate.h"

#define DECIMAL_MIN ((double)0.000000000001)
#define ZERO {false, false, 0, 0}


static num minus(num x, num y)
{
	num answer = ZERO;

	//coming soon

	return answer;
}

static num plus(num x, num y)
{
	num answer = ZERO;

	//integer
	if(x.negative || y.negative)
	{
		if(x.negative ^ y.negative)
		{
			if(y.negative)
			{
				y.negative = false;
				return minus(x, y); //x - y
			}

			else
			{
				x.negative = false;
				return minus(y, x); //y - x
			}
		}

		else if(x.negative && y.negative)
		{
			answer.negative = true;
			answer.integer = (x.integer + y.integer); //(-x) + (-y) == -(x + y)
		}
	}

	else
	{
		answer.integer = (x.integer + y.integer);
	}


	//decimal
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
		}
	}

	return answer;
}

static int calculate_pre_processing()
{

}


int calculate_main()
{

}
*/
