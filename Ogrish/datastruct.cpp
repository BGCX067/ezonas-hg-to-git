//#ifndef __APPLE__
#include "stdafx.h"
//#endif
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
// ############# CHARACTER #############
character_s :: character_s (
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
// ############# ABILITY EVENT #############
Event::Event(int _emitter_id, int _target_id, int _abil_state_id): // ability event constructor
type(ABILITY)//,
{ emitter_id = _emitter_id; ev_abil.target_id = _target_id; ev_abil.abil_state_id = _abil_state_id; }
// ############# ITEM EVENT #############
Event::Event(int _emitter_id, int _item_id): // ability event constructor
type(USE_ITEM)//,
{ emitter_id = _emitter_id; ev_item.item_id = _item_id; }

// ############# COPY CONSTR #############
character_s :: character_s (const character_s & ch):
	moving_speed_default (ch.moving_speed_default  ),
	stealth_range		 (ch.stealth_range		   ),
	defense 			 (ch.defense 			   ),
	attack_bonus 		 (ch.attack_bonus 		   ),
	power				 (ch.power				   ),
	life				 (ch.life				   ),
	mask				 (ch.mask				   ),
	name			     (ch.name			       )
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
