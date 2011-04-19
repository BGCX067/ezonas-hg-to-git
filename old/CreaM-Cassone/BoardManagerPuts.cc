/* ################################################################# */
/* FILE:	BoardManager.cc -- DATE: december 2010 -- Project: Carcassone
/* PURPOSE: placing and arranging tiles etc, that's a singleton
/* AUTHOR:	Jonas ORINOVSKI, EZJONAS@GMAIL.COM / JORINOVSKI@GMAIL.COM
/* ################################################################# */

#include "stdafx.h"

bool BoardManager :: PutCurrentTile(int _x, int _y)
{
	cout << "Tile tried: " << endl;
	CurrentTile -> Show();
	cout << "on: [" << _x << " " << _y << "] ";

	// _x /= 64;
	// _y /= 64;
	TileCellCheck n = CheckTilePut(_x, _y);
	//Verbose(n);
	switch(n)
	{
	case Checks:
		PutValidTile(CurrentTile, _x, _y);
		//PickTile();
		return true;
		
	case ThisIsTheFirstTile:
		PutValidTile(CurrentTile, _x, _y);
		return true;

	case ThereAreNoTileAround:
		return false;

	case ThereAlreadyIsATileThere:
		return false;
	}
}
TileCellCheck BoardManager :: CheckTilePut(/*Tile * _tile, */int _x, int _y)
{
	// there is already a tile there
	if (tile_count == 0)
	{
		return ThisIsTheFirstTile;
	}
	
	if (board[_y][_x] != NULL)
	{
		return ThereAlreadyIsATileThere;
	}
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// checking if there is at least one tile next
	if
	(
			board [_y][_x + 1] == NULL &&
			board [_y][_x - 1] == NULL &&
			board [_y + 1][_x] == NULL &&
			board [_y - 1][_x] == NULL
	)
	{
		return ThereAreNoTileAround;
	}

	// checking if all faces match
	
	// checking east
	if (board [_y][_x + 1] != NULL &&
		CurrentTile -> GetFace(EAST) != board [_y][_x + 1] -> GetFace(WEST))
			return FacesDontMatchEast;

	// checking west
	if (board [_y][_x - 1] != NULL &&
		CurrentTile -> GetFace(WEST) != board [_y][_x - 1] -> GetFace(EAST))
			return FacesDontMatchWest;
	
	// checking south
	if (board [_y + 1][_x] != NULL &&
		CurrentTile -> GetFace(SOUTH) != board [_y + 1][_x] -> GetFace(NORTH))
			return FacesDontMatchSouth;
	
	// checking north
	if (board [_y - 1][_x] != NULL &&
		CurrentTile -> GetFace(NORTH) != board [_y - 1][_x] -> GetFace(SOUTH))
			return FacesDontMatchNorth; // FacesDontMatch
	return Checks;

}
/*bool BoardManager :: PutTile(char _c, int _x, int _y)
{
	Tile * tile = protoer -> MakeTile (_c);
	TileCellCheck n = CheckTilePut(tile, _x, _y);
	// Verbose(n);
//	VerboseGraphic(n);
	if(n != Checks && n != ThisIsTheFirstTile)
	{
		delete tile;
		return false;
	}
	
	PutValidTile(tile, _x, _y);
	return true;
	
}
*/
void BoardManager :: PutValidTile(Tile * _tile, int _x, int _y)
{
	_tile -> SetPosition(_x, _y);
	board [_y][_x] = _tile;
	Tiles.push_back(_tile);
	Drawables.push_back
	(
		new Sprite
		(
			* (_tile->getImgptr()),
			Vector2f(_x * 64 + 32, _y * 64 + 32)
		)
	);
	Drawables.back() -> SetRotation(- _tile -> GetOrientation() * 90);
	//String * str_north = new String (string("") + _tile -> Get());
	//String * str_south = new String (string("") + _tile -> GetSymbol());
	//String * str_east  = new String (string("") + _tile -> GetSymbol());
	//String * str_west  = new String (string("") + _tile -> GetSymbol());
	(Drawables.back()) -> SetCenter(32, 32);
	String * s = new String (string("") + _tile -> GetSymbol());
	s -> SetPosition(_x * 64, _y * 64);
	Drawables.push_back (s);//, * font));
	tile_count += 1;
}
void BoardManager :: PutTileNoCheck(char _c, int _x, int _y)
{
	Tile * tile = protoer -> MakeTile (_c);
	PutValidTile(tile, _x, _y);
}
void BoardManager :: SelectCurrentTile(Tile * _tile)
{
	CurrentTile = _tile;
	CurrentSprite = new Sprite (* (CurrentTile -> getImgptr()));
	CurrentSprite -> SetCenter(32, 32);
}
