#include <cctype>
#include <cmath>
#include <cfloat>
#define NULL 0


/* The function first discards as many whitespace characters 
   (as in isspace) as necessary until the first non-whitespace character is found. 
   Then, starting from this character, takes as many characters as possible 
   that are valid following a syntax resembling that of floating point literals (see below), 
   and interprets them as a numerical value. A pointer to the rest of the string after the last valid character 
   is stored in the object pointed by endptr.
   http://www.cplusplus.com/reference/cstdlib/strtod/?kw=strtod
*/

double strtod(const char *nptr, char **endptr)
{
	if(nptr == NULL)
		goto noconv;

	const char *s = nptr;

	//skip white space
	while( isspace(*s) )
		++s;

	//get the sign
	int sign = *s == '-' ? -1 : 1;
	if( *s == '+' || *s =='-')
		++s;

	//check for "a123"
	const char *save = s;

	//calc the value
	int exponent = 0;
	int got_dot   = 0;
	double result = 0;
	for(char c = *s; *s != '\0'; ++s)
	{
		if( isdigit(*s) )
		{
			if(result > DBL_MAX * 0.1)
				exponent++;
			else
				result = result * 10.0 + (*s - '0');

			if(got_dot)
				exponent--;
		}
		else if(!got_dot && *s == '.')
			got_dot = 1;
		else
			break;
	}

	if(save == s)
		goto noconv;

	if(endptr != NULL)
		*endptr = (char*)s;

	//check for overflow or underflow
	//result times (10 to exponent) 
	if(exponent > 0)
	{
		/*
		    result * pow(10.0, (double) exponent) > DBL_MAX
			but may cause overflow, and may less than DBL_MAX
		*/
		if (result > DBL_MAX * pow(10.0, (double) -exponent)) 
			goto overflow;
	}
	else if(exponent < 0)
	{
		if (result < DBL_MIN * pow(10.0, (double) -exponent))
			goto underflow;
	}

	result *= pow(10.0, (double)exponent);

	return sign * result;



overflow:
	return HUGE_VAL * sign;

underflow:
	if(endptr != NULL)
		*endptr = (char*)nptr;
	return 0.0;

noconv:
	if(endptr != NULL)
		*endptr = (char *)nptr;
	return 0.0;
}

/* 
  细节：
  1.endptr记录处理字符串的最后一个字符，如果下溢或noconv，则等于nptr
  2.overflow时候返回一个大数,此时endptr仍为正常
  3.endptr等于'\0'表示转换正常，否则出错

  思路：
  1.double的有效数字位数为15-16位
  2.123456.1111 小数点后数字仍然按照点前数字处理，只记录指数位数即可，后续统一处理
  3.如果位数超出有效位数，则略去后续数字
    举例：（假设有效位数5）DBL_MAX = 99999
	1.下溢：0.00456789 result = 45678 exponent = -7
	2.上溢：56789123   result = 56789 exponent = 3  56789后，处理1时，exponent自增
	3.5678912345.12222 result = 56789 exponent = 5
	超出有效位数，且出现小数点，exponent不变，即小数点后不影响指数，
	当有效位数满后，只有影响指数大小的操作才会进行记录
*/