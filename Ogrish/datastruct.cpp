//#ifndef __APPLE__
#include "stdafx.h"
//#endif
ability_s :: ability_s // copy constr
	(const ability_s & ab):
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
#ifndef DEFAULT_VALUES
	float _cast_time    ,
	float _cooldown,
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
cooldown      (_cooldown     ),
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
#endif
	{}
character_s :: character_s
	(
#ifndef DEFAULT_VALUES
		float _moving_speed_default	,
		float _stealth_range		,
		float _defense 			   	,
		float _attack_bonus 		,
		float _power				,
		float _life				   	,
		int _mask				   	,
		string _name			   	
	):
moving_speed_default (_moving_speed_default),
stealth_range		 (_stealth_range	   ),
defense 			 (_defense 			   ), 
attack_bonus 		 (_attack_bonus 	   ),
power				 (_power			   ),
life				 (_life				   ), 
mask				 (_mask				   ), 
name			     (_name			   	   )
#endif
{}
character_s :: character_s // copy constr
	(const character_s & ch): 
moving_speed_default (ch.moving_speed_default  ),
stealth_range		 (ch.stealth_range		   ),
defense 			 (ch.defense 			   ),
attack_bonus 		 (ch.attack_bonus 		   ),
power				 (ch.power				   ),
life				 (ch.life				   ),
mask				 (ch.mask				   ),
name			     (ch.name			       )

{}