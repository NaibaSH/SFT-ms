#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "stringhelp.h"
#include <string.h>
#include <ctype.h>
#include "log4c.h"

int main(void)
{
	struct Log4cStruct log = l4cOpen("log.txt", 0);
	l4cPrintf(&log, L4C_INFO, "Defining the tester ...");

	char testStr[] = { "This is a\n string with embedded newline character and\n12345 numbers inside it as well 67890" };
	l4cPrintf(&log, L4C_INFO, "indexString function is running and accept testStr as parameter... ");
	struct StringIndex index = indexString(testStr);
	int i;

	l4cPrintf(&log, L4C_INFO, "Calculating lines is running...");
	printf("LINES\n");
	for (i = 0; i < index.numLines; i++)
	{
		printUntil(index.str, index.lineStarts[i], '\n');
		printf("\n");
	}

	l4cPrintf(&log, L4C_INFO, "Calculating Words is running...");
	printf("\nWORDS\n");
	for (i = 0; i < index.numWords; i++)
	{
		printUntilSpace(index.str, index.wordStarts[i]);
		printf("\n");
	}

	l4cPrintf(&log, L4C_INFO, "Calculating Numbers is running...");
	printf("\nNUMBERS\n");
	for (i = 0; i < index.numNumbers; i++)
	{
		printUntilSpace(index.str, index.numberStarts[i]);
		printf("\n");
	}

	l4cPrintf(&log, L4C_INFO, "Program Done");
	l4cClose(&log);
	return 0;
}