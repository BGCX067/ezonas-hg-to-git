#include <iostream>
#include <string>
using namespace std;


int main()
{
	char c = 'c';
	string s(&c);
	s += 'f';
	string fd(s + 'd' + s);
	cout << fd << endl;
}