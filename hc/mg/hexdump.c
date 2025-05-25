


#include <stdio.h>
#include <stdint.h>


void hex_dump(const char* a, uint8_t* b, unsigned c)
{
	int r14;
	char fp20[20];
	unsigned i = 0;
	if (a != 0)
	{
		fprintf(stderr, "DATA: %s", a);
	}
	fp20[16] = 0;
	while (i != c)
	{
    char r0;
		int r19 = i % 16;
		if (r19 == 0)
		{
			if ((a != 0) || (i != 0))
			{
				fprintf(stderr, "\n");
			}
			fprintf(stderr, "%04x ", i);
		}
		else if ((i % 4) == 0)
		{
			fprintf(stderr, " |");
		}
		fprintf(stderr, " %02X", *b);

		r0 = *b;
		if ((r0 < ' ') || (r0 >= 0x80))
		{
			r0 = '.';
		}
		fp20[r19] = r0;
		if (r19 == 15)
		{
			fprintf(stderr, "  %s", fp20);
		}
		i++;
		b++;
	}
	while ((r14 = i % 16) != 0)
	{
		if ((i % 4) == 0)
		{
			fprintf(stderr, "  ");
		}
		fprintf(stderr, "   ");
		fp20[r14] = 0;
		if (r14 == 15)
		{
			fprintf(stderr, "  %s", fp20);
			break;
		}
		i++;
	}
	fprintf(stderr, "\n");
}

