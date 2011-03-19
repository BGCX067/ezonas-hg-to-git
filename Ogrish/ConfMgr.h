#include "stdafx.h"

class ConfMgr:
	public Ogre :: Singleton <ConfMgr>
{
public:
	static ConfMgr * Instantiate();
	//static ConfMgr * sglt();
	float GetFloat(string);
	SceneNode * FastAdd(string);
    static ConfMgr * getSingletonPtr(void);
protected:
	ConfigFile * configfile;
	static ConfMgr * instance;
	ConfMgr(string str = "conf/gameconf.cfg");
	~ ConfMgr();
};


