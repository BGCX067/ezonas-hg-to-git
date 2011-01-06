/* ################################################################# */
/* FILE:	BoardManager.cc		DATE: december 2010
/* PURPOSE: placing and arranging tiles etc, that's a singleton
/* AUTHOR:	Jonas ORINOVSKI, EZJONAS@GMAIL.COM / JORINOVSKI@GMAIL.COM
/* ################################################################# */

#include "stdafx.h"

typedef list <Tile *> tile_list_t;
typedef tile_list_t :: iterator tile_list_iter_t;
/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO CONSTR. OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
BoardManager :: BoardManager():
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
/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO PutCurrentTile OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
void BoardManager :: PutCurrentTile(int _x, int _y)
{
	_x /= 64;
	_y /= 64;
	switch(CheckTilePut(CurrentTile, _x, _y))
	{
	case Checks:
		CurrentTile -> SetPosition(_x, _y);
		board [_x][_y] = CurrentTile;
		tile_count += 1;
		Tiles.push_back(CurrentTile);
		Sprites.push_back
		(
			new Sprite
			(
				* (CurrentTile -> getImgptr()),
				Vector2f(_x * 64, _y * 64)
			)
		);
		cout << "successfuly put a tile !" << endl;
		PickTile();
		break;
		
	case ThereAreNoTileAround:
		cout << "There are no tiels around this cell !" << endl;
		break;

	case ThereAlreadyIsATileThere:
		cout << "There's already a tile there !" << endl;
		break;
		
	case FacesDontMatch:
		cout << "This tile's faces doesn't match one or all around this cell !" << endl;
		break;
	}
}
/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO CheckTilePut OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
int BoardManager :: CheckTilePut(Tile * _tile, int _x, int _y)
{
	// there is already a tile there
	if (board[_x][_y] != NULL)
	{
		return ThereAlreadyIsATileThere;
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
		return ThereAreNoTileAround;
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
		return FacesDontMatch;
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
		return FacesDontMatch;
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
		return FacesDontMatch;
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
		return FacesDontMatch;
	}
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%}
	return Checks;

}
/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO PutTile OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
// this function's purpose is to place tiles on a saved file's loading
// commomly it's only used when a game is loaded
bool BoardManager :: PutTile(char _c, int _x, int _y)
{
	Tile * tile = protoer -> MakeTile (_c);
	// in case this is the first tile
	// if(tile_count == 0)
	// {
		// board[_x][_y] = tile;
		// tile -> SetPosition(_x, _y);
		// tile_count += 1;
		// Tiles.push_back(tile);
		// Sprites.push_back
		// (
			// new Sprite
			// (
				// * (tile->getImgptr()),
				// Vector2f(_x * 64, _y * 64)
			// )
		 // );
		// return true;
	// }
	
	if (CheckTilePut(tile, _x, _y) == Checks)
	{
		tile -> SetPosition(_x, _y);
		board [_x][_y] = tile;
		Tiles.push_back(tile);
		Sprites.push_back
		(
			new Sprite
			(
				* (tile->getImgptr()),
				Vector2f(_x * 64, _y * 64)
			)
		);
		tile_count += 1;
		return true;
	}
}
/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO PutTile OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
void BoardManager :: DrawTiles()
{
	
	for (sprite_list_iter_t i = Sprites.begin(); i != Sprites.end(); ++i)
	{
		// double dereferencing (iterator and then sprite address)
		render_w -> Draw(* * i);
	}
}
/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO DrawCurrentTile OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
void BoardManager :: DrawCurrentTile(int _x, int _y)
{
	if(CurrentSprite != NULL)
	{
		//CurrentSprite -> SetPosition (Event.MouseMove.X, Event.MouseMove.Y);
		render_w -> Draw (* CurrentSprite);
		CurrentSprite -> SetPosition(_x, _y);
	}
}
/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO PickTile OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
void BoardManager :: PickTile()
{
	if (CurrentTile != NULL)
	{
		delete CurrentSprite;
		delete CurrentTile; // the new is in Tile::Clone
	}
	int Random = sf :: Randomizer :: Random('A', 'X');
	// TilePrototyper * m_tiler = TilePrototyper :: GetSingleton();
	CurrentTile = protoer -> MakeTile((char) Random);
	CurrentSprite = new Sprite (* (CurrentTile -> getImgptr()));
	
}
