// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#define err(s) assert(0 && s)

#include <fstream>
#include <string>
using namespace std;
#include "yaml-cpp\yaml.h"

typedef YAML::Node ynode;
typedef map<string, map <string, string>> nested_map;

enum map_type { none, pairtype, mapping };
#include "other.h"



