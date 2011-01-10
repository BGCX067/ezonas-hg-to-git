/* ################################################################# */
/* FILE:	Tile.h		DATE: december 2010
/* PURPOSE: Tile superclass and all its subclasses (EDIT: just tile now)
/* AUTHOR:	Jonas ORINOVSKI, EZJONAS@GMAIL.COM or JORINOVSKI@GMAIL.COM
/* ################################################################# */

#include "stdafx.h"

enum orientation_t {NORTH,EAST,SOUTH,WEST};
enum face_t {LAND,ROAD,CITY};

/* %%%%%%%%%%%%%%%% Tile %%%%%%%%%%%%%%%% */
class Tile
{
protected:
	char symbol;
	Image * ptrImage;
	orientation_t orientation;
	face_t face_north, face_east, face_south, face_west;
	int x, y;
	bool has_shield, has_church;
	
	//int Players[][];
public:
	char GetSymbol();
	int GetOrientation();
	face_t GetFace(orientation_t _orient);
	Image * getImgptr();
	virtual Tile * Clone();
	void Show();
	Tile(char _c, Image * imgptr);
	void SetPosition(int _x, int _y);
	void SetOrientation(orientation_t _orientation);
	void TurnClockWise();
	
};
