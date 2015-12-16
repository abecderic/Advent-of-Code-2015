#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    int code = 0;
    int chars = 0;
    int c;
    int last = EOF;

    while ((c = getchar()) != EOF)
	{
        if (c == '\"')
		{
			if (last == '\\')
			{
				code++;
				chars++;
			}
			else
			{
				code++;
			}
			last = c;
		}
		else if (c == '\\')
		{
			if (last == '\\')
			{
				code++;
				chars++;
				last = EOF;
			}
			else
			{
				code++;
				last = c;
			}
		}
		else if (c == 'x' && last == '\\')
		{
            c = getchar();
            c = getchar();
            code += 3;
            chars++;
            last = c;
		}
		else if (!isblank(c) && c != '\n')
		{
			code++;
			chars++;
			last = c;
		}
	}
	printf("code: %d\tchars: %d\n", code, chars);
	printf("code-chars: %d\n", code-chars);
	return 0;
}
