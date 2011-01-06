//#define BRUTAL

struct position
{
	float fx, fy;
};

struct sector
{
	int ix, iy;
};

struct game_position : public sector, public position
{
	game_position():
	fx(0.0), fy(0.0), ix(0), iy(0)
	{}
};

/*



*/