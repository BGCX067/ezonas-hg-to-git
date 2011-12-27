// exclusive property of Jonas ORINOVSKI
// all right reserved
// namespace Ogre{class Entity{};};
#include <map>
#include <string>
#include <queue>
using namespace std;

#include "stdafx.h"

#define pr(s) printf("%s\n", s)
#define prx(s) printf("0x%X\n", s)

typedef unsigned int uint;

class Game_machine
{
public:
	Game_machine();
		
// a pass is a frame in term of gameplay.
// the game engine can tun at 60 while the graphics can run at 50 or 120.
// every state is checked in a pass,
	bool pass();
	void fire_ability(event_abil);

	void sample_spell(); // proceed
	void diagnose_characters();
	void diagnose_events();
	// character_s make_character();
	// moving_speed_default, stealth_range, defense, attack_bonus, power, life, mask, name
	character_s make_character(float, float, float, float, float, float, int, string);
	// cast_time, range, missile_speed, effect_moment, mask
//	ability_s make_ability(string, float, float, float, float, float, int, int);
	void go();
private:
	std::map <int, Ogre::Entity *> Entities; // each entity alredy has coord in ogre
	std::map <int, character_s> Characters; // each entity alredy has coord in ogre
	std::map <int, ability_s> Abilities; // each entity alredy has coord in ogre
	std::map <string, int> IDs;

	queue <Event> Events;
	//ability_s ab_sample;

};
/*
inputs (controls + network) into events queue
pass unstacks and checks
generates output accordingly
outputs to ogre
*/
