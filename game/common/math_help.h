#include <iostream>
#include <random>

#include "types.h"

#ifndef MATHHELP_H
#define MATHHELP_H

using namespace std;


int randint(int start, int end);


inline float triangle_area(float x1, float y1, float x2, float y2, float x3, float y3);

bool point_in_triangle(float x, float y, const vec2& p1, const vec2& p2, const vec2& p3);


#endif