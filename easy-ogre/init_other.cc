#include "stdafx.h"

void Application :: init_other()
{
	ifstream ifstr("conf/procedural.yml");
	YAML::Parser parser(ifstr); // remember to pass it by reference
	YAML::Node doc;
	if(! parser.GetNextDocument(doc)) exit(0xbadf00d);

	ProcHouse house;
	house.configure(doc);

}
