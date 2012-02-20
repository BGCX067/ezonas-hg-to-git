#include "stdafx.h"

ItemMgr :: ItemMgr()
{
#ifndef STRING_IDS
	ItemIDs["ripclaw"	  ] = ripclaw	 ;
	ItemIDs["blade"		  ] = blade		 ;
	ItemIDs["kitchen"	  ] = kitchen	 ;
	ItemIDs["klobr"		  ] = klobr		 ;
	ItemIDs["lark"		  ] = lark		 ;

	ItemIDs["mp49r"		  ] = mp49r		 ;
	ItemIDs["k97"		  ] = k97		 ;
	ItemIDs["fl71"		  ] = fl71		 ;

	ItemIDs["psg9"		  ] = psg9		 ;

	ItemIDs["enrjgun"	  ] = enrjgun	 ;
	ItemIDs["flakspr"	  ] = flakspr	 ;
	ItemIDs["fpgun"		  ] = fpgun		 ;

	ItemIDs["ezgun"		  ] = ezgun		 ;
	ItemIDs["snaket"	  ] = snaket	 ;

	ItemIDs["gr_light"	  ] = gr_light	 ;
	ItemIDs["gr_tron"	  ] = gr_tron	 ;
	ItemIDs["gr_wave"	  ] = gr_wave	 ;
	ItemIDs["gr_wind"	  ] = gr_wind	 ;

	ItemIDs["gr_mqrk"	  ] = gr_mqrk	 ;
	ItemIDs["gr_smtex"	  ] = gr_smtex	 ;
	ItemIDs["gr_fire"	  ] = gr_fire	 ;
	ItemIDs["rocket"	  ] = rocket	 ;
	ItemIDs["missl"		  ] = missl		 ;

	ItemIDs["serum"		  ] = serum		 ;
	ItemIDs["pill"		  ] = pill		 ;

	ItemIDs["stdb"		  ] = stdb		 ;
	ItemIDs["hvel"		  ] = hvel		 ;
	ItemIDs["srg"		  ] = srg		 ;
	ItemIDs["fl"		  ] = fl		 ;
	ItemIDs["stackcap"	  ] = stackcap	 ;
	ItemIDs["combcap"	  ] = combcap	 ;
	ItemIDs["flak"		  ] = flak		 ;

	ItemIDs["breath"	  ] = breath	 ;
	ItemIDs["lightbender" ] = lightbender;
	ItemIDs["spyborg"	  ] = spyborg	 ;
	ItemIDs["eyz"		  ] = eyz		 ;

	ItemIDs["lighter"	  ] = lighter	 ;
	ItemIDs["lamp"		  ] = lamp		 ;
	ItemIDs["zpda"		  ] = zpda		 ;
	ItemIDs["pen"		  ] = pen		 ;
	ItemIDs["smokes"	  ] = smokes	 ;
	ItemIDs["binoculars"  ] = binoculars ;
#endif	
	
	Ogre::ConfigFile cf;
	cf.CROSSLOAD("conf/conf-guns.cfg");
	
	for(std::map<std::string, item_e>::iterator it = ItemIDs.begin();
			it != ItemIDs.end(); ++ it)
	{
//		auto truc = it->first;
		ItemsDescr[ItemIDs[it->first]] = cf.getSetting(it->first);
		//PRINTLOG(truc + " ## " + ItemsDescr[ItemIDs[truc]]);
	}
}