#include "stdafx.h"

abil_stats :: abil_stats
	(ushort _dmg_tick, ushort _dmg_instant, ushort _dmg_splash, ushort _power_cost):
	dmg_tick		(_dmg_tick),
	dmg_instant		(_dmg_instant),
	dmg_splash		(_dmg_splash),
	power_cost		(_power_cost)
{}
abil_stats_base :: abil_stats_base
	(ushort _dmg_tick, ushort _dmg_instant, ushort _dmg_splash, ushort _power_cost):
	dmg_tick		(_dmg_tick),
	dmg_instant		(_dmg_instant),
	dmg_splash		(_dmg_splash),
	power_cost		(_power_cost)
{}
abil_bonus :: abil_bonus
	(ushort _dmg_tick, ushort _dmg_instant, ushort _dmg_splash, ushort _power_cost):
	dmg_tick		(_dmg_tick),
	dmg_instant		(_dmg_instant),
	dmg_splash		(_dmg_splash),
	power_cost		(_power_cost)
{}
abil_data :: abil_data
	(ushort _ability_id, ushort _experience):
	ability_id	(_ability_id),
	experience	(_experience)
{}
abil_base :: abil_base
	(ushort _ticks, ushort _mask, float _delay):
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
	SGLT_LOG->stream() <<
		TO_STR(range 		)+
		TO_STR(splash_range	)+
		TO_STR(missile_speed);
}
void abil_base :: diagnose()
{
	SGLT_LOG->stream() << "ticks mask " ;
	SGLT_LOG->stream() <<
		TO_STR(ticks)+
		TO_STR(mask)	+
		TO_STR(delay)	;
}
void abil_data :: diagnose()
{
	SGLT_LOG->stream() << "ability_id experience timeleft delay ";
	SGLT_LOG->stream() <<
		TO_STR(ability_id)+
		TO_STR(experience);
}
void abil_stats_base :: diagnose()
{

	SGLT_LOG->stream() << "dmg_tick dmg_instant dmg_splash power_cost delay"	;
	SGLT_LOG->stream() <<
		TO_STR(dmg_tick)	+
		TO_STR(dmg_instant)+
		TO_STR(dmg_splash)+
		TO_STR(power_cost);
}
void abil_stats :: diagnose()
{
	SGLT_LOG->stream() << "dmg_tick dmg_instant dmg_splash power_cost ";
	SGLT_LOG->stream() <<
		TO_STR(dmg_tick)+		
		TO_STR(dmg_instant	)+
		TO_STR(dmg_splash	)+
		TO_STR(power_cost	);
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
