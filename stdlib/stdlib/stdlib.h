#ifndef _STDLIB_H
#define _STDLIB_H

#define NULL 0

extern long int strtol(const char *nptr, char **endptr, int base);
extern double strtod(const char *nptr, char **endptr);
extern unsigned long int strtoul(const char *nptr, char **endptr, int base);
extern void qsort(void *base, size_t total_num, size_t size, int (*cmp)(const void *, const void *));

#endif