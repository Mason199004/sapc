#include "str.h"
#include <ctype.h>
#include <stdarg.h>
#include <string.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int sap_str_first_nonspace(const char* str, int limit)
{
	int i = 0;
	while (isspace(str[i]))
	{
		i++;
		if (i >= limit) return i;
	}
	return i;
}

int sap_str_first_space(const char* str, int limit)
{
	int i = 0;
	while (!isspace(str[i]))
	{
		i++;
		if (i >= limit) return i;
	}
	return i;
}

int sap_strn_matches(const char* to_cmp, int len, int count, ...)
{
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; ++i)
    {
        char* x = va_arg(args, char*);
        int min = MIN(len, strlen(x));
        if (strncmp(to_cmp, x, min) == 0)
        {
            va_end(args);
            return min;
        }
    }

    va_end(args);
    return 0;
}
