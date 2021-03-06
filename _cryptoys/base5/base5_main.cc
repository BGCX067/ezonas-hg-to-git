#include "base5.h"

int main(int n, char * arg[])
{
	base5 b;
	if(n == 1)
	{
		string s[10];

		s[0] = "HELLO_WORLD.";
		s[1] = "HELLO_WORLD.";
		s[2] = "HELLO_WORLD.";
		s[3] = "HELLO_WORLD.";
		s[4] = "I'M_JONAS";
		s[5] = "WITH DOUDOUE";
		s[6] = "AND DANDAN";
		s[7] = "AND NAFNAF";
		s[8] = "HELLO_WORLD.";
		s[9] = "WE'RE HAPPY";
		
		ulong m[10];
		FOR(10)
			m[i] = b.encode(s[i]);
		
		b.writetofile(m, 10, string("dump.bit"));
		// ulong n = b.encode(s);
		// cout << n << endl;
		// cout << b.decode(n) << endl;

	}
	if(n == 2 and arg[1][0] == 'r')
	{
		vector<string> r =
			b.readfile("dump.bit");
		FOR_ITR(string, r)
			cout << (* itr) << endl;
	}
	else if
	(n == 2 and ((arg[1][0] > ('A'-1) and arg[1][0] < ('Z'+1))
			or   (arg[1][0] > ('a'-1) and arg[1][0] < ('z'+1))))
	{
		string s(arg[1]);
		ulong n = b.encode(s);
		cout << n << endl;
		cout << b.decode(n) << endl;
		
	}
	else if(n == 2 and arg[1][0] > ('0'-1) and arg[1][0] < ('9'+1))
	{

		string input(arg[1]);
		// cout << LONG_MAX << endl;
		ulong result = 0;
		long n = strtol(input.c_str(), 0, 10);
		// if(atol(input.c_str()) > 0xFFFFFFFFFFFFFFFF)
		if(errno == ERANGE and n == LONG_MAX)
		{
			cout << "value bigger than 2^64 - 1, cutting input." << endl;
			string test(input.substr(0, 19)); // 20 chars counting from 0
			// if(strtol(test.c_str(), 0, 10) > BITS64)
			n = strtol(test.c_str(), 0, 10);
			if(errno == ERANGE and n == LONG_MAX)
				test = test.substr(0, 18);
			cout << "input cut to " << test << endl;
			result = strtol(test.c_str(), 0, 10);
			if(strtol(test.c_str(), 0, 10) > BITS64)
				cerr << "hey yo man you miscalculated !" << endl;
		}

		string s(b.decode(n));
		cout << s << endl;
		cout << b.encode(s) << endl;
	}
	
}