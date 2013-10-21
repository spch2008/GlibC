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
	int arr[] = {6,2,4,9, 8,5 ,34,23,45,11,98,56,30,12,3454,678,234,120,898,345,123};
	quicksort(arr, sizeof(arr) / sizeof(int), sizeof(int), compare);

	for(int i = 0; i < sizeof(arr) / sizeof(int); i++)
		cout << arr[i] << " ";
	cout << endl;

	system("pause");
	return 0;
}

