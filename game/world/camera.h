#include <string>
#include <iostream>
#include <vector>
#include <optional>
#include "math.h"

#include <bits/stdc++.h>

#include "../config.h"
#include "../common/types.h"

using namespace std; 

#ifndef CAMERA_H
#define CAMERA_H

class Camera {
public:
    float x, y, z;
    float angle_x, angle_y;
    float last_angle_x, last_angle_y;
    
    float angle_x_sin, angle_x_cos;
    float angle_y_sin, angle_y_cos;

    float fov;
    float halfFovRad;
    float cosHalfFov;

    const int walk_fov = 90;
    const int run_fov = 100;

    float f_h, f_v;
    int near_plane;

    // effects
    bool on_shaking = false;
    float shaking_angle = 0;
    float shaking_angle_sin = 0;
    float shaking_speed = 5;

    const float shaking_mult = 5;

    const int walk_shaking_speed = 5;
    const int run_shaking_speed = 10;
    const int sneak_shaking_speed = 3;

    // methods
    Camera(void);

    void set_fov(float new_fov);

    bool face_visible(RawFace3d& face);
    inline bool triangle_in_fov(const vec3& p1, const vec3& p2, const vec3& p3);

    vec3 point_rotation(vec3& point, bool add_camera_pos);
    vector<vec3> face_clipping(const vec3& point1, const vec3& point2, const vec3& point3);

    vec2 point_projection(vec3& point);
    
    optional<ProjectedFace2d> full_face_projection(RawFace3d& face);
    optional<ProjectedPoint2d> full_point_projection(RawPoint3d& point); 

    vec3 line_clipping(vec3& start, vec3& end);
    optional<ProjectedLine2d> full_line_projection(RawLine3d& line); 

    void update_shaking(float dt);
    void update(float dt);
};


#endif