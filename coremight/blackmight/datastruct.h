struct ability_s
{
	ability_s(float, float, float, float, float, float, float, int, int, int, string);
	float cast_time, 	// 0 means instant
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
};

struct event_abil {	int target_id, emitter_id, spell_id; };
struct event_pos { float pos[6]; };
//struct event_stop { float pos[6]; };
enum event_state
{
	JUMPS,
	LANDS,
	MOVES,
	STOPS,
	USE_ITEM,
	ABILITY
};

struct Event
{
	event_state type;
	union
	{
		event_abil ev_abil;
		event_pos ev_pos;
	};
};


// states
#define MOVING  (1 << 0)
#define RUNNING (1 << 1)
#define FALLING (1 << 2)
#define STUNNED (1 << 3)
#define INVISIBLE (1 << 4)
#define STEALTH (1 << 5)
#define KNOCKED (1 << 6)
#define DEAD	(1 << 7)
#define	BLINDED	(1 << 8)

// ability masks
#define ALLOW_MOVEMENT       (1 << 0)
#define TARGET_IN_FRONT      (1 << 1)
#define REQUIRES_TARGET      (1 << 2)
#define CLICK_LOCATION_EVENT (1 << 3)
#define SPLASH_DAMAGE        (1 << 4)

// events

/*
 * 2 kinds of paradigms for networking:
 * atomic event
 * timed state/transition flow

*/
// type mask
#define PLAYER (1 << 0) // player or MOB
// #define (1 << 1)
// #define (1 << 2)


// #define (1 << 5)
// #define (1 << 6)
// #define (1 << 7)
// #define	(1 << 8)
// #define	(1 << 9)
// #define	(1 << 10)
// #define	(1 << 11)
// #define	(1 << 12)
// #define	(1 << 13)
// #define	(1 << 14)
// #define	(1 << 15)
// #define	(1 << 16)
// #define	(1 << 17)
// #define	(1 << 18)
// #define	(1 << 19)
// #define	(1 << 20)

