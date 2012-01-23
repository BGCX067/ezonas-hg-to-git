#include "stdafx.h"

// ############# CHARACTER #############
character_s :: character_s (
#ifndef DEFAULT_VALUES
	float _moving_speed_default	,
	float _stealth_range		,
	float _defense 			   	,
	float _attack_bonus 		,
	float _power				,
	float _life				   	,
	int _mask				   	
):
	moving_speed_default (_moving_speed_default),
	stealth_range		 (_stealth_range	   ),
	defense 			 (_defense 			   ), 
	attack_bonus 		 (_attack_bonus 	   ),
	power				 (_power			   ),
	life				 (_life				   ), 
	mask				 (_mask				   )//, 
#endif
{}


// ############# COPY CONSTR #############
character_s :: character_s (const character_s & ch):
	moving_speed_default (ch.moving_speed_default  ),
	stealth_range		 (ch.stealth_range		   ),
	defense 			 (ch.defense 			   ),
	attack_bonus 		 (ch.attack_bonus 		   ),
	power				 (ch.power				   ),
	life				 (ch.life				   ),
	mask				 (ch.mask				   )
{}
