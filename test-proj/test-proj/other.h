#include "stdafx.h"

string get_scalar(const ynode & node)			;
void print_pair(const ynode & node)				;
void showtype(const YAML::Node & n)				;
map_type get_map_type(const ynode & node)		;
void print_scalar(const ynode & node)			;
void shownested_map(nested_map & categories)	;
void print_pair(YAML::Iterator & iter)			;
