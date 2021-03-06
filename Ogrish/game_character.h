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
	float
		moving_speed_default,		// might be a int, since it's multiplier
		stealth_range; 			    // the smaller the stealthier
	unsigned short
		mask,
		target_id,
		attack_bonus, 			    // % of bonus attacks, apply in the final pass
		power, 					    // might, mana, energy, etc
		life,					    
		defense, 				    // percentage of damage reduction, negative
		dmg_tick;				    // dmg taken per tick
	
	std::vector <abil_data>  AbilDatas;
	std::vector <abil_stats> AbilStats;
	std::vector <abil_bonus> AbilBonuses;
	character_s(const character_s &);
#ifndef DEFAULT_VALUES
	character_s(
		float _moving_speed_default  = 15.f	,
		float _stealth_range	     = 20.f	,
		unsigned short _defense 	 = 1	,
		unsigned short _attack_bonus = 0	,
		unsigned short _power		 = 100	,
		unsigned short _life		 = 20	,
		unsigned short _mask		 = 0		
		//,string _name			    = "dou"	
		);
#endif
};
