#include "stdafx.h"



float Application :: smoothstep(float x) {assert(x <= 1.0f && x >= 0.0f); return 3.f*x*x - 2.f*x*x*x; }
float Application :: smoothstep2(float x, float from, float to) { return smoothstep(x)*(from - to) + to; }
float Application :: smoothstep_fast(float x) { return smoothstep(smoothstep(x)); }
float Application :: weight_avg(float x, float goal, float slowdown)
{ return ((x * (slowdown - 1)) + goal) / slowdown; }
float Application :: recoil(float x)
{ return recoil_factor * recoil_c * x * exp(1.f - recoil_c * x); }


/*
First method

void rotate(double heading, double attitude, double bank) {
    // Assuming the angles are in radians.
    double c1 = Math.cos(heading/2);
    double s1 = Math.sin(heading/2);
    double c2 = Math.cos(attitude/2);
    double s2 = Math.sin(attitude/2);
    double c3 = Math.cos(bank/2);
    double s3 = Math.sin(bank/2);
    double c1c2 = c1*c2;
    double s1s2 = s1*s2;
    w =c1c2*c3 - s1s2*s3;
  	x =c1c2*s3 + s1s2*c3;
	y =s1*c2*c3 + c1*s2*s3;
	z =c1*s2*c3 - s1*c2*s3;
  }
Second method

void rotate(double heading, double attitude, double bank) {
    // Assuming the angles are in radians.
    double c1 = Math.cos(heading);
    double s1 = Math.sin(heading);
    double c2 = Math.cos(attitude);
    double s2 = Math.sin(attitude);
    double c3 = Math.cos(bank);
    double s3 = Math.sin(bank);
    w = Math.sqrt(1.0 + c1 * c2 + c1*c3 - s1 * s2 * s3 + c2*c3) / 2.0;
    double w4 = (4.0 * w);
    x = (c2 * s3 + c1 * s3 + s1 * s2 * c3) / w4 ;
    y = (s1 * c2 + s1 * c3 + c1 * s2 * s3) / w4 ;
    z = (-s1 * s3 + c1 * s2 * c3 +s2) / w4 ;
  }
Deri
*/