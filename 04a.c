#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int s[] = { 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
	5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
	4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
	6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21};

unsigned int k[] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

unsigned int leftrotate(unsigned int x, unsigned int c)
{
	return (x << c) | (x >> (32 - c));
}

void addIntToArray(char bytes[], int start, unsigned int value)
{
	bytes[start] = (char)(value & 0xFF);
	bytes[start+1] = (char)((value >> 8) & 0xFF);
	bytes[start+2] = (char)((value >> 16) & 0xFF);
	bytes[start+3] = (char)((value >> 24) & 0xFF);
}

/* only works with inputs with 64 bytes of memory allocated and less than 56 bytes of data */
char* md5(char input[], char *result)
{
    int length = (int)strlen(input);

	int i;
	/* add '1' bit and '0' bits until byte length == 56
	 * add message length in bits as little endian */
	input[length] = (char)128;
	for (i = length+1; i < 56; i++)
		input[i] = '\0';
	input[i++] = (char)((length*8) % 256);
	input[i++] = (char)((length*8) / 256);
	for (; i < 64; i++)
		input[i] = '\0';

	unsigned int message[16];
	for (i = 0; i < 16; i++)
	{
		message[i] = (unsigned char)input[4*i+3];
		message[i] = message[i] * 256 + (unsigned char)input[4*i+2];
		message[i] = message[i] * 256 + (unsigned char)input[4*i+1];
		message[i] = message[i] * 256 + (unsigned char)input[4*i];
	}

	/* init hash value */
	unsigned int a0 = 0x67452301;
	unsigned int b0 = 0xEFCDAB89;
	unsigned int c0 = 0x98BADCFE;
	unsigned int d0 = 0x10325476;
	unsigned int a = a0;
	unsigned int b = b0;
	unsigned int c = c0;
	unsigned int d = d0;

	unsigned int f;
	unsigned int g;

	/* main loop */
	for (i = 0; i < 64; i++)
	{
		if (0 <= i && i < 16)
		{
			f = (b & c) | ((~b) & d);
            g = (unsigned)i;
		}
		else if (16 <= i && i < 32)
		{
			f = (b & d) | (c & (~d));
			g = (unsigned)((5*i + 1) % 16);
		}
		else if (32 <= i && i < 48)
		{
            f = b ^ c ^ d;
            g = (unsigned)((3*i + 5) % 16);
		}
		else if (48 <= i && i < 64)
		{
            f = c ^ (b | (~d));
            g = (unsigned)((7*i) % 16);
		}

		unsigned int t = d;
		d = c;
		c = b;
		b = b + leftrotate(a + f + k[i] + message[g], s[i]);
		a = t;
	}

	a0 += a;
	b0 += b;
	c0 += c;
	d0 += d;

	//char result[16];
	addIntToArray(result, 0, a0);
	addIntToArray(result, 4, b0);
	addIntToArray(result, 8, c0);
	addIntToArray(result, 12, d0);

    return result;
}

int main(void)
{
	const char *key = "bgvyzdsv";
	char *input = malloc(64);
	char *result = malloc(16);

	int n = 1;
	while (1)
	{
		char *buffer = malloc(16);
		strcpy(input, key);
		sprintf(buffer, "%d",n);
		strcat(input, buffer);

		md5(input, result);
		if (result[0] == 0 && result[1] == 0 && ((unsigned char)result[2]) < 0x0f)
		{
			printf("found result: n=%d, md5=", n);
			int i;
			for (i = 0; i < 16; i++)
				printf("%02x ", (unsigned char)result[i]);
			printf("\n");
			break;
		}
		n++;
	}

	return 0;
}
