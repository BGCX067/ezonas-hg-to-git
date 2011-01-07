#include "stdafx.h"
GameManager :: GameManager():
		render_w
		(
			new sf::RenderWindow
				(sf :: VideoMode(64 * 7, 64 * 5), "CreaM-Cassone")
		),
		boardmgr(BoardManager :: GetSingleton()),
		mouse_x(0), mouse_y(0)
{}

void GameManager :: LaunchGame()
{
	// these are just tests
	boardmgr -> PutTileNoCheck('X', 3, 2);
	boardmgr -> PutTileNoCheck('F', 3, 2);// cant
	boardmgr -> PutTileNoCheck('F', 1, 1);
	boardmgr -> PutTileNoCheck('S', 2, 3);
	boardmgr -> PutTileNoCheck('S', 2, 2);// cant

	// RenderWindow * App =
	// GameManager :: GetSingleton() -> GetRenderWindowSingleton();
	boardmgr -> PickTile();

	while (render_w -> IsOpened())
	{
		// Process events
		sf::Event Event;
		while (render_w -> GetEvent(Event))
		{
			switch(Event.Type)
			{
/* CLOSIGN EVENT */
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
/* OTHER KEYS*/				
				case 's':
				case Key :: Space:
					boardmgr -> Show();
					break;
				}
				break;
				
/* MOUSE MOVE EVENT */
			case Event :: MouseMoved:
				// cout << "MouseMoved" << endl;
				if (mouse_cell_x != Event.MouseMove.X / 64)
				{
					mouse_cell_x = Event.MouseMove.X / 64;
					cout << "[" << mouse_cell_x << " " << mouse_cell_y << "] ";
				}
				
				if (mouse_cell_y != Event.MouseMove.Y / 64)
				{
					mouse_cell_y = Event.MouseMove.Y / 64;
					cout << "[" << mouse_cell_x << " " << mouse_cell_y << "] ";
				}
				
				mouse_x = Event.MouseMove.X;
				mouse_y = Event.MouseMove.Y;
				break;
/* MOUSE CLICK EVENT */						
			case Event :: MouseButtonPressed:
				// cout << "MouseButtonPressed" << endl;
				boardmgr -> PutCurrentTile (Event.MouseButton.X / 64, Event.MouseButton.Y / 64);
				cout << Event.MouseButton.X / 64 << " " << Event.MouseButton.Y / 64 << endl;
				break;
			}
		}

		// Clear screen
		render_w -> Clear();
		boardmgr -> DrawTiles();
		boardmgr -> DrawCurrentTile(mouse_x - 32, mouse_y - 32);

		//m_boardmgr -> Update();
		// App.Draw(Text);
		render_w -> Display();
	}
	
}
