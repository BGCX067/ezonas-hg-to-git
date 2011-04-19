/* ################################################################# */
/* FILE:	TileFactory.h		DATE: december 2010
/* PURPOSE: Factory design pattern
/* AUTHOR:	Jonas ORINOVSKI, EZJONAS@GMAIL.COM or JORINOVSKI@GMAIL.COM
/* ################################################################# */

#include "stdafx.h"

typedef map <char, ifstream *> file_map_t;
typedef file_map_t :: iterator file_map_iter_t;

class TileFactory
{
	public:
	TileFactory()
	{
		
		
	}	
	Tile * BuildTile(char _c)
	{
		if(_c < 'A' || _c > 'Z')
			return NULL;
		
		return new Tile(_c);
		// switch(_c)
		// {
			// case 'A': return new TileA;
			// case 'B': return new TileB;
			// case 'C': return new TileC;
			// case 'D': return new TileD;
			// case 'E': return new TileE;
			// case 'F': return new TileF;
			// case 'G': return new TileG;
			// case 'H': return new TileH;
			// case 'I': return new TileI;
			// case 'J': return new TileJ;
			// case 'K': return new TileK;
			// case 'L': return new TileL;
			// case 'M': return new TileM;
			// case 'N': return new TileN;
			// case 'O': return new TileO;
			// case 'P': return new TileP;
			// case 'Q': return new TileQ;
			// case 'R': return new TileR;
			// case 'S': return new TileS;
			// case 'T': return new TileT;
			// case 'U': return new TileU;
			// case 'V': return new TileV;
			// case 'W': return new TileW;
			// case 'X': return new TileX;
		// 	default: return NULL;
		// }
	}
};