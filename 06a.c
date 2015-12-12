#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char lights[1000][1000] = {{0}};

int main(void)
{
	char line[64];

	while(scanf("%[^\n]%*c", line) != EOF)
	{
        char *line2 = malloc(64);
        strcpy(line2, line);
        char *part;
        int mode = -1; /* 0 = turn off, 1 = toggle, 2 = turn on */

        part = strtok(line2, " ");
        if (!part)
			printf("ERROR: Part missing in line %s\n", line);
        if (!strcmp(part, "toggle"))
		{
			mode = 1;
		}
		else if (!strcmp(part, "turn"))
		{
			part = strtok(NULL, " ");
			if (!part)
				printf("ERROR: Part missing in line %s\n", line);
            if (!strcmp(part, "on"))
			{
				mode = 2;
			}
			else if (!strcmp(part, "off"))
			{
				mode = 0;
			}
			else
			{
				printf("ERROR: Unexpected token in line %s\n", line);
			}
		}
		else
		{
			printf("ERROR: Unexpected token in line %s\n", line);
		}

		int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
		part = strtok(NULL, " ,");
        if (!part)
			printf("ERROR: Part missing in line %s\n", line);
		x1 = atoi(part);
		part = strtok(NULL, " ,");
        if (!part)
			printf("ERROR: Part missing in line %s\n", line);
		y1 = atoi(part);

		part = strtok(NULL, " ");
        if (!part)
			printf("ERROR: Part missing in line %s\n", line);

		part = strtok(NULL, " ,");
        if (!part)
			printf("ERROR: Part missing in line %s\n", line);
		x2 = atoi(part);
		part = strtok(NULL, " ,");
        if (!part)
			printf("ERROR: Part missing in line %s\n", line);
		y2 = atoi(part);

		for (int j = y1; j <= y2; j++)
		{
			for (int i = x1; i <= x2; i++)
			{
				if (mode == 0)
					lights[j][i] = 0;
				else if (mode == 2)
					lights[j][i] = 1;
				else if (mode == 1)
					lights[j][i] = lights[j][i] == 0 ? 1 : 0;
			}
		}
	}

	int lightsLit = 0;
	for (int j = 0; j < 1000; j++)
	{
		for (int i = 0; i < 1000; i++)
		{
			if (lights[j][i] == 1)
				lightsLit++;
		}
	}

	printf("Lights lit: %d\n", lightsLit);
	return 0;
}
