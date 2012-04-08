#include "stdafx.h"

#define WEAPON        (1 << 24)
#define MELEE         (1 << 25)
#define GUN           (1 << 26)
#define CONSUM        (1 << 27)
#define TOOL          (1 << 28)
#define AMMUN         (1 << 29)
#define WEARABLE      (1 << 30)
#define EXPIRES       (1 << 31)

struct item_trait
{
	ushort trait; // 'uuid' defined by the yaml file
	std::vector<void *> data; // data, directly depends of trait
};

struct ItemMgr
{
public:
	ItemMgr();
	std::vector<unsigned char[32]> Quantities;
	std::vector<unsigned int> hasItemMask;
	std::map <ushort, std::string> ItemNames;
	std::map <std::string, ushort> ItemIDs;
private:
};
