#include "stdafx.h"

Application :: Application():
	scenemanager(NULL),
	listener(NULL),
	// _keepRunning(true),
	root(new Root("plugins_d.cfg"))
{
// use the existing ogre.cfg if it exists, creates it otherwise
	if(!(root -> restoreConfig() || root -> showConfigDialog()))
		exit(0xdeadbeef);
// window
	window = root -> initialise(true, "Ogre3D Beginners Guide");
// scenemanager	
	scenemanager = root -> createSceneManager(ST_GENERIC);
// camera
	camera = scenemanager -> createCamera("Camera");
	camera -> setPosition(Ogre :: Vector3(0, 0, 20));
	camera -> lookAt(Ogre :: Vector3(0, 0, 0));
	camera -> setNearClipDistance(1);
// viewport
	viewport = window -> addViewport(camera);
	viewport -> setBackgroundColour(ColourValue(0.0, 0.0, 0.0));
	camera -> setAspectRatio
	(Real(viewport -> getActualWidth())/ Real(viewport -> getActualHeight()));

/* --------------- resources --------------- */
	ConfigFile cf;
	cf.load("resources_d.cfg");

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
// create the scene
	createScene();
/* --------------- Inputs --------------- */
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
/* --------------- Inputs Objects --------------- */
	inputmanager = InputManager :: createInputSystem(parameters);
	keyboard = static_cast<Keyboard *>
	(inputmanager -> createInputObject(OISKeyboard, false));
	mouse = static_cast<Mouse *>
	(inputmanager -> createInputObject	(OISMouse, false));
/* --------------- FrameListener --------------- */
	listener = new OgrikFrameListener(scenemanager, camera, inputmanager, mouse, keyboard);
	root -> addFrameListener(listener);	
}
Application :: ~ Application()
{
	inputmanager -> destroyInputObject(mouse);
	inputmanager -> destroyInputObject(keyboard);
	InputManager :: destroyInputSystem(inputmanager);

	if(root) delete root;
	if(listener) delete listener;
}

// void Application :: renderOneFrame()
// {
	// WindowEventUtilities :: messagePump();
	// _keepRunning = root -> renderOneFrame();
// }

void Application :: go () {root -> startRendering();}

Application * Application :: instance = NULL;