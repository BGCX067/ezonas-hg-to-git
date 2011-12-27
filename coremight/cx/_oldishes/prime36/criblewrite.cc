////// ==== DUMP_IT ==== //////

bool dump()
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

bool get()
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


void write(string flname = "primes.bi")
{
	filename = flname;
	if (dump()) cout << "Successfully wrote into file named '" << filename
	<< "'." << endl;
}
void write_bin()
{
	string filename_bin = "primes.bin";
	if (dump_bool()) cout << "Binary export sucess: '" << filename_bin
	<< "'." << endl;
}
void read(string flname = "primes.bi")
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
bool dump_bool()
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

bool get_bin()
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
