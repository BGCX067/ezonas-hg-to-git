/* ################################################################# */
/* FILE:	BoardManager.h		DATE: december 2010
/* PURPOSE: placing and arranging tiles etc, that's a singleton
/* AUTHOR:	Jonas ORINOVSKI, EZJONAS@GMAIL.COM / JORINOVSKI@GMAIL.COM
/* ################################################################# */

#if not defined _BOARD_MANAGER_H_
#define _BOARD_MANAGER_H_

#include "stdafx.h"
#include "GameManager.h"

typedef list<Tile *> tile_list_t;
typedef tile_list_t :: iterator tile_list_iter_t;

typedef list<Sprite *> sprite_list_t;
typedef sprite_list_t :: iterator sprite_list_iter_t;

class GameManager;

class BoardManager
{
	
public:
	static BoardManager * GetSingleton()
	{
		static BoardManager _;
		return & _;
	}
	bool PutTile(Tile * _tile, int _x, int _y);
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
protected:
	BoardManager():
		tile_count(0),
		CurrentTile(NULL),
		render_w(GameManager :: GetSingleton() -> GetRenderWindow()),
		protoer(TilePrototyper :: GetSingleton())
		
	{
		for (int i = 0; i < 72; ++i)
		{
			for (int j = 0; j < 72; ++j)
			{
				board[i][j] = NULL;
			}
		}
	}
	
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
