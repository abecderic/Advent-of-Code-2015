#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int floor = 0;
    int pos = 0;
    int c;

	while ((c = getchar()) != EOF)
	{
		pos++;
		if (c == '(')
			floor++;
		else if (c == ')')
			floor--;
		if (floor < 0) break;
	}
    printf("%d", pos);
    return 0;
}
