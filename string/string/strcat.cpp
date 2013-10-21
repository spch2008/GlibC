
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

/* ע�⣺
   1. destination �� source ���ܽ���
   2. ��++���ȼ��ߣ�������δ��֮ǰ�ĵ�ַ
   3. ���ʵ���Ͽ�����'\0'����Ϊc����'\0'ʱ��ֹͣ����ʱ
      '\0'�Ѿ���ֵ
*/