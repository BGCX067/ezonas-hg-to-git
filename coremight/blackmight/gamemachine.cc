#include "gamemachine.h"
// this state machine is about taking inputs and generating outputs,
// handling them in game and also send events on the network.
// networking is mainly handled by sending events to a peer.

ability_s :: ability_s
(
	float _cast_time,
	float _range,
	float _splash_range,
	float _missile_speed,
	float _dmg_tick,
	float _dmg_instant,
	float _dmg_splash,
	int _ticks,
	int _effect_moment,
	int _mask,
	string _name
):

cast_time     (_cast_time    ),
range         (_range        ),
splash_range  (_splash_range ),
missile_speed (_missile_speed),
dmg_tick      (_dmg_tick     ),
dmg_instant   (_dmg_instant  ),
dmg_splash    (_dmg_splash   ),

ticks		  (_ticks),
effect_moment (_effect_moment),
mask		  (_mask),

name		  (_name)
	{}

Game_machine :: Game_machine()
{
//	Abilities[1]
	        ability_s dfs = ability_s
			(
					1.f, 100.f, 5.f, 100.f,
					1.f, 15.f, 3.f,
					1, 5,
					0 + (ALLOW_MOVEMENT | TARGET_IN_FRONT | REQUIRES_TARGET | SPLASH_DAMAGE),
					string("FireBall")
			);


	//Abilities[1] = ability_s(string("Flame"), 1.0f, 100.f, 100.f, 1, 0 + (ALLOW_MOVEMENT | TARGET_IN_FRONT | REQUIRES_TARGET | SPLASH_DAMAGE));

	// moving_speed_default, stealth_range, defense, attack_bonus, power, life, mask, name
	// cast_time, range, missile_speed, effect_moment, mask

	Characters[21] = make_character(15.f, 20.f, 1.f, 0.f, 100.f, 20.f, 0, "dou");
	Characters[22] = make_character(20.f, 20.f, 2.f, 0.f, 100.f, 100.f, 0, "dan");
	Characters[23] = make_character(20.f, 20.f, 1.f, 0.f, 100.f, 100.f, 0, "doue");

}

void Game_machine :: diagnose_events()
{}
void Game_machine :: diagnose_characters()
{}
bool Game_machine :: pass()
{
	if (not Events.empty())
	{
		switch(Events.back().type)
		{
		case JUMPS:

			break;

		case LANDS:
			break;

		case MOVES:
			break;

		case STOPS:
			break;

		case USE_ITEM:
			break;

		case ABILITY:
			break;
		}
		return true;
	}



	return false;
}
void Game_machine :: fire_ability(event_abil ev)
{

}

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


#define GET_BIT(n) (mask & n)
bool get_bit(uint mask, int n) { return mask & n; }
void set_bit(uint * mask, int n)   { (*mask) |= n; }
void unset_bit(uint * mask, int n) { (*mask) &= ~ n; }
uint get_uint_from_mask(uint n, uint top, uint bottom)
{
	// shifts right bottom times
	// ANDs it with a top-times left-shifted FFF
	return (n >> (bottom - 1)) & (0xFFFFFFFF >> (top - bottom + 1));
}

