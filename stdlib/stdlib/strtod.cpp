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
  ϸ�ڣ�
  1.endptr��¼�����ַ��������һ���ַ�����������noconv�������nptr
  2.overflowʱ�򷵻�һ������,��ʱendptr��Ϊ����
  3.endptr����'\0'��ʾת���������������

  ˼·��
  1.double����Ч����λ��Ϊ15-16λ
  2.123456.1111 С�����������Ȼ���յ�ǰ���ִ���ֻ��¼ָ��λ�����ɣ�����ͳһ����
  3.���λ��������Чλ��������ȥ��������
    ��������������Чλ��5��DBL_MAX = 99999
	1.���磺0.00456789 result = 45678 exponent = -7
	2.���磺56789123   result = 56789 exponent = 3  56789�󣬴���1ʱ��exponent����
	3.5678912345.12222 result = 56789 exponent = 5
	������Чλ�����ҳ���С���㣬exponent���䣬��С�����Ӱ��ָ����
	����Чλ������ֻ��Ӱ��ָ����С�Ĳ����Ż���м�¼
*/