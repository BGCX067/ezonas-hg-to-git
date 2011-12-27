// =========================== ability ============================
class Experience
{
protected:
	float _level;
	float _progression;
	void check_level();
};


class Ability
{
protected:
	float _cooldown;
	float _cast_time// equivalent to reload time.
public:
	virtual void fire(); // when something has to be "fired"
	virtual void switcher(); // -------------------- "switched", eg a silencer

};

class Skill: public Ability, public Experience
{};

class mechanic;

class mech_area;		// ex: explosion. damage does not depend on distance.
class mech_cone;		// ex: a wave of water, fireblow...
class mech_arrow;		// ex: a rocket, not moving instantly
class mech_missile;		// ex: missile which loses sight of target
class mech_smart;		// ex: missile with path finding
class mech_ray;			// ex: a bullet, which we consider travels instantly
class mech_lock;		// ex: a locked targetting attack which can't miss

class skill_firearm;
class skill_arm;
class skill_spell;
class skill_enhancement; // better