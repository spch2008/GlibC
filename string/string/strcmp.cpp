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

/* ע�⣺
   1. c1 == \'0' ��ֹ����һ�������ݣ����� "abc" == "abc"
      ��ʱ������ֹ��Ҳ������ֹ���ˣ���ʹ��ֹ��Ҳ�Ǵ����