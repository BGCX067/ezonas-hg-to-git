//#ifndef __APPLE__
#include "stdafx.h"
//#endif

enum event_state   { JUMPS, LANDS, MOVES, STOPS, USE_ITEM, ABILITY };
struct event_abil  { int target_id, abil_state_id; };
struct event_phys  { float pos[3], vel[3], orient[4]; };
struct event_item  { int item_id; };

struct Event
{
	event_state type;
	int emitter_id;
	union
	{
		event_abil ev_abil; //event_phys ev_phys;
		event_item ev_item;
	};
	Event(int, int);
	Event(int, int, int);
};

struct state_abil
{
	int ability_id, experience;
	float timeleft;
	state_abil(int a, int b, float c):
		ability_id(a), experience(b), timeleft(c)
	{}

};
struct state_cast
{
	float time_buffer; int abil_state_id;
	state_cast(float _time_buffer, int _abil_state_id):
		time_buffer(_time_buffer), abil_state_id(_abil_state_id) {}
};

//struct event_stop { float pos[6]; };
/*
 * 2 kinds of paradigms for networking:
 * atomic event
 * timed state/transition flow
 */
/*
struct character_states // remember most values don't go over 100
{
	std::vector<float>
		moving_speed_default,
		stealth_range, 		
		defense, 				
		attack_bonus, 		
		power, 				
		life,
		time_buffer;
	
	std::vector<int> mask, casting_ability_id;
	std::vector<string> name;
	std::vector<std::vector<int> > AbilityIDs;
/*	character_s(const character_s &);
	character_s(
				float _moving_speed_default = 15.f	,
				float _stealth_range	    = 20.f	,
				float _defense 			    = 1.f	,
				float _attack_bonus 	    = 0.f	,
				float _power			    = 100.f	,
				float _life				    = 20.f	,
				int _mask				    = 0		,
				string _name			    = "dou"	
				);
};
*/
