#include "stdafx.h"

void GameManager :: LaunchGame()
{
	TilePrototyper * m_tiler = TilePrototyper :: GetSingleton();
	BoardManager * m_boardmgr = BoardManager :: GetSingleton();
	
	// these are just tests
	m_boardmgr -> PutTile(m_tiler -> MakeTile('X'), 3, 2);
	m_boardmgr -> PutTile(m_tiler -> MakeTile('F'), 3, 2);
	m_boardmgr -> PutTile(m_tiler -> MakeTile('F'), 1, 1);
	m_boardmgr -> PutTile(m_tiler -> MakeTile('S'), 2, 3);
	m_boardmgr -> PutTile(m_tiler -> MakeTile('S'), 2, 2);

	// RenderWindow * App =
	// GameManager :: GetSingleton() -> GetRenderWindowSingleton();
		
	while (render_w -> IsOpened())
	{
		// Process events
		sf::Event Event;
		while (render_w -> GetEvent(Event))
		{
			boardmgr -> DrawTiles;
			switch(Event.Type)
			{
				case Event :: Closed:
					render_w -> Close();
					break;
					
				case Event :: KeyPressed:
					if(Event.Key.Code == 'q') // not 'Q'
						render_w -> Close();
						break;
						
				case Event :: MouseMoved:
					boardmgr -> DrawCurrentTile();
					break;
						
			}
		}

		// Clear screen
		render_w -> Clear();

		m_boardmgr -> Update();
		// App.Draw(Text);
		render_w -> Display();
	}
	
}
