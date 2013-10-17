#include "stdlib.h"
#include <cctype>
#include <climits>
#ifndef UNSIGNED
#define UNSIGNED 0
#endif

#if UNSIGNED
unsigned long int
#else
long int
#endif
strtol(const char *nptr, char **endptr, int base)
{
	if(nptr == NULL)
		goto noconv;

	const char *s = nptr;

	//eat white space
	while( isspace(*s) )
		++s;

	//get the sign
	int sign = *s == '-' ? -1 : 1;
	if( *s == '-' || *s == '+')
		++s;

	//get the base
	if(base < 0 || base == 1 || base > 36)
		base = 10;
	//if base is zero, figure out it ourselves
	if(base == 0)
	{
		if(*s == '0')
		{
			if(toupper(s[1]) == 'X')
			{
				base = 16;
				s += 2;
			}
			else
				base = 8;
		}
		else
			base = 10;
	}

	//used for check overflow
	unsigned long int cutoff = ULONG_MAX / (unsigned long int)base;
	unsigned long int cutlim = ULONG_MAX % (unsigned long int)base;

	//calc the value
	const char *save = s;
	int overflow     = 0;
	unsigned long int result = 0;
	for(unsigned char c = *s; c != '\0';  c = *++s)
	{
		if( isdigit(c) )
			c -= '0';
		else if( isalpha(c) )
			c = toupper(c) - 'A' + 10;
		else
			break;

		//check for valid character
		if( c >= base)
			break;

		//check for overflow
		if(result > cutoff || (result == cutoff && c > cutlim) )
		{
			//result *= (unsigned long int)base <=  result > cutoff
			//result == cutoff && c > cutlim    <=  result += c;
			overflow = 1;
			break;
		}
		else
		{
			result *= (unsigned long int)base;
			result += c;
		}
	}

	if( s == save)
		goto noconv;

	if(endptr != NULL)
		*endptr = (char*)s;

#if	!UNSIGNED
  /* Check for a value that is within the range of
     `unsigned long int', but outside the range of `long int'.  */
  if (result > (sign == -1 ?
	   (unsigned long int) - LONG_MIN : (unsigned long int) LONG_MAX))
    overflow = 1;
#endif


  if (overflow)
    {
#if	UNSIGNED
      return ULONG_MAX;
#else
      return sign == -1 ? LONG_MIN : LONG_MAX;
#endif
    }


  return sign * result;

noconv:
  if (endptr != NULL)
    *endptr = (char *) nptr;
  return 0L;
}

/*
  细节：
  1. base = 0时候，由程序来推测真实的进制
  */