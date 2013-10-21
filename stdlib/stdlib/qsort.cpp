#include "stdlib.h"
#include <malloc.h>  //alloca
#include <string.h>  //memcpy

#define MAX_THRESH 4
#define CHAR_BIT 8
#define STACK_SIZE CHAR_BIT * sizeof(size_t)

#define SWAP(a, b, size)					 \
  do									      \
    {									      \
      register size_t __size = (size);					      \
      register char *__a = (a), *__b = (b);				      \
      do								        \
	  {								            \
	       char __tmp = *__a;						      \
		   *__a++ = *__b;						      \
		   *__b++ = __tmp;						      \
	  } while (--__size > 0);						      \
     } while (0)


// define stack
struct stack_node
{
	char *lo;
	char *hi;	
};
#define PUSH(low, high) ( (void) ( (top->lo = (low)), (top->hi = (high)), ++top) )
#define POP(low, high)  ( (void) ( top--, ((low) = top->lo), ((high) = top->hi)) )
#define STACK_NOT_EMPTY (stack < top)


void quicksort(const void *base, size_t total_num, size_t size, 
	           int (*compare)(const void *, const void *) )
{
	if(total_num == 0)
		return;

	char *pivot_buffer = (char*)alloca(size);
	char *pbase        = (char*)base;

	//const size_t max_thresh = MAX_THRESH * size;
	const size_t max_thresh = 1;
	if(total_num > max_thresh) 
	{
		stack_node stack[STACK_SIZE];
		stack_node *top = stack + 1;

		char *lo = pbase;
		char *hi = &pbase[ size * (total_num - 1) ];

		while(STACK_NOT_EMPTY)
		{
			char *left_ptr  = lo;
			char *right_ptr = hi;
			char *mid_ptr   = lo +  size * ( (hi - lo) / size >> 1);

			char *pivot = pivot_buffer;
			if( compare(mid_ptr, left_ptr) < 0)
				SWAP(left_ptr, mid_ptr, size);
			if( compare(right_ptr, mid_ptr) < 0)
				SWAP(mid_ptr, right_ptr, size);
			else
				goto jump_over;

			if( compare(left_ptr, mid_ptr) < 0)
				SWAP(left_ptr, mid_ptr, size);
            jump_over:;
			memcpy(pivot, mid_ptr, size);

			left_ptr  += size;
			right_ptr -= size;

			do
			{
				while( compare(left_ptr, pivot) < 0)
					left_ptr  += size;
				while( compare(pivot, right_ptr) < 0)
					right_ptr -= size;

				if(left_ptr == right_ptr)
				{
					left_ptr  += size;
					right_ptr -= size;
					break;
				}
				else
				{
					SWAP(left_ptr, right_ptr, size);
					left_ptr  += size;
					right_ptr -= size;
				}
			}while( left_ptr < right_ptr);

			if( (size_t)(right_ptr - lo) <= max_thresh )
			{
				if( (size_t)(hi - left_ptr) <= max_thresh)
					POP(lo, hi);
				else
					lo = left_ptr;
			}
			else if( (size_t)(hi - left_ptr) <= max_thresh ) 
			{
				hi = right_ptr;
			}
			else if( (size_t)(right_ptr - lo) <= (size_t)(hi - left_ptr) )
			{
				PUSH(left_ptr, hi);
				hi = right_ptr;
			}
			else
			{
				PUSH(lo, right_ptr);
				lo = left_ptr;
			}
		}
	}
}


/*
 1. 如果切分区间总在中间，则需要logN次， N为数据总量
    此题中，总是将大的一端加入栈中，处理小的，所以总可以
	在logN次中处理完
 2. 在区间足够小的时候，采用插入排序。最左端的小区间肯定包含
    整个数组的最小值--快排切分原理
 3. 该实现中，插入排序采用了按字节拷贝
*/
