// string.cpp : Defines the entry point for the console application.
//
#include "string.h"
#include <stdio.h>


int main(int argc, char* argv[])
{
	char *str1 = "abc";
	char *str2 = "abc";

    int result = strcmp(str1, str2);
	printf("%d\n", result);
	getchar();

	return 0;
}

