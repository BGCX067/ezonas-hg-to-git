#include "primecrible.h"

// void Crible :: ShowArray()
// {
// 	cout << "\t ";
// 	for (intg i = 1; i < line_size/10; i += 1)
// 		cout << "         " << i;
// 	cout << endl << "\t";
// 	for (intg i = 0; i < line_size; ++i)
// 		cout << i % 10;
// 	for (intg i = 0; i < size_sieve; ++i)
// 	{
// 		if (i % line_size == 0) cout << endl << "+"<< i << "\t";
// 		if ((* crible)[i]) cout << '#';
// 		else cout << '-';//"·";
// 	}
// 	cout << endl;
// }

void Crible :: ShowPrimes(intg a, intg b)
{
	if(a >= b)
	{
		cerr << "[SHOW] bad range" << endl;
		return;
	}
	cout << "[SHOW] primes in [" << number_fmt(a) << ".." << number_fmt(b) << "]: ";
	for (intg i = a; i < b; ++i)
		if ((* crible)[i]) cout << (i) << ", ";
	cout << "end" << endl;
}
void Crible :: ShowPrimes()
{
	for (intg i = 0; i < size_sieve; ++i)
		if ((* crible) [i]) cout << number_fmt(i) << ", ";
	cout << "end"<< endl;	
}
void Crible :: ShowArray()
{
	cout << "[SHOW] array in hexadecimal: ";
	FOR(size_array)
		printf("0x%X, ", array[i]);
	printf("end\n");
}
void Crible :: ShowCribleSet ()
{
	cout << (*crible) << endl;

	// string whole = crible->to_string();
	// 
	// FOR(size_sieve)
	// {
	// 	if(i % 64)
	// 		cout << endl;
	// 	cout << whole[i] << endl;
	// }
	
	// 
	// for
	// (
	// 	vect_bs64_iter iter = crible_vect.begin();
	// 	iter != crible_vect.end();
	// 	++iter
	// )
	// {
	// 	string s = iter -> to_string();
	// 	reverse(s.begin(), s.end());
	// 	cout << s << endl;
	// }

}
void Crible :: ShowCribleSet (intg a, intg b)
{
	if(a >= b)
	{
		cerr << "bad interval" << endl;
		return;
	}
	cout << "printing bits [" << a << ".." << b << "]" << endl;
	FORG(a, b)
		cout << (* crible) [i];
	
	prln;
}
void Crible :: ShowPack(intg a, intg b)
{
	if (b == 0)
		b = count;
	if(a >= b || a > count || b > count)
	{
		cout << "[SHOW] bad range or out of range..." << endl;
		return;
	}
	for (intg i = a; i < b; ++i)
		cout << number_fmt(pack [i]) << ", ";
	// for (vector<ulong>::iterator i = packv.begin(); i != packv.begin() +; ++i)
	// for (auto i = packv.begin(); i != packv.end(); ++i)
		// cout << number_fmt((*i)) << ", ";
	cout << "end." << endl;
}
void Crible :: ShowPrimeByPosition(intg i)
{
	if(i > count)
	{
		cerr << "[SHOW] Did not cribled enough;, try a bigger crible." << endl;
		return;
	}
	cout << "[SHOW] Prime #" << i << ": " << pack[i] << endl;
}
void Crible :: HideThis()
{
// void Crible :: ShowPrimes30()
// {
// 	for (ulong i = 0; i < size_sieve; ++i)
// 		if ((* crible)[i]) cout << unbase :: tumber30(i) << ' ';
// 	cout << endl;	
// }
// void Crible :: ShowPrimes36()
// {
// 	for (ulong i = 0; i < size_sieve; ++i)
// 		if ((* crible)[i]) cout << unbase :: tumber36(i) << ' ';
// 	cout << endl;	
// }
}