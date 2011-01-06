/* ################################################################# */
/* FILE:	BoardManager.cc		DATE: december 2010
/* PURPOSE: placing and arranging tiles etc, that's a singleton
/* AUTHOR:	Jonas ORINOVSKI, EZJONAS@GMAIL.COM / JORINOVSKI@GMAIL.COM
/* ################################################################# */

#include "stdafx.h"

typedef list <Tile *> tile_list_t;
typedef tile_list_t :: iterator tile_list_iter_t;

bool BoardManager :: PutTile(Tile * _tile, int _x, int _y)
{
	// in case this is the first tile
	if(tile_count == 0)
	{
		board[_x][_y] = _tile;
		tile_count += 1;
		Tiles.push_back(_tile);
		Sprites.push_back
		(
			new Sprite
			(
				* (_tile->getImgptr()),
				Vector2f(_x * 64, _y * 64)
			)
		 );
		
		return true;
	}
	
	// there is already a tile there
	if (board[_x][_y] != NULL)
	{
		return false;
	}

	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// checking if there is at least one tile next
	if
	(
		   board [_x + 1][_y]
		&& board [_x - 1][_y] 
		&& board [_x][_y + 1] 
		&& board [_x][_y - 1]
		== NULL
	)
	{
		return false;
	
	}

	// checking if all faces match
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// checking east
	if (board [_x + 1][_y] != NULL)
	{
		if
		(
			_tile -> GetFace(EAST)
			!=
			board [_x + 1][_y] -> GetFace(WEST)
		)
		return false;
	}

	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// checking west
	if (board [_x - 1][_y] != NULL)
	{
		if
		(
			_tile -> GetFace(WEST)
			!=
			board [_x - 1][_y] -> GetFace(EAST)
		)
		return false;
	}
	
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// checking south
	if (board [_y + 1][_y] != NULL)
	{
		if
		(
			_tile -> GetFace(SOUTH)
			!=
			board [_y + 1][_y] -> GetFace(NORTH)
		)
		return false;
	}
	
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// checking north
	if (board [_y - 1][_y] != NULL)
	{
		if
		(
			_tile -> GetFace(NORTH)
			!=
			board [_y - 1][_y] -> GetFace(SOUTH)
		)
		return false;
	}
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	_tile -> SetPosition(_x, _y);
	board [_x][_y] = _tile;
	Tiles.push_back(_tile);
	Sprites.push_back
	(
		new Sprite
		(
			* (_tile->getImgptr()),
			   Vector2f(_x * 64, _y * 64)
		)
	);
	tile_count += 1;
	return true;
}

void BoardManager :: DrawTiles()
{
	
	for (sprite_list_iter_t i = Sprites.begin(); i != Sprites.end(); ++i)
	{
		// double dereferencing (iterator and then sprite address)
		render_w -> Draw(* * i);
	}
}


void BoardManager :: DrawCurrentTile()
{
	if(CurrentSprite != NULL)
	{
		CurrentSprite -> SetPosition (Event.MouseMove.X, Event.MouseMove.Y);
		render_w -> Draw (* CurrentSprite);
	}
	
}


void BoardManager :: Update()
{
	DrawTiles();
}
void BoardManager :: PickTile()
{
	if (CurrentTile != NULL)
	{
		delete CurrentSprite;
		delete CurrentTile; // the new is in Tile::Clone
	}
	int Random = sf :: Randomizer :: Random('A', 'X');
	TilePrototyper * m_tiler = TilePrototyper :: GetSingleton();
	CurrentTile = m_tiler -> MakeTile((char) Random);
	CurrentSprite = new Sprite (* (CurrentTile -> getImgptr()));
	
}
