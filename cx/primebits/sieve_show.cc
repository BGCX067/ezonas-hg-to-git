#include "sieve.h"
#include "basex.h"
#include <map>
// void Sieve :: ShowArray()
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
// 		if ((* Sieve)[i]) cout << '#';
// 		else cout << '-';//"·";
// 	}
// 	cout << endl;
// }

void Sieve :: ShowPrimes(intg a, intg b)
{
	if(a >= b)
	{
		cerr << "[SHOW] bad range" << endl;
		return;
	}
	cout << "[SHOW] primes in [" << number_fmt(a) << ".." << number_fmt(b) << "]: ";
	for (intg i = a; i < b; ++i)
		if ((* Sieve)[i]) cout << (i) << ", ";
	cout << "end" << endl;
}
void Sieve :: ShowPrimesLine()
{
	for (intg i = 0; i < size_sieve; ++i)
		if ((* Sieve) [i]) cout << i << endl;
	cout << "end"<< endl;	
}
void Sieve :: ShowPrimes()
{
	for (intg i = 0; i < size_sieve; ++i)
		if ((* Sieve) [i]) cout << number_fmt(i) << ", ";
	cout << "end"<< endl;	
}
void Sieve :: ShowPrimesBase(int n)
{

	Generate(n);
	printf("10\t\t16\t\t27\t\t30\t\t36 -----\n");
	map<int, vector<string> > results;
	for (intg i = 0; i < size_sieve; ++i)
		if ((* Sieve) [i])
		{
			// char s[0x100];
			// sprintf(s, "%lX", i);
			// results[16].push_back(string(s));
			// results[27].push_back(basex::tumber27(i));
			// results[30].push_back(basex::tumber30(i));
			// results[36].push_back(basex::tumber36(i));
			
			printf
			(
				"%lu\t\t%lX\t\t%s\t\t%s\t\t%s\n",
				i, i,
				basex::tumber27(i).c_str(),
				basex::tumber30(i).c_str(),
				basex::tumber36(i).c_str()
			);
		}
		
	int fds[4] = {16, 27, 30, 36};
	FOR(4)
	{
		
	}
	cout << "end"<< endl;	
}
void Sieve :: ShowArray()
{
	cout << "[SHOW] array in hexadecimal: ";
	FOR(size_array)
		printf("0x%lX, ", array[i]);
	printf("end\n");
}
void Sieve :: ShowSieveSet ()
{
	cout << (*Sieve) << endl;

	// string whole = Sieve->to_string();
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
	// 	vect_bs64_iter iter = Sieve_vect.begin();
	// 	iter != Sieve_vect.end();
	// 	++iter
	// )
	// {
	// 	string s = iter -> to_string();
	// 	reverse(s.begin(), s.end());
	// 	cout << s << endl;
	// }

}
void Sieve :: ShowSieveSet (intg a, intg b)
{
	if(a >= b)
	{
		cerr << "bad interval" << endl;
		return;
	}
	cout << "printing bits [" << a << ".." << b << "]" << endl;
	FORG(a, b)
		cout << (* Sieve) [i];
	
	prln;
}
void Sieve :: ShowPack(intg a, intg b)
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
void Sieve :: ShowPrimeByPosition(intg i)
{
	if(i > count)
	{
		cerr << "[SHOW] Did not Sieved enough;, try a bigger Sieve." << endl;
		return;
	}
	cout << "[SHOW] Prime #" << i << ": " << pack[i] << endl;
}
void Sieve :: HideThis()
{
// void Sieve :: ShowPrimes30()
// {
// 	for (ulong i = 0; i < size_sieve; ++i)
// 		if ((* Sieve)[i]) cout << basex :: tumber30(i) << ' ';
// 	cout << endl;	
// }
// void Sieve :: ShowPrimes36()
// {
// 	for (ulong i = 0; i < size_sieve; ++i)
// 		if ((* Sieve)[i]) cout << basex :: tumber36(i) << ' ';
// 	cout << endl;	
// }
}