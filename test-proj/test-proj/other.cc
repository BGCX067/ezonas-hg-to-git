#include "stdafx.h"

string get_scalar(const ynode & node)
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
void print_pair(YAML::Iterator & iter)
{
	cout
		<< "pair: "
		<< get_scalar(iter.first()) << ": "
		<< get_scalar(iter.second()) << "\n";
}
void print_scalar(const ynode & node)
{
	cout << get_scalar(node) << "\n";
}
void shownested_map(nested_map & categories)
{
	cout << categories.size() << " categories\n";
	for(auto iter = categories.begin(); iter != categories.end(); ++ iter)
	{
		cout << iter->second.size() << " items in this category\n";
		for(auto iter2 = iter->second.begin(); iter2 != iter->second.end(); ++ iter2)
		{
			cout
				<< "["<< iter->first << "]["
				<< iter2->first << "] = "
				<< iter2->second << "\n";
		}
	}
}
