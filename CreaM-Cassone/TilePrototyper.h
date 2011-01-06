/* ################################################################# */
/* FILE:	TilePrototyper.h		DATE: december 2010
/* PURPOSE: the prototype design pattern for all tile from A to X
/* AUTHOR:	Jonas ORINOVSKI, EZJONAS@GMAIL.COM or JORINOVSKI@GMAIL.COM
/* ################################################################# */

#include "stdafx.h"

typedef map <char, Image *> img_map_t;
typedef img_map_t :: iterator img_map_iter_t;
typedef map <char, Tile *> tile_map_t;
typedef tile_map_t :: iterator tile_map_iter_t;


// typedef map <char, Image> img_map_t;
// typedef img_map_t :: iterator img_map_iter_t;
// typedef map <char, Tile> tile_map_t;
// typedef tile_map_t :: iterator tile_map_iter_t;

class TilePrototyper
{
public:
	~ TilePrototyper()
	{
		// Tiles.clear();
		// Images.clear();
		tile_map_iter_t i = Tiles.begin();
		img_map_iter_t j = Images.begin();
		for (;i != Tiles.end(), j != Images.end(); ++i, ++j)
		{
			delete i -> second;
			delete j -> second;
		}
	}
	
	Tile * MakeTile(char _c)
	{
		if(_c < 'A' || _c > 'X')
		{	
			return NULL;
		}
		return Tiles[_c] -> Clone();
	}
	static TilePrototyper * GetSingleton()
	{
		static TilePrototyper _;
		return & _;
	}
protected:
	tile_map_t Tiles;
	img_map_t Images;
	TilePrototyper()
	{
		// images
		string begin("content/");
		string end(".png");
		for (char c = 'A'; c <= 'X'; ++c)
		{
			Image * img = new Image;
			img -> LoadFromFile(begin + c + end);
			Images[c] = img;
			Tiles[c] = new Tile(c, img);
		}
	}

};