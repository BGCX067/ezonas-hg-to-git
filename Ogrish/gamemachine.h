// exclusive property of Jonas ORINOVSKI
// all right reserved
// namespace Ogre{class Entity{};};
#include <map>
#include <string>
#include <queue>
using namespace std;

//#ifndef __APPLE__
#include "stdafx.h"
//#endif
#define pr(s) printf("%s\n", s)
#define prx(s) printf("0x%X\n", s)

typedef unsigned int uint;

class Game_machine
{
public:
	Game_machine();
		
// a pass is a frame in term of gameplay.
	void pass();

	void sample_spell(); // proceed
	void diagnose_characters();
	void diagnose_events();
	void removeState(int id);
	void addState(float f, int id);
	void checkAndApplyAbility(Event * ev);
	// moving_speed_default, stealth_range, defense, attack_bonus, power, life, mask, name
	// cast_time, range, missile_speed, effect_moment, mask
	// ability_s make_ability(string, float, float, float, float, float, int, int);
	void go();
private:
	// data oriented
	float * timeSinceLastFrame;
	std::map <int, Ogre::Entity *> Entities; // each entity alredy has coord in ogre
	
	std::map <int, character_s>	Characters;
	std::map <string, int>		characters_id;

	std::map <int, ability_s>	Abilities;
	std::map <string, int>		abilities_id;

	std::vector<cast_state> States; // object pool
	std::queue<int> Availables;		// which ones are available

	queue <Event> Events;

	ItemMgr item_mgr;

};
/*
inputs (controls + network) into events queue
pass unstacks and checks
generates output accordingly
outputs to ogre
*/
