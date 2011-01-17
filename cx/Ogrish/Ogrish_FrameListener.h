#include "Ogrish.h"

class SuperFrameListener : public FrameListener
{
private:
	Ogre::SceneNode* _node;
	OIS::InputManager* _man;
	OIS::Keyboard* _key;
public:
	SuperFrameListener(Ogre::SceneNode* node,RenderWindow* win)
	{
		_node = node;

		size_t windowHnd = 0;
		std::stringstream windowHndStr;

		win->getCustomAttribute("WINDOW", &windowHnd);
		windowHndStr << windowHnd;
		
		OIS::ParamList pl;
		pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

		_man = OIS::InputManager::createInputSystem( pl );
		_key = static_cast<OIS::Keyboard*>(_man->createInputObject( OIS::OISKeyboard, false ));
	}	
	bool frameStarted(const Ogre::FrameEvent  &evt)
	{		
		_key->capture();
		if(_key->isKeyDown(OIS::KC_ESCAPE))
		{
			return false;
		}
		Ogre::Vector3 translate(0,0,0);
		if(_key->isKeyDown(OIS::KC_W))
		{
			translate += Ogre::Vector3(0,0,-10);
		}
		if(_key->isKeyDown(OIS::KC_S))
		{
			translate += Ogre::Vector3(0,0,10);
		}
		if(_key->isKeyDown(OIS::KC_A))
		{
			translate += Ogre::Vector3(-10,0,0);
		}
		if(_key->isKeyDown(OIS::KC_D))
		{
			translate += Ogre::Vector3(10,0,0);
		}	
		_node->translate(translate*evt.timeSinceLastFrame);
		return true;
	}
};
