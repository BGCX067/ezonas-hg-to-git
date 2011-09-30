#include "sieve.h"

void Sieve :: WriteFile(string filename_output)
{
	FILE * file_output = fopen(filename_output.c_str(), "w");
	
	if(file_output == NULL) {
		cerr << "[WRITE] file not opened properly, aborting" << endl;
		return;		
	}
	// remember fread takes a pointer, so I can't use to_ulong() directly
	cout << "[WRITE] Will write Sieve to " << filename_output << endl;
	// cout << "[WRITE] " << Sieve_vect.size() << " elements will be written" << endl;
	// size_t size_vect = Sieve_vect.size();
	// size_array++;
	cout << "alloacting array of " << size_array << " items" << endl;
	array = new intg[size_array];
	memset(array, 0, size_array);
	cout << "[WRITE] converting to C array" << endl;

	bitset2array();
	// ShowArray();	

	cout << "[WRITE] now writing C-array to file" << endl;
	intg how_many_written = fwrite(array, INTG_BYTES, size_array, file_output);
	cout << "[WRITE] wrote " << how_many_written << " items" << endl;			
	delete [] array;
	fclose(file_output);

}
//////////////////////////////////////////////////////////////////////
void Sieve :: ReadFile(string filename_input)
{
	FILE * file_input = fopen(filename_input.c_str(), "r");
	if(file_input == NULL)
	{
		cerr << "[READ] file not opened properly, aborting" << endl;
		return;
	}
	// calculates and shows file size
	fseek(file_input, 0, SEEK_END);
	intg file_size = ftell(file_input);
	rewind(file_input);

	int fsz = file_size % 0x400;
	int fsz_K = file_size / 0x400;
	int fsz_M = fsz_K / 0x400;
	printf("[READ] file size = ");
	if(fsz_M)   printf("%03dM",fsz_M);
	if(fsz_K) printf("%03dK",fsz_K);
	if(fsz_K) printf("%03d", fsz);
	else printf("%d", fsz);
	printf(" BYTES\n");
	// printf(" bytes (%d bytes)\n", file_size);
	
	// determinate the size of the array to allocate
	size_array = file_size / INTG_BYTES; // size of the ulong array
	size_sieve = size_array * INTG_BITS;
	cout << "[READ] allocating an array of " << size_array << " items" << endl;

	array = new intg[size_array];
	memset(array, 0, size_array);
	
	cout << "[READ] now reading file" << endl;
	intg how_many_read_items
		= fread(array, INTG_BYTES, size_array, file_input);
	
	cout << "[READ] " << how_many_read_items << " items in file" << endl;
	// ShowArray();

	databits = (new bitset<BITS>);
	databits -> set();
	// (* Sieve)[2] = false;
	// (* Sieve)[97] = true;
	array2bitset();
	(* databits)[0] = false;
	(* databits)[1] = false;
	
	delete [] array;
	fclose(file_input);

}

void Sieve :: bitset2array() // KOHRRRRREKT' !
{
	cout << "[B2A] partitionning bitset into an array" << endl;	
	for(intg i = 0; i < size_sieve; ++ i)
		if((* databits)[i])
			array[size_array - (i / INTG_BITS) - 1]
				|= (1UL << (i % INTG_BITS));
	cout << "[B2A] done" << endl;
	// cout << "[B2A] some elements: " << endl;
}

void Sieve :: array2bitset() // KOHRRRRREKT' !
{
	cout << "[A2B] building bitset from array" << endl;
	for(intg i = 0; i < size_sieve, i < size_array * INTG_BITS; ++ i)
		(* databits)[i] =
			array[size_array - i / INTG_BITS - 1]
				& (1UL << ((i % INTG_BITS)));
	cout << "[A2B] done" << endl;
}

void Sieve :: WriteNumbers(string filename)
{
	FILE * file = fopen(filename.c_str(), "w");
	if (file == NULL)
	{
		cerr << "Failed to open the file " << filename << endl;
		return;
	}	
	int i = fwrite(pack, sizeof(intg), count, file);
	cout << "wrote " << i << " things" << endl;
	fclose(file);
}