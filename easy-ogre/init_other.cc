#include "stdafx.h"

void Application :: init_other()
{
	YAML::Parser parser(ifstream("conf/items.yaml"));
	YAML::Node doc;
	if(! parser.GetNextDocument(doc))
		exit(0xf00dbad);
	string s;
	YAML::Iterator i =  doc["weaponry"]["guns"].begin();
	*(i) >> s;
	LOGMSG(s);

}
