#include "stdafx.h"

// item type mask
/*
item
	tool
	weapon	guns
			melee

consum
	weapons
	ammun

*/
//


enum item_e
{
	// weapons
	// melee
	ripclaw	    ,
	blade	    ,
	kitemchen   ,
			    
	// guns	    
	klobr	    ,
	lark	    ,
	
	mp49r		,
	k97			,
	fl71		,
	
	psg9		,
	
	railrif		,
	flakspr		,
	fpgun		,
	
	ezgun		,
	snaket		,
	
	// consum
	gr_light	,
	gr_tron		,
	gr_wave		,
	gr_wind		,

	gr_mqrk		,
	gr_smtex	,
	gr_fire		,
	rocket		,
	missl		,
	
	serum		,
	pill		,


	// ammun
	stdb		,
	hvel		,
	srg			,
	fl			,
	stackcap	,
	combcap		,
	flak		,

	// tool
	breath		,
	lightbender	,
	spyborg		,
	eyz			,

	lighter		,
	lamp		,
	zpda		,
	pen			,
	smokes		,
	scopesigh	,
	binoculars
};



// #define WEAPON (1 <<  0)
// #define  (1 <<  1)
// #define  (1 <<  2)
// #define  (1 <<  3)
// #define  (1 <<  4)
// #define  (1 <<  5)
// #define  (1 <<  6)
// #define  (1 <<  7)
// #define  (1 <<  8)
// #define  (1 <<  9)
// #define  (1 << 10)
// #define  (1 << 11)
// #define  (1 << 12)
// #define  (1 << 13)
// #define  (1 << 14)
// #define  (1 << 15)
// #define  (1 << 16)
// #define  (1 << 17)
// #define  (1 << 18)
// #define  (1 << 19)
// #define  (1 << 20)
