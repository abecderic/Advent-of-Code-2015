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
	int santaX = 0;
	int santaY = 0;
	int roboX = 0;
	int roboY = 0;
	int turn = 0; /* 0 = santa, 1 = robo */
	size = 2;
	houses = malloc(2 * sizeof(int));

	houses[0] = santaX;
	houses[1] = santaY;
	while((c = getchar()) != EOF)
	{
        int x;
        int y;
        if (turn == 0)
		{
			if (c == '^') santaY++;
			else if (c == '>') santaX++;
			else if (c == 'v') santaY--;
			else if (c == '<') santaX--;
			x = santaX;
			y = santaY;
			turn = 1;
		}
        else if (turn == 1)
		{
			if (c == '^') roboY++;
			else if (c == '>') roboX++;
			else if (c == 'v') roboY--;
			else if (c == '<') roboX--;
			x = roboX;
			y = roboY;
			turn = 0;
		}

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
