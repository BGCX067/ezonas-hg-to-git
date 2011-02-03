#include "primecrible.h"
#include "21030.h"

#include <stdlib.h>
Crible :: Crible
(uint n, uint l, string filename_i, string filename_o):

	in(new ifstream(filename_i.c_str())),
	out(new ofstream(filename_o.c_str())),
	WordSize(sizeof(ulong)),
	NumberOfWords(count/WordSize),
	limit(n),
	count(0u),
	size(CRIBLE_SIZE),
	line_size(l)
{
	cout << "crible size = " << size << endl;
	cout << SIZE << "bits in the vcrible" << endl;
	cout << NumberOfWords << " " << WordSize * 8 << " bits words" << endl;
	cout << "The program will only consider " << NumberOfWords * WordSize * 8 << " bits." << endl;
}
void Crible :: ShowArray()
{
	cout << "\t ";
	for (uint i = 1; i < line_size/10; i += 1)
		cout << "         " << i;
	cout << endl << "\t";
	for (uint i = 0; i < line_size; ++i)
		cout << i % 10;
	for (uint i = 0; i < limit; ++i)
	{
		if (i % line_size == 0) cout << endl << "+"<< i << "\t";
		if (crible[i]) cout << '#';
		else cout << '-';//"·";
	}
	cout << endl;
}
void Crible :: Generate ()
{
	// for(int i = 2; i < limit; ++i) crible[i] = true;
	crible.flip();
	crible[0] = false;
	crible[1] = false;
	for (uint i = 2; i < limit; ++i)
	{
		// if there is a false, loop next (false means i is not prime)
		if(crible[i] == false) continue;
		++ count;
		// zeroes out all numbers from 2*m to n (means here, i is prime)
		for(uint k = 2; i*k < limit; ++k)
			crible[i*k] = false;
	}
	cout << "cribled, found " << count << " prime numbers." << endl;
	cout << "The last primes (in the 100 last integers) which were found: " << endl;
	ShowPrimes(limit - 100, limit);
	
}
void Crible :: ShowPrimes(int a, int b)
{
	if(a >= b)
	{
		cout << "bad range" << endl;
		return;
	}
	cout << endl;
	for (int i = a; i < b; ++i)
	{
		if (crible[i]) cout << (i) << ' ';
		//else cout << '-';//"·";
	}
	cout << endl << endl;
}
void Crible :: ShowPrimes()
{
	cout << endl;
	for (uint i = 0; i < limit; ++i)
	{
		if (crible[i]) cout << (i) << ' ';
		//else cout << '-';//"·";
	}
	cout << endl;	
}
void Crible :: ShowPrimes30()
{
	cout << endl;
	for (uint i = 0; i < limit; ++i)
	{
		if (crible[i]) cout << unbase :: tumber30(i) << ' ';
		//else cout << '-';//"·";
	}
	cout << endl;	
}
void Crible :: ShowPrimes36()
{
	cout << endl;
	for (uint i = 0; i < limit; ++i)
	{
		if (crible[i]) cout << unbase :: tumber36(i) << ' ';
		//else cout << '-';//"·";
	}
	cout << endl;	
}
/////////////////////////////////////////////////////////////////////////////
Crible :: ~ Crible()
{
	in -> close();
	out -> close();
	delete in;
	delete out;
}
void Crible :: ReadFile()
{
	// for(word_vect_iter iter = crible.begin(); iter != crible.end(); ++iter)
	if (in -> is_open())
	while(! in -> eof()) // MIGHT CRASH
	{
		// buffer << (*in);
		(* in) >> buffer;
		vcrible.push_back(bitset <SIZE> (buffer));
	}
}
void Crible :: WriteFile()
{
	for(word_vect_iter iter = vcrible.begin(); iter != vcrible.end(); ++iter)
	{
		(* out) << (* iter).to_ulong();
	}
}
void Crible :: Show ()
{
	for(word_vect_iter iter = vcrible.begin(); iter != vcrible.end(); ++iter)
	{
		cout << (* iter).to_string() << endl;
	}
}

void Crible :: Pack()
{
	pack = new uint [count];
	for (int pack_index = 0, i = 0; i < limit; ++ i)
	{
		if(crible [i])
		{
			pack [pack_index] = i;
			++ pack_index;
		}
	}
	
	cout << "finished packing ! here are the last 10 primes:" << endl;
	ShowPack(count - 10, count);
	// ShowPack(10, 100);
}

void Crible :: ShowPack(int a, int b)
{
	if(a >= b || a > count || b > count)
	{
		cout << "bad range or out of range..." << endl;
		return;
	}
	cout << endl;
	for (int i = a; i < b; ++i)
	{
		cout << pack [i] << ' ';
		//else cout << '-';//"·";
	}
	cout << endl << endl;
}


void Crible :: ShowPrimeByPosition(int i)
{
	if(i > count)
	{
		cout << "Did not cribled enough;, try a bigger crible." << endl;
		return;
	}
	cout << "Prime #" << i << ": " << pack[i] << endl;
}
