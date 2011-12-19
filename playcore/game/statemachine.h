// exclusive property of Jonas ORINOVSKI
// all right reserved


// states
#define MOVING  (1 << 0)
#define RUNNING (1 << 1)
#define FALLING (1 << 2)
#define STUNNED (1 << 3)
#define VISIBLE (1 << 4)
#define STEALTH (1 << 5)
#define KNOCKED (1 << 6)
#define DEAD	(1 << 7)
#define	BLINDED	(1 << 8)
#define	(1 << 9)
#define	(1 << 10)
#define	(1 << 11)
#define	(1 << 12)
#define	(1 << 13)
#define	(1 << 14)
#define	(1 << 15)
#define	(1 << 16)
#define	(1 << 17)
#define	(1 << 18)
#define	(1 << 19)
#define	(1 << 20)
// events
#define JUMPS (1 << 0)
#define LANDS (1 << 1)
#define MOVES (1 << 2)
#define STOPS (1 << 3)
#define USE_ITEM (1 << 4)
#define (1 << 5)
#define (1 << 6)
#define (1 << 7)
#define	(1 << 8)
#define	(1 << 9)
#define	(1 << 10)
#define	(1 << 11)
#define	(1 << 12)
#define	(1 << 13)
#define	(1 << 14)
#define	(1 << 15)
#define	(1 << 16)
#define	(1 << 17)
#define	(1 << 18)
#define	(1 << 19)
#define	(1 << 20)


class State_machine
{
	public:
	State_machine();
	~State_machine();
		
	bool pass(); // proceed
	void show_states();
	bool get_state(int mask)
	{ return state_mask & mask; }
	
	private:
	
};

struct ability_s
{
	bool allow_movement;
	bool target_in_front;
	bool requires_target;
	bool click_location_event;
	bool splash_damage;
	float cast_time; 	// 0 means instant
	float range;		// 0 means melee with hitboxes
	float missile_speed; // 0 mean instant
	int effect_moment; 	// start, end, channeled
};


struct character_states_s // remember most values don't go over 100
{
	float moving_speed_default; // might be a int, since it's multiplier
	float stealth_range; // the smaller the stealthier
	float defense; // percentage of damage reduction, negative
	float attack_bonus; // percentage of bonus attacks, apply in the final pass
	float power; // might, mana, energy
	float life;
	int state_mask;
};





