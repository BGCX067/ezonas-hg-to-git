#include "stdafx.h"

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

}

void Game_machine :: diagnose_events()
{}
void Game_machine :: diagnose_characters()
{}
void Game_machine :: removeState(int id)
{
	Availables.push(id);
}
void Game_machine :: addState(float f, int id)
{
	if(!Availables.empty())
	{
		States[Availables.front()].abilityHolderID = id;
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
}

bool Game_machine :: pass()
{
	if (! Events.empty())
	{
		switch(Events.front().type)
		{
		case USE_ITEM:
			break;
		case ABILITY:
			break;
		//case JUMPS: //case LANDS:  //case MOVES:  //case STOPS:
		//	break;	  //	break;	 //	break;		//	break;
		
		}
		Events.pop();
		return true;
	}
	return false;
}

int get_bit(int mask, int n) { return (mask & n); }
void set_bit(int * mask, int n)   { (*mask) |= n; }
void unset_bit(int * mask, int n) { (*mask) &= ~ n; }

// shifts right bottom times
// ANDs it with a top-times left-shifted FFF
int get_int_from_mask(int n, int top, int bottom)
{ return (n >> (bottom - 1)) & (0xFFFFFFFF >> (top - bottom + 1));}

#ifdef CACAPOOPOO
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


