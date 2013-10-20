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
	cout << sizeof(unsigned long int) << endl;

	system("pause");
	return 0;
}

