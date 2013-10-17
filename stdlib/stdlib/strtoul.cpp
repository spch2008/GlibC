
#define UNSIGNED 1
#include "strtol.cpp"

unsigned long int strtoul(const char *nptr, char **endptr, int base)
{
	return strtol(nptr, endptr, base);
}