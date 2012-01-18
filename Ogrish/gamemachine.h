//#ifndef __APPLE__
#include "stdafx.h"
//#endif
#include <map>
#include <string>
#include <queue>
using namespace std;
#define pr(s) printf("%s\n", s)
#define prx(s) printf("0x%X\n", s)
typedef unsigned int uint;

class game_machine
{
public:
	game_machine();
		
	void pass();
	void process_states();
	void process_queue();
	
	void go();
	int checkUsability(int emitter_id, int target_id, int ability_id);
	void applyEffects(int target_id, int ability_id);
	void spendPower(int emitter_id, int abil_state_id);
private:
	// data oriented
	float * timeSinceLastFrame;
	int
		cached_abil,
		cached_emitter,
		cached_target;
	std::vector <Ogre::Entity *>	Entities;

	std::vector <character_s>		Characters;
	queue <Event>					Events;

	std::vector <abil_base>			AbilBases;
	std::vector <abil_data>			AbilData;
	std::vector <abil_stats>		AbilStats;
	std::vector <abil_phys>			AbilPhysics;
	std::vector <abil_bonus>		AbilBonuses;

	ItemMgr item_mgr;

};
/*
inputs (controls + network) into events queue
pass unstacks and checks
generates output accordingly
outputs to ogre
*/
//	std::map <int, character_s>	Characters;
//	std::map <string, int>		characters_id;

//	std::map <int, ability_s>	Abilities;
//	std::map <string, int>		abilities_id;

//	std::vector<cast_state> States; // object pool
//	std::queue<int> Availables;		// which ones are available
