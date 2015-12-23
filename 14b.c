#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MIN_INT -2147483648
#define MAX_WORD_LENGTH 64
#define INIT_SIZE 8
#define ADD_AMOUNT 8

#define LENGTH 2503
#define SPEED_POS 3
#define FLYTIME_POS 6
#define RESTTIME_POS 13
#define LINE_WORDS 15

int getMaximum(unsigned int n, int *values)
{
    unsigned int i;
    int max = MIN_INT;
    for (i = 0; i < n; i++)
	{
		if (values[i] > max)
			max = values[i];
	}
	return max;
}

int main(void)
{
	unsigned int reindeers = 0;
	unsigned int size = INIT_SIZE;
	int state = 0;
	char line[MAX_WORD_LENGTH];
	int *speed = malloc(size * sizeof(int));
	int *flytime = malloc(size * sizeof(int));
	int *resttime = malloc(size * sizeof(int));

	if (!speed || !flytime || !resttime)
	{
		fprintf(stderr, "malloc fail\n");
		exit(-1);
	}

	while(scanf("%s", line) != EOF)
	{
		if (state == SPEED_POS)
			speed[reindeers] = atoi(line);
		else if (state == FLYTIME_POS)
			flytime[reindeers] = atoi(line);
		else if (state == RESTTIME_POS)
			resttime[reindeers] = atoi(line);
		state++;
		if (state == LINE_WORDS)
		{
			state = 0;
			reindeers++;
			if (reindeers >= size)
			{
				size += ADD_AMOUNT;
				speed = realloc(speed, size * sizeof(int));
				flytime = realloc(flytime, size * sizeof(int));
				resttime = realloc(resttime, size * sizeof(int));
				if (!speed || !flytime || !resttime)
				{
					fprintf(stderr, "realloc failed (%d)\n",reindeers);
					exit(-1);
				}
			}
		}
	}

	int *mode = malloc(reindeers * sizeof(int));
	int *counter = malloc(reindeers * sizeof(int));
	int *distance = malloc(reindeers * sizeof(int));
	int *points = malloc(reindeers * sizeof(int));
	if (!mode || !counter || !distance || !points)
	{
		fprintf(stderr, "malloc 2 failed\n");
		exit(-1);
	}

	int i;
	unsigned int reindeer;
	for (reindeer = 0; reindeer < reindeers; reindeer++)
	{
		mode[reindeer] = 0;
		counter[reindeer] = flytime[reindeer];
        distance[reindeer] = 0;
        points[reindeer] = 0;
	}
	for (i = 0; i < LENGTH; i++)
	{
        for (reindeer = 0; reindeer < reindeers; reindeer++)
		{
			if (mode[reindeer] == 0)
				distance[reindeer] += speed[reindeer];
			counter[reindeer]--;
			if (counter[reindeer] == 0)
			{
				if (mode[reindeer] == 0)
				{
					mode[reindeer] = 1;
					counter[reindeer] = resttime[reindeer];
				}
				else
				{
					mode[reindeer] = 0;
					counter[reindeer] = flytime[reindeer];
				}
			}
		}
		int max = getMaximum(reindeers, distance);
		for (reindeer = 0; reindeer < reindeers; reindeer++)
		{
			if (distance[reindeer] == max)
				points[reindeer]++;
		}
	}
	printf("The best reindeer has %d points.\n", getMaximum(reindeers, points));
	return 0;
}
