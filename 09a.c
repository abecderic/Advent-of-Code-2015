#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 64
#define START_LINES 10
#define MAX_INT 2147483647

int lines_allocated;
char **lines;
int current_line;

void readStdinIntoLines(void)
{
	/* allocate memory for lines */
	lines = (char **)malloc(sizeof(char *) * START_LINES);
	if (!lines)
	{
		fprintf(stderr, "Out of memory! (size = %d)\n", START_LINES);
		exit(-1);
	}
	lines_allocated = START_LINES;

	current_line = 0;
	char line[MAX_LINE_LENGTH];

	while(scanf("%[^\n]%*c", line) != EOF)
	{
        if (current_line >= lines_allocated)
		{
            /* get more memory */
            lines_allocated += START_LINES;
            lines = (char **)realloc(lines, sizeof(char *) * (unsigned)lines_allocated);
            if (!lines)
			{
				fprintf(stderr, "Out of memory! (size = %d)\n", lines_allocated);
				exit(-1);
			}
		}
		/* allocate memory for line */
        lines[current_line] = malloc(MAX_LINE_LENGTH);
        if (!lines[current_line])
		{
			fprintf(stderr, "Out of memory! (size = %d) at line %d\n", lines_allocated, current_line);
			exit(-1);
		}
		/* put line in array */
		strcpy(lines[current_line], line);
		current_line++;
	}
}

void freeLines(void)
{
	/* free memory */
	for (current_line--; current_line >= 0; current_line--)
	{
		free(lines[current_line]);
	}
	free(lines);
}

int *matrix;

int getLength(int *array, int n)
{
	int length = 0;
	int i;

    for (i = 1; i < n; i++)
	{
        length += matrix[array[i-1] * n + array[i]];
	}

	return length;
}

int currentMin = MAX_INT;

void doPermutation(int *array, int start, int n)
{
    if (start >= n)
	{
        int length = getLength(array, n);
        if (length < currentMin)
			currentMin = length;
	}
	else
	{
		int i;
		int j;

		for (i = 0; i < n; i++)
		{
			/* if already in array, don't add again */
			for (j = 0; j < start; j++)
			{
				if (array[j] == i)
				{
					j = -1;
					break;
				}
			}

			if (j != -1)
			{
				array[start] = i;
				doPermutation(array, start+1, n);
			}
		}
	}
}

int main(void)
{
	readStdinIntoLines();

	int i = current_line;
	int n = 1; /* amount of places */

    while (i >= n)
    {
    	i -= n;
    	n++;
    }

	matrix = malloc((unsigned int)(n) * (unsigned int)(n) * sizeof(int));
	int originID = 0;
	int destinationID = 0;
	int length;

	/* fill matrix with distances */
	for (i = 0; i < current_line; i++)
	{
		char *part = malloc(sizeof(char) * MAX_LINE_LENGTH);
		strcpy(part, lines[i]);

		destinationID++;
		if (destinationID == n)
		{
			originID++;
			destinationID = originID+1;
		}

		part = strtok(part, " ");
		part = strtok(NULL, " ");
		part = strtok(NULL, " ");
		part = strtok(NULL, " ");
		part = strtok(NULL, " ");
		/* we only care about the number at the end */
        length = atoi(part);

        matrix[originID * n + destinationID] = length;
        matrix[destinationID * n + originID] = length;
	}

	int array[n];
	for (i = 0; i < n; i++)
		array[i] = i;
	doPermutation(array, 0, n);

	printf("shortest distance: %d\n", currentMin);

	freeLines();
	return 0;
}
