#include "stdafx.h"

ItemMgr :: ItemMgr()
{
	//Ogre::ConfigFile cf;
	//cf.CROSSLOAD("conf/conf-guns.cfg");
	//
	//for(std::map<std::string, item_e>::iterator it = ItemIDs.begin();
	//		it != ItemIDs.end(); ++ it)
	//{
//	//	auto truc = it->first;
	//	ItemsDescr[ItemIDs[it->first]] = cf.getSetting(it->first);
	//	//LOGMSG(truc + " ## " + ItemsDescr[ItemIDs[truc]]);
	//}
}
void ItemMgr::load_yaml(string s)
{
	ifstream ifstr(s);
	YAML::Parser parser(ifstr); // remember to pass it by reference
	if(! parser.GetNextDocument(doc)) exit(0xbadf00d);
	//const ynode * aa = doc.FindValue("trait");
	//unroll(doc, "XXXX");

	unroll(doc, "XXXX");
}
void ItemMgr::add_item(string s, string category)
{
	ItemNames.push_back(s);
}
void ItemMgr::make_masks()
{

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
	}
}

void ItemMgr::unroll(const YAML::Node & node, string category)
{
	switch(node.Type())
	{
		case YAML::NodeType::Map:
			for(auto i = node.begin(); i != node.end(); ++i)
			{
				switch(i.second().Type())
				{
				case YAML::NodeType::Map:
					category = get_scalar(i.first());
					n_trait = i.second().FindValue("_trait");
					if(n_trait != NULL)
						trait = get_scalar(* n_trait);
				case YAML::NodeType::Sequence:
					unroll(i.second(), category);
					break;
				case YAML::NodeType::Scalar:
				case YAML::NodeType::Null:
					//categories[category][get_scalar(i.first())] = 1;
					//items[get_scalar(i.first())] = 1;
					add_item(get_scalar(i.first()), category); // will use trait in the future, need to set traits for categories
					break;
				}
			}
			break;
		case YAML::NodeType::Scalar:
		case YAML::NodeType::Null: // only with sequences
			//assert(0&&"this case should be treated inside map case");
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
