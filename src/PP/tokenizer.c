#include "tokenizer.h"
#include <string.h>

const char* keywords[] = {
		"alignas","alignof","auto","bool","break","case","char",
		"const","constexpr","continue","default","do","double",
		"else","enum","extern","false","float","for","goto",
		"if","inline","int","long","nullptr","register","restrict",
		"return","short","signed","sizeof","static","static_assert","struct",
		"switch","thread_local","true","typedef","typeof","typeof_unqual",
		"union","unsigned","void","volatile","while","_Atomic","_BitInt",
		"_Complex","_Decimal128","_Decimal32","_Decimal64","_Generic","_Imaginary",
		"_Noreturn",
};

#define num_keywords (sizeof(keywords) / sizeof(char*))

//Valid identifier
//57  >= x >= 48
//90  >= x >= 65
//122 >= x >= 97
//95
//36


bool sap_tokenizer_is_keyword(const char* str, int len)
{
	for (int i = 0; i < num_keywords; ++i)
	{
		if (strncmp(str, keywords[i], len) == 0)
		{
			return true;
		}
	}

	return false;
}

bool sap_tokenizer_is_identifier(const char* str, int len)
{
#define x str[0]
	if (!(x >= 65 && x <= 90))
		if (!(x >= 97 && x <=122))
			if (x != 95)
				if (x != 36) return false;
#undef x
#define x str[i]
	for (int i = 1; i < len; ++i)
	{
		if (x >= 48 && x <= 57) continue;
		if (x >= 65 && x <= 90) continue;
		if (x >= 97 && x <=122) continue;
		if (x == 95)            continue;
		if (x == 36)            continue;
		return false;
	}
	return true;
#undef x
}