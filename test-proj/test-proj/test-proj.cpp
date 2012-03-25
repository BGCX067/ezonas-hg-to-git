#include "stdafx.h"

typedef vector<string> strv;
vector<string> getkeys(YAML::Node & n)
{
	vector<string> v;
	for(auto it = n.begin(); it != n.end(); ++it)
	{
		string s;
		it.first() >> s;
		v.push_back(s);
	}
	return v;
}
int _tmain(int argc, _TCHAR* argv[])
{
	YAML::Parser parser(ifstream("test.yml"));
	//YAML::Parser parser(ifstream("yamlint.yml"));
	YAML::Node doc;
	if(! parser.GetNextDocument(doc)) exit(0xf00dbad);

	strv a = getkeys(doc);
	for(auto it = a.begin(); it != a.end(); ++it)
		cout << *it << "\n";

	system("PAUSE");
	return 0;
}

