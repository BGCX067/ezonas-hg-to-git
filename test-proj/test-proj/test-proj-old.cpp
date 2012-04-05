#include "stdafx.h"

typedef YAML::Node ynode;
int spaces = 0;
void indent() { for(int i = 0; i < spaces * 4; ++i) cout << " "; }
enum map_type { none, pairtype, mapping };
map <string, map <string, string>> categories;
string current_category("none"), previous_category, key, value;

void showtype(const YAML::Node & n)
{
	switch(n.Type())
	{
	case YAML::NodeType::Null:		cout << "NULL\n"	;
	case YAML::NodeType::Scalar:	cout << "Scalar\n"	;
	case YAML::NodeType::Sequence:	cout << "Sequence\n"	;
	case YAML::NodeType::Map:		cout << "Map\n"	;
	}
}
map_type get_map_type(const ynode & node)
{
	if(node.Type() == YAML::NodeType::Map)
	switch(node.begin().second().Type())
	{
	case YAML::NodeType::Map: // mapping
		return mapping;
	case YAML::NodeType::Null: 
	case YAML::NodeType::Scalar: // pair
		return pairtype;
	default:
		return none;
	}
	else showtype(node);
}
void print_scalar(const ynode & node)
{
	string s;
	node >> s;
	cout << s << "\n";
}
string get_string(const ynode & node)
{
	string s;
	switch(node.Type())
	{
	case YAML::NodeType::Scalar:
		node >> s;
		break;
	case YAML::NodeType::Null:
		s = "EMPTY";
		break;
	default: assert("error, neither null or scalar !");
	}
	return s;
}
void extract(const ynode & node)
{
	switch(get_map_type(node))
	{
	case pairtype:
		key = get_string(node.begin().first());
		value = get_string(node.begin().second());
		categories [current_category] [key] = value;
		break;
	case mapping:
		cout << node.size() << "\n";
		previous_category = current_category;
		for(auto it = node.begin(); it != node.end(); ++ it)
		{
		current_category = get_string(it.first());
			extract(it.second());
			current_category = previous_category;
		}
		break;
	case none:
	default:
		cout << "?\n";
		break;
	}
}
void print_pair(const ynode & node)
{
	cout
		<< get_string(node.begin().first()) << " "
		<< get_string(node.begin().second()) << "\n";
}
void unroll(const YAML::Node & node)
{
	switch(node.Type())
	{
		case YAML::NodeType::Map:
			for(auto it = node.begin(); it != node.end(); ++ it)
			{
				indent();
				print_scalar(it.first());  // show key
				spaces ++;
				unroll(it.second());
				spaces--;				// unroll map
				cout << "\n";
			}
			break;
		case YAML::NodeType::Scalar:
			{
				indent();
				print_scalar(node);
				break;
			}
		case YAML::NodeType::Null:
			indent();
			cout << "null";
			break;
		case YAML::NodeType::Sequence:
			for(auto it = node.begin(); it != node.end(); ++ it)
			{ 
				indent();
				cout << "sequence item:\n";
				spaces ++;
				unroll(*it);
				spaces --;
				
			}
			break;
		default: cout << "error: undefined type";	break;
	}
}
void unroll_extract(const YAML::Node & node)
{
    switch(node.Type())
    {
        case YAML::NodeType::Map:
            if(get_map_type(node) == mapping)
            for(auto it = node.begin(); it != node.end(); ++ it)
            {
                indent();
                print_scalar(it.first());  // show key
                spaces ++;
                unroll_extract(it.second());
                spaces--;                   // unroll map
                cout << "\n";
            }
            else
            if(get_map_type(node) == pairtype)
            {
                indent();
                print_pair(node);
                break;
            }

            break;
        case YAML::NodeType::Scalar:
            {
                indent();
                print_scalar(node);
                break;
            }
        case YAML::NodeType::Null:
            indent();
            cout << "null";
            break;
        case YAML::NodeType::Sequence:
            for(auto it = node.begin(); it != node.end(); ++ it)
            { 
                indent();
                cout << "sequence item:\n";
                spaces ++;
                unroll_extract(*it);
                spaces --;
                
            }
            break;
        default: cout << "error: undefined type";       break;
    }
}
void unroll_extract2(const YAML::Node & node)
{
	switch(node.Type())
	{
		case YAML::NodeType::Map:
			if(get_map_type(node) == mapping)
				for(auto it = node.begin(); it != node.end(); ++ it)
					unroll_extract(it.second());
			else if(get_map_type(node) == pairtype)
				print_pair(node);
			break;
		case YAML::NodeType::Scalar:
		case YAML::NodeType::Null:
			break;
		case YAML::NodeType::Sequence:
			for(auto it = node.begin(); it != node.end(); ++ it)
				unroll_extract(*it);
			break;
		default: cout << "error: undefined type";	break;
	}
}
void showmapmap()
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
void show_node_content(const ynode & node) // mainly designed as a non recursive function, treats scalars, but it's not the goal here
{
	switch(node.Type())
	{
	case YAML::NodeType::Map:
		if(get_map_type(node) == mapping)
		{
			cout << "mapping ";
			print_scalar(node.begin().first());
			for(auto i = node.begin(); i!= node.end(); i++) // fffuuuu
			{
				showtype(i.second());
			}
		}
		else if(get_map_type(node) == pairtype)
		{
			
		}
		break;
	case YAML::NodeType::Sequence:
		break;
	case YAML::NodeType::Scalar:
		print_scalar(node);
		break;
	case YAML::NodeType::Null:
		break;
	default:;
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	ifstream ifstr("items3.yml");
	//ifstream ifstr("sample2.yml");
	YAML::Parser parser(ifstr); // remember to pass it by reference
	YAML::Node doc;
	if(! parser.GetNextDocument(doc)) exit(0xbadf00d);

	extract(doc);
	showmapmap();
	

	system("PAUSE");
	return 0;
}

//enum node_type { null, map, list, scalar };
//struct Node
//{
//	node_type type;
//	void * node_content; // std::pair, std::string, 
//	vector<void *> nodes;
//};


