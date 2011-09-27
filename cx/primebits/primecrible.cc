#include "primecrible.h"
#include "21030.h"
#include <cstdlib>

string Crible :: number_fmt(intg n)
{
	// cout << "(" << n << ")" << endl;
	char s[128];
	sprintf(s, "%lu", n);
	string r(s);
	reverse(r.begin(), r.end());
	int space_inserted = 0;
	size_t how_many_spaces = r.length() / 3;

	if(r.length() % 3 != 0)
		how_many_spaces += 1;

	for(int i = 1; i < how_many_spaces; ++i)
	{
		r.insert(3 * i + space_inserted, " ");
		space_inserted += 1;
	}
	reverse(r.begin(), r.end());

	return r;
}
void print_spaces_bytes(ulong n)
{
//	ulong len   = n % 1000;
//	ulong len_K = (n % 1000000) / 1000;
//	ulong len_M = (n % 1000000000) / 1000000;
//	ulong len_G = n / 1000000000;

	intg n8 = n / 8UL;
	
	intg len8   = n8 % 1000;
	intg len_K8 = (n8 % 1000000) / 1000;
	intg len_M8 = (n8 % 1000000000) / 1000000;
//	ulong len_G8 = n8 / 1000000000;
	
	// printf("%lu bits = %lu bytes\n", n, n8);

	// printf("%03lu %03lu %03lu %03lu bits = %03luG %03luM %03luK %03lu bytes\n",
	// printf("0x%lX bits = %03luM %03luK %03lu bytes\n", // UINT
	printf("0x%lX bits = %03luM %03luK %03lu bytes\n",
		// len_G,  len_M,  len_K,  len,
		n,
		// len_G8,
		len_M8, len_K8, len8);
}
Crible :: Crible (int _line_size): pack(NULL), crible(NULL), array(NULL), count(0U)
{
	cout << "bitset hard limit (set at compile time) = ";
	print_spaces_bytes(BITS);
}
void Crible :: Generate (intg _size_sieve)
{
	size_sieve = _size_sieve;
	cout << "crible size (how far the sieve will go) = ";
	print_spaces_bytes(size_sieve);

	size_array  = size_sieve / INTG_BITS;
	// cout << "[GEN] Using Eratosthenes Sieve algorithm to find primes" << endl;
	cout << "[GEN] allocating bitset of " << number_fmt(BITS) << " bits" << endl;
	// cout << "[GEN] remember that depending of BITS value, this can crash" << endl;
	
	crible = (new bitset<BITS>);

	// cout << "[GEN] setting all bits to 1, setting [0] and [1] as not primes" << endl;
	crible->set();
	(* crible)[0] = false;
	(* crible)[1] = false;
	cout << "[GEN] let's loop !" << endl;
	time_t start = time(NULL);

	for (intg i = 2; i < size_sieve; ++i)
	{
		// if there is a false, loop next (false means i is not prime)
		if((* crible)[i] == false) continue;
		++ count;
		// zeroes out all numbers from 2*m to n (means here, i is prime)
		// for(ulong k = 2; i*k < size_sieve; ++k)
		for(intg k = 2; i*k < size_sieve; ++k)
			(* crible)[i*k] = false;
	}
	time_t end = time(NULL);
	double sec = difftime(end, start);
	if (sec > 1.0) 
		cout << "[GEN] found " << number_fmt(count) <<
		" prime numbers in " << sec << " seconds" << endl;
}

Crible :: ~ Crible()
{
	if(pack)
		delete [] pack;
	if(crible)
		delete crible;
}
void Crible :: Pack(intg n)
{
	cout << "[PACK] using the crible to make a list of prime numbers " << endl;
	if (n == 0)
	{
		cout << "[PACK] Using default count value: " << count << endl;
		n = count;
	}
	else
		cout << "[PACK] Using argument value: " << n << endl;		
	// pack = new ulong [n];
	pack = new intg [n];

	for (
		// ulong pack_index = 0, i = 0;
		intg pack_index = 0, i = 0;
		(i < size_sieve)
			and (pack_index < n);
		++ i)
		
	{
		// cout << (i < size_sieve) and (pack_index < n);
		// cout << i << " " << pack_index << endl;
		if((* crible) [i])
		{
			// cout << i << " is prime" << endl;
			pack [pack_index] = i;
			++ pack_index;
			// cout << ((i < size_sieve) and (pack_index < n)) << " " << endl;
			// packv.push_back(i);
		}
	
	}
	
	// cout << "[PACK] finished packing ! here are the last 5 primes: ";
	// ShowPack(count - 5, count);

}
