#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int c = 0;
int last = 0;
int last2 = 0;

int getNextNumber(void)
{
    char buffer[64] = {0};
	int i = 0;
    while((c = getchar()) != EOF)
	{
		if (isdigit(c) || c == '-')
		{
			buffer[i++] = (char)c;
			break;
		}
		else if (c == '{' || c == '}' || c == '[' || c == ']')
			break;

		if (last2 == 'r' && last == 'e' && c == 'd')
			break;
		last2 = last;
		last = c;
	}

	if (c == EOF || c == '{' || c == '}' || c == 'd' || c == '[' || c == ']')
		return 0;
    while ((c = getchar()) != EOF)
	{
        if (isdigit(c))
			buffer[i++] = (char)c;
		else break;
	}
	return atoi(buffer);
}

int getNumberFromObj(void);

int getNumberFromArr(void)
{
	int sum = 0;
    while (c != EOF)
	{
		sum += getNextNumber();
		if (c == '{')
			sum += getNumberFromObj();
		else if (c == '[')
			sum += getNumberFromArr();
		else if (c == ']')
			break;
	}
	return sum;
}

int getNumberFromObj(void)
{
    int reds = 0;
    int sum = 0;
    while (c != EOF)
	{
		sum += getNextNumber();
		if (c == '{')
			sum += getNumberFromObj();
		else if (c == '}')
			break;
		else if (c == '[')
			sum += getNumberFromArr();
		else if (c == 'd')
			reds++;
	}
	if (reds > 0)
		return 0;
	else
		return sum;
}

int main(void)
{
	int sum = getNumberFromObj();

	printf("sum: %d\n", sum);
	return 0;
}
