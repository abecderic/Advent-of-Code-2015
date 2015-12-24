#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 256

#define CHILDREN 3
#define CATS 7
#define SAMOYEDS 2
#define POMERANIANS 3
#define AKITAS 0
#define VIZSLAS 0
#define GOLDFISH 5
#define TREES 3
#define CARS 2
#define PERFUMES 1

int main(void)
{
	int sue;
	int amount;
	char line[MAX_LINE_LENGTH];

	while(scanf("%[^\n]%*c", line) != EOF)
	{
		int result = 1;
		char *part = malloc(sizeof(char) * MAX_LINE_LENGTH);
		if (!part)
		{
			fprintf(stderr, "malloc failed\n");
			exit(-1);
		}
		strcpy(part, line);

		part = strtok(part, " "); /* Sue */
		part = strtok(NULL, " "); /* number */
		sue = atoi(part);

		part = strtok(NULL, " "); /* item */
        while (part != NULL)
		{
			if (!strcmp(part, "children:")) amount = CHILDREN;
			else if (!strcmp(part, "cats:")) amount = CATS;
			else if (!strcmp(part, "samoyeds:")) amount = SAMOYEDS;
			else if (!strcmp(part, "pomeranians:")) amount = POMERANIANS;
			else if (!strcmp(part, "akitas:")) amount = AKITAS;
			else if (!strcmp(part, "vizslas:")) amount = VIZSLAS;
			else if (!strcmp(part, "goldfish:")) amount = GOLDFISH;
			else if (!strcmp(part, "trees:")) amount = TREES;
			else if (!strcmp(part, "cars:")) amount = CARS;
			else if (!strcmp(part, "perfumes:")) amount = PERFUMES;
			else fprintf(stderr, "item %s not found\n", part);

            part = strtok(NULL, " "); /* amount */
            int value = atoi(part);
            if (amount != value)
				result = 0;

			part = strtok(NULL, " "); /* item */
		}

		if (result)
			printf("Sue: %d\n", sue);
	}
	return 0;
}
