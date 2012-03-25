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

int _tmain(int argc, _TCHAR* argv[])
{
#define TEST
#ifndef TEST
	YAML::Parser parser(ifstream("items3.yaml"));
#else
	YAML::Parser parser(ifstream("test.yaml"));
#endif
	YAML::Node doc;
	if(! parser.GetNextDocument(doc))
		exit(0xf00dbad);
	string s;
#ifndef TEST
	test_type(doc["item"]["cloth"])		  ;
	test_type(doc["item"]["tinkering"])	  ;
	test_type(doc["item"]["food"])		  ;
	test_type(doc["item"]["utility"])	  ;
	test_type(doc["item"]["machine"])	  ;
	test_type(doc["item"]["weaponry"])	  ;
#else
	test_type(doc["item"]["list2"]["itemC"]);//["didi"]);
	doc["item"]["list2"]["itemC"]["didi"].FindValue("didi
	doc["item"]["list2"]["itemC"]["didi"].FindValue("didi
#endif
//	YAML::NodeType::value type = node
	//doc.
	system("PAUSE");
	return 0;
}

