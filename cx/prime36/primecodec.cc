#include "primewords.h"

// primecodec ::
////// ==== CRIBLER ==== //////
ulong primecodec :: cribler()
{
	crible[0] = false;
	crible[1] = false;
	for(int i = 2; i < num_cap; ++i) crible[i] = true;

	for (ulong i = 2; i < num_cap; ++i)
		{
			// if there is a false, loop next (false means i is not prime)
			if(crible[i] == false) continue;
			++ count;
			// zeroes out all numbers from 2*m to n (means here, i is prime)
			for(ulong k = 2; i*k < num_cap; ++k)
				crible[i*k] = false;
		}
	return count;
}
////// ==== POP_LIST ==== //////

void primecodec :: pop_list(int r = 10)
{
	cout << r << " columns by row..." << endl;
	printf ("√ø ∫Ω\t");
	for(int i = 1; i <= r; ++i) cout << "c:" << i << "\t";
	for(int i = 0; i < count; ++i)
	{
		if(not (i % r)) cout << endl << "r:" << i/10 << "\t";
		cout << primes[i] << "\t";
	}

	cout << endl << "#eoli" << endl;
}
////// ==== POP_LIST2 ==== //////

void primecodec :: pop_list2(int r = 5)
{
	cout << r << " columns by row..." << endl;
	printf ("√ø ∫Ω\t");
	for(int i = 1; i <= r; ++i) cout << "c:" << i << "\t";
	for(int i = 0; i < count; ++i)
	{
		if(not (i % r)) cout << endl;
		cout << i << ":" << primes[i] << "\t";
	}

	cout << endl << "#eoli" << endl;
}
////// ==== DUMP_IT ==== //////

bool primecodec :: dump()
{
	if (count < 1)
	{
		cout << "Not enough primes number generated to write something." << endl;
		return false;
	}

	FILE * file = fopen(filename.c_str(), "w");
	if (file == NULL)
	{
		cout << "Failed to open the file in write-binary mode." << endl;
		fclose(file);
		return false;
	}
	cout << fwrite(primes, sz, count, file) << " elements written." << endl;
	fclose(file);
	return true;

}
////// ==== GET_IT ==== //////

bool primecodec :: get()
{
	FILE * file = fopen(filename.c_str(), "r");
	if (file == NULL)
	{
		cout << "Failed to open the file in read-binary mode." << endl;
		return false;
	}
	else
//	cout << "file handle: " << file << endl;
	// get filesize
	fseek(file, 0, SEEK_END);
	int file_size = ftell(file);
	rewind(file);
	count = file_size / sz;
	primes = new ulong[count];
	ulong el = fread(primes, sz, count, file);
	//if (el == 0) cout << "Failed to read the content, 0 elements read" << endl;


	// creating the array where the stuff will be raed into
	cout << "file size = " << file_size << ", size_of = " << sz << endl;

	fclose (file);
	return true;
}

////// ==== IS_PRIME ==== //////
void primecodec :: is_prime (ulong n)
{
	if (count < 1)
	{
		if (get_bin())
		{
			if (crible[n]) cout << "You can look like a lucky fellow now... " <<
			endl << n << " is a prime, dude ! :)" << endl;
			else cout << "My deep condoleances, god has since long factorised that number. You can still add 2 to it, maybe, you never know." << endl;
			return;
		}
		else
		{
			cout << "Failed to read the bin file... generating..." << endl;
			gen(n*2);
			if (crible[n]) cout << "You can look like a lucky fellow now... " <<
			endl << n << " is a prime, dude ! :)" << endl;
			else cout << "My deep condoleances, god has since long factorised that number. You can still add 2 to it, maybe, you never know." << endl;
			return;
		}
	}
	else //// I COULD HAVE ADD A GOTO, BUT THERE WAS A VELOCIRAPTOR IN MY ROOM
	{
		if (crible[n]) cout << "You can look like a lucky fellow now... " <<
		endl << n << " is a prime, dude ! :)" << endl;
		else cout << "My deep condoleances, god has since long factorised that number. You can still add 2 to it, maybe, you never know." << endl;
		return;
	}
//	else cout <<
}

////// ==== PRIME_STACK ==== //////
void primecodec :: prime_stack ()
{
	ulong next = 0;
	for(ulong i = 1; i < num_cap; ++i)
		if (crible[i])
		{
			primes[next] = i;
			++ next; // necessary
		}
}

