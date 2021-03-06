// #include "Ogre\Ogre.h"
// #include <iostream>
#include "stdafx.h"
using namespace std;
using namespace Ogre;

class GameConfig
{
public:
	GameConfig(string _filename) { configfile.load(_filename); }
	float GetValue(string);
protected:
	ConfigFile configfile;
};

class GameResource
{
public:
	GameResource(string _filename) { configfile.load(_filename); }
	string GetValue(string);
protected:
	ConfigFile configfile;
};


