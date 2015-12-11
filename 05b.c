#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char line[17];
	int niceStrings = 0;

	while(scanf("%s", line) != EOF)
	{
		int amountPairs = 0;
		int amountRepeats = 0;
		int length = (int)strlen(line);

		for (int i = 1; i < length; i++)
		{
			for (int j = 1; j < i-1; j++)
			{
				if (line[j-1] == line[i-1] && line[j] == line[i])
					amountPairs++;
			}
			if (i >= 2 && line[i-2] == line[i])
				amountRepeats++;
		}
		if (amountPairs >= 1 && amountRepeats >= 1)
			niceStrings++;
	}
	printf("Nice strings: %d\n", niceStrings);
	return 0;
}