////// ==== COUNTER ==== //////
void primecodec :: counter
(int slices)
{
	ulong step = count / slices;
	cout << "showing number of prime number by slices of " << step << endl;
	cout << "will show " << slices << " slices." << endl;

	ulong countee[slices];
	for (int i = 0; i < slices; ++i) countee[i] = 0;
	for (ulong u = 0; u < slices; ++u)
		for (ulong i = u * step; i < (u + 1) * step; ++i)
			if (crible[i]) countee[u]+= 1;

	for (ulong i = 0; i < slices; ++i)
	cout << i * step << "-" << (i + 1) * step - 1 << ": " << countee[i] << endl;
	cout << "done!" << endl;
}

////// ==== DEFAULT CONSTRUCTOR ==== //////
primecodec :: primecodec() :
sz(sizeof(ulong)), primes(NULL), crible(NULL), count(0)
{
	cout << "·······························································" <<
	endl << "| ¬∫◊        Prime number testing project                 ◊∫¬ |" <<
	endl << "| ¬∫◊             All rights reserved, Jonas O.           ◊∫¬ |" <<
	endl << "| ¬∫◊                    ezjonas@gmail.com                ◊∫¬ |" <<
	endl << "·······························································" <<
	endl;
// 	printf ("reminder: maximum unsigned long: %.0e\n", (float)(((ulong)18446744073709551615));//only unsigned in c90 my ass
	printf ("reminder: maximum unsigned long: 18e18\n");

}
////// ==== CONSTRUCTOR ==== //////
// removed

////// ==== (default) DESTRUCTOR ==== //////
primecodec :: ~primecodec()
{
	delete[] primes;
	delete[] crible;
	cout << ".·˙˙·..·˙˙·.·˙˙·..·˙˙·..·˙˙·..·˙˙·..·˙˙·..·˙˙·..·˙˙·..·˙˙·..·˙" << endl;
}


void primecodec :: show()
{
	if (count != 0)
	pop_list();
	else
	cout << "No loaded/generated data to print !" << endl;
}
void primecodec :: write(string flname = "primes.bi")
{
	filename = flname;
	if (dump()) cout << "Successfully wrote into file named '" << filename
	<< "'." << endl;
}
void primecodec :: write_bin()
{
	string filename_bin = "primes.bin";
	if (dump_bool()) cout << "Binary export sucess: '" << filename_bin
	<< "'." << endl;
}
void primecodec :: read(string flname = "primes.bi")
{
	filename = flname;
	get();
	cout << "Read from file named '" << filename << "'." << endl;
	cout << count << " elements loaded" << endl << "last is " << primes[count-1] << endl;

// 	string str = itoa ((unsgined int)[count-1], 10);
// 	cout << "There seems that the largest computer number has
// 	for (int i = 0; i < 30; ++i)
// 	cout << i << ": " << primes[i] << endl;
}
void primecodec :: gen(ulong cap)
{
	num_cap = cap;
	printf ("cap: %.0e\n", (float)num_cap);
	crible = new bool[num_cap];
	count = cribler();
	primes = new ulong[count];
	prime_stack();

	cout << count << " primes, largest: " << primes[count - 1] << endl;

}

///

////// ==== DUMP_IT ==== //////

bool primecodec :: dump_bool()
{
	cout << "dump_bool: writing the erastostene in its boolean form" << endl;
	string bin_filename = "primes.bin";
	if (count < 1)
	{
		cout << "Not enough primes number generated to write something." << endl;
		return false;
	}

	FILE * bin_file = fopen(bin_filename.c_str(), "w");
	if (bin_file == NULL)
	{
		//cout << "Failed to open the file in write-binary mode." << endl;
		fclose(bin_file);
		return false;
	}
	cout << fwrite(crible, sizeof(bool), num_cap, bin_file) << " elements written." << endl;
	fclose(bin_file);
	return true;

}
////// ==== GET_IT ==== //////

bool primecodec :: get_bin()
{
	string bin_filename = "primes.bin";
	FILE * bin_file = fopen(bin_filename.c_str(), "r");
	if (bin_file == NULL)
	{
		cout << "Failed to open the file in read-binary mode." << endl;
		return false;
	}
	else
//	cout << "file handle: " << file << endl;
	// get filesize
	fseek(bin_file, 0, SEEK_END);
	int file_size = ftell(bin_file);
	rewind(bin_file);
	int bin_sz = sizeof(bool);
	int bin_count = file_size / bin_sz;
	crible = new bool[bin_count];
	ulong el = fread(crible, bin_sz, bin_count, bin_file);
	//if (el == 0) cout << "Failed to read the content, 0 elements read" << endl;
	printf ("%.0e elements in the bool array\n", (float) el);
	//cout << el << " elements in the bool array" << endl;
	// creating the array where the stuff will be raed into

	fclose (bin_file);
	return true;
}
