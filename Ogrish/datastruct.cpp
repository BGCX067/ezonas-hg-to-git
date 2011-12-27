#include "stdafx.h"

ability_s :: ability_s(const ability_s & ab):
cast_time     (ab.cast_time    ),
range         (ab.range        ),
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


ability_s :: ability_s
(
	float _cast_time    ,
	float _range        ,
	float _splash_range ,
	float _missile_speed,

	float _dmg_tick     ,
	float _dmg_instant  ,
	float _dmg_splash   ,

	int _ticks          ,
	int _effect_moment  ,

	int _mask           ,
	string _name         
):

cast_time     (_cast_time    ),
range         (_range        ),
splash_range  (_splash_range ),
missile_speed (_missile_speed),
dmg_tick      (_dmg_tick     ),
dmg_instant   (_dmg_instant  ),
dmg_splash    (_dmg_splash   ),

ticks		  (_ticks),
effect_moment (_effect_moment),
mask		  (_mask),

name		  (_name)
	{}
