#include "primecrible.h"
#include "21030.h"

#include <stdlib.h>
Crible :: Crible
(ulong _limit, int _line_size, string filename_i, string filename_o):

	in(new ifstream(filename_i.c_str())),
	out(new ofstream(filename_o.c_str())),
	WordSize(sizeof(ulong)),
	NumberOfWords(count/WordSize),
	limit(_limit),
	count(0u),
	size(_limit),
	line_size(_line_size),
	crible(new bitset<BITS>)
{
	cout.setf (ios::hex, ios::basefield);
	cout.setf (ios::showbase);
	cout << "bitset hard limit = " << BITS
	
	cout << "crible size = " << size << endl;
	cout << "bitset hard limit = " << BITS << endl;
	// shits makes no sense if not initialized properly against bitset
	// (dude I like to talk like a computer scientist, it's so cool).
	// cout << SIZE << "bits in the vcrible" << endl;
	// cout << NumberOfWords << " " << WordSize * 8 << " bits words" << endl;
	// cout << "The program will only consider " << NumberOfWords * WordSize * 8 << " bits." << endl;
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
		if ((* crible)[i]) cout << '#';
		else cout << '-';//"·";
	}
	cout << endl;
}
void Crible :: Generate ()
{
	// for(int i = 2; i < limit; ++i) crible[i] = true;
	crible->flip();
	(* crible)[0] = false;
	(* crible)[1] = false;
	// for (uint i = 2; i < limit; ++i)
	// {
	// 	// if there is a false, loop next (false means i is not prime)
	// 	if(crible[i] == false) continue;
	// 	++ count;
	// 	// zeroes out all numbers from 2*m to n (means here, i is prime)
	// 	for(uint k = 2; i*k < limit; ++k)
	// 		crible[i*k] = false;
	// }
	for (ulong i = 2; i < limit; ++i)
	{
		// if there is a false, loop next (false means i is not prime)
		if((* crible)[i] == false) continue;
		++ count;
		// zeroes out all numbers from 2*m to n (means here, i is prime)
		for(ulong k = 2; i*k < limit; ++k)
			(* crible)[i*k] = false;
	}
	cout << "cribled, found " << count << " prime numbers." << endl;
	cout << "The last primes (in the 100 last integers) which were found: " << endl;
	ShowPrimes(limit - 100, limit);
	
}
void Crible :: ShowPrimes(ulong a, ulong b)
{
	if(a >= b)
	{
		cout << "bad range" << endl;
		return;
	}
	cout << endl;
	for (ulong i = a; i < b; ++i)
	{
		if ((* crible)[i]) cout << (i) << ' ';
		//else cout << '-';//"·";
	}
	cout << endl << endl;
}
void Crible :: ShowPrimes()
{
	cout << endl;
	for (ulong i = 0; i < limit; ++i)
	{
		if ((* crible)[i]) cout << (i) << ' ';
		//else cout << '-';//"·";
	}
	cout << endl;	
}
void Crible :: ShowPrimes30()
{
	cout << endl;
	for (ulong i = 0; i < limit; ++i)
	{
		if ((* crible)[i]) cout << unbase :: tumber30(i) << ' ';
		//else cout << '-';//"·";
	}
	cout << endl;	
}
void Crible :: ShowPrimes36()
{
	cout << endl;
	for (ulong i = 0; i < limit; ++i)
	{
		if ((* crible)[i]) cout << unbase :: tumber36(i) << ' ';
		//else cout << '-';//"·";
	}
	cout << endl;	
}
/////////////////////////////////////////////////////////////////////////////
Crible :: ~ Crible()
{
	if (in -> is_open()) in -> close();
	if (out -> is_open()) out -> close();
	delete in;
	delete out;
}
void Crible :: ReadFile()
{
	// for(word_vect_iter iter = crible.begin(); iter != crible.end(); ++iter)
	if (in -> is_open())
	while(! in -> eof()) // MIGHT CRASH
	{
		(* in) >> buffer;
		crible_vect.push_back(bitset <ULONG_BITS> (buffer));
	}
	else
	{
		cout << "the file is not open, could not read... aborting"  << endl;
	}
}
void Crible :: WriteFile()
{
	if(out -> is_open())
	{
		for
		(
			vect_bs64_iter iter = crible_vect.begin();
			iter != crible_vect.end();
			++iter
		)
		{
			(* out) << (* iter).to_ulong();
		}
		cout << "finished writing" << endl;
	}
	else
	{
		cout << "the file is not open, could not write... aborting"  << endl;
	}
	
}
void Crible :: ShowCribleSet ()
{
	cout << "showing binary of the crible" << endl;
	for
	(
		vect_bs64_iter iter = crible_vect.begin();
		iter != crible_vect.end();
		++iter
	)
	{
		cout << iter -> to_string() << endl;
	}
}

void Crible :: Pack()
{
	pack = new ulong [count];
	for (ulong pack_index = 0, i = 0; i < limit; ++ i)
	{
		if((* crible) [i])
		{
			pack [pack_index] = i;
			++ pack_index;
		}
	}
	
	cout << "finished packing ! here are the last 10 primes:" << endl;
	ShowPack(count - 10, count);
	// ShowPack(10, 100);
}

void Crible :: ShowPack(ulong a, ulong b)
{
	if(a >= b || a > count || b > count)
	{
		cout << "bad range or out of range..." << endl;
		return;
	}
	cout << endl;
	for (ulong i = a; i < b; ++i)
	{
		cout << pack [i] << ' ';
		//else cout << '-';//"·";
	}
	cout << endl;
}


void Crible :: ShowPrimeByPosition(ulong i)
{
	if(i > count)
	{
		cout << "Did not cribled enough;, try a bigger crible." << endl;
		return;
	}
	cout << "Prime #" << i << ": " << pack[i] << endl;
}

void Crible :: ChunkizeCrible()
{
	for(ulong i = 0; i < size; ++ i)
	{
		//crible_vect[i / 64] [i % 64] = crible[i];
	}
}
// void Crible :: OpenFiles()
// {
// 	in -> open();
// 	out -> open();
// 	cout << " Files were opened" << endl;
// }
// void Crible :: CloseFiles()
// {
// 	in -> close();
// 	out -> close();
// 	cout << " Files were closed" << endl;
// }
