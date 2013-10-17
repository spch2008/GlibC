
#include "stdlib.h"
#define UNSIGNED 1


unsigned long int strtoul(const char *nptr, char **endptr, int base)
{
	return strtol(nptr, endptr, base);
}