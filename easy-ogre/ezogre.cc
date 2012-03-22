#include "stdafx.h"

Root		 * root;
RenderWindow * window;
SceneManager * scmgr;
Camera 		 * camera;
Viewport 	 * viewport;
OIS::InputManager * inputmanager;
OIS::Keyboard 	 * keyboard;
OIS::Mouse 		 * mouse;

Vec3 translate(0,0,0), translate2(0,0,0);
float moving_speed = 10.f, timeSinceLastFrame = 0.0f, rotating_speed = 0.001f;
bool stop = false;
SceneNode * cam_node, * babar;

struct Application:
	public FrameListener,
	public OIS::KeyListener,
	public OIS::MouseListener
{

	Application(): FrameListener() {}
    ~ Application()
	{
		inputmanager -> destroyInputObject( mouse);
		inputmanager -> destroyInputObject( keyboard);
		OIS::InputManager :: destroyInputSystem( inputmanager);

		if(root) delete root;
		else exit(0xb00b);
	}
	bool frameRenderingQueued(const FrameEvent & evt)
	{
		keyboard -> capture();
		mouse -> capture();
		timeSinceLastFrame = evt.timeSinceLastFrame;
		cam_node -> translate
		(cam_node->getOrientation() *  translate * moving_speed * timeSinceLastFrame);
		assert(translate.length() <= 1.0f);
		babar->yaw(Radian(timeSinceLastFrame));
		return ! stop;
	}
	// ####### OIS #######
	bool mouseMoved		(const OIS::MouseEvent &e)
	{
		cam_node ->   yaw(Radian(- e.state.X.rel * rotating_speed), Ogre::Node::TS_WORLD);
		cam_node -> pitch(Radian(- e.state.Y.rel * rotating_speed));
		return true;
	}
	bool mousePressed	(const OIS::MouseEvent &e, OIS::MouseButtonID id) { return true; }
	bool mouseReleased	(const OIS::MouseEvent &e, OIS::MouseButtonID id) { return true; }
	bool keyPressed		(const OIS::KeyEvent &e)
	{
		using namespace OIS;
		switch(e.key)
		{
		case KC_ESCAPE: stop = true; break;
		case KC_UP: case KC_W:						translate2.z -=  1.f; break;
		case KC_DOWN: case KC_S:					translate2.z +=  1.f; break;
		case KC_LEFT: case KC_A:					translate2.x -=  1.f; break;
		case KC_RIGHT: case KC_D:					translate2.x +=  1.f; break;
		case KC_F7:	camera->setPolygonMode(PM_WIREFRAME); break;
		case KC_F8:	camera->setPolygonMode(PM_SOLID); break;
			

		case KC_PGUP: case KC_Q: case KC_LSHIFT:	translate2.y -=  1.f; break;
		case KC_PGDOWN: case KC_E: case KC_SPACE:	translate2.y +=  1.f; break;
		case KC_MINUS:
			if(camera ->getFOVy() > Degree(10.f))
				camera ->setFOVy(camera ->getFOVy() - Radian(timeSinceLastFrame) *20.f);
			break;
		case KC_EQUALS:
			if(camera ->getFOVy() < Degree(120.f))
				camera ->setFOVy(camera ->getFOVy() + Radian(timeSinceLastFrame) *20.f);
			break;
		default: break;
		}
		translate = translate2;
		translate.normalise();
		return true;
	}
	bool keyReleased	(const OIS::KeyEvent &e)
	{
		//Ogre :: Vector3 translate(0, 0, 0);
		using namespace OIS;
		switch(e.key)
		{
			case KC_ESCAPE:
				stop = true;
				break;

			case KC_UP: case KC_W:							translate2.z +=  1.f; break;
			case KC_DOWN: case KC_S:						translate2.z -=  1.f; break;

			//case KC_LEFT: case KC_A:						rot -= .002f; break;
			//case KC_RIGHT: case KC_D:						rot += .002f; break;
			case KC_LEFT: case KC_A:						translate2.x +=  1.f; break;
			case KC_RIGHT: case KC_D:						translate2.x -=  1.f; break;

			case KC_PGUP: case KC_Q: case KC_LSHIFT:		translate2.y +=  1.f; break;
			case KC_PGDOWN: case KC_E: case KC_SPACE:		translate2.y -=  1.f; break;

			default:
				break;
	}  
	translate = translate2;
	translate.normalise();
	return true;
}
	void init()
	{
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
#endif
		if(root -> restoreConfig() == false)
			if (root -> showConfigDialog() == false)
				exit (0xdeadbeef);

		window	 = root -> initialise(true, "Easy Ogre demonstration");
		scmgr	 = root -> createSceneManager(ST_GENERIC);
		camera	 = scmgr -> createCamera("Camera");
		viewport = window -> addViewport(camera);
		/* changing some settings */
		camera -> setNearClipDistance(1);
		camera -> setAspectRatio
			(Real(viewport -> getActualWidth())/ Real(viewport -> getActualHeight()));
		root -> addFrameListener(this);
	}
	void init_resources()
	{
		// RESOURCES ////////////////////////////////////////
		ConfigFile cf;
	#ifdef __APPLE__
		cf.load(macBundlePath() + "/Contents/Resources/"+"conf/resources_d.cfg");
		PRINTLOG(macBundlePath() + "/Contents/Resources/");
	#else
		cf.load("conf/resources_d.cfg");
	#endif

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
	#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
				Ogre::String archName;
				// OS X does not set the working directory relative to the app,
				// In order to make things portable on OS X we need to provide
				// the loading with it's own bundle path location
				if (!Ogre::StringUtil::startsWith(dataname, "/", false)) // only adjust relative dirs
					dataname = Ogre::String(Ogre::macBundlePath() + "/Contents/Resources/" + dataname);
	#endif
				ResourceGroupManager :: getSingleton().addResourceLocation(
					dataname, typeName, sectionName);
				LOGMSG(sectionName+": "+typeName+" | "+dataname);
			}
		}
		ResourceGroupManager :: getSingleton().initialiseAllResourceGroups();
	}
	void init_inputs()
	{
		OIS::ParamList parameters;
		unsigned int windowHandle = 0;
		ostringstream windowHandleString;
		 window -> getCustomAttribute("WINDOW", & windowHandle);
		windowHandleString << windowHandle;
		parameters.insert(make_pair("WINDOW", windowHandleString.str()));
		parameters.insert(make_pair("WINDOW", windowHandleString.str()));
	// those settings unhide the cursor (from ogre's wiki snippets)
	#if defined OIS_WIN32_PLATFORM
		parameters.insert(make_pair(string("w32mouse"), 	string("DISCL_FOREGROUND" )));
		parameters.insert(make_pair(string("w32mouse"), 	string("DISCL_NONEXCLUSIVE")));
		parameters.insert(make_pair(string("w32keyboard"), 	string("DISCL_FOREGROUND")));
		parameters.insert(make_pair(string("w32keyboard"), 	string("DISCL_NONEXCLUSIVE")));
	#elif defined OIS_LINUX_PLATFORM
		parameters.insert(make_pair(string("x11mouse_grab"), 	string("false")));
		parameters.insert(make_pair(string("x11mouse_hide"), 	string("false")));
		parameters.insert(make_pair(string("x11keyboard_grab"), string("false")));
		parameters.insert(make_pair(string("XAutoRepeatOn"), 	string("true")));
	#endif
	/* ### Inputs Objects ################################################## */
		 inputmanager = OIS::InputManager :: createInputSystem(parameters);
		 keyboard = static_cast<OIS::Keyboard *>
			( inputmanager -> createInputObject(OIS::OISKeyboard, true));
		 mouse = static_cast<OIS::Mouse *>
			( inputmanager -> createInputObject	(OIS::OISMouse, true));
		 mouse -> setEventCallback(this);
		 keyboard -> setEventCallback(this);
	}	
	void init_scene()
	{
		cam_node = scmgr->getRootSceneNode()->createChildSceneNode("cam_node");
		cam_node -> attachObject(camera);
		babar = NODE("babar");
		Entity * e = ENTITY("bonome", "bonome.mesh");
		LOGMSG(e->getName());
		babar->attachObject(scmgr->getEntity("bonome"));

		SceneNode * light_node = scmgr -> getRootSceneNode()-> createChildSceneNode("light1");
		Light * light = scmgr -> createLight("light1");
		light -> setType(Light :: LT_POINT);
		light_node -> attachObject(light);
		light_node -> setPosition(3, 3, 3);

		light_node = scmgr -> getRootSceneNode()-> createChildSceneNode("light2");
		light = scmgr -> createLight("light2");
		light -> setType(Light :: LT_POINT);
		light_node -> attachObject(light);
		light_node -> setPosition(-3, 3, -3);
		cam_node->setPosition(0,0,3);
	}
	void init_other()
	{
		YAML::Parser parser(ifstream("test.yaml"));
		YAML::Node doc;
		while(parser.GetNextDocument(doc))
		{}
	}
};

#ifdef __APPLE__
int main()
#elif _CONSOLE
int main(int argc, char * argv[])
#else
int /*__stdcall*/ WinMain(HINSTANCE a, HINSTANCE b, LPSTR c, int d)
#endif
{
	Application app;
	app.init();
	LOGMSG("------------- init started -------------");
	app.init_resources();
	app.init_inputs();
	app.init_scene();
	app.init_other();
	LOGMSG("------------- init ended -------------");
	root->startRendering();
	return 0;
}
