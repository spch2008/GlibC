#include "stdlib.h"
#include <cstring>
#include <malloc.h>



void msort_with_tmp(void *base, size_t num, size_t size,
                    int (*compare)(const void *, const void *),
					char *t)
{
	if( num <= 1)
		return;

	int num1    = num / 2;
	char *base1 = (char*)base;
	int num2    = num - num1;
	char *base2 = (char*)base + size * num1;

	msort_with_tmp(base1, num1, size, compare, t);
	msort_with_tmp(base2, num2, size, compare, t);

	char *tmp = t;
	while(num1 > 0 && num2 > 0)
	{
		if( (*compare)(base1, base2) <= 0)
		{
			memcpy(tmp, base1, size);
			base1 += size;
			--num1;
		}
		else
		{
			memcpy(tmp, base2, size);
			base2 += size;
			 --num2;
		}
		tmp += size;
	}
	if(num1 > 0)                             
		memcpy(tmp, base1, num1 * size);   //base1 | base2， base2's elem is tail and sorted
	memcpy(base, t, (num - num2) * size);
}

void qsort(void *base, size_t total_num, size_t size, 
	       int (*cmp)(const void *, const void *))
{
	size_t total_size = size * total_num;
	if(total_size < 1024)
	{
		msort_with_tmp(base, total_num, size, cmp, (char*)alloca(total_size) );
	}
	else
	{
		char *tmp = (char*)malloc(size);
		if(tmp == NULL)
		{
			extern void _quicksort(void *base, size_t total_num, size_t size, int (*compare)(const void *, const void *) );
			_quicksort(base, total_num, size, cmp);
		}
		else
		{
			msort_with_tmp(base, total_num, size, cmp, tmp );
			free( tmp );
		}
	}
}

/*
  注意：
  使用_quicksort时，需要extern声明
*/