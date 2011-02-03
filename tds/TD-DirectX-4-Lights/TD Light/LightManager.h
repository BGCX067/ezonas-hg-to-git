/**
 * LightManager.h
 * 
 * @author  Fabsther
 * @since   14/06/2010
 * @version 1.0
 */

#ifndef LIGHTMANAGER__H
#define LIGHTMANAGER__H

#include <d3dx9.h>
#include <vector>
#include <fstream>
#include "Helper.h"
#include "Light.h"
using namespace std;

class LightManager
{
	struct LightElement
	{
		Light* Lumiere;
		//add your parameters here
	};

	protected:
	
		vector<LightElement> m_LightList;

		LightManager();
		IDirect3DDevice9* m_D3DDevice;

	public:

		~LightManager();
		static LightManager* GetSingleton();
		void Load( IDirect3DDevice9* _D3DDevice );
		void Update();

};

#endif //LIGHTMANAGER__H