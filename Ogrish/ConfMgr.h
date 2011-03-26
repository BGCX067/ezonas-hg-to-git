#include "stdafx.h"

class ConfMgr:
	public Ogre :: Singleton <ConfMgr>
{
public:
	static ConfMgr * Instantiate();
	//static ConfMgr * sglt();
	float GetFloat(string);
	SceneNode * FastAdd(string);
	SceneNode *  AddLight(string);
	Vec3 & getvect(string _s);
    static ConfMgr * getSingletonPtr(void);

protected:
	ConfigFile * configfile;
	static ConfMgr * instance;
	ConfMgr(string str = "conf/gameconf.cfg");
	~ ConfMgr();
};


