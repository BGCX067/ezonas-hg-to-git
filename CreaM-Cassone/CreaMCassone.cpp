// CreaMCassone.cpp�: d�finit le point d'entr�e pour l'application console.
//

#include "stdafx.h"

#if defined __APPLE__
int main(int argc, char * argv[])
#else
int main(int argc, char * argv[])
#endif
{
	GameManager :: GetSingleton() -> LaunchGame(); 
	return 0;
}

