//#ifndef __APPLE__
#include "stdafx.h"
#define AB_BASE(ch, ab) AbilBases [AbilDatas[ch][ab].ability_id]
//#endif
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

			if(AB_BASE(chd_emit, chd_ab).mask & HAS_COOLDOWN)// fires instantly, cooldown after
			{
				Characters[chd_trg].life -= AbilStats[chd_emit][chd_ab].dmg_instant;       //
				// WARNING dottable spells are not spammable						       // 
				if(AB_BASE(chd_emit, chd_ab).mask & HAS_DOT)						       //
					Characters[chd_trg].dmg_tick += AbilStats[chd_emit][chd_ab].dmg_tick;  // apply damage and dot ONCE
 
				AbilDatas[chd_emit][chd_ab].timeleft = 								       // 
					AbilDatas[chd_emit][chd_ab].delay;								       // init timer
			}
			else // loads up, fire after
			{ 
				AbilDatas[chd_emit][chd_ab].timeleft = 
					AbilDatas[chd_emit][chd_ab].delay;
				if(AB_BASE(chd_emit, chd_ab).mask & HAS_DOT)						       //
					Characters[chd_trg].dmg_tick += AbilStats[chd_emit][chd_ab].dmg_tick;  // apply damage and dot ONCE
			}
			break;
		case JUMPS: case LANDS: case MOVES: case STOPS: break;
		}
		Events.pop();
	}
}
// TODO: dfs skip check flag 
void game_machine :: process_states()
{
	FOR_VECT(AbilDatas, array<abil_data, 10>)
	{
		FOR(10)
		{
			if((*it)[i].timeleft > 0.f || (*it)[i])
				(*it)[i].timeleft -= (*timeSinceLastFrame);
			else if(Abilities[it2->ability_id].mask & HAS_COOLDOWN) // casting finished, firing now
				applyEffects(it->target_id, it2->ability_id);
			// else {} // fired, cd is over
			//if(it->timeleft > 0.f)
			//	it->timeleft -= (*timeSinceLastFrame);
			//else if(Abilities[it2->ability_id].mask & HAS_COOLDOWN) // casting finished, firing now
			//	applyEffects(it->target_id, it2->ability_id);
			//// else {} // fired, cd is over
		}
	}
}

//void game_machine :: spendPower(int emitter_id, int abil_state_id){}
int game_machine :: checkUsability(int emitter_id, int target_id, int ability_id){}
void game_machine :: applyEffects(int target_id, int ability_id)
{
// Characters[it->target_id].life -= Abilities[it2->ability_id].dmg_instant;
	Characters[target_id].life -= AbilStats[ability_id].dmg_instant;
	// WARNING dottable spells are not spammable
	if(Abilities[ability_id].mask & HAS_DOT)
		Characters[target_id].dmg_tick += Abilities[ability_id].dmg_tick;
}
	
int get_bit(int mask, int n) { return (mask & n); }
void set_bit(int * mask, int n)   { (*mask) |= n; }
void unset_bit(int * mask, int n) { (*mask) &= ~ n; }

// shifts right bottom times
// ANDs it with a top-times left-shifted FFF
int get_int_from_mask(int n, int top, int bottom)
{ return (n >> (bottom - 1)) & (0xFFFFFFFF >> (top - bottom + 1));}
