#include "multibitset.h"

multibitset :: multibitset (ulong n_vectors)://, ulong bitset_width = 64):
	data(n_vectors)
{}

// bool & multibitset :: operator[] (const ulong & index)
// {
// 	cout << index << ": requesting [" << index / BITSET_WIDTH << "]["
// 		<< index % BITSET_WIDTH << "]" << endl;
// 	return data[index / BITSET_WIDTH] [index % BITSET_WIDTH];
// }

bool multibitset :: read(ulong index)
{
	return data[index / BITSET_WIDTH] [index % BITSET_WIDTH];
}

void multibitset :: write(ulong index, bool value)
{
	data[index / BITSET_WIDTH] [index % BITSET_WIDTH] = value;
}

void multibitset :: flip()
{
	for(mvb_itr itr = data.begin(); itr < data.end(); ++itr)
	{
		itr -> flip();
	}
}