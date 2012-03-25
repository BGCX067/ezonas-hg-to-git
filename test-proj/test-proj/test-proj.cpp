// test-proj.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


void test_type(const YAML::Node & n)
{
	switch(n.Type())
	//switch(dada->Type())
	{
		case (YAML::NodeType::Null		)	: cout << "null" << "\n"; break;
		case (YAML::NodeType::Scalar	)	: cout << "scalar" << "\n"; break;
		case (YAML::NodeType::Sequence	)	: cout << "seq" << "\n"; break;
		case (YAML::NodeType::Map		)	: cout << "map" << "\n"; break;
	}
}
typedef vector<string> strv;

vector<string> getkeys(YAML::Node & n)
{
	vector<string> v;
	for(auto it = n.begin(); it != n.end(); ++it)
	{
		string s;
		it.first() >> s;
		v.push_back(s);
		//cout << s << "\n";
	}
	return v;
}
int _tmain(int argc, _TCHAR* argv[])
{
#define TESTSTS
#ifndef TEST
	YAML::Parser parser(ifstream("items3.yml"));
#else
	YAML::Parser parser(ifstream("sample.yml"));
#endif
	YAML::Node doc;
	if(! parser.GetNextDocument(doc))
		exit(0xf00dbad);

#ifndef TEST
	//auto item = doc.FindValue("item");
	strv a = getkeys(doc);
	for(auto it = a.begin(); it != a.end(); ++it)
		cout << *it << "\n";

#else
	test_type(doc);//["didi"]);
	//doc["item"]["list2"]["itemC"]["didi"].FindValue("didi
	//doc["item"]["list2"]["itemC"]["didi"].FindValue("didi
	auto it = doc.begin();
	doc["receipt"].;
	cout << s << "\n";
#endif
//	YAML::NodeType::value type = node
	//doc.
	system("PAUSE");
	return 0;
}

