#include "common.h"

struct Item
{
	Item(string _name): name(_name_) {};
	string name;
};
struct ItemActive: public Item
{

};
struct ItemPassive: public Item // example: a clue item
{

};
struct Weapon: public ItemActive
{

};

struct FireArm: public Weapon
{
	// min time between 2 shots, -, -, damage per shot
	float tick, ammoclip, ammomax, damage;
};

struct WhiteArm: public Weapon
{

};

// struct Ammunition
// {

// };