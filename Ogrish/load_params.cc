#include "stdafx.h"

string			Application :: GetString(string _s)
{
	return configfile->getSetting(_s);
}
float			Application :: GetFloat	(string _s)
{
	float result = float(0xdeadbeef);
	istringstream istrstr(configfile -> getSetting(_s, StringUtil :: BLANK, "1.0"));
	istrstr >> result;
	return result;
}
int				Application :: GetInt	(string _s)
{
	int result = 0xdeadbeef;
	istringstream istrstr(configfile -> getSetting(_s, StringUtil :: BLANK, "0"));
	istrstr >> result;
	return result;
}
Vec3			Application :: GetVect3	(string _s)
{
	istringstream iss(configfile -> getSetting(_s));
	// string s = configfile -> getSetting(_s);
	float x, y, z;

	iss >>  x >> y >> z;

	return Vec3(x, y, z);
}
Ogre::Vector2	Application	:: GetVect2	(string _s)
{
	istringstream iss(configfile -> getSetting(_s));
	// string s = configfile -> getSetting(_s);
	float x, y;

	iss >> x >> y;

	return Ogre::Vector2(x, y);
}
