// done by jokoon ezjonas@gmail.com zonas.free.fr

#include "stdafx.h"

#define ynode YAML::Node
struct ProceduralBuilding
{
	float scale_x, scale_y, scale_z;
	std::map<std::string, Procedural::Shape> Shapes;
	virtual void configure(const YAML::Node & node) = 0;
};

struct ProcHouse: public ProceduralBuilding
{
	virtual void configure(const YAML::Node & node)
	{
		node["house"]["scale_x"]->begin().second() >> scale_x;
		node["house"]["scale_y"]->begin().second() >> scale_y;
		node["house"]["scale_z"]->begin().second() >> scale_z;
		//node.FindValue("house")->FindValue("scale_x")->begin().second() >> scale_x;
		//node.FindValue("house")->FindValue("scale_y")->begin().second() >> scale_y;
		//node.FindValue("house")->FindValue("scale_z")->begin().second() >> scale_z;
	}
};
struct ProcTenement: public ProceduralBuilding
{
	virtual void configure(const YAML::Node & node)
	{
		
	}
};
struct ProcWarehouse: public ProceduralBuilding
{
	virtual void configure(const YAML::Node & node)
	{
		
	}
};
struct ProcShop: public ProceduralBuilding
{
	virtual void configure(const YAML::Node & node)
	{
		
	}
};
