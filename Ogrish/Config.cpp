//#ifndef __APPLE__
#include "stdafx.h"
//#endif

void Application :: LoadEntity(string _s)
{
	istringstream iss(configfile -> getSetting(_s));
	float x, y, z, scale;
	string mesh_filename, material_name, scenenode_create;

	iss >> mesh_filename >> scale >> material_name >> x >> y >> z >> scenenode_create;
	bool scenenode_create_bool;
	if(scenenode_create == "true") scenenode_create_bool = true;
	else scenenode_create_bool = false;
	/* "-" loads the same named .mesh / material */
	Entity * ent;
	if(mesh_filename == "-") ent = SGLT_SCMGR -> createEntity(_s, _s + ".mesh");
	else					 ent = SGLT_SCMGR -> createEntity(_s, mesh_filename);

	if (material_name == "-") ent -> setMaterialName(_s + ".material");
	else if (material_name == "x")  PRINTLOG("No material used for "+_s);
	else					  ent -> setMaterialName(material_name);

	if(scenenode_create_bool)
	{
		SceneNode * node = SGLT_RSN->createChildSceneNode(_s, Vec3(x, y, z));
		node -> attachObject(ent);
		Nodes.push_back(node);
		node->showBoundingBox(true);
	}
	else
		Nodes.push_back(NULL);

		
	//ent->setP
	Entities.push_back(ent);
	isMoving.push_back(false);

#ifdef PHYSICS
	btCollisionObject * colobj = new btCollisionObject();
	collisionWorld->getCollisionObjectArray().push_back(colobj);
	colobj->setCollisionShape(sphere);
#endif
}
SceneNode * Application :: AddLight(string _s)
{
	istringstream iss(configfile -> getSetting(_s));
	// string s = configfile -> getSetting(_s);
	float x, y, z, dir_x, dir_y, dir_z;
	string type;

	iss >> dir_x >> dir_y >> dir_z >> type >> x >> y >> z;

	SceneNode * node = SGLT_SCMGR -> createSceneNode(_s);
	Light * light = SGLT_SCMGR -> createLight(_s);
	
	if(type == "DIR")
	{
		light -> setType(Light :: LT_DIRECTIONAL);
		light -> setDirection(dir_x, dir_y, dir_z);
	}
	if(type == "SPOT")
	{	
		light -> setType(Light :: LT_SPOTLIGHT);
		light -> setDirection(dir_x, dir_y, dir_z);
	}

	if(type == "POINT") light -> setType(Light :: LT_POINT);
	
	node -> attachObject(light);
	
	((SGLT_SCMGR) -> getRootSceneNode()) -> addChild(node);
	
	node -> setPosition(x, y, z);

	return node;
}
Vec3 Application :: GetVect3(string _s)
{
	istringstream iss(configfile -> getSetting(_s));
	// string s = configfile -> getSetting(_s);
	float x, y, z;

	iss >>  x >> y >> z;

	return Vec3(x, y, z);
}
SceneTypeMask Application :: GetScMgrType()
{
	string str = configfile -> getSetting("SceneManager");
	if(str == "BSP_INTERIOR") return ST_INTERIOR;
	if(str == "OCTREE_GENERIC") return ST_GENERIC;
	return ST_GENERIC;
}
float Application :: GetFloat(string _s)
{
	float result = float(0xdeadbeef);
	istringstream istrstr(configfile -> getSetting(_s, StringUtil :: BLANK, "1.0"));
	istrstr >> result;
	return result;
}
int Application :: GetInt(string _s)
{
	int result = 0xdeadbeef;
	istringstream istrstr(configfile -> getSetting(_s, StringUtil :: BLANK, "0"));
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
