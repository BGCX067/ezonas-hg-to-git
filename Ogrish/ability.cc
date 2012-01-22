#include "stdafx.h"

void abil_stats :: make_data(abil_data * ab, abil_bonus * bonus)
{
// TODO
}
abil_stats :: abil_stats
	(int _dmg_tick = 0, int _dmg_instant = 0, int _dmg_splash = 0, int _power_cost = 0):
	dmg_tick		(_dmg_tick),
	dmg_instant		(_dmg_instant),
	dmg_splash		(_dmg_splash),
	power_cost		(_power_cost)
{}
abil_stats_base :: abil_stats_base
	(int _dmg_tick = 0, int _dmg_instant = 0, int _dmg_splash = 0, int _power_cost = 0):
	dmg_tick		(_dmg_tick),
	dmg_instant		(_dmg_instant),
	dmg_splash		(_dmg_splash),
	power_cost		(_power_cost)
{}
abil_data :: abil_data
	(int _ability_id = 0, int _experience = 0, float _timeleft = 1.f, float _delay = 1.f):
	ability_id	(_ability_id),
	experience	(_experience),
	timeleft	(_timeleft),
	delay		(_delay) // for now cooldown as casting timer will be fixed
{}
abil_base :: abil_base
	(int _ticks = 5, int _mask = ABIL_DEFAULT):
	ticks		(_ticks),
	mask		(_mask)
{}
abil_phys :: abil_phys	
	(float _range = 30.f, float _splash_range = 5.f, float _missile_speed = 100.f):
	range(_range),
	splash_range	(_splash_range),
	missile_speed	(_missile_speed)
{}

#ifdef OBSOLETE
// ############# ABILITY #############
ability_s :: ability_s (
#ifndef DEFAULT_VALUES
	//float _cast_time     = 1.f  ,
	//float _cooldown      = 1.f  ,
	float _delay		 ,
	float _range         ,
	float _splash_range  ,
	float _missile_speed ,
						 
	float _dmg_tick      ,
	float _dmg_instant   ,
	float _dmg_splash    ,
	float _power_cost    ,
						 
	int _ticks           ,
	int _effect_moment   ,
	int _mask            ,

	string _name         
):

	//cast_time     (_cast_time    ),
	//cooldown      (_cooldown     ),
	delay		  (_delay		 ),
	range         (_range        ),
	splash_range  (_splash_range ),
	missile_speed (_missile_speed),

	dmg_tick      (_dmg_tick     ),
	dmg_instant   (_dmg_instant  ),
	dmg_splash    (_dmg_splash   ),
	power_cost    (_power_cost   ),

	ticks		  (_ticks),
	effect_moment (_effect_moment),
	mask		  (_mask),

	name		  (_name)
#endif
{}

ability_s :: ability_s // copy constr
(const ability_s & ab):
//cast_time     (ab.cast_time    ),
//range         (ab.range        ),
delay		  (ab.delay		   ),
splash_range  (ab.splash_range ),
missile_speed (ab.missile_speed),
dmg_tick      (ab.dmg_tick     ),
dmg_instant   (ab.dmg_instant  ),
dmg_splash    (ab.dmg_splash   ),

ticks		  (ab.ticks),
effect_moment (ab.effect_moment),
mask		  (ab.mask),

name		  (ab.name)
{}


#endif
