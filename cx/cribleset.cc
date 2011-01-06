#include <bitset>
#include <fstream>
#include <iostream>
using namespace std;

#define MAX 1000
typedef vector <char> :: iterator chr_vec_iter_t;

class cribleset
{
public:
	cribleset
	(
		string outname = "cribleset_in",
		string inname = "cribleset_out"
	):
		in(inname),
		out(outname),
		size_in(0),
		size_out(0)
	{}
	
	void read()
	{
		in.seekg (0, ifstream :: end);
		int size_in = in.tellg();
		in.seekg(0);
		cout << "size found: " << size_in << " bytes." << endl;
		if(size_in != 0)
		{
			infile.read (buffer,size_in);
		}
	}
	
	void write()
	{}
	
	void show()
	{
		for (chr_vec_iter_t iter = buffer.begin(); iter != buffer.end(); ++ iter)
		cout << * iter << endl;
	}
protected:
	ifstream in;
	ofstream out;
	int size_in, size_out;
	vector <char> buffer;
	bitset<MAX> crible_set;
};

/*
typedef unsigned char uchr
uchr c = 0;
int max = MAX/8;
for (int i = 0; i < max; ++i)
{
	for (int i = 0; i < 8; ++i)
	{
		c |= (crible_set & (1 << i)
	}
	write
}*/

int main ()
{

}