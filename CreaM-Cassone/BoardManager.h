/* ################################################################# */
/* FILE:	BoardManager.h		DATE: december 2010 Project: Carcassone
/* PURPOSE: placing and arranging tiles etc, that's a singleton
/* AUTHOR:	Jonas ORINOVSKI, EZJONAS@GMAIL.COM / JORINOVSKI@GMAIL.COM
/* ################################################################# */

#ifndef _BOARD_MANAGER_H_
#define _BOARD_MANAGER_H_

#include "stdafx.h"
#include "GameManager.h"

// tile list
typedef list<Tile *> tile_list_t;
typedef tile_list_t :: iterator tile_list_iter_t;
// player pair
//typedef pair <string, Player *> player_pair_t;
//typedef player_pair_t :: iterator player_pair_iter_t;
// player (pair) list
//typedef list <player_pair_t> player_list_t;
//typedef player_list_t :: iterator player_list_iter_t;
// drawable list
typedef list<Drawable *> draw_list_t;
typedef draw_list_t :: iterator draw_list_iter_t;

// available tile map
typedef map <char, int> :: iterator intchar_iter_t;

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
// main functions
public:
	static BoardManager * GetSingleton();
protected:
	BoardManager();
	~ BoardManager();
public:	
	void DrawTiles();
	void TurnCurrentTile();
	void PickTile();
	Tile * PickATile();
	void SelectCurrentTile(Tile * _tile);	
	void DrawCurrentTile(int _x, int _y);
	// void OnePlayerPlays(int, int);
// put
	void PutValidTile(Tile * _tile, int _x, int _y);
	bool PutCurrentTile(int _x, int _y);
	void PutTileNoCheck(char _c, int _x, int _y);
	TileCellCheck CheckTilePut(/*Tile * ,*/ int x, int y);
	// bool PutTile(char _c, int _x, int _y);
// misc
	void Show();
	void Verbose(TileCellCheck n);
	void VerboseGraphic(TileCellCheck n);
protected:
	Tile * board [72] [72];
	int tile_count, board_x, board_y, tile_reserve;

	Tile * CurrentTile;
	Sprite * CurrentSprite;
	String * WillItBlend;

	map <char, int> TileStack; // stack as in you know, a stack of card.
	tile_list_t Tiles;
	draw_list_t Drawables;
	RenderWindow * render_w;
	TilePrototyper * protoer;
};
#endif // _BOARD_MANAGER_H_

