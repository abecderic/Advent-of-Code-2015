#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define AMOUNT 150

int *containers;
int minFilledContainers = AMOUNT;
int possibilities = 0;

void doLoop(int currentAmount, int pos, int filledContainers, int n)
{
	if (pos == n)
	{
		if (currentAmount == AMOUNT && filledContainers < minFilledContainers)
		{
			possibilities = 1;
			minFilledContainers = filledContainers;
		}
		else if (currentAmount == AMOUNT && filledContainers == minFilledContainers)
			possibilities++;
	}
	else
	{
        doLoop(currentAmount, pos + 1, filledContainers, n); /* don't fill current container */
        doLoop(currentAmount + containers[pos], pos + 1, filledContainers + 1, n); /* fill current container */
	}
}

int main(void)
{
    int amount = 0;
    containers = malloc(sizeof(int));
	if (!containers)
	{
		fprintf(stderr, "malloc fail\n");
		exit(-1);
	}

	char line[sizeof(int)];
	while(scanf("%s", line) != EOF)
	{
        amount++;
        containers = realloc(containers, (unsigned)amount * sizeof(int));
        if (!containers)
		{
			fprintf(stderr, "realloc fail\n");
			exit(-1);
		}

        containers[amount-1] = atoi(line);
	}

	doLoop(0, 0, 0, amount);
	printf("possibilities: %d\n", possibilities);
	return 0;
}
