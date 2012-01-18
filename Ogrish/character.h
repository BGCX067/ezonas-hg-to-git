#include "stdafx.h"
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
#define SNARED	  (1 << 9)

struct character_s // remember most values don't go over 100
{
	float moving_speed_default, // might be a int, since it's multiplier
	stealth_range, 			    // the smaller the stealthier
	defense, 				    // percentage of damage reduction, negative
	attack_bonus, 			    // % of bonus attacks, apply in the final pass
	power, 					    // might, mana, energy, etc
	life,					    
	dmg_tick;				    // dmg taken per tick
	int mask, target_id;

	
	std::vector<abil_data> Abildatas;
	std::vector<abil_stats> AbilStats;
	character_s(const character_s &);
#ifndef DEFAULT_VALUES
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
#endif
};
