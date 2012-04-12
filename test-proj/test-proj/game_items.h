#include "stdafx.h"

typedef unsigned short ushort ;

typedef std::vector<void *> data_t;	// data, directly depends of trait
typedef ushort item_trait;
//typedef YAML::Node ynode;

struct ItemMgr
{
	ItemMgr();

	ynode doc;
	const ynode * n_trait;
	string trait;
	//std::vector<unsigned char[32]> Quantities;
	//std::vector<unsigned int> hasItemMask;
	// "bimap"
	std::vector <std::string>		ItemNames;	
	std::map <std::string, ushort>	ItemIDs;
	std::map <std::string, ushort>	mask_names;
	std::vector<ushort>				masks;
	std::vector<vector<void*>>		ItemData;

	void load_yaml(string filename);
	size_t get_item_index();
	void make_masks();
	void make_bimap();
	void diagnose();

	void unroll(const YAML::Node & node, string category);
	void unroll_map(const YAML::Node & node);
	void set_mask(string item, string mask, bool set = true);

	std::string get_scalar(const ynode & node);
};

//list<ushort> items;

struct cargo
{
	ushort item_id ;
};

struct wrapped_article
{

};