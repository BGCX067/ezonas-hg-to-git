#ifndef __APPLE__
#include "stdafx.h"
#endif

class ConfMgr:
	public Ogre :: Singleton <ConfMgr>
{
public:
	static ConfMgr * Instantiate();
	//static ConfMgr * sglt();
    static ConfMgr * getSingletonPtr(void);

	ConfMgr(string str = "conf/gameconf.cfg");
	~ ConfMgr();
};




