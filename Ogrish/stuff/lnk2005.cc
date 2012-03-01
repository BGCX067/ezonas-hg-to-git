I omitted `#include "stdafx.h` in each file.
//stdafx.h (precompiled headers)

    #include a.h
    #include b.h
	class stuff;
	stuff * s
// a.h

    class thing{float f; void fun()};
// a.cc

    void thing::fun(){}
    thing::thing():
    	f(b->f) {} // lnk 2005 linking error
// b.h

    struct stuff
    {
    float f;
    thing * t;
    };
// b.cc

    stuff::stuff(): f(3.4) { t = new thing; }
//main.cc

    int main()
    {
    	s = new stuff;
    	s -> fun();
    }
	
I'm getting