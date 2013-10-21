
#include "string.h"

char * strcat ( char * destination, const char * source )
{
	char *s1 = destination;
	const char *s2 = source;

	//find the tail destination
	char c;
	do
	{
		c = *s1++;
	}while( c != '\0');

	//return the last character of destination
	s1 -= 2;

	//copy from source to destination containning '\0'
	do
	{
		c = *s2++;
		*++s1 = c;
	}while( c != '\0');

	return destination;
}

/* 注意：
   1. destination 与 source 不能交叉
   2. 后++优先级高，但返回未加之前的地址
   3. 最后，实际上拷贝了'\0'。因为c等于'\0'时候停止，此时
      '\0'已经赋值
*/