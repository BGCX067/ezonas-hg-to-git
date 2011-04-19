/* ################################################################# */
/* FILE:	Player.h		DATE: december 2010 Project: Carcassone
/* PURPOSE: That, sir, defines what is a player. I shall not say more.
/* AUTHOR:	Jonas ORINOVSKI, EZJONAS@GMAIL.COM / JORINOVSKI@GMAIL.COM
/* ################################################################# */

#include "stdafx.h"

class Player
{
public:
	Player();
	~ Player();
	
	void SelectTile();
	void PickAndReplaceTile();
	Tile * GetTile(int n);
	string GetName() {return name;}
	static int GetPlayerCount() {return player_count;}
	void SelectNextTile();
	void SelectPrevTile();
	Tile * GetCurrentTile();
protected:
	int current_tile;
	Tile * Tiles[5];
	BoardManager * boardmgr;
	TilePrototyper * protoer;
	string name;
	static int player_count;
	static string default_names[];
};

