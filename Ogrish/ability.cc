#include "stdafx.h"

abil_stats :: abil_stats
	(int _dmg_tick, int _dmg_instant, int _dmg_splash, int _power_cost):
	dmg_tick		(_dmg_tick),
	dmg_instant		(_dmg_instant),
	dmg_splash		(_dmg_splash),
	power_cost		(_power_cost)
{}
abil_stats_base :: abil_stats_base
	(int _dmg_tick, int _dmg_instant, int _dmg_splash, int _power_cost):
	dmg_tick		(_dmg_tick),
	dmg_instant		(_dmg_instant),
	dmg_splash		(_dmg_splash),
	power_cost		(_power_cost)
{}
abil_data :: abil_data
	(int _ability_id, int _experience, float _timeleft):
	ability_id	(_ability_id),
	experience	(_experience),
	timeleft	(_timeleft)
{}
abil_base :: abil_base
	(int _ticks, int _mask, float _delay):
	ticks		(_ticks),
	mask		(_mask),
	delay		(_delay)
{}
abil_phys :: abil_phys	
	(float _range, float _splash_range, float _missile_speed):
	range(_range),
	splash_range	(_splash_range),
	missile_speed	(_missile_speed)
{}



void abil_phys :: diagnose()
{
	SGLT_LOG->stream() << "range splash_range missile_speed " ;
	SGLT_LOG->stream() << range 		;
	SGLT_LOG->stream() << splash_range	;
	SGLT_LOG->stream() << missile_speed	;
}
void abil_base :: diagnose()
{
	SGLT_LOG->stream() << "ticks mask " ;
	SGLT_LOG->stream() << ticks	;
	SGLT_LOG->stream() << mask	;
	SGLT_LOG->stream() << delay	;
}
void abil_data :: diagnose()
{
	SGLT_LOG->stream() << "ability_id experience timeleft delay ";
	SGLT_LOG->stream() << ability_id;
	SGLT_LOG->stream() << experience;
	SGLT_LOG->stream() << timeleft	;
}
void abil_stats_base :: diagnose()
{

	SGLT_LOG->stream() << "dmg_tick dmg_instant dmg_splash power_cost delay"	;
	SGLT_LOG->stream() << dmg_tick	;
	SGLT_LOG->stream() << dmg_instant;
	SGLT_LOG->stream() << dmg_splash;
	SGLT_LOG->stream() << power_cost;
}
void abil_stats :: diagnose()
{
	SGLT_LOG->stream() << "dmg_tick dmg_instant dmg_splash power_cost ";
	SGLT_LOG->stream() << dmg_tick		;
	SGLT_LOG->stream() << dmg_instant	;
	SGLT_LOG->stream() << dmg_splash	;
	SGLT_LOG->stream() << power_cost	;
}

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
