#include "stdafx.h"

Application * Application :: instance = NULL;
Application :: Application():
	scenemanager(NULL),
	FrameListener(),
//	listener(NULL),
	// _keepRunning(true),
	root(new Root("conf/plugins_d.cfg")),
	gameconfig(new GameConfig("conf/gameconf.cfg")),
	game_rc(new GameResource("conf/game_rc.cfg")),
	moving_speed(gameconfig -> GetValue("moving_speed")),
	rotating_speed(gameconfig -> GetValue("rotating_speed")),
	laser_width(1.f)
{
// use the existing ogre.cfg if it exists, creates it otherwise
	if(!(root -> restoreConfig() || root -> showConfigDialog()))
		exit(0xdeadbeef);
	// window
	window = root -> initialise(true, "Ogre3D Beginners Guide");
	window -> reposition(20, 20);
	{/* ### scenemanager #################################################### */
		scenemanager = root -> createSceneManager(ST_GENERIC);
		rootnode = scenemanager -> getRootSceneNode();
	}
	{/* ### camera ########################################################## */
		camera = scenemanager -> createCamera("Camera");
		camera -> setPosition(Ogre :: Vector3(0, 0, 20));
		camera -> lookAt(Ogre :: Vector3(0, 0, 0));
		camera -> setNearClipDistance(1);
	}
	{/* ### viewport ######################################################## */
		viewport = window -> addViewport(camera);
		viewport -> setBackgroundColour(ColourValue(0.0, 0.0, 0.0));
		camera -> setAspectRatio
		(Real(viewport -> getActualWidth())/ Real(viewport -> getActualHeight()));
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
	{/* ### Billboards ###################################################### */
//		bbset scenemanager -> create
	}
	{/* ### Inputs ########################################################## */
		ParamList parameters;

		unsigned int windowHandle = 0;
		ostringstream windowHandleString;

		window -> getCustomAttribute("WINDOW", &windowHandle);
		windowHandleString << windowHandle;
		parameters.insert(make_pair("WINDOW", windowHandleString.str()));
	// those settings unhide the cursor (from ogre's wiki snippets)
	#if defined OIS_WIN32_PLATFORM
		parameters.insert(make_pair(string("w32mouse"), string("DISCL_FOREGROUND" )));
		parameters.insert(make_pair(string("w32mouse"), string("DISCL_NONEXCLUSIVE")));
		parameters.insert(make_pair(string("w32keyboard"), string("DISCL_FOREGROUND")));
		parameters.insert(make_pair(string("w32keyboard"), string("DISCL_NONEXCLUSIVE")));
	#elif defined OIS_LINUX_PLATFORM
		parameters.insert(make_pair(string("x11mouse_grab"), string("false")));
		parameters.insert(make_pair(string("x11mouse_hide"), string("false")));
		parameters.insert(make_pair(string("x11keyboard_grab"), string("false")));
		parameters.insert(make_pair(string("XAutoRepeatOn"), string("true")));
	#endif
	/* ### Inputs Objects ################################################## */
		inputmanager = InputManager :: createInputSystem(parameters);
		keyboard = static_cast<Keyboard *>
		(inputmanager -> createInputObject(OISKeyboard, false));
		mouse = static_cast<Mouse *>
		(inputmanager -> createInputObject	(OISMouse, false));
	}
	{/* ### FrameListener ################################################### */
		root -> addFrameListener(this);
	}
	{/* ### Scene queries ################################################### */
//		cursor_ray = Ray(camera -> getPosition(), camera -> getDirection());
//		RSQ = scenemanager -> createRayQuery(cursor_ray);
		raycast = new RayCast(camera, scenemanager);
	}
	{// create the scene
		createScene();
	}
	 /*  ### Finished building the appli, congratulations myself ! ########## */
}
Application :: ~ Application()
{
	inputmanager -> destroyInputObject(mouse);
	inputmanager -> destroyInputObject(keyboard);
	InputManager :: destroyInputSystem(inputmanager);

	if(root) delete root;
}
void Application :: go ()
{
	if(instance != NULL)
		root -> startRendering();
	else
		exit(0xdeadc0de);
}
float GameConfig :: GetValue(string _s)
{
	float result = 0xdeadbeef;
	istringstream istrstr(configfile.getSetting(_s, StringUtil :: BLANK, "1.0"));
	istrstr >> result;
	return result;
}
string GameResource :: GetValue(string _s)
{return configfile.getSetting(_s, StringUtil :: BLANK, "sphere.mesh");}
void Application :: AddPlane()
{
	Ogre :: Plane plane(Ogre :: Vector3 :: UNIT_Y, -10);
	Ogre :: MeshManager :: getSingleton().createPlane
		("plane",
			ResourceGroupManager :: DEFAULT_RESOURCE_GROUP_NAME, plane,
			1500, 1500, 20, 20, true, 1, 5, 5, Ogre :: Vector3 :: UNIT_Z);

	entplane = scenemanager -> createEntity("LightPlaneEntity", "plane");
	rootnode -> createChildSceneNode() -> attachObject(entplane);
	entplane -> setMaterialName("Examples/Rocky");
}
