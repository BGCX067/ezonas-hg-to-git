#include "stdafx.h"


struct item_trait
{
	ushort trait; // 'uuid' defined by the yaml file
	std::vector<void *> data; // data, directly depends of trait
};
