#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int c;
int amount;

unsigned int readNext(unsigned int pos, char *input)
{
	if (!isdigit(input[pos]))
	{
		fprintf(stderr, "not a number in input\n");
		exit(-1);
	}
	c = input[pos];
	int i;
	amount = 1;
	while ((i = input[pos++]) == c)
		amount++;
	amount--;
	pos--;
	c = c - '0';
	return pos;
}

int addNumber(int pos, char *input, int number)
{
	char str[15] = {0};
	snprintf(str, 15, "%d", number);

    int i = 0;
    while (str[i] != '\0')
	{
        input[pos++] = str[i++];
	}
	return pos;
}

int main(void)
{
    const char *input = "1113122113";
    const int repeats = 40;
    char *seqO;
    char *seqN;
    unsigned int length;
    int i;


	seqO = malloc(strlen(input) + 1);
	if (!seqO)
	{
		fprintf(stderr, "malloc fail on seqO\n");
		exit(-1);
	}
	strcpy(seqO, input);

	seqN = malloc(strlen(input) + 1);
	if (!seqN)
	{
		fprintf(stderr, "malloc fail on seqN\n");
		exit(-1);
	}

    for (i = 0; i < repeats; i++)
	{
		length = strlen(seqO);
		seqN = realloc(seqN, (length + 1) * 2);
		if (!seqN)
		{
			fprintf(stderr, "realloc fail on seqN\n");
			exit(-1);
		}

		unsigned int posO = 0;
		int posN = 0;
        while (posO < length)
		{
            posO = readNext(posO, seqO);
			posN = addNumber(posN, seqN, amount);
			posN = addNumber(posN, seqN, c);
		}
        seqN[posN] = '\0';

		seqO = realloc(seqO, (strlen(seqN) + 1) * 2);
		if (!seqO)
		{
			fprintf(stderr, "realloc fail on seqO\n");
			exit(-1);
		}
		strcpy(seqO, seqN);
	}
    printf("length: %d\n", strlen(seqN));
	return 0;
}
