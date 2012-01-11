#include "stdafx.h"

/*
item
	tool
	weapon	guns
			melee
consum
	weapons
	ammun
*/

int make_mask(int i, int j)
{
	return i + j;
}
enum item_e
{
	// weapons
	
	// melee
	ripclaw	     = 101,
	blade	     = 102,
	kitemchen    = 103,

	// guns	     = 
	klobr	     = 201,
	lark	     = 202,

	mp49r		 = 203,
	k97			 = 204,
	fl71		 = 205,

	psg9		 = 206,

	railrif		 = 207,
	flakspr		 = 208,
	fpgun		 = 209,

	ezgun		 = 210,
	snaket		 = 211,

	// consum	 = 
	gr_light	 = 301,
	gr_tron		 = 302,
	gr_wave		 = 303,
	gr_wind		 = 304,

	gr_mqrk		 = 305,
	gr_smtex	 = 306,
	gr_fire		 = 307,
	rocket		 = 308,
	missl		 = 309,

	serum		 = 310,
	pill		 = 311,

	// ammun	 = 
	stdb		 = 401,
	hvel		 = 402,
	srg			 = 403,
	fl			 = 404,
	stackcap	 = 405,
	combcap		 = 406,
	flak		 = 407,

	// tool		 = 
	breath		 = 501,
	lightbender	 = 502,
	spyborg		 = 503,
	eyz			 = 504,

	lighter		 = 505,
	lamp		 = 506,
	zpda		 = 507,
	pen			 = 508,
	smokes		 = 509,
	scopesigh	 = 510,
	binoculars	 = 511
};
/*
#define WEAPON        (1 <<  0)
#define MELEE         (1 <<  1)
#define GUN           (1 <<  2)
#define CONSUM        (1 <<  3)
#define TOOL          (1 <<  4)
#define AMMUN         (1 <<  5)
#define WEARABLE      (1 <<  6)
#define EXPIRES       (1 <<  7)
//#define               (1 <<  8)
//#define               (1 <<  9)
//#define               (1 << 10)
//#define               (1 << 11)
//#define               (1 << 12)
//#define               (1 << 13)
//#define               (1 << 14)
//#define               (1 << 15)
//#define               (1 << 16)
//#define               (1 << 17)
//#define               (1 << 18)
//#define               (1 << 19)
//#define               (1 << 20)
//#define               (1 << 21)
//#define               (1 << 22)
//#define               (1 << 23)
#define WEAPON        (1 << 24)
#define MELEE         (1 << 25)
#define GUN           (1 << 26)
#define CONSUM        (1 << 27)
#define TOOL          (1 << 28)
#define AMMUN         (1 << 29)
#define WEARABLE      (1 << 30)
#define EXPIRES       (1 << 31)
*/
#define WEAPON        (1 << 24)
#define MELEE         (1 << 25)
#define GUN           (1 << 26)
#define CONSUM        (1 << 27)
#define TOOL          (1 << 28)
#define AMMUN         (1 << 29)
#define WEARABLE      (1 << 30)
#define EXPIRES       (1 << 31)

enum item_e2
{
	// weapons
	
	// melee
	ripclaw	     = 1  + WEAPON + MELEE,
	blade	     = 2  + WEAPON + MELEE,
	kitemchen    = 3  + WEAPON + MELEE,

	// guns	     = 	  + WEAPON
	klobr	     = 1  + WEAPON + GUN,
	lark	     = 2  + WEAPON + GUN,

	mp49r		 = 3  + WEAPON + GUN,
	k97			 = 4  + WEAPON + GUN,
	fl71		 = 5  + WEAPON + GUN,

	psg9		 = 6  + WEAPON + GUN,

	railrif		 = 7  + WEAPON + GUN,
	flakspr		 = 8  + WEAPON + GUN,
	fpgun		 = 9  + WEAPON + GUN,

	ezgun		 = 10 + WEAPON + GUN,
	snaket		 = 11 + WEAPON + GUN,

	// consum	 = 		WEAPON + GUN
	gr_light	 = 1  + WEAPON + CONSUM,
	gr_tron		 = 2  + WEAPON + CONSUM,
	gr_wave		 = 3  + WEAPON + CONSUM,
	gr_wind		 = 4  + WEAPON + CONSUM,

	gr_mqrk		 = 5  + WEAPON + CONSUM,
	gr_smtex	 = 6  + WEAPON + CONSUM,
	gr_fire		 = 7  + WEAPON + CONSUM,
	rocket		 = 8  + WEAPON + CONSUM,
	missl		 = 9  + WEAPON + CONSUM,

	serum		 = 10 + WEAPON + CONSUM + MELEE,
	pill		 = 11 + WEAPON + CONSUM + MELEE,

	// ammun	 = 
	stdb		 = 1  + AMMUN,
	hvel		 = 2  + AMMUN,
	srg			 = 3  + AMMUN,
	fl			 = 4  + AMMUN,
	stackcap	 = 5  + AMMUN,
	combcap		 = 6  + AMMUN,
	flak		 = 7  + AMMUN,

	// tool		 = 
	breath		 = 1  + TOOL,
	lightbender	 = 2  + TOOL,
	spyborg		 = 3  + TOOL,
	eyz			 = 4  + TOOL,

	lighter		 = 5  + TOOL,
	lamp		 = 6  + TOOL,
	zpda		 = 7  + TOOL,
	pen			 = 8  + TOOL,
	smokes		 = 9  + TOOL,
	scopesigh	 = 10 + TOOL,
	binoculars	 = 11 + TOOL
};


class ItemsMgr
{
	std::map<item_e, std::string> ItemsDescr;
	ItemsMgr()
	{
	
	}
};


