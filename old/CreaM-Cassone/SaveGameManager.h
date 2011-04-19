#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class SaveGameManager
{
public:
	~ SaveGameManager();
	static SaveGameManager * GetSingleton();
protected:
	SaveGameManager(string filename);// = "creacassone.savegame.txt");
	ifstream * in;
	ofstream * out;
	vector <string> Lines;
};