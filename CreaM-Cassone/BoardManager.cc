/* ################################################################# */
/* FILE:	BoardManager.cc -- DATE: december 2010 -- Project: Carcassone
/* PURPOSE: placing and arranging tiles etc, that's a singleton
/* AUTHOR:	Jonas ORINOVSKI, EZJONAS@GMAIL.COM / JORINOVSKI@GMAIL.COM
/* ################################################################# */

#include "stdafx.h"

typedef list <Tile *> tile_list_t;
typedef tile_list_t :: iterator tile_list_iter_t;

BoardManager :: BoardManager():
	protoer(TilePrototyper :: GetSingleton()),
	render_w(GameManager :: GetSingleton() -> GetRenderWindow()),
	tile_count(0), tile_reserve(0),
	board_x(20), board_y(20),
	CurrentTile(NULL)//, WillItBlend(NULL)
{
	for (int i = 0; i < 72; ++i)
	{
		for (int j = 0; j < 72; ++j)
		{
			board[i][j] = NULL;
		}
	}
	//font -> LoadFromFile(fontpath);
	TileStack['A'] = 2;
	TileStack['B'] = 4;
	TileStack['C'] = 1;
	TileStack['D'] = 4;
	TileStack['E'] = 5;
	TileStack['F'] = 2;
	TileStack['G'] = 1;
	TileStack['H'] = 3;
	TileStack['I'] = 2;
	TileStack['J'] = 3;
	TileStack['K'] = 3;
	TileStack['L'] = 3;
	TileStack['M'] = 2;
	TileStack['N'] = 3;
	TileStack['O'] = 2;
	TileStack['P'] = 3;
	TileStack['Q'] = 2;
	TileStack['R'] = 3;
	TileStack['S'] = 2;
	TileStack['T'] = 1;
	TileStack['U'] = 8;
	TileStack['V'] = 9;
	TileStack['W'] = 4;
	TileStack['X'] = 1;
	cout << "do" << endl;

	for (intchar_iter_t i = TileStack.begin(); i != TileStack.end(); ++ i)
	{tile_reserve += i -> second;}


}
BoardManager :: ~ BoardManager()
{
	// Tiles.clear();
	// Sprites.clear();
	for(draw_list_iter_t i = Drawables.begin(); i != Drawables.end(); ++i)
	{
		delete * i;
	}
}
BoardManager * BoardManager :: GetSingleton()
{
	static BoardManager _;
	return & _;
}
void BoardManager :: DrawTiles()
{
	for (draw_list_iter_t i = Drawables.begin(); i != Drawables.end(); ++i)
	{
		// double dereferencing (iterator and then sprite address)
		render_w -> Draw(* * i);
	}
	// if(WillItBlend != 0)
		// render_w -> Draw(*WillItBlend);
}
void BoardManager :: DrawCurrentTile(int _x, int _y)
{
	if(CurrentSprite != NULL)
	{
		//CurrentSprite -> SetPosition (Event.MouseMove.X, Event.MouseMove.Y);
		CurrentSprite -> SetPosition(_x, _y);
		CurrentSprite -> SetRotation(- CurrentTile -> GetOrientation() * 90);
		render_w -> Draw (* CurrentSprite);
	}
}
void BoardManager :: PickTile()
{
	// if (CurrentTile != NULL)
	// {
		// delete CurrentSprite;
		// delete CurrentTile; // the new is in Tile::Clone
	// }
	char Random = sf :: Randomizer :: Random('A', 'X');
	// TilePrototyper * m_tiler = TilePrototyper :: GetSingleton();
	CurrentTile = protoer -> MakeTile(Random);
	cout << "picked tile: " << endl;
	CurrentTile -> Show();
}
Tile * BoardManager :: PickATile()
{
	if(tile_reserve < 1)
	{
		cout << "no more tile available !" << endl;
		return NULL;
	}
	char Random = 0;
	do
	{
		Random = sf :: Randomizer :: Random('A', 'X');
		// TilePrototyper * m_tiler = TilePrototyper :: GetSingleton();
	}
	while(TileStack[Random] == 0);
	TileStack[Random] -= 1;
	tile_reserve -= 1;
	return protoer -> MakeTile(Random);
}
void BoardManager :: TurnCurrentTile()
{
	CurrentTile -> TurnClockWise();
	CurrentTile -> Show();
}

