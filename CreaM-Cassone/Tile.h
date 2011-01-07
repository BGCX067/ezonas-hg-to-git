/* ################################################################# */
/* FILE:	Tile.h		DATE: december 2010
/* PURPOSE: Tile superclass and all its subclasses (EDIT: just tile now)
/* AUTHOR:	Jonas ORINOVSKI, EZJONAS@GMAIL.COM or JORINOVSKI@GMAIL.COM
/* ################################################################# */

#include "stdafx.h"

enum orientation_t
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

enum face_t
{
	LAND,
	ROAD,
	CITY
};

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
public:
	char GetSymbol() {return symbol;}
	int GetOrientation() {return orientation;}
	face_t GetFace(orientation_t _orient);
	// Image * getImgptr() {return ptrImage;}
	Image * getImgptr() {return ptrImage;}
	virtual Tile * Clone() {return new Tile(*this);} /* prototype design pattern !*/
	void Show();
	Tile(char _c, Image * imgptr);
	
	void SetPosition(int _x, int _y)
	{
		if (_x < 0 || _y < 0 || _x > 71 || _y > 71)
		{
			cout << "bad coordinates !" << endl;
			return;
		}
		x = _x;
		y = _y;
	}
	
	
	void Turn(orientation_t _orientation)
	{
		orientation = _orientation;
	}
	
};
