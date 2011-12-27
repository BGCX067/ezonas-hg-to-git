#include <stdio.h>
#include <stdlib.h>

#define BYTE unsigned char

typedef unsigned long long int SizeType;

const SizeType Limit = 10000000000ULL;

int main () {
	printf("%ld\n", sizeof(SizeType));
	printf("%lld\n", 10000000000ULL);
	BYTE *sieve = malloc(Limit);
	if (sieve!=NULL) {
		printf("Wow, it worked!\n");
		free(sieve);
	} else {
		printf("Too damn big.\n");
		printf("Trying bits.\n");
		sieve = malloc(Limit/8);
		if (sieve!=NULL) {
			printf("We can do bits.\n");
			free(sieve);
		} else {
			printf("Still too damn big.\n");
		}
	}
	return 0;
}
