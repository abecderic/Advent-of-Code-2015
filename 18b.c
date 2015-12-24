#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 100
#define STEPS 100

int *matrix;
int *matrixNew;

int getLight(int x, int y)
{
    if (x < 0 || y < 0 || x >= SIZE || y >= SIZE)
		return 0;
	else
		return matrix[y * SIZE + x];
}

void animate(void)
{
    int i;
    for (i = 0; i < SIZE*SIZE; i++)
	{
        int x = i%SIZE;
        int y = i/SIZE;
        int neighbors = 0;
        int dx;
        int dy;

		if ((x == 0 || x == SIZE-1) && (y == 0 || y == SIZE-1))
		{
			matrixNew[i] = 1;
			continue;
		}

        for (dy = -1; dy <= 1; dy++)
		{
			for (dx = -1; dx <= 1; dx++)
			{
				if (dy == 0 && dx == 0)
					continue;
                neighbors += getLight(x + dx, y + dy);
			}
		}

        if (matrix[i] == 1)
		{
            if (neighbors == 2 || neighbors == 3)
				matrixNew[i] = 1;
			else
				matrixNew[i] = 0;
		}
		else
		{
			if (neighbors == 3)
				matrixNew[i] = 1;
			else
				matrixNew[i] = 0;
		}
	}
}

void copyOver(void)
{
	int i;
	for (i = 0; i < SIZE*SIZE; i++)
	{
        matrix[i] = matrixNew[i];
	}
}

int main(void)
{
    matrix = malloc(SIZE * SIZE * sizeof(int));
    matrixNew = malloc(SIZE * SIZE * sizeof(int));
    if (!matrix || !matrixNew)
	{
		fprintf(stderr, "malloc failed\n");
		exit(-1);
	}

	int i = 0;
	int c;
	while ((c = getchar()) != EOF)
	{
		if (c == '\n' || c == '\r')
			continue;
		else if (c == '#')
			matrix[i] = 1;
		else if (c == '.')
			matrix[i] = 0;
		else
			fprintf(stderr, "unrecognized character: %c\n", c);
		i++;
	}

	for (i = 0; i < STEPS; i++)
	{
		animate();
		copyOver();
	}

	int lightsOn = 0;
	for (i = 0; i < SIZE*SIZE; i++)
	{
        if (matrix[i] == 1)
			lightsOn++;
	}

	printf("lights on after %d steps: %d\n", STEPS, lightsOn);
	return 0;
}
