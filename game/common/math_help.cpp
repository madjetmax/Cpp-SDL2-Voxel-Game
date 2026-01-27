#include "math_help.h"



int randint(int start, int end) {
    static std::mt19937 gen(std::random_device{}());  // create once
    std::uniform_int_distribution<> dis(start, end);
    return dis(gen);
}

inline float triangle_area(float x1, float y1, float x2, float y2, float x3, float y3) {
    return std::abs((x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2)) / 2.0f);
}

bool point_in_triangle(float x, float y, const vec2& p1, const vec2& p2, const vec2& p3) {
    float A  = triangle_area(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
    float A1 = triangle_area(x, y, p2.x, p2.y, p3.x, p3.y);
    float A2 = triangle_area(p1.x, p1.y, x, y, p3.x, p3.y);
    float A3 = triangle_area(p1.x, p1.y, p2.x, p2.y, x, y);

    // Use epsilon for floating-point tolerance
    const float EPS = 0.5f; // you can tweak this (try 0.1–1.0 depending on scale)
    return std::abs(A - (A1 + A2 + A3)) < EPS;
}