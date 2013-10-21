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


#define min(a, b) ( (a) > (b) ? (b) : (a) )

// define stack
struct stack_node
{
	char *lo;
	char *hi;	
};
#define PUSH(low, high) ( (void) ( (top->lo = (low)), (top->hi = (high)), ++top) )
#define POP(low, high)  ( (void) ( top--, ((low) = top->lo), ((high) = top->hi)) )
#define STACK_NOT_EMPTY (stack < top)


void _quicksort(void *base, size_t total_num, size_t size, 
	           int (*compare)(const void *, const void *) )
{
	if(total_num == 0)
		return;

	char *pivot_buffer = (char*)alloca(size);
	char *pbase        = (char*)base;


	const size_t max_thresh = MAX_THRESH * size; 
	if(total_num > MAX_THRESH) 
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

			//find the pivot, using three median value
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

			//the elems left_ptr and right_ptr point to are sorted��left middle right��
			//so we omit them to speed up
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
					// += size prepare for below sort env
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

    
	char *end_ptr    = &pbase[ size * (total_num - 1) ];
	//because maybe the length of the array is less than maxthresh
	char *thresh_ptr = min(end_ptr, pbase + max_thresh); 

	/* set up a sentinel to speed the inner loop */
	char *tmp_ptr = pbase;
	char *run_ptr = pbase;
	for(run_ptr += size; run_ptr <= thresh_ptr; run_ptr += size)
		if( (*compare)(run_ptr, tmp_ptr) < 0 )
			tmp_ptr = run_ptr;
	if(tmp_ptr != pbase)
		SWAP(pbase, tmp_ptr, size);

	//insert sort
	run_ptr = pbase;
	while( (run_ptr+=size) <= end_ptr)
	{
		//find insert position
		tmp_ptr = run_ptr - size;
		while( (*compare)(run_ptr, tmp_ptr) < 0 )
			tmp_ptr -= size;
		tmp_ptr += size;

		if(tmp_ptr != run_ptr)
		{
			char *trav = run_ptr + size;
			while(--trav >= run_ptr)
			{
				char c = *trav;
                char *hi, *lo;

                for (hi = lo = trav; (lo -= size) >= tmp_ptr; hi = lo)
					*hi = *lo;
                *hi = c;
			}
		}
	}
}
			

/*
 1. ����з����������м䣬����ҪlogN�Σ� NΪ��������
    �����У����ǽ����һ�˼���ջ�У�����С�ģ������ܿ���
	��logN���д�����
 2. �������㹻С��ʱ�򣬲��ò�����������˵�С����϶�����
    �����������Сֵ--�����з�ԭ��
 3. ��ʵ���У�������������˰��ֽڿ���
 4. ˼�룺ģ��ջ����һ����ѹ��ջ����һ���ֽ��д�������С������
          �������ѹ��ջ��
 5. MAX_THRESH��Ԫ�����崦���ʱ��ʹ�ã���max_thresh������Ԫ�ش�Сsize��
    ��ָ�����ֽڼ����ʱ��ʹ��
 6. ����֪ʶ���������򣬿�������ջ˼��
 7. do {} while(0) ���������Զ��Ż������ڲ�Ԫ����Ϊһ������,while(0)���޷ֺ�
    http://blog.csdn.net/chenhu_doc/article/details/856468
*/
