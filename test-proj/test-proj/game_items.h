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
	std::vector <std::string> ItemNames;	
	std::map <std::string, ushort> ItemIDs;
	std::map <std::string, ushort> mask_names;
	std::vector<ushort> masks;

	void load_yaml(string filename);
	size_t get_item_index();
	void make_masks();
	void unroll(const YAML::Node & node, string category);
	void ItemMgr::add_item(string s, string category);
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