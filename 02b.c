#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char line[14];
	int total = 0;

	while(scanf("%s", line) != EOF)
	{
		int dim[3];
		char* number = strtok(line, "x");
		for (int i = 0; i < 3; i++)
		{
			dim[i] = strtol(number, (char **)NULL, 10);
			number = strtok(NULL, "x");
		}

		int ribbon = dim[0]+dim[2] < dim[1]+dim[2] ? dim[0]+dim[2] : dim[1]+dim[2];
		ribbon = dim[0]+dim[1] < ribbon ? dim[0]+dim[1] : ribbon;
		ribbon *= 2;
		int bow = dim[0]*dim[1]*dim[2];

		total += ribbon+bow;
	}

	printf("%d",total);
	return 0;
}
