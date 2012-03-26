#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	YAML::Parser parser(ifstream("test2.yml"));
	//YAML::Parser parser(ifstream("items9.yml"));
	YAML::Node doc;
	if(! parser.GetNextDocument(doc)) exit(0xbadf00d);

	vector<string> string_vector;// = getkeys(doc);
	for(auto it = doc.begin(); it != doc.end(); ++it)
	{
		string s;
		it.first() >> s;
		string_vector.push_back(s);
	}


	for(auto it = string_vector.begin(); it != string_vector.end(); ++it)
		cout << *it << "\n";

	system("PAUSE");
	return 0;
}

