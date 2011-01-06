// stdafx.h : fichier Include pour les fichiers Include système standard,
// ou les fichiers Include spécifiques aux projets qui sont utilisés fréquemment,
// et sont rarement modifiés
//


// #pragma once

// #ifndef _INCLUDES_H_
// #define _INCLUDES_H_

#ifndef _STD_AFX_H_
#define _STD_AFX_H_
//#include "targetver.h"

#include <stdio.h>
//#include <tchar.h>



// TODO: faites référence ici aux en-têtes supplémentaires nécessaires au programme

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