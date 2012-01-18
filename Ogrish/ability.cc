#include "stdafx.h"


void abil_stats :: make_data(abil_data * ab, abil_bonus * bonus)
{
// TODO
}
abil_stats :: abil_stats(int d = 1000, int dt = 0, int di = 0, int ds = 0, int cost = 0):
delay(d), dmg_tick(dt), dmg_instant(di), dmg_splash(ds), power_cost(cost) {}

abil_data :: abil_data(int ab_id = 0, int xp = 0, float t = 1.f):
ability_id(ab_id), experience(xp), timeleft(t) {}

abil_base :: abil_base(int _ticks = 5, int _mask = ABIL_DEFAULT):
ticks(_ticks), mask(_mask) {}

abil_phys :: abil_phys(float r = 30.f, float sr = 5.f, float sp = 100.f):
range(r), splash_range(sr), missile_speed(sp) {}