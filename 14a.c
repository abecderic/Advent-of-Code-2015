#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MIN_INT -2147483648
#define MAX_WORD_LENGTH 64

#define LENGTH 2503
#define NAME_POS 0
#define SPEED_POS 3
#define FLYTIME_POS 6
#define RESTTIME_POS 13
#define LINE_WORDS 15

int evaluateReindeer(const int speed, const int flytime, const int resttime)
{
	int mode = 0; /* 0 = fly, 1 = rest */
	int i;
	int distance = 0;
	int counter = flytime;
	for (i = 0; i < LENGTH; i++)
	{
        if (mode == 0)
			distance += speed;
		counter--;
        if (counter == 0)
		{
            if (mode == 0)
			{
				mode = 1;
				counter = resttime;
			}
			else
			{
				mode = 0;
				counter = flytime;
			}
		}
	}
	return distance;
}

int main(void)
{
	int bestReindeer = MIN_INT;
	int state = 0;
	char line[MAX_WORD_LENGTH];
	int speed;
	int flytime;
	int resttime;

	while(scanf("%s", line) != EOF)
	{
		if (state == NAME_POS)
			printf("%s ", line);
		else if (state == SPEED_POS)
			speed = atoi(line);
		else if (state == FLYTIME_POS)
			flytime = atoi(line);
		else if (state == RESTTIME_POS)
			resttime = atoi(line);
		state++;
		if (state == LINE_WORDS)
		{
			state = 0;
			int length = evaluateReindeer(speed, flytime, resttime);
			printf("has travelled %d km.\n", length);
			if (length > bestReindeer)
				bestReindeer = length;
		}
	}
	printf("The best reindeer has travelled %d km.\n", bestReindeer);
	return 0;
}
