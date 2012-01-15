//#ifndef __APPLE__
#include "stdafx.h"
//#endif
// this state machine is about taking inputs and generating outputs,
// handling them in game and also send events on the network.
// networking is mainly handled by sending events to a peer.
Game_machine :: Game_machine()
{
	Abilities[1] = ability_s();

	// moving_speed_default, stealth_range, defense, attack_bonus, power, life, mask, name
	// cast_time, range, missile_speed, effect_moment, mask

	Characters[3] = character_s();
	Characters[21] = character_s(15.f, 20.f, 1.f, 0.f, 100.f, 20.f, 0, "dou");
	Characters[22] = character_s(20.f, 20.f, 2.f, 0.f, 100.f, 100.f, 0, "dan");
	Characters[23] = character_s(20.f, 20.f, 1.f, 0.f, 100.f, 100.f, 0, "doue");
	Characters[22].AbilityIDs.push_back(1);
}

void Game_machine :: diagnose_events()
{}
void Game_machine :: diagnose_characters()
{}
void Game_machine :: removeState(int id)
{
	Availables.push(id);		// queue is a list and States is a vector so queue is used
	States[id].abilityID = -1; 	// to reuse but we need something else when iterating the vector
}
void Game_machine :: addState(float f, int id)
{
	if(!Availables.empty())
	{
		States[Availables.front()].abilityID = id;
		States[Availables.front()].time_buffer = f;
		Availables.pop();
	}
	else
		States.push_back(cast_state(f, id));
}
void Game_machine :: checkAndApplyAbility(Event * ev)
{
	// Ability
	//		float cast_time, cooldown, range, splash_range, missile_speed,
	//			dmg_tick, dmg_instant, dmg_splash;
	//		int ticks, effect_moment, mask;
	// State_cast
	//		abilityHolderID, time_buffer
}
void Game_machine :: pass()
{
	// event queue
	// problem is, with network, I will need to control the rate at which I
	// process events. Normally I can just process one event per frame.

	// ######################################################
	// ############# EVENT AND STATE PROCESSING #############
	// ######################################################

	if (! Events.empty())
	{
		switch(Events.front().type)
		{
		case CAST_END:
			break;
		case USE_ITEM:
			break;
		case ABILITY:
	/*
	1. check for reach, cooldown, mana, character avail.
		distance/range, collision with obstacle
	2. spawn a state_cast if non instant
	NOTE: no concept of actions/reactions, if an ability checks, the reaction is automatic
	3. 
	*/
			break;
		case JUMPS: case LANDS: case MOVES: case STOPS: break;
		}
		Events.pop();
	}
	// process timed cast states

	for(std::vector<cast_state>::iterator it = States.begin();
		it != States.end(); ++ it)
		{
			if (it -> abilityID == -1) continue;
			if(it -> time_buffer < 0.0f)
			{
				Events.push(Event(
			}
			else
				it->time_buffer -= (*timeSinceLastFrame);
		}

}

int get_bit(int mask, int n) { return (mask & n); }
void set_bit(int * mask, int n)   { (*mask) |= n; }
void unset_bit(int * mask, int n) { (*mask) &= ~ n; }

// shifts right bottom times
// ANDs it with a top-times left-shifted FFF
int get_int_from_mask(int n, int top, int bottom)
{ return (n >> (bottom - 1)) & (0xFFFFFFFF >> (top - bottom + 1));}

#ifdef OBSOLETE
character_s Game_machine :: make_character(
	float moving_speed_default,
	float stealth_range,
	float defense,
	float attack_bonus,
	float power,
	float life,
	int mask,
	string name)
{
	character_s ret =
	{
		moving_speed_default,
		stealth_range,
		defense,
		attack_bonus,
		power,
		life,
		mask,
		name
	};

	return ret;
}
#endif


