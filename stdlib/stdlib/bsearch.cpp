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

/* 注意：
   1. void *指针不能进行加减操作，注意转成char *
   2. l < u 与 l <= u
      关键之处在于只剩两个元素的时候，即l与u分别指向相邻的
	  两个元素。此时，如果u的初始值指向末尾的元素，则u所指
	  内容需要判断， l <= u，这样, m = (l + u) / 2可以进行
	  两次操作。而如果u指向末尾而不指向末尾元素，m = (l + u) / 2
	  只需要处理l指向的元素，而u指向的元素不需要比较

	  l < u 与 l <= u 分歧出现在最后两个元素的时候

	3. 使用二分搜索，元素必须排序
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