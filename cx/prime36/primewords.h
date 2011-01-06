// #include "mkzr.h"
#include "primecodec.h"

#define co(s) cout << s << endl

#define A 'A'
#define Z 'Z'
#define ASC_OFS 64

#define POWER27 13
#define POWER36 13
#define ASC_OFS_N10 58
#define ASC_OFS_N 48

class workode : public primecodec
{
	char chr36 (ulong n);
	ulong int_pow (ulong n, int p);

	string tumber(ulong ul);


public:
	void show();
	// 	workode();
	// 	~workode();
// protected:
	void pop_list(int r);

};