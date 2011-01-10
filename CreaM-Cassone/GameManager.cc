/* ################################################################# */
/* FILE:	GameManager.cc -- DATE: december 2010 -- Project: Carcassone
/* PURPOSE: Manages the ... game
/* AUTHOR:	Jonas ORINOVSKI, EZJONAS@GMAIL.COM or JORINOVSKI@GMAIL.COM
/* ################################################################# */

#include "stdafx.h"

GameManager :: GameManager():
	render_w
	(new RenderWindow(sf :: VideoMode(64 * 7, 64 * 5), "CreaM-Cassone")),
	boardmgr(BoardManager :: GetSingleton()),
	mouse_x(0), mouse_y(0), player_count(0), current_player(0)
{}

GameManager :: ~ GameManager()
{
	for(player_vect_iter_t i = Players.begin(); i != Players.end(); ++ i)
	{
		delete * i;
	}
}
GameManager * GameManager :: GetSingleton()
{
	static GameManager _;
	return & _;
}
RenderWindow * GameManager :: GetRenderWindow()
{
	return render_w;
}
void GameManager :: LaunchGame()
{
	// these are just test purposed puts
	boardmgr -> PutTileNoCheck('X', 3, 2);
	boardmgr -> PutTileNoCheck('F', 3, 2); // cant
	boardmgr -> PutTileNoCheck('F', 1, 1);
	boardmgr -> PutTileNoCheck('H', 0, 0);
	boardmgr -> PutTileNoCheck('S', 2, 3);
	boardmgr -> PutTileNoCheck('S', 2, 2); // cant

	// RenderWindow * App =
	// GameManager :: GetSingleton() -> GetRenderWindowSingleton();
	// boardmgr -> PickTile();

	AddPlayer();
	AddPlayer();
	AddPlayer();
	AddPlayer();
	
	player_count = Player :: GetPlayerCount();
	boardmgr -> SelectCurrentTile(CurrentPlayer -> GetCurrentTile());

	while (render_w -> IsOpened())
	{
		// Process events
		sf::Event Event;
		while (render_w -> GetEvent(Event))
		{
			switch(Event.Type)
			{
// QUITTING EVENT -------------------------------------------------
			case Event :: Closed:
				render_w -> Close();
				break;
					
			case Event :: KeyPressed:
				switch(Event.Key.Code)
				{
				case 'q':
				case Key :: Escape:
					render_w -> Close();
					break;
// OTHER KEYS -------------------------------------------------
				case 's':
				case Key :: Space:
					boardmgr -> Show();
					break;
				}
				break;
				
// MOUSE MOVE EVENT -------------------------------------------------
			case Event :: MouseMoved:
				mouse_cell_x = (Event.MouseMove.X) / 64;
				mouse_cell_y = (Event.MouseMove.Y) / 64;		
				if (mouse_cell_x != (Event.MouseMove.X) / 64)
					cout << "[" << mouse_cell_x << " " << mouse_cell_y << "] ";	
				if (mouse_cell_y != (Event.MouseMove.Y) / 64)
					cout << "[" << mouse_cell_x << " " << mouse_cell_y << "] ";
				
				mouse_x = Event.MouseMove.X;
				mouse_y = Event.MouseMove.Y;
				break;
// MOUSE CLICK EVENT -------------------------------------------------
			case Event :: MouseButtonPressed:
				switch(Event.MouseButton.Button)
				{
// MOUSE CLICK LEFT -------------------------------------------------
				case Mouse :: Left:
					OnePlayerPlays
					(Event.MouseButton.X / 64, Event.MouseButton.Y / 64);
					
					// cout << Event.MouseButton.X / 64 << " " 
					// << Event.MouseButton.Y / 64 << endl;
					break;
// MOUSE CLICK RIGHT -------------------------------------------------
				case Mouse :: Right:
					boardmgr -> TurnCurrentTile();
					break;
				}
				// cout << "MouseButtonPressed" << endl;
				break;
// MOUSE WHEEL -------------------------------------------------
			case Event :: MouseWheelMoved:
				switch(Event.MouseWheel.Delta)
				{
				case -1:
					CurrentPlayer -> SelectNextTile();
					boardmgr -> SelectCurrentTile(CurrentPlayer -> GetCurrentTile());
					break;
				case 1:
					CurrentPlayer -> SelectPrevTile();
					boardmgr -> SelectCurrentTile(CurrentPlayer -> GetCurrentTile());
					break;
				}
				break;
			}
		}

		// Clear screen
		render_w -> Clear();
		boardmgr -> DrawTiles();
		// boardmgr -> DrawCurrentTile(mouse_x, mouse_y);
		boardmgr -> DrawCurrentTile(mouse_x, mouse_y);

		//m_boardmgr -> Update();
		// App.Draw(Text);
		render_w -> Display();
	}
}
void GameManager :: OnePlayerPlays(int x, int y)
{
	cout << "Plays: " << CurrentPlayer -> GetName() << endl;
	// this function is called only when the user click left.
	boardmgr -> SelectCurrentTile(CurrentPlayer -> GetCurrentTile());
	TileCellCheck n = boardmgr -> CheckTilePut(x, y);
	if(n == Checks)
	{
		boardmgr -> PutCurrentTile(x, y);
		CurrentPlayer -> PickAndReplaceTile();
		current_player = (current_player + 1) % player_count;
		CurrentPlayer = Players[current_player];
		cout << "Played: " << CurrentPlayer -> GetName() << endl;
		boardmgr -> SelectCurrentTile(CurrentPlayer -> GetCurrentTile());
	}
	else
		boardmgr -> Verbose(n);
}

void GameManager :: AddPlayer()
{
	CurrentPlayer = new Player;
	Players.push_back(CurrentPlayer);
}

