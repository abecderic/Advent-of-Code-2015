#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LENGTH 8

void incrementString(char *string, int pos)
{
    if (string[pos] == 'z')
	{
		string[pos] = 'a';
        if (pos > 0) incrementString(string, pos-1);
	}
	else
		string[pos]++;
}

int hasStraight(char *string)
{
    int i;
    for (i = 0; i < LENGTH; i++)
	{
        if (string[i-2]+1 == string[i-1] && string[i-1]+1 == string[i])
			return 1;
	}
	return 0;
}

int onlyAllowed(char *string)
{
    int i;
    for (i = 0; i < LENGTH; i++)
	{
		if (string[i] == 'i' || string[i] == 'o' || string[i] == 'l')
			return 0;
	}
	return 1;
}

int hasDouble(char *string)
{
    int doubles = 0;
	int i;
	for (i = 1; i < LENGTH; i++)
	{
		if (string[i-1] == string[i])
		{
			doubles++;
			i++;
		}
	}
	return doubles >= 2;
}

int main(void)
{
    const char *input = "hxbxwxba";
    const int amount = 2;
    char *string = malloc(strlen(input) + 1);
    if (!string)
	{
		fprintf(stderr, "malloc fail with string\n");
		exit(-1);
	}
    strcpy(string, input);

	int i;
	for (i = 0; i < amount; i++)
	{
		while (!hasStraight(string) || !onlyAllowed(string) || !hasDouble(string))
		{
			incrementString(string, LENGTH-1);
		}
		if (i < amount-1) incrementString(string, LENGTH-1);
	}
    printf("%s\n", string);
	return 0;
}
