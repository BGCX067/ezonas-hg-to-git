#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "BoardManager.h"
#include "stdafx.h"

class BoardManager;

class GameManager
{
public:
	static GameManager * GetSingleton()
	{
		static GameManager _;
		return & _;
	}
	void LaunchGame();
	RenderWindow * GetRenderWindow()
	{
		return render_w;
	}
protected:
	GameManager();
	sf :: RenderWindow * render_w;
	BoardManager * boardmgr;
	int mouse_x, mouse_y, mouse_cell_x, mouse_cell_y;
	// int mouse_click_x, mouse_click_y;
};
#endif // _GAME_MANAGER_H_