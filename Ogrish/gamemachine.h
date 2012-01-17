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
	
	void removeState(int id);
	void addState(float f, int id);
	void go();
private:
	// data oriented
	float * timeSinceLastFrame;
	int
		cached_abil,
		cached_emitter,
		cached_target;
	std::vector <Ogre::Entity *>	Entities;

	std::vector <state_abil>		States;
	std::vector <character_s>		Characters;
	std::vector <ability_s>			Abilities;
	queue <Event>					Events;
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
