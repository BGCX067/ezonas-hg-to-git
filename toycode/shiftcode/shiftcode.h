#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;



// alphabet: A-Z ,.:; ?!
//const char * ab =
const static string abt =
"\
0123456789\
ABCDEFGHIJKLMNOPQRSTUVWXYZ\
.,:;!?'\"\
-=+*\
()[]{}<>\
~@#$%^&/\\| ";
const int sz = abt.size();
#define END sz

int roll(char, char);
int rollout(int, int);
string decode(int size, int * from);
int num (char c);
char chur (int n);
void show_code(int * a, int szz);
