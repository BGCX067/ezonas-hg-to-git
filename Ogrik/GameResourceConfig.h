// #include "Ogre\Ogre.h"
// #include <iostream>
#include "stdafx.h"
using namespace std;
using namespace Ogre;

class GameResourceConfig
{
public:
	GameResourceConfig(string _filename) {  }
	float GetFloat(string);
protected:
	ConfigFile configfile;
};

