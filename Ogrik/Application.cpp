#include "stdafx.h"

SceneNode * Application :: QuickAdd(string _s)
{
	SceneNode * node = scenemanager -> createSceneNode(_s);
	node -> attachObject(scenemanager -> createEntity(_s));
	rootnode -> addChild(node);
	return node;
}
// WARNING: Fast doesn't have anything to do with
// performance here. This is only for scene creation (which has no performance matter) !
SceneNode * Application :: FastAdd(string _s)
{
	istringstream iss(configfile -> getSetting(_s));
	string s = configfile -> getSetting(_s);
	float x, y, z, scale;
	string mesh_filename, material_name;

	//iss >> mesh_filename;
	//iss >> scale;
	//iss >> material_name;
	//iss >> x;
	//iss >> y;
	//iss >> z;
	iss >> mesh_filename >> scale >> material_name >> x >> y >> z;
	// iss >> z >> y >> x >> material_name >> scale >> mesh_filename;

	SceneNode * node = scenemanager -> createSceneNode(_s);
	Entity * ent = scenemanager -> createEntity(mesh_filename);
	if (material_name != "-") ent -> setMaterialName(material_name);
	node -> attachObject(scenemanager -> createEntity(mesh_filename));
	rootnode -> addChild(node);
	node -> setScale(scale, scale, scale);
	node -> setPosition(x, y, z);
	return node;
}
Application :: Application():
// ##### INITIALIZATIONS HERE ##########################################################
	scenemanager(NULL),
	FrameListener(),
	root(new Root("conf/plugins_d.cfg")),
	configfile (new ConfigFile)
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
		//camera -> setPosition(Ogre :: Vector3(0, 0, 20));
		//camera -> lookAt(Ogre :: Vector3(0, 0, 0));
		camera -> setNearClipDistance(1);
	}
	{// ### First Person Camera Object ######################################
		fpersoncam = new FPersonCam(camera, rootnode);
	}
	{/* ### viewport ######################################################## */
		viewport = window -> addViewport(camera);
		viewport -> setBackgroundColour(ColourValue(0.1, 0.1, 0.1));
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
		raycast = new RayCast(camera, scenemanager);
	}
	{//gameplay tweakables
		configfile -> load("conf/gameconf.cfg");

		moving_speed	= GetFloat("moving_speed");
		rotating_speed	= - GetFloat("rotating_speed");
		laser_width		= GetFloat("laser_width");
		trace_width		= GetFloat("trace_width");
		bullet_speed	= GetFloat("bullet_speed");
		trace_length	= GetFloat("trace_length");
	}
	{// create the scene
		createScene();
	}
	 /*  ### Finished building the appli, congratulations myself ! ########## */
// ##### INITIALIZATIONS END ##########################################################
}
Application :: ~ Application()
{
	inputmanager -> destroyInputObject(mouse);
	inputmanager -> destroyInputObject(keyboard);
	InputManager :: destroyInputSystem(inputmanager);
	delete fpersoncam;
	delete configfile;
	if(root) delete root;
}
void Application :: go ()
{
	if(instance != NULL)
		root -> startRendering();
	else
		exit(0xdeadc0de);
}
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
const float Application :: GetFloat(string _s)
{
	float result = 0xdeadbeef;
	istringstream istrstr(configfile -> getSetting(_s, StringUtil :: BLANK, "1.0"));
	istrstr >> result;
	return result;
}
Application * Application :: instance = NULL;
Application * Application :: GetSingleton() {return instance;}
void Application :: Instantiate() {static Application inst; instance = & inst;}
