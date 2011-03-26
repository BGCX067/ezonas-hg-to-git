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
	float result = 0xdeadbeef;
	istringstream istrstr(configfile -> getSetting(_s, StringUtil :: BLANK, "1.0"));
	istrstr >> result;
	return result;
}
//void ConfMgr :: Instantiate(string filepath)
//{
//	static ConfMgr inst(filepath);
//	instance = & inst;
//}
//ConfMgr * ConfMgr :: sglt()
//	{return instance;}
// WARNING: Fast doesn't have anything to do with
// performance here. This is only for scene creation
// (which has no performance matter) !
SceneNode * ConfMgr :: FastAdd(string _s)
{
	istringstream iss(configfile -> getSetting(_s));
	// string s = configfile -> getSetting(_s);
	float x, y, z, scale;
	string mesh_filename, material_name;

	iss >> mesh_filename >> scale >> material_name >> x >> y >> z;

	SceneNode * node = Application :: getSingletonPtr() -> GetScMgr() -> createSceneNode(_s);
	
	Entity * ent = Application :: getSingletonPtr() -> GetScMgr() -> createEntity(mesh_filename);
	if (material_name != "-") ent -> setMaterialName(material_name);
	//node -> attachObject(Application :: getSingletonPtr() -> GetScMgr() -> createEntity(mesh_filename));
	node -> attachObject(ent);
	((Application :: getSingletonPtr() -> GetScMgr()) -> getRootSceneNode()) -> addChild(node);
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



ConfMgr * ConfMgr :: instance = NULL;
