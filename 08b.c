#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    int encoded = 0;
    int chars = 0;
    int c;
    int last = EOF;

    while ((c = getchar()) != EOF)
	{
        if (c == '\"')
		{
			chars++;
			encoded += 2;
			last = c;
		}
		else if (c == '\\')
		{
			if (last == '\\')
			{
				chars++;
				last = EOF;
			}
			else
			{
				chars++;
				last = c;
			}
			encoded += 2;
		}
		else if (c == 'x' && last == '\\')
		{
            c = getchar();
            c = getchar();
            chars += 3;
            encoded += 3;
            last = c;
		}
		else if (!isblank(c) && c != '\n')
		{
			chars++;
			encoded++;
			last = c;
		}
		else if (c == '\n')
			encoded += 2;
	}
	printf("encoded: %d\tchars: %d\n", encoded, chars);
	printf("encoded-chars: %d\n", encoded-chars);
	return 0;
}
