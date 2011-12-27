struct ability_s
{
	float cast_time, 	// 0 means instant
	      range,		// 0 means melee with hitboxes
	      missile_speed;// 0 mean instant
	int effect_moment, mask; 	// start, end, channeled
};
ß

struct character_s // remember most values don't go over 100
{
	float moving_speed_default, // might be a int, since it's multiplier
	      stealth_range, 		// the smaller the stealthier
	      defense, 				// percentage of damage reduction, negative
	      attack_bonus, 		// % of bonus attacks, apply in the final pass
	      power, 				// might, mana, energy, etc
	      life;
	int mask;
	string name;
};

struct event_cast {	int target_id, emitter_id, spell_id; };
struct event_pos { float pos[6]; };
struct event_stop { float pos[6]; };