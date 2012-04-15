#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	try
	{
		ItemMgr mgr;
		mgr.load_yaml("items3.yml");
		//for(auto i = mgr.ItemNames.begin(); i != mgr.ItemNames.end(); ++ i)
			//cout << * i << "\n";
		mgr.make_masks();
		mgr.make_bimap();
		mgr.diagnose();
	}
	catch(YAML::ParserException& e)
	{
		std::cout << e.what() << "\n";
	}

	system("PAUSE");
	return 0;
}