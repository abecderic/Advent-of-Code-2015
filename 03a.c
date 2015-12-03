#include <stdio.h>
#include <stdlib.h>

int size;
int *houses;

int contains(int x, int y)
{
	for (int i = 0; i+1 < size; i += 2)
	{
		if (houses[i] == x && houses[i+1] == y) return 1;
	}
	return 0;
}

int main(void)
{
	int c;
	int x = 0;
	int y = 0;
	size = 2;
	houses = malloc(2 * sizeof(int));

	houses[0] = x;
	houses[1] = y;
	while((c = getchar()) != EOF)
	{
        if (c == '^') y++;
        else if (c == '>') x++;
        else if (c == 'v') y--;
        else if (c == '<') x--;

        if (!contains(x, y))
		{
			houses = realloc(houses, (unsigned)size * 2 * sizeof(int));
			houses[size++] = x;
			houses[size++] = y;
		}
	}

	printf("%d", (size/2));
	return 0;
}
