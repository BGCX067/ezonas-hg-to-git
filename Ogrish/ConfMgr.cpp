#include "stdafx.h"

template<> ConfMgr * Ogre :: Singleton <ConfMgr> :: ms_Singleton = 0;
ConfMgr :: ConfMgr(string filepath):
	configfile(new ConfigFile)
//	rootnode((Application :: GetScMgr()) -> getRootSceneNode()),
{
	configfile -> load(filepath);
}
ConfMgr :: ~ ConfMgr()
{
	delete configfile;
}
float ConfMgr :: GetFloat(string _s)
{
	float result = float(0xdeadbeef);
	istringstream istrstr(configfile -> getSetting(_s, StringUtil :: BLANK, "1.0"));
	istrstr >> result;
	return result;
}
int ConfMgr :: GetInt(string _s)
{
	int result = 0xdeadbeef;
	istringstream istrstr(configfile -> getSetting(_s, StringUtil :: BLANK, "1.0"));
	istrstr >> result;
	return result;
}
SceneNode * ConfMgr :: FastAdd(string _s)
{
	istringstream iss(configfile -> getSetting(_s));

	// string s = configfile -> getSetting(_s);
	float x, y, z, scale;
	string mesh_filename, material_name;

	// unwraps config string
	iss >> mesh_filename >> scale >> material_name >> x >> y >> z;

	SceneNode * node = Application :: getSingletonPtr() -> GetScMgr() -> createSceneNode(_s);
	/* "-" loads the same named .mesh */
	Entity * ent;
	if(mesh_filename == "-")
		ent = Application :: getSingletonPtr() -> GetScMgr() -> createEntity(_s + ".mesh");
	else
		ent = Application :: getSingletonPtr() -> GetScMgr() -> createEntity(mesh_filename);
	/*   */

	/* "+" loads the same named .material */
	/* "-" loads no material */
	if (material_name != "-")
		ent -> setMaterialName(material_name);
	else 
		if (material_name == "+")
			ent -> setMaterialName(_s + ".material");
	/*   */
	//node -> attachObject(Application :: getSingletonPtr() -> GetScMgr() -> createEntity(mesh_filename));
	node -> attachObject(ent);
	((Application :: getSingletonPtr() -> GetScMgr()) -> getRootSceneNode()) -> addChild(node);
	if(scale != 1.0f) 
		node -> setScale(scale, scale, scale);
	node -> setPosition(x, y, z);
	return node;
}
SceneNode * ConfMgr :: AddLight(string _s)
{
	istringstream iss(configfile -> getSetting(_s));
	// string s = configfile -> getSetting(_s);
	float x, y, z, dir_x, dir_y, dir_z;
	string type;

	iss >> dir_x >> dir_y >> dir_z >> type >> x >> y >> z;

	SceneNode * node = Application :: getSingletonPtr() -> GetScMgr() -> createSceneNode(_s);
	Light * light = Application :: getSingletonPtr() -> GetScMgr() -> createLight(_s);
	
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
	
	((Application :: getSingletonPtr() -> GetScMgr()) -> getRootSceneNode()) -> addChild(node);
	
	node -> setPosition(x, y, z);

	return node;
}
Vec3 & ConfMgr :: getvect(string _s)
{
	istringstream iss(configfile -> getSetting(_s));
	// string s = configfile -> getSetting(_s);
	float x, y, z;

	iss >>  x >> y >> z;

	return Vec3(x, y, z);
}
SceneTypeMask ConfMgr :: GetScMgrType()
{
	string str = configfile -> getSetting("SceneManager");
	if(str == "BSP_INTERIOR") return ST_INTERIOR;
	if(str == "OCTREE_GENERIC") return ST_GENERIC;
	return ST_GENERIC;
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
