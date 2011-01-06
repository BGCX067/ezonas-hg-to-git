#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <iostream>
using namespace std;

typedef unsigned long ulong;

class primecodec
{
	string filename; // the filename where the numbers will be saved as text
	bool dump(); // writes into a file
	bool get(); // read from a file
	bool dump_bool(); // writes booleans into a file, serves is_prime()
	bool get_bin(); // read from a file

protected:

	ulong num_cap; // doesn't compute number larger than this
	ulong count; // numbers of prime numbers computed
	int sz;

	ulong * primes; // the actual prime number array
	bool * crible; // the eratosthene crible

	ulong cribler(); // compute the crible
	void prime_stack (); // ?

	void pop_list(int r); // shows the prime number


public:
	void pop_list2(int r); // shows the prime number's number
	// (ex: 3 is the 2nd prime number)
	void counter (int step); // ? - oh yeah this shows how much primes there is in a slice/interval of numbers. This just seemed to be useless.
	void show();

	void read(string flname);
	void write(string flname);
	void write_bin();

	void gen(ulong cap);
	// this function generates the sieve, it did not make this in the constructor because it can optionnaly open a bin/text file.
	void is_prime (ulong n);

// default constructor

	primecodec();
	~primecodec();
};
