#include "stdafx.h"

#define WEAPON        (1 << 24)
#define MELEE         (1 << 25)
#define GUN           (1 << 26)
#define CONSUM        (1 << 27)
#define TOOL          (1 << 28)
#define AMMUN         (1 << 29)
#define WEARABLE      (1 << 30)
#define EXPIRES       (1 << 31)

enum item_e
{
#ifndef ITEMS
	// melee
	ripclaw	     = 1  + WEAPON + MELEE,
	blade	     = 2  + WEAPON + MELEE,
	kitchen      = 3  + WEAPON + MELEE,

	// guns	     = 	  + WEAPON
	klobr	     = 1  + WEAPON + GUN,
	lark	     = 2  + WEAPON + GUN,

	mp49r		 = 3  + WEAPON + GUN,
	k97			 = 4  + WEAPON + GUN,
	fl71		 = 5  + WEAPON + GUN,

	psg9		 = 6  + WEAPON + GUN,

	enrjgun		 = 7  + WEAPON + GUN,
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
	binoculars	 = 10 + TOOL
#endif
};
class ItemMgr
{
private:
	std::map <item_e, std::string> ItemsDescr;
	std::map <std::string, item_e> ItemIDs;
public:
	ItemMgr();
};