#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_LINE_LENGTH 64
#define START_LINES 10
#define MIN_INT -2147483648

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

int getHappiness(int *array, int n)
{
	int happiness = 0;
	int i;

    for (i = 1; i < n; i++)
	{
        happiness += matrix[array[i-1] * n + array[i]];
        happiness += matrix[array[i] * n + array[i-1]];
	}

	happiness += matrix[array[n-1] * n + array[0]];
	happiness += matrix[array[0] * n + array[n-1]];
	return happiness;
}

int currentMax = MIN_INT;

void doPermutation(int *array, int start, int n)
{
    if (start >= n)
	{
        int happiness = getHappiness(array, n);
        if (happiness > currentMax)
			currentMax = happiness;
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
	int people = (int)(0.5 * (sqrt(4 * (double)i + 1) + 1)) + 1;

	matrix = malloc((unsigned int)people * (unsigned int)people * sizeof(int));

	for (i = 0; i < people*people; i++)
		matrix[i] = 0;

	int personA = 0;
	int personB = 0;
	int modifier;
	int happiness;

	/* fill matrix with happiness units in/decrease */
	for (i = 0; i < current_line; i++)
	{
		char *part = malloc(sizeof(char) * MAX_LINE_LENGTH);
		if (!part)
		{
			fprintf(stderr, "malloc failed for line %d\n", i);
			exit(-1);
		}
		strcpy(part, lines[i]);

		personB++;
		if (personB == people-1)
		{
			personA++;
			personB = 0;
		}
		if (personB == personA)
			personB++;

		part = strtok(part, " "); /* name */
		part = strtok(NULL, " "); /* would */
		part = strtok(NULL, " "); /* gain / lose */
		if (!strcmp(part, "gain"))
			modifier = 1;
		else if (!strcmp(part, "lose"))
			modifier = -1;
		else
		{
			fprintf(stderr, "unexpected part %s in line %d\n", part, i);
			exit(-1);
		}

		part = strtok(NULL, " "); /* happiness unit */
		happiness = atoi(part);

		/* don't care about rest of line */
		matrix[personB * people + personA] = modifier * happiness;
	}

	int array[people];
	for (i = 0; i < people; i++)
		array[i] = i;
	doPermutation(array, 0, people);

	printf("maximum happiness: %d\n", currentMax);

	freeLines();
	return 0;
}
