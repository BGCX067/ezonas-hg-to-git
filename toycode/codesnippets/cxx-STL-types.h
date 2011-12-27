/*-----------------------------------------------------------------------------*/
/* FILE		: cxx-STL-types.h
/* AUTHOR	: Jonas ORINOVSKI "jokoon"
/* DATE		: 2010-12
/* DESCR	: <some standard I decided by myself for STL reccurrent types>
/* CONTACT	: ezjonas@gmail.com jorinovski@gmail.com
/*-----------------------------------------------------------------------------*/

// #include <algorithm>

/*
[itr_]<ls, v, m><str, int, float>
examples:

vec_str
itr_map_float
ls_int
itr_ls_str

*/
#include <string>
/* %%%%%%%%%%%% LIST %%%%%%%%%%%% */
#include <list>
typedef list <string> ls_str;
typedef list <int> ls_int;
typedef list <float> ls_float;

typedef ls_str :: iterator   itr_ls_str;
typedef ls_int :: iterator   itr_ls_int;
typedef ls_float :: iterator itr_ls_float;

/* %%%%%%%%%%%% VECTOR %%%%%%%%%%%% */
#include <vector>
typedef vector <string> vec_str;
typedef vector <int> vec_int;
typedef vector <float> vec_float;

typedef vec_str :: iterator   itr_vec_str;
typedef vec_int :: iterator   itr_vec_int;
typedef vec_float :: iterator itr_vec_float;

/* %%%%%%%%%%%% MAP %%%%%%%%%%%% */
#include <map>
typedef map <string> mstr;
typedef map <int> mint;
typedef map <float> mfloat;

typedef map_str :: iterator   itr_map_str;
typedef map_int :: iterator   itr_map_int;
typedef map_float :: iterator itr_map_float;

