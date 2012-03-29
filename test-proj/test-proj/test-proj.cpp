#include "stdafx.h"


void gettype(const YAML::Node & n)
{
	switch(n.Type())
	{
	case YAML::NodeType::Null:		cout << string("NULL")		<< "\n"	;
	case YAML::NodeType::Scalar:	cout << string("Scalar")	<< "\n"	;
	case YAML::NodeType::Sequence:	cout << string("Sequence")	<< "\n"	;
	case YAML::NodeType::Map:		cout << string("Map")		<< "\n"	;
	}
}
int spaces = 0;
void indent() { for(int i = 0; i < spaces * 4; ++i) cout << " "; }
void unroll(const YAML::Node & node)
{
	switch(node.Type())
	{
		case YAML::NodeType::Map:		
		{
			for(auto it = node.begin(); it != node.end(); ++ it)
			{
				string s; it.first() >> s;
				indent();
				cout << s << "\n";
				const YAML::Node & dada = it.second();
				spaces ++;
				unroll(dada);
				spaces--;
				cout << "\n";
			}
			break;
		}

		case YAML::NodeType::Scalar:
		{
			indent();
			string s; node >> s;
			cout << "found scalar " << s << "\n";
			break;
		}
		case YAML::NodeType::Null:
		{
			indent();
			cout << "null";
			break;
		}
		case YAML::NodeType::Sequence:
		{
			//cout << "sequence";
			for(auto it = node.begin(); it != node.end(); ++ it)
			{
				string s; *it >> s;
				indent();
				cout << s << "\n";
			}
			break;
		}
		default: cout << "error: undefined";	break;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	ifstream ifstr("test2.yml");
	YAML::Parser parser(ifstr); // remember to pass it by reference
	YAML::Node doc;
	if(! parser.GetNextDocument(doc)) exit(0xbadf00d);

	unroll(doc);

	system("PAUSE");
	return 0;
}

