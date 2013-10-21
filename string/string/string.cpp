// string.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "string.h"
using std::cout;
using std::endl;


int main(int argc, char* argv[])
{
	char one[100] = "abcd";
	cout << one << endl;

	char *two = "efghigklmnopqrst";
	strcat(one, two);
	cout << one << endl;

	system("pause");
	return 0;
}

