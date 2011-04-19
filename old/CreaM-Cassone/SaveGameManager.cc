#include "SaveGameManager.h"
SaveGameManager :: SaveGameManager(string name = "creacassone.savegame.txt")
{
	in = new ifstream(name.c_str());
	if (in -> is_open())
	{
		string tmp;
		while(! in -> eof())
		// while (*(in) >> tmp)
		{
			getline (*in, tmp);
			Lines.push_back(tmp);
		}
		for(vector<string> :: iterator i;
			i != Lines.begin();
			++ i)
		{
			cout << *i << endl;
		}
	}
}
SaveGameManager * SaveGameManager :: GetSingleton()
{
	static SaveGameManager _;
	return & _;
}

SaveGameManager :: ~ SaveGameManager()
{
	
}

int main()
{
	SaveGameManager * sgmgr = SaveGameManager :: GetSingleton();
	
}