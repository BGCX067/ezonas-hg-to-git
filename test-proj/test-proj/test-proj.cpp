#include "stdafx.h"

//int spaces = -1;
//void indent() { for(int i = 0; i < spaces * 4; ++i) cout << " "; }
//nested_map categories;
//map<string, int> items;
//string current_category("none"), previous_category, key_category, key_item, value;
//const ynode * n;
//string dada;
/*
void add_item(string s)
{
	
}
void unroll(const YAML::Node & node, string category)
{
	spaces++;
	switch(node.Type())
	{
		case YAML::NodeType::Map:
			for(auto i = node.begin(); i != node.end(); ++i)
			{
				indent();
				switch(i.second().Type())
				{
				case YAML::NodeType::Map:
					n = i.second().FindValue("_trait");
					if(n != NULL) dada = get_scalar(*n);
					category = get_scalar(i.first());
				case YAML::NodeType::Sequence:
					print_scalar(i.first());
					unroll(i.second(), category);
					break;
				case YAML::NodeType::Scalar:
				case YAML::NodeType::Null:
					print_pair(i);
					categories[category][get_scalar(i.first())] = 1;
					items[get_scalar(i.first())] = 1;
					break;
				}
			}
			break;
		case YAML::NodeType::Scalar:
		case YAML::NodeType::Null: // only with sequences
			indent();
			print_scalar(node);
			break;
		case YAML::NodeType::Sequence:
			for(auto it = node.begin(); it != node.end(); ++ it)
			{ 
				indent();
				cout << "sequence item: ";
				unroll(*it, category);
			}
			break;
		default: cout << "error: undefined type";	break;
	}
	spaces--;
}
*/
int _tmain(int argc, _TCHAR* argv[])
{
//	ifstream ifstr("testdada.yml");
//	//ifstream ifstr("sample2.yml");
//	YAML::Parser parser(ifstr); // remember to pass it by reference
//	YAML::Node doc;
//	if(! parser.GetNextDocument(doc)) exit(0xbadf00d);
//
//	map<string, short> dd;
//
//	unroll(doc, "XXXX");
//	//for(auto i = items.begin(); i != items.end(); ++i)
//		//cout << i->first << "\n";
//	shownested_map(categories);
//	//print_scalar(n->begin().second());
//	cout << dada << "\n";
	try
	{
		ItemMgr mgr;
		mgr.load_yaml("items3.yml");
	}
	catch(YAML::ParserException& e)
	{
		std::cout << e.what() << "\n";
	}


	system("PAUSE");
	return 0;
}