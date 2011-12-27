#include "common.h"

struct Life
{
	float life, metab;
};

struct Mind
{
	float mind, consc;
};

struct Experience
{
	float level, progr;
};

struct Ability
{
	
};


// While Ability describes the code for performing actions, Skill describes how
// its parameters are handled, such as ranges, experience, tick, etc.

struct Skill: public Ability
{
	Experience exp;
};

struct Character
{
	Life life;
	Mind mind;
	Experience exp;
	map <Skill *> skills;
	map <Item *> items;
};

