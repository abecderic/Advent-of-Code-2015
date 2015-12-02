#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int floor = 0;
    int c;

	while ((c = getchar()) != EOF)
	{
		if (c == '(')
			floor++;
		else if (c == ')')
			floor--;
	}
    printf("%d", floor);
    return 0;
}
