#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 64
#define LINE_WORDS 11

#define INCREDIENTS 4
#define CAP_POS 2
#define DUR_POS 4
#define FLA_POS 6
#define TEX_POS 8
#define CAL_POS 10
#define TOTAL_TEASPOONES 100

int capacity[INCREDIENTS] = {0};
int durability[INCREDIENTS] = {0};
int flavor[INCREDIENTS] = {0};
int texture[INCREDIENTS] = {0};
int calories[INCREDIENTS] = {0};

unsigned int calcTotalScore(int n, int *teaspoones)
{
    int cap = 0;
    int dur = 0;
    int fla = 0;
    int tex = 0;

	int i;
	for (i = 0; i < n; i++)
	{
        cap += teaspoones[i] * capacity[i];
        dur += teaspoones[i] * durability[i];
        fla += teaspoones[i] * flavor[i];
        tex += teaspoones[i] * texture[i];
	}

    if (cap < 0)
		cap = 0;
	if (dur < 0)
		dur = 0;
	if (fla < 0)
		fla = 0;
	if (tex < 0)
		tex = 0;
	return (unsigned)(cap * dur * fla * tex);
}

unsigned int bestScore = 0;

void doSetTeaspoones(int n, int *values, int pos, int distribute)
{
    if (pos == n)
	{
        unsigned int score = calcTotalScore(n, values);
		if (score > bestScore)
			bestScore = score;
	}
	else if (distribute == 0)
	{
		values[pos] = 0;
		doSetTeaspoones(n, values, pos+1, distribute);
	}
	else
	{
        int i;
        for (i = 0; i <= distribute; i++)
		{
            values[pos] = i;
            doSetTeaspoones(n, values, pos+1, distribute-i);
		}
	}
}

int main(void)
{
	int incredient = 0;
	int state = 0;
	char word[MAX_WORD_LENGTH];

    while(scanf("%s", word) != EOF)
	{
		if (state == CAP_POS)
			capacity[incredient] = atoi(word);
		else if (state == DUR_POS)
			durability[incredient] = atoi(word);
		else if (state == FLA_POS)
			flavor[incredient] = atoi(word);
		else if (state == TEX_POS)
			texture[incredient] = atoi(word);
		else if (state == CAL_POS)
			calories[incredient] = atoi(word);

		state++;
		if (state == LINE_WORDS)
		{
			state = 0;
			incredient++;
		}
	}

	int values[INCREDIENTS] = {0};
	doSetTeaspoones(INCREDIENTS, values, 0, TOTAL_TEASPOONES);
    printf("best score: %d\n", bestScore);
	return 0;
}
