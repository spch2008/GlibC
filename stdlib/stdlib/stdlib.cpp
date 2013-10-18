// stdlib.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <malloc.h>
#include "stdlib.h"
using std::cout;
using std::endl;

int compare(const void *key, const void *elem)
{
	return *((int*)key) - *((int*)elem);
}

int main(int argc, char* argv[])
{
	int arr[] = {1,2,3,5,8,12,15,23,45,78};
	int key = 15;
	int *ptr = (int*)bsearch(&key, arr, sizeof(arr)/sizeof(int), sizeof(int), compare);

	cout << *ptr << endl;

	int *p = (int*)alloca(102400000);
	cout << p << endl;

	system("pause");
	return 0;
}

