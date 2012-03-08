#include "stdafx.h"

Application :: Application():
	FrameListener(),
	raycallback(btVector3(0,0,0),btVector3(0,0,0))
{
	configfile = new ConfigFile;
	/* initializing all objects */
#ifdef __APPLE__
	root = new Root(macBundlePath() + "/Contents/Resources/"+"conf/plugins_d-mac.cfg",
				macBundlePath() + "/Contents/Resources/"+"conf/Ogre.cfg",
				macBundlePath() + "/Contents/Resources/"+"conf/Ogre.log");
	configfile -> load(macBundlePath() + "/Contents/Resources/"+"conf/gameconf.cfg");
#else
#ifdef _DEBUG
	root = new Root("conf/plugins_d.cfg", "conf/Ogre.cfg", "conf/Ogre.log");
#else	 
	root = new Root("conf/plugins.cfg", "conf/Ogre.cfg", "conf/Ogre.log");
#endif
	configfile -> load("conf/gameconf.cfg");
#endif
	if(root -> restoreConfig() == false)
		if (root -> showConfigDialog() == false)
			exit (0xdeadbeef);

	window	 = root -> initialise(true, "Zevil");
	scmgr	 = root -> createSceneManager(GetScMgrType());
	camera	 = scmgr -> createCamera("Camera");
	viewport = window -> addViewport(camera);
	n_root = scmgr -> getRootSceneNode();
	/* changing some settings */
	PRINTLOG("------- configuring some misc. parameters -------");
	camera -> setNearClipDistance(1);
	camera -> setAspectRatio
		(Real(viewport -> getActualWidth())/ Real(viewport -> getActualHeight()));
	root -> addFrameListener(this);

}
