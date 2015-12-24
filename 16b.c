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

#define CHILDREN_M 0
#define CATS_M -1
#define SAMOYEDS_M 0
#define POMERANIANS_M 1
#define AKITAS_M 0
#define VIZSLAS_M 0
#define GOLDFISH_M 1
#define TREES_M -1
#define CARS_M 0
#define PERFUMES_M 0

int main(void)
{
	int sue;
	int amount;
	int modifier;
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
			if (!strcmp(part, "children:")) { amount = CHILDREN; modifier = CHILDREN_M;}
			else if (!strcmp(part, "cats:")) { amount = CATS; modifier = CATS_M;}
			else if (!strcmp(part, "samoyeds:")) { amount = SAMOYEDS; modifier = SAMOYEDS_M;}
			else if (!strcmp(part, "pomeranians:")) { amount = POMERANIANS; modifier = POMERANIANS_M;}
			else if (!strcmp(part, "akitas:")) { amount = AKITAS; modifier = AKITAS_M;}
			else if (!strcmp(part, "vizslas:")) { amount = VIZSLAS; modifier = VIZSLAS_M;}
			else if (!strcmp(part, "goldfish:")) { amount = GOLDFISH; modifier = GOLDFISH_M;}
			else if (!strcmp(part, "trees:")) { amount = TREES; modifier = TREES_M;}
			else if (!strcmp(part, "cars:")) { amount = CARS; modifier = CARS_M;}
			else if (!strcmp(part, "perfumes:")) { amount = PERFUMES; modifier = PERFUMES_M; }
			else fprintf(stderr, "item %s not found\n", part);

            part = strtok(NULL, " "); /* amount */
            int value = atoi(part);
            if (modifier == 0 && amount != value)
				result = 0;
			else if (modifier == -1 && value <= amount)
				result = 0;
			else if (modifier == 1 && value >= amount)
				result = 0;

			part = strtok(NULL, " "); /* item */
		}

		if (result)
			printf("Sue: %d\n", sue);
	}
	return 0;
}
