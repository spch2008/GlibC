#ifndef _STDLIB_H
#define _STDLIB_H

#define NULL 0

long int strtol(const char *nptr, char **endptr, int base);
double strtod(const char *nptr, char **endptr);
unsigned long int strtoul(const char *nptr, char **endptr, int base);
void quicksort(const void *base, size_t total_num, size_t size, int (*compare)(const void *, const void *) );

#endif