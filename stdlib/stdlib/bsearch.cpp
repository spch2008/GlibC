#include "stdlib.h"
void* bsearch (const void *key, const void *base,
	           size_t num, size_t size,
			   int (*compare)(const void *, const void *) )
{
	size_t l = 0;
	size_t u = num;
	size_t m;
	const void *p;
	while(l < u)
	{
		m = (l + u) / 2;
		p = ( ( (const char *)base ) + ( size * m) );
		int cmp = (*compare)(key, p);

		if(cmp > 0)
			u = m;
		else if(cmp < 0)
			l = m + 1;
		else
			return (void*)p;
	}
	return NULL;
}

/* ע�⣺
   1. void *ָ�벻�ܽ��мӼ�������ע��ת��char *
   2. l < u �� l <= u
      �ؼ�֮������ֻʣ����Ԫ�ص�ʱ�򣬼�l��u�ֱ�ָ�����ڵ�
	  ����Ԫ�ء���ʱ�����u�ĳ�ʼֵָ��ĩβ��Ԫ�أ���u��ָ
	  ������Ҫ�жϣ� l <= u������, m = (l + u) / 2���Խ���
	  ���β����������uָ��ĩβ����ָ��ĩβԪ�أ�m = (l + u) / 2
	  ֻ��Ҫ����lָ���Ԫ�أ���uָ���Ԫ�ز���Ҫ�Ƚ�

	  l < u �� l <= u ����������������Ԫ�ص�ʱ��

	3. ʹ�ö���������Ԫ�ر�������
  */

/*
void* bsearch (const void *key, const void *base,
	           size_t num, size_t size,
			   int (*compare)(const void *, const void *) )
{
	size_t l = 0;
	size_t u = num - 1;
	size_t m;
	const void * p;
	while( l <= u)
	{
		m = (l + u ) / 2;
		p = ( (char *)base + (size *m) );
		int cmp = (*compare)(key, p);

		if(cmp > 0)
			u = m - 1;
		else if(cmp < 0)
			l = m + 1;
		else
			return (void *)p;
	}
	return NULL;
}
*/