#ifdef FUCKSHIT
#include "stdafx.h"
//#endif
#define WEAPON        (1 << 24)
#define MELEE         (1 << 25)
#define GUN           (1 << 26)
#define CONSUM        (1 << 27)
#define TOOL          (1 << 28)
#define AMMUN         (1 << 29)
#define WEARABLE      (1 << 30)
#define EXPIRES       (1 << 31)


enum item_melee
{
	melee_ripclaw   = 1 ,  
	melee_blade	    = 2 ,  
	melee_kitchen   = 3 ,  
};
enum item_gun
{
	gun_klobr	    = 1 ,  
	gun_lark	    = 2 ,  

	gun_mp49r		= 3 ,  
	gun_k97			= 4 ,  
	gun_fl71		= 5 ,  

	gun_psg9		= 6 ,  

	gun_enrjgun		= 7 ,  
	gun_flakspr		= 8 ,  
	gun_fpgun		= 9 ,  

	gun_ezgun		= 10,  
	gun_snaket		= 11,  
};
enum item_gun2
{
	gun_glock19  	=  1,
	gun_M9       	=  2,
	gun_M3benelli	=  3,
	gun_M416     	=  4,
	gun_M24      	=  5,

	gun_MK3      	=  6,
	gun_P99      	=  7,
	gun_deagle   	=  8,
	gun_MP5      	=  9,
	gun_AK       	= 10,
	gun_famas    	= 11,

	gun_sigpro   	= 12,
	gun_M1911    	= 13,
	gun_tar21    	= 14,
	gun_XM8      	= 15,
	gun_PSG1     	= 16,
};
enum item_consum
{
	consum_gr_light	= 1 ,  
	consum_gr_tron	= 2 ,  
	consum_gr_wave	= 3 ,  
	consum_gr_wind	= 4 ,  

	consum_gr_mqrk	= 5 ,  
	consum_gr_smtex	= 6 ,  
	consum_gr_fire	= 7 ,  
	consum_rocket	= 8 ,  
	consum_missl	= 9 ,  

	consum_serum	= 10,  
	consum_pill		= 11,  
};
enum item_ammun
{
	ammun_stdb		= 1 ,  
	ammun_hvel		= 2 ,  
	ammun_srg		= 3 ,  
	ammun_fl		= 4 ,  
	ammun_stackcap	= 5 ,  
	ammun_combcap	= 6 ,  
	ammun_flak		= 7 ,  
};
enum item_tool
{
	tool_breath		 = 1 ,  
	tool_lightbender = 2 ,  
	tool_spyborg	 = 3 ,  
	tool_eyz		 = 4 ,  

	tool_lighter	 = 5 ,  
	tool_lamp		 = 6 ,  
	tool_zpda		 = 7 ,  
	tool_pen		 = 8 ,  
	tool_smokes		 = 9 ,  
	tool_binoculars	 = 10,  
};

enum item_e
{
#ifndef ITEMS
	// melee_
	ripclaw	    = melee_ripclaw	+ WEAPON + MELEE,
	blade	    = melee_blade	+ WEAPON + MELEE,
	kitchen     = melee_kitchen + WEAPON + MELEE,
								
	// guns_
	klobr	    = gun_klobr		+ WEAPON + GUN,
	lark	    = gun_lark	    + WEAPON + GUN,

	mp49r		= gun_mp49r		+ WEAPON + GUN,
	k97			= gun_k97		+ WEAPON + GUN,
	fl71		= gun_fl71		+ WEAPON + GUN,

	psg9		= gun_psg9		+ WEAPON + GUN,

	enrjgun		= gun_enrjgun	+ WEAPON + GUN,
	flakspr		= gun_flakspr	+ WEAPON + GUN,
	fpgun		= gun_fpgun		+ WEAPON + GUN,

	ezgun		= gun_ezgun		+ WEAPON + GUN,
	snaket		= gun_snaket	+ WEAPON + GUN,
									
	// consum_
	gr_light	= consum_gr_light	+ WEAPON + CONSUM,
	gr_tron		= consum_gr_tron	+ WEAPON + CONSUM,
	gr_wave		= consum_gr_wave	+ WEAPON + CONSUM,
	gr_wind		= consum_gr_wind	+ WEAPON + CONSUM,

	gr_mqrk		= consum_gr_mqrk	+ WEAPON + CONSUM,
	gr_smtex	= consum_gr_smtex	+ WEAPON + CONSUM,
	gr_fire		= consum_gr_fire	+ WEAPON + CONSUM,
	rocket		= consum_rocket		+ WEAPON + CONSUM,
	missl		= consum_missl		+ WEAPON + CONSUM,

	serum		= consum_serum		+ WEAPON + CONSUM + MELEE,	
	pill		= consum_pill		+ WEAPON + CONSUM + MELEE,	
											
	// ammun_
	stdb		= ammun_stdb		+ AMMUN,
	hvel		= ammun_hvel		+ AMMUN,
	srg			= ammun_srg			+ AMMUN,
	fl			= ammun_fl			+ AMMUN,
	stackcap	= ammun_stackcap	+ AMMUN,
	combcap		= ammun_combcap		+ AMMUN,
	flak		= ammun_flak		+ AMMUN,
									
	// tool_
	breath		= tool_breath		+ TOOL,
	lightbender	= tool_lightbender	+ TOOL,
	spyborg		= tool_spyborg		+ TOOL,
	eyz			= tool_eyz			+ TOOL,

	lighter		= tool_lighter		+ TOOL,
	lamp		= tool_lamp			+ TOOL,
	zpda		= tool_zpda			+ TOOL,
	pen			= tool_pen			+ TOOL,
	smokes		= tool_smokes		+ TOOL,
	binoculars	= tool_binoculars	+ TOOL
#endif

};
class ItemMgr
{
public:
	ItemMgr();
	std::vector<unsigned char[32]> Quantities;
	std::vector<unsigned int> hasItemMask;
	std::map <item_e, std::string> ItemsDescr;
	std::map <std::string, item_e> ItemIDs;
private:
};
/*enum item_e2
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
	gr_light	 = 1  + WEAPON + CONSUM,				//
	gr_tron		 = 2  + WEAPON + CONSUM,				//
	gr_wave		 = 3  + WEAPON + CONSUM,				//
	gr_wind		 = 4  + WEAPON + CONSUM,				//
														//
	gr_mqrk		 = 5  + WEAPON + CONSUM,				//
	gr_smtex	 = 6  + WEAPON + CONSUM,				//
	gr_fire		 = 7  + WEAPON + CONSUM,				//
	rocket		 = 8  + WEAPON + CONSUM,				//
	missl		 = 9  + WEAPON + CONSUM,				//
														//
	serum		 = 10 + WEAPON + CONSUM + MELEE,		//
	pill		 = 11 + WEAPON + CONSUM + MELEE,		//
														//
	// ammun	 = 										//
	stdb		 = 1  + AMMUN,							//
	hvel		 = 2  + AMMUN,							//
	srg			 = 3  + AMMUN,							//
	fl			 = 4  + AMMUN,							//
	stackcap	 = 5  + AMMUN,							//
	combcap		 = 6  + AMMUN,							//
	flak		 = 7  + AMMUN,							//

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
};*/
#endif