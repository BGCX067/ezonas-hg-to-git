#include "stdafx.h"

Application * Application :: instance = NULL;

Application :: Application():
// ##### INITIALIZATIONS HERE ##########################################################
	FrameListener(),
	root(new Root("conf/plugins_d.cfg", "conf/Ogre.cfg"))
{
// use the existing ogre.cfg if it exists, creates it otherwise
	if(!(root -> restoreConfig() || root -> showConfigDialog()))
		exit(0xdeadbeef);
	// window
	window = root -> initialise(true, "Ogre3D Beginners Guide");
	window -> reposition(20, 20);
	{/* ### scenemanager #################################################### */
		scmgr = root -> createSceneManager(ST_GENERIC);
		rootnode = scmgr -> getRootSceneNode();
	}
	{/* ### camera ########################################################## */
		camera = scmgr -> createCamera("Camera");
		camera -> setNearClipDistance(1);
	}
	{/* ### resources ####################################################### */
		ConfigFile cf;
		cf.load("conf/resources_d.cfg");

		ConfigFile :: SectionIterator sectionIter = cf.getSectionIterator();
		String sectionName, typeName, dataname;
		while (sectionIter.hasMoreElements())
		{
			sectionName = sectionIter.peekNextKey();
			ConfigFile :: SettingsMultiMap * settings = sectionIter.getNext();
			ConfigFile :: SettingsMultiMap :: iterator i;
			for (i = settings -> begin(); i != settings -> end(); ++i)
			{
				typeName = i -> first;
				dataname = i -> second;

				ResourceGroupManager :: getSingleton().addResourceLocation(
					dataname, typeName, sectionName);
			}
		}

		ResourceGroupManager :: getSingleton().initialiseAllResourceGroups();
	}
	{//gameplay tweakables
		ConfMgr :: Instantiate("conf/gameconf.cfg");
	}
	{// ### First Person Camera Object ######################################
		fpersoncam = new FPersonCam(camera, rootnode, window);
	}
	{/* ### viewport ######################################################## */
		viewport = window -> addViewport(camera);
		viewport -> setBackgroundColour(ColourValue(0.1, 0.1, 0.1));
		camera -> setAspectRatio
		(Real(viewport -> getActualWidth())/ Real(viewport -> getActualHeight()));
	}
	{/* ### FrameListener ################################################### */
		root -> addFrameListener(this);
	}
	{// create the scene
		createScene();
	}
	 /*  ### Finished building the appli, congratulations myself ! ########## */
// ##### INITIALIZATIONS END ##########################################################
}
Application :: ~ Application()
{
	delete fpersoncam;
	if(root) delete root;
}
void Application :: go ()
{
	root -> startRendering();
}
void Application :: AddPlane()
{
	Ogre :: Plane plane(Ogre :: Vector3 :: UNIT_Y, -10);
	Ogre :: MeshManager :: getSingleton().createPlane
		("plane",
			ResourceGroupManager :: DEFAULT_RESOURCE_GROUP_NAME, plane,
			1500, 1500, 20, 20, true, 1, 5, 5, Ogre :: Vector3 :: UNIT_Z);

	entplane = scmgr -> createEntity("LightPlaneEntity", "plane");
	rootnode -> createChildSceneNode() -> attachObject(entplane);
	entplane -> setMaterialName("Examples/Rocky");
}
Application * Application :: sglt()
{
	static Application _;
	return & _;
}
SceneManager * Application :: GetScMgr()
{
	return scmgr;
}
