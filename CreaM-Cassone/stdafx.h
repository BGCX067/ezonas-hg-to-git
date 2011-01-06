// stdafx.h�: fichier Include pour les fichiers Include syst�me standard,
// ou les fichiers Include sp�cifiques aux projets qui sont utilis�s fr�quemment,
// et sont rarement modifi�s
//


// #pragma once

// #ifndef _INCLUDES_H_
// #define _INCLUDES_H_

#ifndef _STD_AFX_H_
#define _STD_AFX_H_
//#include "targetver.h"

#include <stdio.h>
//#include <tchar.h>



// TODO: faites r�f�rence ici aux en-t�tes suppl�mentaires n�cessaires au programme

/* ######################## STD ######################## */
#include <iostream>
#include <string>

#include <fstream>

#include <map>
#include <list>

using namespace std;

/* ##################### SFML ##################### */
//#include "SFML\System.hpp"
#if defined __APPLE__
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#else
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#endif
using namespace sf;


/* ################## PROJECT FILES ################## */
#include "Tile.h"
#include "TilePrototyper.h"

#include "BoardManager.h"
#include "GameManager.h"
//#include "TileFactory.h"

#endif // _STD_AFX_H_