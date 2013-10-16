
#include <cctype>
const int INT_MIN = -2147483648;
const int INT_MAX = 2147483647;

int atoi(const char *nptr)
{
	const char *s = nptr;
	//skip white  space
	while(isspace(*s))
		++s;

	if(*s == '\0')
		goto noconv;

	//check for a sign
	int negative = 0;
    if(*s == '+')
	{
		negative = 0;
		++s;
	}
	else if(*s == '-')
	{
		negative = 1;
		++s;
	}

	//check for "+\0" or "-\0" or"+a"
	const char *save = s;

	int base   = 10;
	//unsigned can store bigger value£¬ can use to judge overflow
	unsigned int result = 0; 
	for(char c = *s; c != '\0'; c = *++s)
	{
		//calc the distance of asclls
		if( isdigit(c) )
			c -= '0';
		else
			break;

		result *= base;
		result += c;
	}

	if( s == save)
		goto noconv;

	//check for overflow  
	//overflow : such as -8 ~ 7£¬ any num lower than -8 or bigger than 7
	int overflow = 0;
	if( result > ( negative ? (unsigned)-INT_MIN : (unsigned)INT_MAX) )
		overflow = 1;
	if(overflow)
		return negative ? INT_MIN : INT_MAX;

	//got correct result
	return negative ? result : -result;

noconv:
	return 0;
}