typedef uint64 uint64_t;
typedef int64 int64_t;

struct loc_t
{
	float longitude;
	float latitude;
};

enum POI_e
{
	city,
	train_station,
	bus_station,
	super_market,
	mall,
	plaza,
	municipality,
	
	work_place,
	home,
	shop,
	restaurant,
	service
};



struct POI_t
{
	uint64 id;
	loc_t location;
	POI_e type;
	char name[32];
};

struct pin_t
{
	loc_t location;
	uint64 id;
	char name[32];
};

