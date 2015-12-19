#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int c = 0;

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
	}

	if (c == EOF)
		return 0;
    while ((c = getchar()) != EOF)
	{
        if (isdigit(c))
			buffer[i++] = (char)c;
		else break;
	}
	return atoi(buffer);
}

int main(void)
{
	int sum = 0;

	while (c != EOF)
	{
		sum += getNextNumber();
	}

	printf("sum: %d\n", sum);
	return 0;
}
