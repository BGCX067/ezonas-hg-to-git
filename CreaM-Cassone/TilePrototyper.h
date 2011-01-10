/* ################################################################# */
/* FILE:	TilePrototyper.h	DATE: december 2010 Project: Carcassone
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
	~ TilePrototyper();
	Tile * MakeTile(char _c);
	static TilePrototyper * GetSingleton();
protected:
	tile_map_t Tiles;
	img_map_t Images;
	TilePrototyper();
};
