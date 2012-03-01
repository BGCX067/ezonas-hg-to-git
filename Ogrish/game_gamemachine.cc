#include "stdafx.h"


//#define AB_BASE(ch, ab) AbilBases [AbilDatas[ch][ab].ability_id]
#define AB_BASE(ch, ab) AbilBases [Characters[ch].AbilDatas[ab].ability_id]

// called at startup
void game_machine :: loadAbilStatBases()
{
	// getting spell name list
	Ogre::ConfigFile cf;
	cf. CROSSLOAD("conf/abils.cfg");
	Ogre::StringVector strs = StringUtil::split(cf.getSetting("spells"));

/*	boost::split(strs,
				 std::string(cf.getSetting("spells")),
				 boost::is_any_of("\t "));*/
	for(StringVector::iterator it = strs.begin(); it != strs.end(); ++it)
	{
		istringstream iss(cf.getSetting(*it));
		if(iss)
		{
			float delay, range, splr, speed;
			int ticks, d_t, d_i, d_s, p_cost;
			string mask;
			// unwrapping as usual, works better than split: split cannot deal with multi-spaces eg "  ".
			iss >> mask >> delay >> ticks >> d_t >> d_i >> d_s >> range >> splr >> speed >> p_cost;

			if (delay == 0.f) delay = 0.5f; // "global cd"
			AbilStatBases .push_back(abil_stats_base(d_t, d_i, d_s, p_cost));
			AbilPhysics	  .push_back(abil_phys(range, splr, speed));
			AbilBases	  .push_back(abil_base(ticks, make_abil_mask(mask), delay));
			AbilNames	  .push_back(*it);
		}
	}
}
void game_machine :: loadCharacters()
{
	// some chars
	Characters.push_back(character_s());
	Characters.push_back(character_s());
	Characters.push_back(character_s());
	// their names
	CharNames.push_back("dou");
	CharNames.push_back("dan");
	CharNames.push_back("nouf");
	// giving them some abilities with some xp, and then spawning some stat data holder
	Characters[0].AbilDatas.push_back(abil_data(3, 12345));
	Characters[1].AbilDatas.push_back(abil_data(2, 12345));
	Characters[2].AbilDatas.push_back(abil_data(5, 12345));

	Characters[0].AbilStats.push_back(abil_stats());
	Characters[1].AbilStats.push_back(abil_stats());
	Characters[2].AbilStats.push_back(abil_stats());
		
	// now applying ability bonuses
	for(std::vector<character_s>::iterator it = Characters.begin(); it != Characters.end(); ++it)
	{
		size_t sz = it->AbilStats.size();
		// I needed the actual index, and was lazy enough to use std::distance
		FOR(sz) //it->AbilStats[i]
		make_stat(  it->AbilDatas[i].ability_id,
					it->AbilDatas[i].experience,
					it->AbilStats[i], 
					it->AbilBonuses[i]);
	}
}
void game_machine :: loadAbilBonuses()
{
	Ogre::ConfigFile cf;
	cf. CROSSLOAD("conf/abilbonus.cfg");
}
void game_machine :: make_stat			(int abst_base, int experience, abil_stats & abst, abil_bonus & bonus)
{
	int level = experience / 100;
	abst.dmg_instant = AbilStatBases[abst_base].dmg_instant	+ (level * bonus.dmg_instant);
	abst.dmg_splash  = AbilStatBases[abst_base].dmg_splash	+ (level * bonus.dmg_splash );
	abst.dmg_tick    = AbilStatBases[abst_base].dmg_tick	+ (level * bonus.dmg_tick   );
	abst.power_cost  = AbilStatBases[abst_base].power_cost	+ (level * bonus.power_cost );
}
int  game_machine :: make_abil_mask		(string flags)
{
	size_t n = flags.size();
	int ret = 0;
	for(size_t i = 0; i < n; ++i)
		if(flags[i] == '1')
			ret += (1 << i);
	return ret;
}

// called in game loop
/**/ game_machine :: game_machine():
timeSinceLastFrame(appli -> timeSinceLastFrame)
{
// this state machine is about taking inputs and generating outputs,
// handling them in game and also send events on the network.
// networking is mainly handled by sending events to a peer.
	loadAbilStatBases();
	SGLT_LOG -> stream() << AbilNames[3];
	AbilStatBases [3].diagnose();
	AbilPhysics	  [3].diagnose();
	AbilBases	  [3].diagnose();
	// moving_speed_default, stealth_range, defense, attack_bonus, power, life, mask, name
	// cast_time, range, missile_speed, effect_moment, mask
}
void game_machine :: update()
{
	switch(3)
	{
		case JUMPS: case LANDS: case MOVES: case STOPS: break;
	}
}
void game_machine :: process_ability	(ushort _abil, ushort _emit, ushort _target)
{
		// base:  ticks, mask;
		// phys:  range, splash_range, missile_speed;
		// data:  ability_id, experience; timeleft;
		// stats: delay, dmg_tick, dmg_instant, dmg_splash, power_cost;
		/* TODO: check for reach, cooldown, mana, character avail.
			distance/range, collision with obstacle */
		if(AB_BASE(_emit, _abil).mask & HAS_COOLDOWN) // fires instantly, cooldown after
			apply_effect(_emit, _target, _abil);

		if(availables.empty())
			Timers.push_back(timer_state(_emit, _abil, _target, AB_BASE(_emit,_abil).delay));
		else
		{
			Timers[availables.back()] = timer_state(_emit, _abil, _target, AB_BASE(_emit,_abil).delay);
			availables.pop();
		}
}
void game_machine :: apply_effect		(ushort emit, ushort target, ushort abil)
{
	Characters[target].life -= Characters[emit].AbilStats[abil].dmg_instant;
	// WARNING dottable spells are not spammable						        
	if(AB_BASE(emit, abil).mask & HAS_DOT) // apply damage and dot ONCE					       
		Characters[target].dmg_tick += Characters[emit].AbilStats[abil].dmg_tick;  

}
void game_machine :: process_states()
{
	for(auto it = Timers.begin(); it != Timers.end(); ++ it)
	{
		if(it -> delay > 0.f)
			it -> delay -= timeSinceLastFrame;
		else if(AB_BASE(it->emit, it->abil).mask & HAS_COOLDOWN) // casting finished, firing now
		{
			apply_effect(it->emit, it->target, it->abil);
			availables.push(std::distance(Timers.begin(), it));
		}
		else // fired, cd is over
			availables.push(std::distance(Timers.begin(), it));
	}
}
int  game_machine :: checkUsability		(int emitter_id, int target_id, int ability_id)
{
	return 343;
}

// shifts right bottom times
// ANDs it with a top-times left-shifted FFF
int get_int_from_mask	(int n, int top, int bottom)
{ return (n >> (bottom - 1)) & (0xFFFFFFFF >> (top - bottom + 1));}
void unset_bit			(int & mask, int n)		{ mask &= ~ n; }

