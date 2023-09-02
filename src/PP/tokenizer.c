#include "tokenizer.h"
#include "../STR/str.h"
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

const char* punctuators[] = {
			"[",  "]",  "(",  ")",  "{",  "}",  ".",  "->",
			"++",  "--", "&", "*", "+", "-", "~", "!",
			"/", "%", "<<", ">>", "<", ">", "<=", ">=",
			"==", "!=", "^", "|", "&&", "||","?", ":",
			"::", ";", "...","=", "*=", "/=", "%=", "+=",
			"-=", "<<=", ">>=", "&=", "^=", "|=",",", "#",
			"##","<:", ":>", "<%", "%>", "%:", "%:%:"
};

#define num_keywords (sizeof(keywords) / sizeof(char*))
#define num_punctuators (sizeof(punctuators) / sizeof(char*))

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

bool sap_tokenizer_is_punctuator(const char* str, int len)
{
	for (int i = 0; i < num_punctuators; ++i)
	{
		if (strncmp(str, punctuators[i], len) == 0)
		{
			return true;
		}
	}

	return false;
}

bool is_octal(char c)
{
    return c >= 0 && c <= 7;
}

bool is_hex(char c)
{
    return c>= 0 && c <= 9 || c >= 'a' && c <= 'f' || c >= 'A' && c <= 'F';
}

int sap_tokenizer_is_string_lit(const char* str, int len)
{
    int i = sap_strn_matches(str, len, 4, "u", "U", "L", "u8");

    if (str[i++] == '"')
	{
		while (str[i] != '"')
		{
			if (str[i] == '\\')
			{
				if (sap_strn_matches(str + i, 2, 11, "\\’", "\\\"", "\\?", "\\n", "\\a", "\\b", "\\f", "\\n", "\\r", "\\t", "\\v"))
				{
					i+=2;
					continue;
				}
				if (is_octal(str[i + 1]))
				{
					i+=2;
					continue;
				}
				if (is_hex(str[i + 1]))
				{
					i+=2;
					continue;
				}
				return 0;
			}
			if (str[i] == '\n')
			{
				return 0;
			}
			i++;
		}
		return ++i;
	}
	return 0;
}