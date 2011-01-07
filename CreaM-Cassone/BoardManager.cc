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
		//board({}),,
		board_x(20),
		board_y(20),
		protoer(TilePrototyper :: GetSingleton()),
		font(new Font),
#ifdef __APPLE__		
		fontpath("profont-x11/ProFont_r400-11.pcf")
#else
		fontpath("content\\profont-x11\\ProFont_r400-11.pcf")
#endif
{
	for (int i = 0; i < 72; ++i)
	{
		for (int j = 0; j < 72; ++j)
		{
			board[i][j] = NULL;
		}
	}
	font -> LoadFromFile(fontpath);
}
void BoardManager :: Verbose(TileCellCheck n)
{
	switch(n)
	{
		case Checks:
			cout << "Successfuly put this tile: " << endl;
			CurrentTile -> Show();
			break;
		case ThereAreNoTileAround:
			cout << "No tiles around this cell !" << endl;
			break;
		case ThisIsTheFirstTile:
			cout << "First tile put without question." << endl;
			break;
		case ThereAlreadyIsATileThere:
			cout << "Already a tile there !" << endl;
			break;
		
		case FacesDontMatch:
		case FacesDontMatchSouth:
		case FacesDontMatchEast:
		case FacesDontMatchNorth:
		case FacesDontMatchWest:
		// cout << "This tile's faces doesn't match one or all around this cell ! here is the face that poses problem:" << endl;
		cout << "Faces dont match: ";
		switch(n)
		{
			default: cout << "SEEMS YOU SMOKED RAM AGAIN !" << endl; break;
			case FacesDontMatchSouth: cout << "south !" << endl; break;
			case FacesDontMatchEast:  cout << "east !" << endl; break;
			case FacesDontMatchNorth: cout << "north !" << endl; break;
			case FacesDontMatchWest:  cout << "west !" << endl; break;
		}
		break;
	}
}

/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO PutCurrentTile OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
void BoardManager :: PutCurrentTile(int _x, int _y)
{
	cout << "Tile tried: " << endl;
	CurrentTile -> Show();
	cout << "on: [" << _x << " " << _y << "] ";

	// _x /= 64;
	// _y /= 64;
	TileCellCheck n = CheckTilePut(CurrentTile, _x, _y);
	Verbose(n);
	switch(n)
	{
	case Checks:
		PutValidTile(CurrentTile, _x, _y);
		PickTile();
		break;
		
	case ThisIsTheFirstTile:
		PutValidTile(CurrentTile, _x, _y);
		break;

	case ThereAreNoTileAround:
		break;

	case ThereAlreadyIsATileThere:
		break;

	}
}
/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO CheckTilePut OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
TileCellCheck BoardManager :: CheckTilePut(Tile * _tile, int _x, int _y)
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
			_tile -> GetFace(EAST) != board [_y][_x + 1] -> GetFace(WEST))
			return FacesDontMatchEast;

	// checking west
	if (board [_y][_x - 1] != NULL &&
			_tile -> GetFace(WEST) != board [_y][_x - 1] -> GetFace(EAST))
			return FacesDontMatchWest;
	
	// checking south
	if (board [_y + 1][_x] != NULL &&
			_tile -> GetFace(SOUTH) != board [_y + 1][_x] -> GetFace(NORTH))
			return FacesDontMatchSouth;
	
	// checking north
	if (board [_y - 1][_x] != NULL &&
			_tile -> GetFace(NORTH) != board [_y - 1][_x] -> GetFace(SOUTH))
			return FacesDontMatchNorth; // FacesDontMatch
	return Checks;

}
/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO PutTile OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
// this function's purpose is to place tiles on a saved file's loading
// commomly it's only used when a game is loaded
bool BoardManager :: PutTile(char _c, int _x, int _y)
{
	Tile * tile = protoer -> MakeTile (_c);
	TileCellCheck n = CheckTilePut(tile, _x, _y);
	Verbose(n);
	if(n != Checks && n != ThisIsTheFirstTile)
	{
		delete tile;
		return false;
	}
	
	PutValidTile(tile, _x, _y);
}

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
				Vector2f(_x * 64, _y * 64)
			)
		);
		//String * str_north = new String (string("") + _tile -> Get());
		//String * str_south = new String (string("") + _tile -> GetSymbol());
		//String * str_east  = new String (string("") + _tile -> GetSymbol());
		//String * str_west  = new String (string("") + _tile -> GetSymbol());
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
/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO PutTile OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
void BoardManager :: DrawTiles()
{
	
	for (draw_list_iter_t i = Drawables.begin(); i != Drawables.end(); ++i)
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
	// if (CurrentTile != NULL)
	// {
		// delete CurrentSprite;
		// delete CurrentTile; // the new is in Tile::Clone
	// }
	int Random = sf :: Randomizer :: Random('A', 'X');
	// TilePrototyper * m_tiler = TilePrototyper :: GetSingleton();
	CurrentTile = protoer -> MakeTile((char) Random);
	cout << "picked tile: " << endl;
	CurrentTile -> Show();
	CurrentSprite = new Sprite (* (CurrentTile -> getImgptr()));
}

void BoardManager :: Show()
{
	cout << "Showing the grid: " << endl;

	for (int y = 0; y < board_y; ++y)
	{
		for (int x = 0; x < board_x; ++x)
		{
			if (board[y][x] == NULL)
			{
				cout << '-';
			}
			else
			{
				cout << board[y][x] -> GetSymbol();
			}
		}
		cout << endl;
	}
	cout << endl;

}
