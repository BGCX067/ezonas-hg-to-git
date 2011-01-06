#if not defined _GAME_MANAGER_H_
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
	GameManager():
	render_w(new sf::RenderWindow
			 (sf :: VideoMode(64 * 12, 64 * 10), "CreaM-Cassone")),
	boardmgr(BoardManager :: GetSingleton())
	{}
	sf :: RenderWindow * render_w;
	BoardManager * boardmgr;
};
#endif // _GAME_MANAGER_H_