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

#define f(name) std::string(#name ##": "+TO_STR(name))


void abil_phys :: diagnose()
{
	SGLT_LOG->stream() <<
		f(range)		+" | "+
		f(splash_range)	+" | "+
		f(missile_speed);
}
void abil_base :: diagnose()
{
	SGLT_LOG->stream() <<
		f(ticks)	+" | "+
		f(mask)		+" | "+
		f(delay);
}
void abil_data :: diagnose()
{
	SGLT_LOG->stream() <<
		f(ability_id)	+" | "+
		f(experience);
}
void abil_stats_base :: diagnose()
{

	SGLT_LOG->stream() <<
		f(dmg_tick)		+" | "+
		f(dmg_instant)	+" | "+
		f(dmg_splash)	+" | "+
		f(power_cost);
}
void abil_stats :: diagnose()
{
	SGLT_LOG->stream() <<
		f(dmg_tick)			+" | "+		
		f(dmg_instant	)	+" | "+
		f(dmg_splash	)	+" | "+
		f(power_cost	);
}
