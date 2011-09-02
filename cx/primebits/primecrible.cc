#include "primecrible.h"
#include "21030.h"
#include <cstdlib>

string Crible :: number_fmt(ulong n)
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
	ulong len   = n % 1000;
	ulong len_K = (n % 1000000) / 1000;
	ulong len_M = (n % 1000000000) / 1000000;
	ulong len_G = n / 1000000000;

	ulong n8 = n / 8UL;
	
	ulong len8   = n8 % 1000;
	ulong len_K8 = (n8 % 1000000) / 1000;
	ulong len_M8 = (n8 % 1000000000) / 1000000;
	ulong len_G8 = n8 / 1000000000;
	
	// printf("%lu bits = %lu bytes\n", n, n8);

	// printf("%03lu %03lu %03lu %03lu bits = %03luG %03luM %03luK %03lu bytes\n",
	printf("0x%lX bits = %03luM %03luK %03lu bytes\n",
		// len_G,  len_M,  len_K,  len,
		n,
		// len_G8,
		len_M8, len_K8, len8);
}
Crible :: Crible
(ulong _size_sieve, int _line_size):

	WordSize(sizeof(ulong)),
	NumberOfWords(count/WordSize),
	count(0u),
	size_sieve(_size_sieve),
	size_array (size_sieve / 64 + 1),
	line_size(_line_size),
	crible(new bitset<BITS>),
	crible_vect(size_array),
	pack(NULL)
{
	cout << "bitset hard limit (set at compile time) = ";
	print_spaces_bytes(BITS);
	
	cout << "crible size (how far the sieve will go) = ";
	print_spaces_bytes(size_sieve);

}
void Crible :: Generate ()
{
	cout << "[GEN] Using Eratosthenes Sieve algorithm to find primes " << endl;

	cout << "[GEN] flipping bits, setting 0 and 1 as not primes" << endl;
	crible->flip();
	(* crible)[0] = false;
	(* crible)[1] = false;
	cout << "[GEN] let's loop !" << endl;
	time_t start = time(NULL);

	// for (ulong i = 2; i < size_sieve; ++i)
	for (uint i = 2; i < size_sieve; ++i)
	{
		// if there is a false, loop next (false means i is not prime)
		if((* crible)[i] == false) continue;
		++ count;
		// zeroes out all numbers from 2*m to n (means here, i is prime)
		// for(ulong k = 2; i*k < size_sieve; ++k)
		for(uint k = 2; i*k < size_sieve; ++k)
			(* crible)[i*k] = false;
	}
	time_t end = time(NULL);
	double sec = difftime(end, start);
	cout << "[GEN] found " << number_fmt(count) << " prime numbers" << endl;
	printf("time spent: %.0lf seconds\n", sec);
	ShowPrimes(size_sieve - 25, size_sieve);
	
}

Crible :: ~ Crible()
{
	if(pack) delete [] pack;
}
void Crible :: Pack(ulong n)
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
	pack = new uint [n];

	for (
		// ulong pack_index = 0, i = 0;
		uint pack_index = 0, i = 0;
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
void Crible :: Chunkize()
{

	cout << "[CHUNK] partitionning crible into 64 bits bitsets" << endl;
	for(uint i = 0; i < size_sieve; ++ i)
	{
		crible_vect[i / 64] [i % 64] = (*crible)[i];
		// crible_vect.push_back((*crible)[i]); // LOL STUPID !
		// cout << (*crible)[i] << " " << i << endl;
	}
}
void Crible :: Chunkize2()
{
	cout << "[CHUNK] partitionning crible into an array of ulong" << endl;
	
	for(uint i = 0; i < size_array - 1; ++ i)
		for(uint j = 0; j < 64; ++ j)
		// for(int j = 63; -1 < j; -- j)
			if((* crible)[64 * i + j])
			{
				cout << i << " \t" << j << "\t\t" << 64 * i + j << endl;	
				array[i / 64] &= (1L << j);
			}
}
// void Crible :: WriteFile(string filename_output)
// {
// 	FILE * file_output = fopen(filename_output.c_str(), "w");
// 	
// 	if(file_output == NULL) {
// 		cerr << "[WRITE] file not opened properly, aborting" << endl;
// 		return;		
// 	}
// 
// 	cout << "[WRITE] Will write crible to " << filename_output << endl;
// 	cout << "[WRITE] " << crible_vect.size() << " elements will be written" << endl;
// 	size_t size_vect = crible_vect.size();
// 
// 	cout << "[WRITE] converting to C array" << endl;
// 	array = new intg[size_vect];
// #ifdef USE_VECTORS
// 	FOR(size_vect)
// 	{
// 		cout << crible_vect[i].to_string() << endl;
// 		array[i] = crible_vect[i].to_ulong();
// 	}
// #endif	
// 	cout << "[WRITE] now writing to file" << endl;
// 	fwrite(array, ULONG_BYTES, size_vect, file_output);
// 	cout << "[WRITE] finished writing" << endl;			
// 	free(array);
// 	fclose(file_output);
// 
// }
// void Crible :: ReadFile(string filename_input)
// {
// 	FILE * file_input = fopen(filename_input.c_str(), "r");
// 	if(file_input == NULL)
// 	{
// 		cerr << "[READ] file not opened properly, aborting" << endl;
// 		return;
// 	}
// 	
// 	fseek(file_input, 0, SEEK_END);
// 	int file_size = ftell(file_input);
// 	rewind(file_input);
// 
// 	int fsz = file_size % 0x400;
// 	int fsz_K = file_size / 0x400;
// 	int fsz_M = fsz_K / 0x400;
// 	printf("[READ] file size = %0dM %03dK %03d bytes (%d bytes)\n",
// 		fsz_M, fsz_K, fsz, file_size);
// 	
// 	size_array = file_size / ULONG_BYTES - 1; // size of the ulong array
// 	// size_t size_vect = crible_vect.size(); // size of the vectors
// 	// cout << "note: size_vect = " << size_vect << endl
// 	cout << "note: size_array = " << size_array << endl;
// 		
// 	cout << "[READ] allocating an array of" << size_array << " ulong" << endl;
// 	array = new ulong[size_array]; // allocating array
// 	
// 	cout << "[READ] reading file" << endl;
// 	ulong items64 = fread(array, ULONG_BYTES, size_array, file_input);
// 	
// 	cout << "[READ] " << items64 << "items, last is "
// 		<< array[size_array - 1] << endl;
// 	
// 	
// 	for(int i = 0; i < size_array; ++ i)
// 		for(int j = 63; j > -1; -- j)
// 			(* crible)[64 * i + j] = array[j] & (1 << j);
// 	
// 	delete (array);
// 	fclose(file_input);
// }