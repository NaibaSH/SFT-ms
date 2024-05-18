#define _CRT_SECURE_NO_WARNINGS
#include "stringhelp.h"
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "log4c.h"
int nextWhite(const char* str)
{
	struct Log4cStruct log = l4cOpen("log.txt", 1);
	l4cPrint(&log, L4C_INFO, "nextWhite(): Is running.");

	int i, result = -1;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			result = i;
		}
		else {
			char errorMsg[256];
			snprintf(errorMsg, sizeof(errorMsg), "Unexpected character at index %d: '%c'", i, str[i]);
			l4cError(&log, errorMsg);
		}
	}
	if (result < 0) {
		l4cError(&log, "Assertion failed in nextWhite(): result is negative.");
	}
	l4cPrint(&log, L4C_INFO, "nextWhite() result: %d", result);
	l4cPrintf(&log, L4C_INFO, "nextWhite(): End of function.");
	l4cClose(&log);

	return result >= 0 ? result : i;
}
int isNumber(const char* str, const int len)
{
	struct Log4cStruct log = l4cOpen("log.txt", 1);
	l4cInfo(&log, "isnumber(): Has been called for string: ");
	l4cPrintf(&log, L4C_INFO, " isnumber() str: %s", str);
	l4cPrintf(&log, L4C_INFO, "isnumber() length: %d", len);
	int i, result = 1;
	for (i = 0; i <= len && result; i++)
	{
		l4cPrintf(&log, L4C_INFO, "isnumber() str: %s", str);
		result = isdigit(str[i]);
	}
	l4cPrintf(&log, L4C_INFO, "nextWhite() result: %d", result);
	l4cInfo(&log, " isnumber(): End of function ...");
	l4cClose(&log);

	return result;
}
struct StringIndex indexString(const char* str)
{
	struct Log4cStruct log = l4cOpen("log.txt", 0);
	l4cPrintf(&log, L4C_INFO, " Entering indexString Function");
	assert(str != NULL);
	l4cPrintf(&log, L4C_INFO, "Test string: %s", str);
	struct StringIndex result = { {0}, {0}, {0}, 0, 0, 0 };
	char buf[MAX_WORD_SIZE + 1] = { 0 };
	int i, sp;
	strcpy(result.str, str);
	if (str[0] != '\0')
	{
		result.lineStarts[0] = 0;
		result.numLines = 1;
		assert(result.numLines == 1);
		assert(result.lineStarts[0] == 0);
		l4cPrintf(&log, L4C_INFO, "Found newline at index %d: %s", 0, getLine(&result, 0));
	}
	for (i = 0; str[i] != '\0'; i++)
	{
		l4cPrintf(&log, L4C_INFO, "Current value of 'i' in the iteration = %d: ", i);
		while (str[i] != '\0' && isspace(str[i]))
		{
			if (str[i] == '\0')
			{
				result.lineStarts[result.numLines++] = i + 1;
				l4cPrintf(&log, L4C_INFO, " Found new line at index %d: %s", result.lineStarts[result.numLines - 1]
					, getLine(&result, result.numLines - 1));
			}
			i++;
		}
		for (sp = 0; str[sp + i] != '\0' && !isspace(str[sp + i]); sp++);
		if (isNumber(str + i, sp))
		{
			result.numberStarts[result.numNumbers++] = i;
			l4cPrintf(&log, L4C_INFO, "New number starts at index %d", result.numberStarts[result.numNumbers - 1]);
		}
		else
		{
			result.wordStarts[result.numWords++] = i;
			l4cPrintf(&log, L4C_INFO, "New word starts at index %d", result.wordStarts[result.numWords - 1]);
		}
		i += sp - 1;
	}
	assert(strlen(result.str) == strlen(str));
	l4cPrintf(&log, L4C_INFO, "Exiting indexstringFunction");
	return result;
}
int getNumberLines(const struct StringIndex* idx)
{
	return idx->numLines;
}
int getNumberWords(const struct StringIndex* idx)
{
	return idx->numWords;
}
int getNumberNumbers(const struct StringIndex* idx)
{
	return idx->numNumbers;
}
void getWord(char word[], const struct StringIndex* idx, int wordNum)
{
	int i, sp, start;
	word[0] = '\0';
	if (wordNum < idx->numWords && wordNum >= 0)
	{
		start = idx->wordStarts[wordNum];
		sp = nextWhite(idx->str + start);
		for (i = 0; i <= sp; i++)
		{
			word[i] = idx->str[start + i];
		}
		word[sp] = '\0';
	}
}
void getNumber(char word[], const struct StringIndex* idx, int numberNum)
{
	int i, sp, start;
	word[0] = '\0';
	if (numberNum < idx->numNumbers && numberNum >= 0)
	{
		start = idx->numberStarts[numberNum];
		sp = nextWhite(idx->str + start);
		for (i = 0; i < sp; i++)
		{
			word[i] = idx->str[sp + i];
		}
		word[sp] = '\0';
	}
}
char* getLine(struct StringIndex* idx, int lineNum)
{
	char* result = NULL;
	if (lineNum < idx->numLines && lineNum >= 0)
	{
		result = idx->str + idx->lineStarts[lineNum];
	}
	return result;
}
void printUntil(const char* s, const int start, const char terminator)
{
	int i;
	for (i = start; s[i] != '\0' && s[i] != terminator; i++)
		printf("%c", s[i]);
}
void printUntilSpace(const char* s, const int start)
{
	int i;
	for (i = start; s[i] != '\0' && !isspace(s[i]); i++)
		printf("%c", s[i]);
}