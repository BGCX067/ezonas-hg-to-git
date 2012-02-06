#include "stdafx.h"

// ability masks
#define ALLOW_MOVEMENT       (1 << 0)
#define TARGET_IN_FRONT      (1 << 1)
#define REQUIRES_TARGET      (1 << 2)
#define CLICK_LOCATION_EVENT (1 << 3)
#define SPLASH_DAMAGE        (1 << 4)
#define HAS_COOLDOWN         (1 << 5)
#define HAS_DOT				 (1 << 6)

#define ABIL_DEFAULT (ALLOW_MOVEMENT | TARGET_IN_FRONT | REQUIRES_TARGET | SPLASH_DAMAGE)

struct abil_base;	// this are constant data for the abilities
struct abil_phys;	// only hold float values -- those should stay constant
struct abil_bonus;	// this hold values used to calculate abil_stat values
struct abil_data;	// hold by players
struct abil_stats;	// those are hold by players, it stores actual ability constant statistic after applying bonuses

struct abil_base			 // BASE -- unique
{ unsigned short ticks, mask; float delay; abil_base(unsigned short _ticks = 5, unsigned short _mask = ABIL_DEFAULT, float _delay = 1.0f); void diagnose();};
struct abil_phys 
{							 // PHYS -- unique
	float range, splash_range, missile_speed;
	abil_phys(float _range = 30.f, float _splash_range = 5.f, float _missile_speed = 100.f); void diagnose();
};
struct abil_bonus 
{							 // BONUS -- charact-wise
	// TODO
	unsigned short dmg_tick, dmg_instant, dmg_splash, power_cost;
	abil_bonus(unsigned short _dmg_tick = 0, unsigned short _dmg_instant = 0, unsigned short _dmg_splash = 0, unsigned short _power_cost = 0);
	void diagnose();
};
struct abil_data 
{							 // DATA -- charact-wise
	unsigned short ability_id, experience; float timeleft;
	abil_data(unsigned short _ability_id = 0, unsigned short _experience = 0, float _timeleft = 1.f); void diagnose();
};
struct abil_stats_base;
struct abil_stats 
{ 							 // STATS -- charact-wize
	unsigned short dmg_tick, dmg_instant, dmg_splash, power_cost;
	abil_stats(unsigned short _dmg_tick = 0, unsigned short _dmg_instant = 0, unsigned short _dmg_splash = 0, unsigned short _power_cost = 0); void diagnose();
	
};
struct abil_stats_base
{ 							 // STATS -- charact-wize
	unsigned short dmg_tick, dmg_instant, dmg_splash, power_cost;
	abil_stats_base	(unsigned short _dmg_tick = 0, unsigned short _dmg_instant = 0, unsigned short _dmg_splash = 0, unsigned short _power_cost = 0); void diagnose();
};