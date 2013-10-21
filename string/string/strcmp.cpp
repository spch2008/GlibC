#include "string.h"

int strcmp ( const char * str1, const char * str2 )
{
	char c1, c2;
	do
	{
		c1 = *str1++;
		c2 = *str2++;
		if( c1 == '\0')
			return c1 - c2;
	}while( c1 == c2);

	return c1 - c2;
}

/* 注意：
   1. c1 == \'0' 防止出现一样的数据，比如 "abc" == "abc"
      此时可能终止，也可能终止不了，即使终止，也是错误答案