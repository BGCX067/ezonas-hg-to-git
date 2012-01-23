//#ifndef __APPLE__
#include "stdafx.h"
//#endif
//#define AB_BASE(ch, ab) AbilBases [AbilDatas[ch][ab].ability_id]
#define AB_BASE(ch, ab) AbilBases [Characters[ch].AbilDatas[ab].ability_id]
/*
for(std::vector<XXXX>::iterator it = XXX.begin(); it != XXX.end(); ++it)
for(auto it = XXX.begin(); it != XXX.end(); ++it)
*/
void game_machine :: loadAbilStatBases()
{
	Ogre::ConfigFile cf;
	cf. CROSSLOAD("conf/abils.cfg");
	std::vector<std::string> strs;
	boost::split(strs, cf.getSetting("spells"), boost::is_any_of("\t "));
	for(auto it = strs.begin(); it != strs.end(); ++it)
	{
		istringstream iss(cf.getSetting(*it));
		if(iss)
		{
			float delay, range, splr, speed;
			int ticks, d_t, d_i, d_s, p_cost;
			string mask;
			iss >> mask >> delay >> ticks >> d_t >> d_i >> d_s >> range >> splr >> speed >> p_cost;

			if (delay == 0.f) delay = 0.5f;
			AbilStatBases	.push_back(abil_stats_base(d_t, d_i, d_s, p_cost));
			AbilPhysics		.push_back(abil_phys(range, splr, speed));
			AbilBases		.push_back(abil_base(ticks, make_mask(mask), delay));
			AbilNames		.push_back(*it);
		}
	}
}

int game_machine::make_mask(string flags)
{
	size_t n = flags.size();
	int ret = 0;
	for(size_t i = 0; i < n; ++i)
		if(flags[i] == '1')
			ret += (1 << i);
	return ret;
}

void game_machine :: loadAbilBonuses()
{
	Ogre::ConfigFile cf;
	cf. CROSSLOAD("conf/abilbonus.cfg");
}

// this state machine is about taking inputs and generating outputs,
// handling them in game and also send events on the network.
// networking is mainly handled by sending events to a peer.
game_machine :: game_machine()//:
//AbilBase(),
//AbilData(std::vector <std::vector <abil_data>> (abil_data()))
{
	loadAbilStatBases();
	SGLT_LOG->stream() << AbilNames[3];
	AbilStatBases [3].diagnose();
	AbilPhysics	  [3].diagnose();
	AbilBases	  [3].diagnose();
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
					AbilBases[Characters[chd_emit].AbilDatas[chd_ab].ability_id].delay;
			}
			else // loads up, fire after
			{ 
				Characters[chd_emit].AbilDatas[chd_ab].timeleft = 
					AbilBases[Characters[chd_emit].AbilDatas[chd_ab].ability_id].delay;
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
int game_machine :: checkUsability(int emitter_id, int target_id, int ability_id){return 343;}
	
int get_bit(int mask, int n) { return (mask & n); }
void set_bit(int * mask, int n)   { (*mask) |= n; }
void unset_bit(int * mask, int n) { (*mask) &= ~ n; }

// shifts right bottom times
// ANDs it with a top-times left-shifted FFF
int get_int_from_mask(int n, int top, int bottom)
{ return (n >> (bottom - 1)) & (0xFFFFFFFF >> (top - bottom + 1));}
