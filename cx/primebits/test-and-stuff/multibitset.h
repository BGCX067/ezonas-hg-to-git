#include <vector>
#include <bitset>
#include <iostream>

using namespace std;

#define BITSET_WIDTH 64
typedef unsigned long ulong;
typedef vector < bitset <64> > :: iterator mvb_itr;
class multibitset
{
public:
	// bool & operator[](const ulong & index);
	multibitset(ulong n_vectors);
	bool read(ulong index);
	void write(ulong index, bool value);
	void flip();
protected:
	vector <bitset <BITSET_WIDTH> > data;
	
};