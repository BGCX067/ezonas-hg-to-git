#include <iostream>
#include <cstdio>
#define ULONG_BYTES 8
#define ULONG_BITS 64

typedef unsigned int uint;
typedef unsigned long ulong;

#define bitword(n) (1UL << n)

#define FOR(n) for(int i = 0; i < n; ++ i)
using namespace std;