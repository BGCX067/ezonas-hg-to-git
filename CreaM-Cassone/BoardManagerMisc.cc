/* ################################################################# */
/* FILE:	BoardManager.cc -- DATE: december 2010 -- Project: Carcassone
/* PURPOSE: placing and arranging tiles etc, that's a singleton
/* AUTHOR:	Jonas ORINOVSKI, EZJONAS@GMAIL.COM / JORINOVSKI@GMAIL.COM
/* ################################################################# */

#include "stdafx.h"

void BoardManager :: Verbose(TileCellCheck n)
{
	switch(n)
	{
		case Checks:
			cout << "Successfuly put this tile: " << endl;
			CurrentTile -> Show();
			break;
		case ThereAreNoTileAround:
			cout << "No tiles around this cell !" << endl;
			break;
		case ThisIsTheFirstTile:
			cout << "First tile put without question." << endl;
			break;
		case ThereAlreadyIsATileThere:
			cout << "Already a tile there !" << endl;
			break;
		
		case FacesDontMatch:
		case FacesDontMatchSouth:
		case FacesDontMatchEast:
		case FacesDontMatchNorth:
		case FacesDontMatchWest:
		// cout << "This tile's faces doesn't match one or all around this cell ! here is the face that poses problem:" << endl;
		cout << "Faces dont match: ";
		switch(n)
		{
			default: cout << "SEEMS YOU SMOKED RAM AGAIN !" << endl; break;
			case FacesDontMatchSouth: cout << "south !" << endl; break;
			case FacesDontMatchEast:  cout << "east !" << endl; break;
			case FacesDontMatchNorth: cout << "north !" << endl; break;
			case FacesDontMatchWest:  cout << "west !" << endl; break;
		}
		break;
	}
}
void BoardManager :: VerboseGraphic(TileCellCheck n)
{
	if(WillItBlend != 0)
	{
		delete WillItBlend;
	}
	WillItBlend = new String("VINEGAHRRRRRH");
	switch(n)
	{
		case Checks:
			WillItBlend->SetText("This tile can be put here");
			CurrentTile -> Show();
			break;
		case ThereAreNoTileAround:
			WillItBlend->SetText("No tiles around this cell !");
			break;
		case ThisIsTheFirstTile:
			WillItBlend->SetText("First tile put without question.");
			break;
		case ThereAlreadyIsATileThere:
			WillItBlend->SetText("Already a tile there !");
			break;
		
		case FacesDontMatch:
		case FacesDontMatchSouth:
		case FacesDontMatchEast:
		case FacesDontMatchNorth:
		case FacesDontMatchWest:
		// WillItBlend->SetText("This tile's faces doesn't match one or all around this cell ! here is the face that poses problem:");
		WillItBlend->SetText("Faces dont match: ");
		switch(n)
		{
			default: WillItBlend->SetText("SEEMS YOU SMOKED RAM AGAIN !"); break;
			case FacesDontMatchSouth: WillItBlend->SetText("south !"); break;
			case FacesDontMatchEast:  WillItBlend->SetText("east !"); break;
			case FacesDontMatchNorth: WillItBlend->SetText("north !"); break;
			case FacesDontMatchWest:  WillItBlend->SetText("west !"); break;
		}
		break;
	}
}
void BoardManager :: Show()
{
	cout << "Showing the grid: " << endl;

	for (int y = 0; y < board_y; ++y)
	{
		for (int x = 0; x < board_x; ++x)
		{
			if (board[y][x] == NULL)
			{
				cout << '-';
			}
			else
			{
				cout << board[y][x] -> GetSymbol();
			}
		}
		cout << endl;
	}
	cout << endl;
}

