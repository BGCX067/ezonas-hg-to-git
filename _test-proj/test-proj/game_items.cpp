#include "stdafx.h"

ItemMgr :: ItemMgr()
{
}
void ItemMgr::load_yaml(string s)
{
	ifstream ifstr(s);
	YAML::Parser parser(ifstr); // remember to pass it by reference
	if(! parser.GetNextDocument(doc)) exit(0xbadf00d);
	//const ynode * aa = doc.FindValue("trait");
	//unroll(doc, "XXXX");

	unroll(doc, "XXXX");
	diagnose();
}
void ItemMgr::diagnose()
{
	cout << "*------- MASKS --------*\n";
	for(auto a = mask_names.begin(); a != mask_names.end(); ++a)
		cout << a->first << ": " << a->second << "\n";
	cout << "*------- ITEM ID --------*\n";
	for(auto a = ItemIDs.begin(); a != ItemIDs.end(); ++a)
		cout << a->first << ": " << a->second << "\n";
	cout << "*------- ITEM NAMES & MASKS --------*\n";
	size_t u = ItemNames.size(), v = masks.size();
	assert(u == v);
	for(int i = 0; i < u; ++i)
		cout << ItemNames[i] << "\t" << masks[i] << "\n";
}

void ItemMgr::make_bimap()
{
	for(auto i = ItemNames.begin(); i != ItemNames.end(); ++i)
		ItemIDs[*i] = std::distance(ItemNames.begin(), i);
}
void ItemMgr::make_masks()
{
	vector<std::string> strings;
	const ynode * trait_map = doc.FindValue("trait");
	if(trait_map == NULL) assert (0 && "no mapping named trait");
	if (trait_map->Type() == YAML::NodeType::Map)
		for(auto i = trait_map->begin(); i != trait_map->end(); ++i)
			strings.push_back(get_scalar(i.first()));
	if(strings.size() > 16)
		assert(0&&"too many mask, change to uint, ushort is max 16 flags");
	if(strings.size() < 1)
		assert(0&&"empty");
	for(int i = 0; i < 16 && i < strings.size(); ++ i)
		mask_names[strings[i]] = 1<<i;


}
std::string ItemMgr::get_scalar(const ynode & node)
{
	string s;
	switch(node.Type())
	{
	case YAML::NodeType::Scalar:
		node >> s;
		return s;
	case YAML::NodeType::Null:
		return string("void");
	default: 
		assert(0 && "error, neither null or scalar !");
		return string("get_scalar_error");
	}
}
void ItemMgr::set_mask(string item, string mask, bool set)
{
	if(set)
		masks[ItemIDs[item]] |= mask_names[mask];
	else
		masks[ItemIDs[item]] &= ~ (0 | mask_names[mask]); // unsets
}

void ItemMgr::unroll(const YAML::Node & node, string category)
{
	string mask_to_apply = "0";
	switch(node.Type())
	{
		case YAML::NodeType::Map:
			for(auto i = node.begin(); i != node.end(); ++i)
			{
				switch(i.second().Type())
				{
				case YAML::NodeType::Map:
					category = get_scalar(i.first());
					if(mask_names.find(category) != mask_names.end())
						mask_to_apply = category; // save for later
					//n_trait = i.second().FindValue("_trait");
					//if(n_trait != NULL)
					//	trait = get_scalar(* n_trait);
				case YAML::NodeType::Sequence:
					unroll(i.second(), category);
					break;
				case YAML::NodeType::Scalar:
				case YAML::NodeType::Null:
					if(mask_to_apply != "0")
						masks.push_back(mask_names[mask_to_apply]);
					else
						masks.push_back(0);
					ItemNames.push_back(get_scalar(i.first()));
					assert(ItemNames.size() == masks.size());
					//categories[category][get_scalar(i.first())] = 1;
					//items[get_scalar(i.first())] = 1;
					break;
				}
			}
			break;
		case YAML::NodeType::Scalar:
		case YAML::NodeType::Null: // only with sequences
			//assert(0&&"this case should be treated inside map case");
			cout << "sequence item: ";
			print_scalar(node);
			break;
		case YAML::NodeType::Sequence:
			for(auto it = node.begin(); it != node.end(); ++ it)
				unroll(*it, category);
			break;
		default: assert(0&&"error: undefined type");
			break;
	}
}
