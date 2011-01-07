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

// typedef list<Sprite *> sprite_list_t;
// typedef sprite_list_t :: iterator sprite_list_iter_t;
typedef list<Drawable *> draw_list_t;
typedef draw_list_t :: iterator draw_list_iter_t;

enum TileCellCheck
{
	Checks,
	ThisIsTheFirstTile,
	ThereAreNoTileAround,
	ThereAlreadyIsATileThere,
	FacesDontMatch,
	FacesDontMatchNorth,
	FacesDontMatchWest,
	FacesDontMatchEast,
	FacesDontMatchSouth
};

class GameManager;

class BoardManager
{
	
public:
	static BoardManager * GetSingleton()
	{
		static BoardManager _;
		return & _;
	}
	~ BoardManager()
	{
		Tiles.clear();
		// Sprites.clear();
		for(draw_list_iter_t i = Drawables.begin(); i != Drawables.end(); ++i)
		{
			delete * i;
		}
	}
	void DrawTiles();
	void Show();
	void Verbose(TileCellCheck n);
	void PickTile();
	void PutValidTile(Tile * _tile, int _x, int _y);
	void PutCurrentTile(int _x, int _y);
	void PutTileNoCheck(char _c, int _x, int _y);

	TileCellCheck CheckTilePut(Tile *, int x, int y);
	bool PutTile(char _c, int _x, int _y);
	void DrawCurrentTile(int _x, int _y);
protected:
	BoardManager();	
	Tile * board [72] [72];
	int tile_count, board_x, board_y;
	Tile * CurrentTile;
	Sprite * CurrentSprite;
	
	// this will help keep track of the order of put tiles, it will also be used to draw tiles
	tile_list_t Tiles;
	// sprite_list_t Sprites;
	draw_list_t Drawables;
	RenderWindow * render_w;
	TilePrototyper * protoer;
	Font * font;
	string fontpath;
};
#endif // _BOARD_MANAGER_H_
