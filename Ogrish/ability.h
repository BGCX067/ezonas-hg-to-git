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


struct ability_s
{
	float delay, range, splash_range, missile_speed,
		  dmg_tick, dmg_instant, dmg_splash, power_cost;
	int ticks, effect_moment, mask;
	std::string name;

	ability_s
#ifndef DEFAULT_VALUES
	(
		float _delay		 = 1.f  ,
		float _range         = 100.f,
		float _splash_range  = 5.f  ,
		float _missile_speed = 100.f,

		float _dmg_tick      = 1.f  ,
		float _dmg_instant   = 15.f ,
		float _dmg_splash    = 3.f  ,
		float _power_cost	 = 1.f  ,

		int _ticks           = 1    ,
		int _effect_moment   = 5    ,

		int _mask            = 0 + (ALLOW_MOVEMENT | TARGET_IN_FRONT | REQUIRES_TARGET | SPLASH_DAMAGE),
		std::string _name    = string("FireBall")
	);	
#endif
	ability_s(const ability_s &);
};

struct abil_base
{ int ticks, mask; abil_base(int _ticks = 5, int _mask=ABIL_DEFAULT);};

struct abil_stats
{ 
	int delay, dmg_tick, dmg_instant, dmg_splash, power_cost;
	abil_stats(int d = 1000, int dt = 0, int di = 0, int ds = 0, in cost = 0);
	void make_data(abil_data * ab, abil_bonus * bonus);
};

struct abil_data
{
	int ability_id, experience; float timeleft;
	abil_data(int ab_id = 0, int xp = 0, float t = 1.f);
};

struct abil_phys
{
	float range, splash_range, missile_speed;
	abil_phys(float r = 30.f, float sr = 5.f, float sp = 100.f);
};

struct abil_bonus
{
// TODO
};

//abil_state(int a, int b, float c): ability_id(a), experience(b), timeleft(c) {}
