//#ifndef __APPLE__
#include "stdafx.h"
//#endif
//#define AB_BASE(ch, ab) AbilBases [AbilDatas[ch][ab].ability_id]
#define AB_BASE(ch, ab) AbilBases [Characters[ch].AbilDatas[ab].ability_id]
/*
for(std::vector<XXXX>::iterator it = XXX.begin(); it != XXX.end(); ++it)
*/
void game_machine :: loadAbilStatBases()
{
	Ogre::ConfigFile cf;
	cf. CROSSLOAD("conf/abils.txt");
}

void game_machine :: loadAbilBonuses()
{
	Ogre::ConfigFile cf;
	cf. CROSSLOAD("conf/abilbonus.txt");
}

// this state machine is about taking inputs and generating outputs,
// handling them in game and also send events on the network.
// networking is mainly handled by sending events to a peer.
game_machine :: game_machine()//:
//AbilBase(),
//AbilData(std::vector <std::vector <abil_data>> (abil_data()))
{
	//FOR_VECT(Abilities, ability_s) // those loops grants all character with all abilities
	//{
	//	Characters.push_back(character_s());
	//	AbilData.push_back(
	//
	//}

	//	FOR_VECT2(Characters, character_s)
	//	{
	//		it2->Abilities.push_back(
	//			abil_state(std::distance(Abilities.begin(), it),100,it->delay));
	//	}
	
	// moving_speed_default, stealth_range, defense, attack_bonus, power, life, mask, name
	// cast_time, range, missile_speed, effect_moment, mask
}
void game_machine :: process_queue()
{
	// base:  ticks, mask;
	// phys:  range, splash_range, missile_speed;
	// data:  ability_id, experience; timeleft;
	// stats: delay, dmg_tick, dmg_instant, dmg_splash, power_cost;

	if (! Events.empty()) // here comes inputs, network and controls
	{					  // we just transfer events into states
		switch(Events.front().type)
		{
		case USE_ITEM:
			break;
		case ABILITY:
			/* TODO: check for reach, cooldown, mana, character avail.
			   distance/range, collision with obstacle */
			chd_trg  = Events.front().ev_abil.target_id;
			chd_ab   = Events.front().ev_abil.abil_state_id;
			chd_emit = Events.front().emitter_id;

			if(AB_BASE(chd_emit, chd_ab).mask & HAS_COOLDOWN) // fires instantly, cooldown after
			{
				Characters[chd_trg].life -= Characters[chd_emit].AbilStats[chd_ab].dmg_instant;
				// WARNING dottable spells are not spammable						        
				if(AB_BASE(chd_emit, chd_ab).mask & HAS_DOT) // apply damage and dot ONCE					       
					Characters[chd_trg].dmg_tick += Characters[chd_emit].AbilStats[chd_ab].dmg_tick;  
 
				Characters[chd_emit].AbilDatas[chd_ab].timeleft =  // 
					Characters[chd_emit].AbilDatas[chd_ab].delay;  // init timer
			}
			else // loads up, fire after
			{ 
				Characters[chd_emit].AbilDatas[chd_ab].timeleft = 
					Characters[chd_emit].AbilDatas[chd_ab].delay;
				//if(AB_BASE(chd_emit, chd_ab).mask & HAS_DOT)			
					//Characters[chd_trg].dmg_tick += Characters[chd_emit].AbilStats[chd_ab].dmg_tick;  // apply damage and dot ONCE
			}
			break;
		case JUMPS: case LANDS: case MOVES: case STOPS: break;
		}
		Events.pop();
	}
}
void game_machine :: process_states()
{
	for(std::vector<character_s>::iterator it = Characters.begin(); it != Characters.end(); ++it)
	{
		for(std::vector<abil_data>::iterator it2 = it->AbilDatas.begin(); it2 != it->AbilDatas.end(); ++it2)
		{
			if(it2->timeleft > 0.f)
				it2->timeleft -= (*timeSinceLastFrame);
			else if(AbilBases[it2->ability_id].mask & HAS_COOLDOWN) // casting finished, firing now
			{
				Characters[chd_trg].life -= Characters[chd_emit].AbilStats[chd_ab].dmg_instant;
				// WARNING dottable spells are not spammable						        
				if(AB_BASE(chd_emit, chd_ab).mask & HAS_DOT)						       
					Characters[chd_trg].dmg_tick += Characters[chd_emit].AbilStats[chd_ab].dmg_tick;  // apply damage and dot ONCE
			}
			//applyEffects(it->target_id, it2->ability_id);
			// else {} // fired, cd is over
		}
	}
}
int game_machine :: checkUsability(int emitter_id, int target_id, int ability_id){}
	
int get_bit(int mask, int n) { return (mask & n); }
void set_bit(int * mask, int n)   { (*mask) |= n; }
void unset_bit(int * mask, int n) { (*mask) &= ~ n; }

// shifts right bottom times
// ANDs it with a top-times left-shifted FFF
int get_int_from_mask(int n, int top, int bottom)
{ return (n >> (bottom - 1)) & (0xFFFFFFFF >> (top - bottom + 1));}
