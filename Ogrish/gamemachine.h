//#ifndef __APPLE__
#include "stdafx.h"
//#endif

#define COMPOSITION

#include <map>
#include <string>
#include <queue>
#include <array>
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
	
	void loadAbilStatBases();
	void loadAbilBonuses();
	void loadCharacters();

	int make_abil_mask(string flags);
	void make_stat(int abst_base, int experience, abil_stats & abst, abil_bonus & bonus);

	void go();

	int checkUsability(int emitter_id, int target_id, int ability_id);
	void applyEffects(int target_id, int ability_id);
	void spendPower(int emitter_id, int abil_state_id);
private:
	// data oriented
	float * timeSinceLastFrame;
	int
		chd_ab,
		chd_emit,
		chd_trg;
	std::vector <Ogre::Entity *> Entities;

	std::vector <std::string>	   CharNames;		
	std::vector <character_s>	   Characters;
	queue <Event>				   Events;

	std::vector <std::string>	   AbilNames;		

#ifndef COMPOSITION
	std::vector <abil_stats> AbilStats;
	std::vector <abil_data> AbilDatas;
#endif
	std::vector <abil_base>		   AbilBases;		// BASE -- unique
	std::vector <abil_phys>		   AbilPhysics;		// PHYS -- unique
	std::vector <abil_stats_base>  AbilStatBases;
	
	ItemMgr item_mgr;
};
/*
inputs (controls + network) into events queue
pass unstacks and checks
generates output accordingly
outputs to ogre
*/
