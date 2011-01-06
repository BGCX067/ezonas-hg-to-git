/* ################################################################# */
/* FILE:	Tile.cpp		DATE: december 2010
/* PURPOSE: ctors for each Tile<SYMBOL> class
/* AUTHOR:	Jonas ORINOVSKI, EZJONAS@GMAIL.COM or JORINOVSKI@GMAIL.COM
/* ################################################################# */

#include "stdafx.h"

Tile :: Tile(char _c, Image * imgptr):
	symbol(_c),
	ptrImage(imgptr),
	
	orientation(NORTH),
	
	face_north(LAND),
	face_east(LAND),
	face_south(LAND),
	face_west(LAND),
	
	has_shield(false),
	has_church(false)
{
	switch(_c)
	{             
		case 'A':
			face_south = ROAD;
			has_church = true;		
			break;
			
		case 'B':
			has_church = true;
			break;

			
		case 'C':
			face_north = CITY;
			face_south = CITY;
			face_west = CITY;
			face_east = CITY;
			has_shield = true;
			break;


		case 'D':
			face_north = ROAD;
			face_south = ROAD;
			face_east = CITY;
			break;


		case 'E':
			face_north = CITY;
			break;


		case 'F':
			face_west = CITY;
			face_east = CITY;
			has_shield = true;
			break;


		case 'G':
			face_north = CITY;
			face_south = CITY;
			break;


		case 'H':
			face_west = CITY;
			face_east = CITY;
			break;


		case 'I':
			face_south = CITY;
			face_east = CITY;
			break;


		case 'J':
			face_north = CITY;
			face_south = ROAD;
			face_east = ROAD;
			break;


		case 'K':
			face_north = ROAD;
			face_west = ROAD;
			face_east = CITY;
			break;


		case 'L':
			face_north = ROAD;
			face_south = ROAD;
			face_west = ROAD;
			face_east = CITY;
			break;


		case 'M':
			face_north = CITY;
			face_east = CITY;
			has_shield = true;
			break;


		case 'N':
			face_north = CITY;
			face_east = CITY;
			break;


		case 'O':
			face_north = CITY;
			face_east = CITY;
			face_south = ROAD;
			face_east = ROAD;
			has_shield = true;
			break;


		case 'P':
			face_north = CITY;
			face_east = CITY;
			face_south = ROAD;
			face_east = ROAD;
			break;


		case 'Q':
			face_north = CITY;
			face_west = CITY;
			face_east = CITY;
			has_shield = true;
			break;


		case 'R':
			face_north = CITY;
			face_west = CITY;
			face_east = CITY;
			break;


		case 'S':
			face_north = CITY;
			face_south = ROAD;
			face_west = CITY;
			face_east = CITY;
			has_shield = true;
			break;


		case 'T':
			face_north = CITY;
			face_south = ROAD;
			face_west = CITY;
			face_east = CITY;
			break;


		case 'U':
			face_north = ROAD;
			face_south = ROAD;
			break;


		case 'V':
			face_west = ROAD;
			face_south = ROAD;
			break;


		case 'W':
			face_west = ROAD;
			face_east = ROAD;
			face_south = ROAD;
			break;


		case 'X':
			face_north = ROAD;
			face_south = ROAD;
			face_west = ROAD;
			face_east = ROAD;
			break;


		default:			
			break;


	}		
}
