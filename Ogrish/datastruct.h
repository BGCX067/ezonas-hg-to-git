#include "stdafx.h"
enum event_state { JUMPS, LANDS, MOVES, STOPS, USE_ITEM, ABILITY };
struct event_abil { int target_id, spell_id; };
struct event_pos  { float pos[6]; };
struct event_item { int item_id; };

struct Event
{
	event_state type;
	int emitter_id;
	union
	{
		event_abil ev_abil;
		event_pos ev_pos;
		event_item ev_item;
	};
};
struct Event_network
{
	event_state type;
	union
	{
		event_abil ev_abil;
		event_pos ev_pos;
		event_item ev_item;
	};
};


// state masks
#define MOVING    (1 << 0)
#define RUNNING   (1 << 1)
#define FALLING   (1 << 2)
#define STUNNED   (1 << 3)
#define INVISIBLE (1 << 4)
#define STEALTH   (1 << 5)
#define KNOCKED   (1 << 6)
#define DEAD	  (1 << 7)
#define	BLINDED	  (1 << 8)

// ability masks
#define ALLOW_MOVEMENT       (1 << 0)
#define TARGET_IN_FRONT      (1 << 1)
#define REQUIRES_TARGET      (1 << 2)
#define CLICK_LOCATION_EVENT (1 << 3)
#define SPLASH_DAMAGE        (1 << 4)

#define ABIL_DEFAULT (ALLOW_MOVEMENT | TARGET_IN_FRONT | REQUIRES_TARGET | SPLASH_DAMAGE)

struct ability_s
{
	//ability_s(float, float, float, float, float, float, float, int, int, int, string);
	ability_s
		(
#ifndef DEFAULT_VALUES
		float _cast_time     = 1.f  ,
		float _cooldown      = 1.f,
		float _range         = 100.f,
		float _splash_range  = 5.f  ,
		float _missile_speed = 100.f,

		float _dmg_tick      = 1.f  ,
		float _dmg_instant   = 15.f ,
		float _dmg_splash    = 3.f  ,

		int _ticks           = 1    ,
		int _effect_moment   = 5    ,

		int _mask            = 0 + (ALLOW_MOVEMENT | TARGET_IN_FRONT | REQUIRES_TARGET | SPLASH_DAMAGE),
		std::string _name    = string("FireBall")
#endif
	);	
	ability_s(const ability_s &);
	float cast_time, 	// 0 means instant
		  cooldown,	     
		  range,		// 0 means melee with hitboxes
		  splash_range, // 0 won't mean it doesn't splash
	      missile_speed,// 0 mean instant
		  dmg_tick,
		  dmg_instant,
		  dmg_splash;
	int ticks,
		effect_moment,
		mask; // start, end, channeled

	string name;
};
struct character_s // remember most values don't go over 100
{
	float moving_speed_default, // might be a int, since it's multiplier
	      stealth_range, 		// the smaller the stealthier
	      defense, 				// percentage of damage reduction, negative
	      attack_bonus, 		// % of bonus attacks, apply in the final pass
	      power, 				// might, mana, energy, etc
	      life;
	int mask;
	string name;
	character_s(const character_s &);
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
struct cast_state
{
	cast_state(float _time_buffer):
		time_buffer(_time_buffer) {}
	float time_buffer;
	int ability_id;
};

//struct event_stop { float pos[6]; };
/*
 * 2 kinds of paradigms for networking:
 * atomic event
 * timed state/transition flow
 */
// type mask
#define PLAYER (1 << 0) // player or MOB


