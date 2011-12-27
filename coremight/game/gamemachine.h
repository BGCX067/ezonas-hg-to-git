// exclusive property of Jonas ORINOVSKI
// all right reserved
namespace Ogre{class Entity{};};
#include <map>
#include <string>
#include <deque>
using namespace std;

#include "struct.h"
#include "mask-define.h"


typedef unsigned int uint;

class Game_machine
{
public:
	Game_machine();
		
// a pass is a frame in term of gameplay.
// the game engine can tun at 60 while the graphics can run at 50 or 120.
// every state is checked in a pass,
	bool pass();
	void fire_ability(int,int);
	void sample_spell(); // proceed
	void diagnose_characters();
	void diagnose_events();
	character_s make_character();
	void go();
private:
	map <int, Ogre::Entity *> Entities; // each entity alredy has coord in ogre
	map <int, character_s> Characters; // each entity alredy has coord in ogre
	map <int, ability_s> Abilities; // each entity alredy has coord in ogre
	map <string, int> IDs;
	deque <event_s *> EventQueue;
	ability_s ab_sample;

};
/*
inputs (controls + network) into events queue
    v
pass unstacks and checks
    v
generates output accordingly
*/

//targets are only client-interface side
