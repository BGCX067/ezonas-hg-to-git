#include "stdafx.h"

class ConfMgr :
	public Ogre :: Singleton <ConfMgr>
{
public:
	static void Instantiate(string);
	static ConfMgr * sglt();
	float GetFloat(string);
	SceneNode * FastAdd(string);
protected:
	ConfMgr(string);
	~ ConfMgr();
	ConfigFile * configfile;
	static ConfMgr * instance;
};


