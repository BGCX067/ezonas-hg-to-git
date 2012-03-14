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
	void putMesh3(const std::string& meshName, const Vector3& position)
	{ putMeshMat(meshName, "derp", position, false); }
	void putMesh2(const std::string& meshName, const Vector3& position)
	{ putMeshMat(meshName, "derp", position, false); }
	void putMesh(const std::string& meshName, const Vector3& position)
	{ putMeshMat(meshName, "derp", position, true); }
	void putMeshMat(const std::string& meshName, const std::string& matName,
		const Vector3& position, bool castShadows)
	{
		Entity* ent2 = scmgr->createEntity(meshName);
		SceneNode* sn = scmgr->getRootSceneNode()->createChildSceneNode();
		sn->attachObject(ent2);
		sn->setPosition(position);
		ent2->setMaterialName(matName);
		ent2->setCastShadows(castShadows);
	}
	void putmesh(string s, Vec3 pos)
	{
		NODE(s)->attachObject(ENTITY(s, s));
		scmgr->getSceneNode(s)->setPosition(pos);
		scmgr->getEntity(s)->setMaterialName("derp");	
	}
	void init_other()
	{
		// -- Ground plane
		Procedural::PlaneGenerator().setNumSegX(20).setNumSegY(20).setSizeX(150).setSizeY(150).setUTile(5.0).setVTile(5.0).realizeMesh("planeMesh");
		putMesh2("planeMesh", Vec3(0,0,0));

		// -- Road
		// The path of the road, generated from a simple spline
		Procedural::Path p = Procedural::CatmullRomSpline3().setNumSeg(8).addPoint(0,0,0).addPoint(0,0,10).addPoint(10,0,10).addPoint(20,0,0).close().realizePath().scale(2);
		// The shape that will be extruded along the path
		Procedural::Shape s = Procedural::Shape().addPoint(-1.2f,.2f).addPoint(-1.f,.2f).addPoint(-.9f,.1f).addPoint(.9f,.1f).addPoint(1.f,.2f).addPoint(1.2f,.2f).scale(2).setOutSide(Procedural::SIDE_LEFT);
		// This is an example use of a shape texture track, 
		// which specifies how texture coordinates should be mapped relative to the shape points
		Procedural::Track textureTrack = Procedural::Track(Procedural::Track::AM_POINT).addKeyFrame(0,0).addKeyFrame(2,.2).addKeyFrame(3,.8).addKeyFrame(5,1);
		// The extruder actually creates the road mesh from all parameters
		Procedural::Extruder().setExtrusionPath(&p).setShapeToExtrude(&s).setShapeTextureTrack(&textureTrack).setUTile(20.).realizeMesh("extrudedMesh");
		putMesh3("extrudedMesh", Vec3(0,0,0));

		// -- Pillar
		// The path of the pillar, just a straight line
		Procedural::Path pillarBodyPath = Procedural::LinePath().betweenPoints(Vector3(0,0,0), Vector3(0,5,0)).realizePath();
		// We're doing something custom for the shape to extrude
		Procedural::Shape pillarBodyShape;
		const int pillarSegs=64;
		for (int i=0;i<pillarSegs;i++)						
			pillarBodyShape.addPoint(.5*(1-.15*Math::Abs(Math::Sin(i/(float)pillarSegs*8.*Math::TWO_PI))) * 
						Vector2(Math::Cos(i/(float)pillarSegs*Math::TWO_PI), Math::Sin(i/(float)pillarSegs*Math::TWO_PI)));
		pillarBodyShape.close();
		// We're also setting up a scale track, as traditionnal pillars are not perfectly straight
		Procedural::Track pillarTrack = Procedural::CatmullRomSpline2().addPoint(0,1).addPoint(0.5,.95).addPoint(1,.8).realizeShape().convertToTrack(Procedural::Track::AM_RELATIVE_LINEIC);
		// Creation of the pillar body
		Procedural::TriangleBuffer pillarTB;
		Procedural::Extruder().setExtrusionPath(&pillarBodyPath).setShapeToExtrude(&pillarBodyShape).setScaleTrack(&pillarTrack).setCapped(false).setPosition(0,1,0).addToTriangleBuffer(pillarTB);
		// Creation of the top and the bottom of the pillar
		Procedural::Shape s3 = Procedural::RoundedCornerSpline2().addPoint(-1,-.25).addPoint(-1,.25).addPoint(1,.25).addPoint(1,-.25).close().realizeShape().setOutSide(Procedural::SIDE_LEFT);
		Procedural::Path p3;
		for (int i=0;i<32;i++)
		{
			Ogre::Radian r = (Ogre::Radian) (Ogre::Math::HALF_PI-(float)i/32.*Ogre::Math::TWO_PI);
			p3.addPoint(0,-.5+.5*i/32.*Math::Sin(r),-1+.5*i/32.*Math::Cos(r));
		}
		p3.addPoint(0,0,-1).addPoint(0,0,1);
		for (int i=0;i<32;i++)
		{
			Ogre::Radian r = (Ogre::Radian) (Ogre::Math::HALF_PI-(float)i/32.*Ogre::Math::TWO_PI);
			p3.addPoint(0,-.5+.5*(1-i/32.)*Math::Sin(r),1+.5*(1-i/32.)*Math::Cos(r));
		}
		Procedural::Extruder().setExtrusionPath(&p3).setShapeToExtrude(&s3).setPosition(0,6.,0).addToTriangleBuffer(pillarTB);
		//Procedural::BoxGenerator().setPosition(0,6.5,0).addToTriangleBuffer(pillarTB);
		Procedural::BoxGenerator().setPosition(0,.5,0).addToTriangleBuffer(pillarTB);
		pillarTB.transformToMesh("pillar");
		// We put the pillars on the side of the road
		for (int i=0;i<p.getSegCount();i++)
			if (i%2==0)
				putMeshMat("pillar", "derp", p.getPoint(i)+4*p.getAvgDirection(i).crossProduct(Ogre::Vector3::UNIT_Y).normalisedCopy(),false);

		// -- Jarre
		// 
		Procedural::TriangleBuffer tb;
		// Body
		Procedural::Shape jarreShape = Procedural::CubicHermiteSpline2().addPoint(Ogre::Vector2(0,0), Ogre::Vector2::UNIT_X, Ogre::Vector2::UNIT_X)
																.addPoint(Ogre::Vector2(2,3))
																.addPoint(Ogre::Vector2(.5,5), Ogre::Vector2(-1,1).normalisedCopy(), Ogre::Vector2::UNIT_Y)
																.addPoint(Ogre::Vector2(1,7), Ogre::Vector2(1,1).normalisedCopy()).realizeShape().thicken(.1).getShape(0);
		Procedural::Lathe().setShapeToExtrude(&jarreShape).addToTriangleBuffer(tb);
		// Handle 1
		Procedural::Shape jarreHandleShape = Procedural::CircleShape().setRadius(.2).realizeShape();
		Procedural::Path jarreHandlePath = Procedural::CatmullRomSpline3().addPoint(Ogre::Vector3(0,6.5,.75))
																.addPoint(Ogre::Vector3(0,6,1.5))
																.addPoint(Ogre::Vector3(0,5,.55)).setNumSeg(10).realizePath();					
		Procedural::Extruder().setShapeToExtrude(&jarreHandleShape).setExtrusionPath(&jarreHandlePath).addToTriangleBuffer(tb);		
		// Handle2
		jarreHandlePath.reflect(Ogre::Vector3::UNIT_Z);
		Procedural::Extruder().setShapeToExtrude(&jarreHandleShape).setExtrusionPath(&jarreHandlePath).addToTriangleBuffer(tb);		
		tb.transformToMesh("jarre");
		putMeshMat("jarre", "derp", Vector3(5,0,5),false);
		

/*	    Procedural::SphereGenerator().setRadius(2.f).setUTile(5.).setVTile(5.).realizeMesh("sphereMesh");
		putmesh("sphereMesh", Vector3(0,10,0));

		Procedural::CylinderGenerator().setHeight(3.f).setRadius(1.f).setUTile(3.).realizeMesh("cylinderMesh");
		putmesh("cylinderMesh", Vector3(10,10,0));

		Procedural::TorusGenerator().
			setRadius(3.f).setSectionRadius(1.f).setUTile(10.).setVTile(5.).realizeMesh("torusMesh");
		putmesh("torusMesh", Vector3(-10,10,0));

		Procedural::ConeGenerator().
			setRadius(2.f).setHeight(3.f).setNumSegBase(36).setNumSegHeight(2).setUTile(3.).realizeMesh("coneMesh");
		putmesh("coneMesh", Vector3(0,10,-10));

		Procedural::TubeGenerator().
			setHeight(3.f).setUTile(3.).realizeMesh("tubeMesh");
		putmesh("tubeMesh", Vector3(-10,10,-10));

		Procedural::BoxGenerator().
			setSizeX(2.0).setSizeY(4.f).setSizeZ(6.f).realizeMesh("boxMesh");
		putmesh("boxMesh", Vector3(10,10,-10));

		Procedural::CapsuleGenerator()
			.setHeight(2.f).realizeMesh("capsuleMesh");
		putmesh("capsuleMesh", Vector3(0,10,10));

		Procedural::TorusKnotGenerator()
			.setRadius(2.f).setSectionRadius(.5f).setUTile(3.f).setNumSegCircle(64).setNumSegSection(16).realizeMesh("torusKnotMesh");
		putmesh("torusKnotMesh", Vector3(-10,10,10));

		Procedural::IcoSphereGenerator()
			.setRadius(2.).setNumIterations(1).setUTile(5.).setVTile(5.).realizeMesh("icoSphereMesh");
		putmesh("icoSphereMesh", Vector3(10,15,10));

		Procedural::IcoSphereGenerator()
			.setRadius(2.).setNumIterations(2).setUTile(5.).setVTile(5.).realizeMesh("icoSphereMesh2");
		putmesh("icoSphereMesh2", Vector3(10,10,10));

		Procedural::RoundedBoxGenerator()
			.setSizeX(1.f).setSizeY(5.f).setSizeZ(5.f).setChamferSize(1.f).realizeMesh("roundedBoxMesh");
		putmesh("roundedBoxMesh", Vector3(20,10,10));		
		*/
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
