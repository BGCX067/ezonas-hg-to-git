#include <iostream>
#include <cstdio>
using namespace std;

// #define ULONG_BYTES 8
// #define ULONG_BITS 64
// 
// #define UINT_BYTES 4
// #define UINT_BITS 32

typedef unsigned int uint;
typedef unsigned int intg;
typedef unsigned long ulong;
typedef std::string str;

#define INTG_BYTES 4
#define INTG_BITS 32
#define str string

#define bitword(n) (1UL << n)

#define FOR(n) for(int i = 0; i < n; ++ i)
#define FORG(m, n) for(int i = m; i < n; ++ i)
#define FOR_ITR(type, v) for(vector<type>::iterator itr = v.begin(); itr != v.end(); ++ itr)

#define pr(s) cout << s << endl
#define pvar(s1, s2) cout << s1 << " = " << s2 << endl

#define pr_(s) cout << s << " "
#define prln cout << endl
#define prx(n) printf("0x%X\n", n)
#define p_ cout << " "