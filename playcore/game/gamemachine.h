// exclusive property of Jonas ORINOVSKI
// all right reserved
namespace Ogre{class Entity{};};
#include <map>
#include <string>
#include <deque>
#include "state-masks.h"
typedef unsigned int uint;
using namespace std;

struct ability_s
{
	// bool allow_movement,
	//      target_in_front,
	//      requires_target,
	// 	    click_location_event,
	//      splash_damage;

	float cast_time, 	// 0 means instant
	      range,		// 0 means melee with hitboxes
	      missile_speed;// 0 mean instant
	int effect_moment, mask; 	// start, end, channeled
};

struct character_s // remember most values don't go over 100
{
	float moving_speed_default, // might be a int, since it's multiplier
	      stealth_range, 		// the smaller the stealthier
	      defense, 				// percentage of damage reduction, negative
	      attack_bonus, 		// % of bonus attacks, apply in the final pass
	      power, 				// might, mana, energy, etc
	      life;
	int mask;
	string name;
};

struct event_s
{
	float pos[3]; // if it's null it's standardly the emitter location
	int target_id, emitter_id, spell_id;
};
class Game_machine
{
public:
	Game_machine();
		
// a pass is a frame in term of gameplay.
// the game engine can tun at 60 while the graphics can run at 50 or 120.
// every state is checked in a pass,
	bool pass();
	void fire_ability();
	void sample_spell(); // proceed
	void diagnose();
	
	
	character_s make_character();
	
private:
	map <int, Ogre::Entity *> Entities; // each entity alredy has coord in ogre
	map <int, character_s> Characters; // each entity alredy has coord in ogre
	map <int, ability_s> Abilities; // each entity alredy has coord in ogre
	map <string, int> IDs;
	deque <event_s *> event_queue;
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
