#ifndef CALCULATE_H
#define CALCULATE_H

//vvvv		define

enum
{
	PLUS = 0,
	MINUS = 1,
	TIMES = 2,
	DIVIDE = 3,
	LEFI_BRACKET = 4,
	RIGHT_BRACKET = 5
};

typedef struct number
{
	_Bool negative;
	_Bool have_decimal;
	unsigned long integer;
	double decimal;
}num;

//vvvvvvvvvv	function

int calculate_main(char *expression);

num plus(num x, num y);
num minus(num x, num y);

#endif
