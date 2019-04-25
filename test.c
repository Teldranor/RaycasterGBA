#include <stdlib.h>
#include <stdio.h>

int main()
{
	unsigned char a = 0b10101010;
	for (unsigned char i=0; i<11; i++) {
		unsigned char b = a;
		unsigned char j = i;
		printf("b = %d =\t", a);
		while (b) {
			if (b & 1)
				printf("1");
			else
				printf("0");
			b >>= 1;
		}
		printf("\n");
		printf("j = %d =\t", i);
		while (j) {
			if (j & 1)
				printf("1");
			else
				printf("0");
			j >>= 1;
		}
		printf("\n");
		unsigned char r = a & i;
		printf("r = %d =\t", r);
		while (r) {
			if (r & 1)
				printf("1");
			else
				printf("0");
			r >>= 1;
		}
		printf("\n");
	}
	return 0;
}
