/* ################################################################# */
/* FILE:	Tile.cpp		DATE: december 2010
/* PURPOSE: ctors for each Tile<SYMBOL> class
/* AUTHOR:	Jonas ORINOVSKI, EZJONAS@GMAIL.COM or JORINOVSKI@GMAIL.COM
/* ################################################################# */

#include "stdafx.h"

face_t Tile :: GetFace(orientation_t _orient)
{
	switch(_orient)
	{
		// case NORTH: return (face_north + orientation) % 4;
		// case EAST: return (face_east + orientation) % 4;
		// case SOUTH: return (face_south + orientation) % 4;
		// case WEST: return (face_west + orientation) % 4;
		case NORTH: return face_north;
		case EAST:  return face_east;
		case SOUTH: return face_south;
		case WEST:  return face_west;
		// default: return -1;
	}
}
void Tile :: TurnClockWise()
{
	orientation = (orientation_t)((orientation + 1) % 4);

	// we rotate all the faces
	face_t tmp = face_north;
	face_north = face_west;
	face_west = face_south;
	face_south = face_east;
	face_east = tmp;
}
char Tile :: GetSymbol() { return symbol; }
int Tile :: GetOrientation() { return orientation; }
Image * Tile :: getImgptr() { return ptrImage; }
Tile * Tile :: Clone() { return new Tile(*this); } /* prototype design pattern !*/
void Tile :: SetOrientation(orientation_t _orientation) {orientation = _orientation;}

void Tile :: SetPosition(int _x, int _y)
{
	if (_x < 0 || _y < 0 || _x > 71 || _y > 71)
	{
		cout << "bad coordinates !" << endl;
		return;
	}
	x = _x;
	y = _y;
}


Tile :: Tile(char _c, Image * imgptr):
	symbol(_c),
	ptrImage(imgptr),
	
	orientation(NORTH),
	
	// face_north(LAND),
	// face_east(LAND),
	// face_south(LAND),
	// face_west(LAND),
	
	has_shield(false),
	has_church(false)
{
	face_north = LAND;
	face_east = LAND;
	face_south = LAND;
	face_west = LAND;

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
		face_west = CITY;
		has_shield = true;
		break;


	case 'N':
		face_north = CITY;
		face_west = CITY;
		break;


	case 'O':
		face_north = CITY;
		face_west = CITY;
		face_south = ROAD;
		face_east = ROAD;
		has_shield = true;
		break;


	case 'P':
		face_north = CITY;
		face_west = CITY;
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
		cout << "houston, this tile has a problem: " << _c << endl;
		break;
	}
}


void Tile :: Show()
{
	string str[3] =
	{
		"LAND",
		"ROAD",
		"CITY"
	};
	cout << symbol << endl;
	//cout << "\t" << str[face_north] << endl;
	//cout << str[face_west] << "\t\t" << str[face_east] << endl;
	//cout << "\t" << str[face_south] << endl;
}
