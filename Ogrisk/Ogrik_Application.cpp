#include "stdafx.h"

Application :: Application()
{
	_sceneManager = NULL;
	_listener = NULL;
	_keepRunning = true;
}

Application :: ~ Application()
{
	if(_root)
	{
		delete _root;
	}
	if(_listener)
	{
		delete _listener;
	}
}

void Application :: loadResources()
{
	ConfigFile cf;
	cf.load("resources_d.cfg");


	ConfigFile::SectionIterator sectionIter = cf.getSectionIterator();
	String sectionName, typeName, dataname;
	while (sectionIter.hasMoreElements())
	{
		sectionName = sectionIter.peekNextKey();
		ConfigFile::SettingsMultiMap *settings = sectionIter.getNext();
		ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			dataname = i->second;

			ResourceGroupManager::getSingleton().addResourceLocation(
				dataname, typeName, sectionName);

		}
	}


	ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

int Application :: startup()
{
	_root = new Root("plugins_d.cfg");


	if(!(_root -> restoreConfig() || _root->showConfigDialog()))
	{
		return -1;
	}

	RenderWindow* window = _root->initialise(true,"Ogre3D Beginners Guide");

	_sceneManager = _root->createSceneManager(ST_GENERIC);

	Camera* camera = _sceneManager->createCamera("Camera");
	camera->setPosition(Ogre :: Vector3(0,0,50));
	camera->lookAt(Ogre :: Vector3(0,0,0));
	camera->setNearClipDistance(5);


	Viewport* viewport = window->addViewport(camera);
	viewport->setBackgroundColour(ColourValue(0.0,0.0,0.0));
	camera->setAspectRatio(Real(viewport->getActualWidth())/ Real(viewport->getActualHeight()));


	loadResources();
	createScene();

	_listener = new OgrikFrameListener(window,camera);
	_root->addFrameListener(_listener);

	return 0;

}

void Application :: createScene()
{
	Entity* ent = _sceneManager->createEntity("Sinbad.mesh");

	_sceneManager->getRootSceneNode()->attachObject(ent);

}

void Application :: renderOneFrame()
{
	WindowEventUtilities::messagePump();
	_keepRunning = _root->renderOneFrame();
}

bool Application :: keepRunning()
{
	return _keepRunning;
}
