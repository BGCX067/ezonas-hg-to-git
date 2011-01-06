#include "stdafx.h"
GameManager :: GameManager():
		render_w
		(
			new sf::RenderWindow
				(sf :: VideoMode(64 * 12, 64 * 10), "CreaM-Cassone")
		),
		boardmgr(BoardManager :: GetSingleton()),
		mouse_x(0), mouse_y(0)
{}

void GameManager :: LaunchGame()
{
	
	// these are just tests
	boardmgr -> PutTile('X', 3, 2);
	boardmgr -> PutTile('F', 3, 2);
	boardmgr -> PutTile('F', 1, 1);
	boardmgr -> PutTile('S', 2, 3);
	boardmgr -> PutTile('S', 2, 2);

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
				if(Event.Key.Code == 'q' || Event.Key.Code == Key :: Escape) // not 'Q'
					render_w -> Close();
				break;
/* MOUSE MOVE EVENT */						
			case Event :: MouseMoved:
				// cout << "MouseMoved" << endl;
				mouse_x = Event.MouseMove.X - 32;
				mouse_y = Event.MouseMove.Y - 32;
				break;
/* MOUSE CLICK EVENT */						
			case Event :: MouseButtonPressed:
				// cout << "MouseButtonPressed" << endl;
				boardmgr -> PutCurrentTile ((Event.MouseButton.X), (Event.MouseButton.Y));
				break;
			}
		}

		// Clear screen
		render_w -> Clear();
		boardmgr -> DrawTiles();
		boardmgr -> DrawCurrentTile(mouse_x, mouse_y);

		//m_boardmgr -> Update();
		// App.Draw(Text);
		render_w -> Display();
	}
	
}
