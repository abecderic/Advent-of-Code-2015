#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 64
#define START_LINES 10

struct tableentry
{
	char *key;
	int value;
	struct tableentry *next;
};

int tablesize = 0;
struct tableentry table;
const struct tableentry empty;

void putInTable(struct tableentry *entry, char *key, int value)
{
    if (entry->key != NULL && !strcmp(key, entry->key))
	{
		/* edit value if key already exists */
		entry->value = value;
	}
    else if (entry->next == NULL)
	{
		/* add new key-value pair */
		struct tableentry *next = malloc(sizeof(struct tableentry));
		next->key = malloc(strlen(key));
		strcpy(next->key, key);
		next->value = value;
		next->next = NULL;
		entry->next = next;
		tablesize++;
	}
	else
		putInTable(entry->next, key, value);
}

int getFromTable(struct tableentry *entry, char *key)
{
    if (entry == NULL)
		return -1;
    if (entry->key != NULL && !strcmp(key, entry->key))
	{
        while (entry->value < 0) entry->value += 0xFFFF;
        return entry->value % 0xFFFF;
	}
	else
		return getFromTable(entry->next, key);
}

void printTable(struct tableentry *entry)
{
	if (entry == NULL) return;
	printf("%s: %u (%d)\n", entry->key, (unsigned short)(entry->value % 0xFFFF), entry->value);
	printTable(entry->next);
}

void freeTable(struct tableentry *entry)
{
    if (entry == NULL) return;
    freeTable(entry->next);
    free(entry);
}

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

int strEndsWith(const char *string, const char *suffix)
{
    size_t stringL = strlen(string);
    size_t suffixL = strlen(suffix);
    return strncmp(string + stringL - suffixL, suffix, suffixL) == 0;
}

int getValueOf(char *);

int simpleGetValueOf(char *wire)
{
	/* if this isn't a wire but a value */
    if (isdigit(wire[0]))
		return atoi(wire);

	/* wire only 1 character long -> add space infront */
    if (strlen(wire) == 1)
    {
        char newWire[3] = {0};
        newWire[0] = ' ';
        newWire[1] = wire[0];
        newWire[2] = '\0';
        wire = newWire;
    }

    int i = getFromTable(&table, wire);
    if (i != -1)
		return i;
	else
    {
    	int j = getValueOf(wire);
        putInTable(&table, wire, j);
        return j;
    }
}

int getValueOf(char *wire)
{
	int i;
	for (i = 0; i < current_line; i++)
	{
        if (strEndsWith(lines[i], wire))
		{
			/* part is string up to -> */
			char *part = malloc(sizeof(char) * MAX_LINE_LENGTH);
			strcpy(part, lines[i]);
			part = strtok(part, "-");

            if (strstr(part, "AND") != NULL)
			{
				char *part1 = strtok(part, " ");
                part = strtok(NULL, " "); /* the AND */
                char *part2 = strtok(NULL, " ");

                int value1 = simpleGetValueOf(part1);
                int value2 = simpleGetValueOf(part2);
                return (value1 & value2) & 0xFFFF;
			}
			else if (strstr(part, "OR") != NULL)
			{
                char *part1 = strtok(part, " ");
                part = strtok(NULL, " "); /* the OR */
                char *part2 = strtok(NULL, " ");

                int value1 = simpleGetValueOf(part1);
                int value2 = simpleGetValueOf(part2);
                return (value1 | value2) & 0xFFFF;
			}
			else if (strstr(part, "NOT") != NULL)
			{
                part = strtok(part, " "); /* the NOT */
                char *part0 = strtok(NULL, " ");

                int value0 = simpleGetValueOf(part0);
                return (~value0) & 0xFFFF;
			}
			else if (strstr(part, "LSHIFT") != NULL)
			{
				char *part1 = strtok(part, " ");
                part = strtok(NULL, " "); /* the LSHIFT */
                char *part2 = strtok(NULL, " ");

                int value1 = simpleGetValueOf(part1);
                int value2 = simpleGetValueOf(part2);
                return (value1 << value2) & 0xFFFF;
			}
			else if (strstr(part, "RSHIFT") != NULL)
			{
				char *part1 = strtok(part, " ");
                part = strtok(NULL, " "); /* the RSHIFT */
                char *part2 = strtok(NULL, " ");

                int value1 = simpleGetValueOf(part1);
                int value2 = simpleGetValueOf(part2);
                return (value1 >> value2) & 0xFFFF;
			}
			else if (isdigit(part[0]))
			{
                return atoi(part);
			}
			else
			{
                /* remove trailing space */
                if (part[2] == ' ')
                {
                	part[2] = '\0';
                }
				if (part[1] == ' ')
				{
					part[1] = '\0';
				}
				return simpleGetValueOf(part);
			}
		}
	}
	printf("Wire %s not found!\n", wire);
	return -1;
}

int main(void)
{
	readStdinIntoLines();

    const char *key = " a";
	char *wire = malloc(strlen(key) + 1);
    strcpy(wire, key);
    int i = getValueOf(wire);
	printf("a is: %d\n", i);

	freeTable(&table);
	freeLines();
	return 0;
}
