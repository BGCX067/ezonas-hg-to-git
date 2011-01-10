/* ################################################################# */
/* FILE:	GameManager.h		DATE: december 2010 Project: Carcassone
/* PURPOSE: Manages the ... game
/* AUTHOR:	Jonas ORINOVSKI, EZJONAS@GMAIL.COM or JORINOVSKI@GMAIL.COM
/* ################################################################# */

#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "BoardManager.h"
#include "stdafx.h"
class Player;

//typedef map <string, Player *> player_map_t;
//typedef player_map_t :: iterator player_map_iter_t;

typedef vector <Player *> player_vect_t;
typedef player_vect_t :: iterator player_vect_iter_t;
class BoardManager;
typedef map <string, Player> :: iterator player_map_iter_t; // banzai

class GameManager
{
public:
	static GameManager * GetSingleton();
	~ GameManager();

	void LaunchGame();
	RenderWindow * GetRenderWindow();
	void OnePlayerPlays(int, int);
	void AddPlayer();
	
protected:
	GameManager();
	sf :: RenderWindow * render_w;
	BoardManager * boardmgr;
	int mouse_x, mouse_y, mouse_cell_x, mouse_cell_y, player_count, current_player;
	// int mouse_click_x, mouse_click_y;
	// map <string, Player *> Players;
	vector <Player *> Players;
// we use a player iterator here
	Player * CurrentPlayer;
};
#endif // _GAME_MANAGER_H_

