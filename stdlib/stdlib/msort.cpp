#include "stdlib.h"
#include <cstring>


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
		memcpy(tmp, base1, num1 * size);   //base1 | base2£¬ base2's elem is tail and sorted
	memcpy(base, t, (num - num2) * size);
}

