#ifdef FUCKSHIT
#include "stdafx.h"
//#endif
void Application :: LoadEntity(string _s)
{
	istringstream iss(configfile -> getSetting(_s));
	float x, y, z, scale;
	string mesh_filename, material_name, flag;

	iss >> mesh_filename >> scale >> material_name >> x >> y >> z >> flag;

	/* "-" loads the same named .mesh / material */
	Ogre::Entity * ent;
	if(mesh_filename == "-") ent = SGLT_SCMGR -> createEntity(_s, _s + ".mesh");
	else					 ent = SGLT_SCMGR -> createEntity(_s, mesh_filename);

	if (material_name == "-") ent -> setMaterialName(_s + ".material");
	else if (material_name == "x")  PRINTLOG("No material used for "+_s);
	else					  ent -> setMaterialName(material_name);
	
	Ogre::SceneNode * node;
	if (flag == "target")
	{
		node = cam_ctrlr -> getTargetNode();
		cam_ctrlr -> setEntity(ent);
	}
	else
	{
		node = SGLT_RSN->createChildSceneNode(_s, Ogre::Vector3(x, y, z));
		node -> attachObject(ent);
		Nodes.push_back(node);
	}
	node->showBoundingBox(true);
	
	Entities.push_back(ent);
	isMoving.push_back(false);

#ifdef PHYSICS
	btCollisionObject * colobj = new btCollisionObject();
	collisionWorld->getCollisionObjectArray().push_back(colobj);
	colobj->setCollisionShape(sphere);
#endif
}
void Application :: Populate()
{
	// REMINDER: FOR THE 5432nd TIME, HEIGHT IS Y (forward is x)
	int population = GetInt("population");
	istringstream iss(configfile -> getSetting("pop_zone"));
	float  A_x, A_z, B_x, B_z;
	iss >> A_x >> A_z >> B_x >> B_z;

	std::string pop_mesh = configfile -> getSetting("pop_mesh");
	for(int i = 0 ; i < population; ++ i)
	{
		Ogre::SceneNode * node = SGLT_RSN -> createChildSceneNode();
		node -> attachObject(SGLT_SCMGR -> createEntity(pop_mesh));
		node -> setPosition(
			Ogre::Math::RangeRandom(A_x, B_x),
			Ogre::Real(0),
			Ogre::Math::RangeRandom(A_z, B_z)
			);
		Nodes.push_back(node);
	}
}

Ogre::SceneNode * Application :: AddLight(string _s)
{
	istringstream iss(configfile -> getSetting(_s));
	// string s = configfile -> getSetting(_s);
	float x, y, z, dir_x, dir_y, dir_z;
	string type;

	iss >> dir_x >> dir_y >> dir_z >> type >> x >> y >> z;

	Ogre::SceneNode * node = SGLT_SCMGR -> createSceneNode(_s);
	Ogre::Light * light = SGLT_SCMGR -> createLight(_s);
	
	if(type == "DIR")
	{
		light -> setType(Ogre::Light :: LT_DIRECTIONAL);
		light -> setDirection(dir_x, dir_y, dir_z);
	}
	if(type == "SPOT")
	{	
		light -> setType(Ogre::Light :: LT_SPOTLIGHT);
		light -> setDirection(dir_x, dir_y, dir_z);
	}

	if(type == "POINT") light -> setType(Ogre::Light :: LT_POINT);
	
	node -> attachObject(light);
	
	((SGLT_SCMGR) -> getRootSceneNode()) -> addChild(node);
	
	node -> setPosition(x, y, z);

	return node;
}
Ogre::Vector3 Application :: GetVect3(string _s)
{
	istringstream iss(configfile -> getSetting(_s));
	// string s = configfile -> getSetting(_s);
	float x, y, z;

	iss >>  x >> y >> z;

	return Ogre::Vector3(x, y, z);
}
Ogre::Vector2 Application :: GetVect2(string _s)
{
	istringstream iss(configfile -> getSetting(_s));
	// string s = configfile -> getSetting(_s);
	float x, y;

	iss >>  x >> y;

	return Ogre::Vector2(x, y);
}
Ogre::SceneTypeMask Application :: GetScMgrType()
{
	string str = configfile -> getSetting("SceneManager");
	if(str == "BSP_INTERIOR") return Ogre::SceneType:: ST_INTERIOR;
	if(str == "OCTREE_GENERIC") return Ogre::SceneType::ST_GENERIC;
	return Ogre::SceneType::ST_GENERIC;
}
float Application :: GetFloat(string _s)
{
	float result = float(0xdeadbeef);
	istringstream istrstr(configfile -> getSetting(_s, Ogre::StringUtil :: BLANK, "1.0"));
	istrstr >> result;
	return result;
}
int Application :: GetInt(string _s)
{
	int result = 0xdeadbeef;
	istringstream istrstr(configfile -> getSetting(_s, Ogre::StringUtil :: BLANK, "0"));
	istrstr >> result;
	return result;
}

/*
memo from wiki:
The argument to createSceneManager (getSceneManager in older releases) specifies the type of scene manager to use, based on the following values:

ST_GENERIC - Generic scene manager (Octree if you load Plugin_OctreeSceneManager, DotScene if you load Plugin_DotSceneManager)
ST_EXTERIOR_CLOSE - Terrain Scene Manager
ST_EXTERIOR_FAR - Nature scene manager <sub>This mode is not present anymore in Ogre 1.0. Use "Terrain", or "Paging Landscape" instead.</sub>
ST_EXTERIOR_REAL_FAR - Paging Scene Manager
ST_INTERIOR - BSP scene manager
*/
#endif