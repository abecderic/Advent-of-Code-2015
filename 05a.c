#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char line[17];
	int niceStrings = 0;

	while(scanf("%s", line) != EOF)
	{
		int vowels = 0;
		int lettersDouble = 0;
		int badStrings = 0;
		char last = EOF;
		int length = (int)strlen(line);

		for (int i = 0; i < length; i++)
		{
			if (line[i] == 'a' || line[i] == 'e' || line[i] == 'i' ||
				line[i] == 'o' || line[i] == 'u')
				vowels++;
			if (last != EOF)
			{
                if (last == line[i])
					lettersDouble++;
				if (last == 'a' && line[i] == 'b')
					badStrings++;
				if (last == 'c' && line[i] == 'd')
					badStrings++;
				if (last == 'p' && line[i] == 'q')
					badStrings++;
				if (last == 'x' && line[i] == 'y')
					badStrings++;
			}
			last = line[i];
		}
		if (vowels >= 3 && lettersDouble >= 1 && badStrings <= 0)
			niceStrings++;
	}
	printf("Nice strings: %d\n", niceStrings);
	return 0;
}
