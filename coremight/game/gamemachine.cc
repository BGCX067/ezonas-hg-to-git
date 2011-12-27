#include "gamemachine.h"

// this state machine is about taking inputs and generating outputs,
// handling them in game and also send events on the network.
// networking is mainly handled by sending events to a peer.

Game_machine :: Game_machine()
{
	ab_sample.mask = 0 + (ALLOW_MOVEMENT
                          | TARGET_IN_FRONT     
                          | REQUIRES_TARGET     
                          | SPLASH_DAMAGE);

	ab_sample.cast_time = 1.f;
	ab_sample.range = 100.f;
	ab_sample.missile_speed = 100.f;

	ab_sample.effect_moment = 1;
	
	Characters[21] = make_character();
	Characters[22] = make_character();
	Characters[23] = make_character();
	Characters[21].name = "dou";
	Characters[22].name = "dan";
	Characters[23].name = "doue";

}

void Game_machine :: diagnose_events()
{
	
}

void Game_machine :: diagnose_characters()
{
	
}

bool Game_machine :: pass()
{
	if (EventQueue
	for(deque<event_s>::iterator iter; iter != )
}

void Game_machine :: fire_ability(int emitter, int target)
{
	
}


uint get_uint_from_mask(uint n, uint top, uint bottom)
{
	// shifts right bottom times
	n >>= bottom - 1;

	// ANDs it with a top-times left-shifted FFF
	uint mask = 0xFFFFFFFF >> (top - bottom + 1);
	
	return n & mask;
}

character_s Game_machine :: make_character()
{
	character_s ret;
	ret.moving_speed_default = 20.f;
	ret.stealth_range = 20.f;
	ret.defense = 1.f;
	ret.attack_bonus = 0.f;
	ret.power = 100.f;
	ret.life = 100.f;
	
	ret.name = "unnamed";
	ret.mask = 0;
	return ret;
}

#define GET_BIT(n) (mask & n)
bool get_bit(uint mask, int n) { return mask & n; }
bool set_bit(uint * mask, int n)   { (*mask) |= n; }
bool unset_bit(uint * mask, int n) { (*mask) &= ~ n; }

