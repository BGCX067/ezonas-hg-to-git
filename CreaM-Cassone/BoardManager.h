/* ################################################################# */
/* FILE:	BoardManager.h		DATE: december 2010
/* PURPOSE: placing and arranging tiles etc, that's a singleton
/* AUTHOR:	Jonas ORINOVSKI, EZJONAS@GMAIL.COM / JORINOVSKI@GMAIL.COM
/* ################################################################# */

#ifndef _BOARD_MANAGER_H_
#define _BOARD_MANAGER_H_

#include "stdafx.h"
#include "GameManager.h"

typedef list<Tile *> tile_list_t;
typedef tile_list_t :: iterator tile_list_iter_t;

typedef list<Sprite *> sprite_list_t;
typedef sprite_list_t :: iterator sprite_list_iter_t;

enum {Checks, ThereAreNoTileAround, ThereAlreadyIsATileThere, FacesDontMatch};

class GameManager;

class BoardManager
{
	
public:
	static BoardManager * GetSingleton()
	{
		static BoardManager _;
		return & _;
	}
	void DrawTiles();
	~ BoardManager()
	{
		Tiles.clear();
		// Sprites.clear();
		for(sprite_list_iter_t i = Sprites.begin(); i != Sprites.end(); ++i)
		{
			delete * i;
		}
	}
	void PickTile();
	void PutCurrentTile(int _x, int _y);
	int CheckTilePut(Tile *, int x, int y);
	bool PutTile(char _c, int _x, int _y);
	void DrawCurrentTile(int _x, int _y);
protected:
	BoardManager();	
	Tile * board [72] [72];
	int tile_count;
	Tile * CurrentTile;
	Sprite * CurrentSprite;
	
	// this will help keep track of the order of put tiles, it will also be used to draw tiles
	tile_list_t Tiles;
	sprite_list_t Sprites;
	RenderWindow * render_w;
	TilePrototyper * protoer;
};
#endif // _BOARD_MANAGER_H_
