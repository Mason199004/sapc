#include "str.h"
#include <ctype.h>

int sap_str_first_nonspace(const char* str)
{
	int i = 0;
	while (isspace(str[i]))
	{
		i++;
	}
	return i;
}

int sap_str_first_space(const char* str)
{
	int i = 0;
	while (!isspace(str[i]))
	{
		i++;
	}
	return i;
}
