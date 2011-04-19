/* ################################################################# */
/* FILE:	TileFactory.h		DATE: december 2010
/* PURPOSE: Factory design pattern
/* AUTHOR:	Jonas ORINOVSKI, EZJONAS@GMAIL.COM or JORINOVSKI@GMAIL.COM
/* ################################################################# */

#include "stdafx.h"

TilePrototyper :: ~ TilePrototyper()
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

Tile * TilePrototyper :: MakeTile(char _c)
{
	if(_c < 'A' || _c > 'X')
	{	
		return NULL;
	}
	return Tiles[_c] -> Clone();
}

TilePrototyper * TilePrototyper :: GetSingleton()
{
	static TilePrototyper _;
	return & _;
}

TilePrototyper :: TilePrototyper()
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
