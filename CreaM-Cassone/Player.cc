/* ################################################################# */
/* FILE:	Player.cc -- DATE: december 2010 -- Project: Carcassone
/* PURPOSE: That, sir, defines what is a player. I shall not say more.
/* AUTHOR:	Jonas ORINOVSKI, EZJONAS@GMAIL.COM / JORINOVSKI@GMAIL.COM
/* ################################################################# */

#include "stdafx.h"

Player :: Player():
	boardmgr(BoardManager :: GetSingleton()),
	protoer(TilePrototyper :: GetSingleton()),
	current_tile(0)
{
	Tiles[0] = boardmgr -> PickATile();
	Tiles[1] = boardmgr -> PickATile();
	Tiles[2] = boardmgr -> PickATile();
	Tiles[3] = boardmgr -> PickATile();
	Tiles[4] = boardmgr -> PickATile();
	
	name = default_names[player_count % 4];
	player_count += 1;
	
}

Player :: ~ Player()
{
	delete Tiles[0];
	delete Tiles[1];
	delete Tiles[2];
	delete Tiles[3];
	delete Tiles[4];
}

Tile * Player :: GetTile(int n)
{
	if (n > -1 && n < 6)
		return Tiles[n];
	else
		return Tiles[0];
}

void Player :: PickAndReplaceTile ()
{
	//if (n > -1 && n < 6)
	//{
		Tiles[current_tile] = 
			BoardManager :: GetSingleton() -> PickATile();
		return;
	//}
	//else
		//Tiles[0] = BoardManager :: GetSingleton() -> PickATile();
}

int Player :: player_count = 0;
string Player :: default_names[] = 
{
	"Ruby",
	"TonCafeIlVaEtreFroid",
	"CocoCommeLaNoixDeCoco",
	"IlEtaitUnPetitHommeQuiSAppelaitCacahuette",
	"JabhorreLaNotationHongroise",
	"JaimeBienLesHongroises",
	"AvezVousDejaVu",
	"ParfoisJeMangeDuColinAMidi(LeColinEstAussiUnPoisson!)",
	"Anticonstitutionnellement",
	"JaiUnCorpsBeauJeSuisUnCorbeau"
};

void Player :: SelectNextTile()
{
	current_tile = (current_tile + 1) % 5;
	cout << "current tile: " << current_tile + 1 << " " 
		<< Tiles[current_tile] -> GetSymbol()
		<< endl;
}
void Player :: SelectPrevTile()
{
	if (current_tile == 0) current_tile = 4;
	else current_tile = (current_tile - 1) % 5;
	cout << "current tile: " << current_tile + 1 << " " 
		<< Tiles[current_tile] -> GetSymbol()
		<< endl;
}

Tile * Player :: GetCurrentTile()
{
	return Tiles[current_tile];
}
