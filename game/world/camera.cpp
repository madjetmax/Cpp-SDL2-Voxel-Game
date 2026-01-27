#include "camera.h"

Camera::Camera() {
    x = 0;
    y = 0;
    z = -200;

    angle_x = 0;
    angle_y = 0;

    last_angle_x = 1;
    last_angle_y = 1;

    fov = 90;

    halfFovRad = (fov + 40) * 0.5f * (M_PI / 180.0f);
    cosHalfFov = cos(halfFovRad);

    // for projection
    float fov_horizontal = (fov + 40) * (M_PI / 180.0f); 
	f_h = (WINDOW_W / 2) / tan(fov_horizontal / 2.0f);
	f_v = (WINDOW_W / 2) / tan(fov_horizontal / 2.0f);

    near_plane = 5;
}

void Camera::set_fov(float new_fov) {
    fov = new_fov;
    // for projection
    float fov_horizontal = (fov + 40) * (M_PI / 180.0f); 
	f_h = (WINDOW_W / 2) / tan(fov_horizontal / 2.0f);
	f_v = (WINDOW_W / 2) / tan(fov_horizontal / 2.0f);

    // fot frustum culling
    halfFovRad = (fov + 40) * 0.5f * (M_PI / 180.0f);
    cosHalfFov = cos(halfFovRad);
}


vec3 Camera::point_rotation(vec3& point, bool add_camera_pos) {
    float point_x = point.x;
    float point_y = -point.y + shaking_mult * shaking_angle_sin;
    float point_z = point.z;

    if (add_camera_pos) {
        point_x -= x;
        point_y += y;
        point_z -= z;
    }

    // around y (horizontal)
    float y = point_y;

    float res_x = point_x * angle_y_cos + point_z * angle_y_sin;
    float z = -point_x * angle_y_sin + point_z * angle_y_cos;
    
    // around x (vertical)
    float res_y = y * angle_x_cos - z * angle_x_sin;
    float res_z = y * angle_x_sin + z * angle_x_cos;
    
    
    return {res_x, res_y, res_z};
}


inline vec3 intersect_near_plane(const vec3& p_in, const vec3& p_out, float near_plane) {
    float t = (near_plane - p_in.z) / (p_out.z - p_in.z);
    return {
        p_in.x + t * (p_out.x - p_in.x),
        p_in.y + t * (p_out.y - p_in.y),
        near_plane
    };
}

vector<vec3> Camera::face_clipping(const vec3& p1, const vec3& p2, const vec3& p3) {
    // Preallocate result with up to 4 points
    vector<vec3> points;
    points.reserve(4);

    // Count how many points are in front
    bool in1 = p1.z > near_plane;
    bool in2 = p2.z > near_plane;
    bool in3 = p3.z > near_plane;
    int inside_count = in1 + in2 + in3;

    // Case 1: all behind
    if (inside_count == 0)
        return {};

    // Case 2: all in front
    if (inside_count == 3)
        return { p1, p2, p3 };

    // Case 3: one or two points inside
    // To simplify logic, collect all 3 in arrays
    const vec3* pts[3] = { &p1, &p2, &p3 };
    const bool inside[3] = { in1, in2, in3 };

    if (inside_count == 1) {
        // One inside → 4 vertices (quad)
        for (int i = 0; i < 3; ++i) {
            if (inside[i]) {
                points.push_back(*pts[i]);
                for (int j = 0; j < 3; ++j) {
                    if (!inside[j])
                        points.push_back(intersect_near_plane(*pts[i], *pts[j], near_plane));
                }
                break;
            }
        }
    } else if (inside_count == 2) {
        // Two inside → 3 vertices (triangle)
        int out_index = (!in1) ? 0 : (!in2 ? 1 : 2);
        const vec3& p_out = *pts[out_index];

        for (int i = 0; i < 3; ++i) {
            if (inside[i]) {
                points.push_back(*pts[i]);
                points.push_back(intersect_near_plane(*pts[i], p_out, near_plane));
            }
        }
    }

    return points;
}

vec2 Camera::point_projection(vec3& point) {
    float point_x = point.x;
    float point_y = point.y;
    float point_z = point.z;

    float draw_x = float(WINDOW_W / 2.0f) + (point_x * f_h) / point_z;
    float draw_y = float(WINDOW_H / 2.0f) + (point_y * f_v) / point_z;

    return {draw_x, draw_y};
}

bool Camera::face_visible(RawFace3d& face) {
    // * ange y (horizontal)
    bool visible_angle_y = false;
    if (face.visiblity_angle_y_add == 180) {
        visible_angle_y = true;
    } else {
        int face_center_x = (face.point1.x + face.point2.x + face.point3.x) / 3;
        int face_center_z = (face.point1.z + face.point2.z + face.point3.z) / 3;

        int dist_x = x - face_center_x;
        int dist_z = z - face_center_z;

        // get angle from dist
        float radians_y = atan2(dist_x, dist_z);
        int face_angle_y = radians_y * (180.0f / M_PI) + 180;

        // get start and end angle
        int start_angle = face.visiblity_angle_y - face.visiblity_angle_y_add;
        int end_angle = face.visiblity_angle_y + face.visiblity_angle_y_add;
        
        // set visibility
        if (start_angle < 0) {
            if (face_angle_y == clamp(face_angle_y, 360 + start_angle, 360)) {
                visible_angle_y = true;
            }
        }
        if (end_angle > 360) {
            if (face_angle_y == clamp(face_angle_y, 0, end_angle - 360)) {
                visible_angle_y = true;
            }
        } else {
            if (face_angle_y == clamp(face_angle_y, start_angle, end_angle)) {
                visible_angle_y = true;
            }
        }

        if (!visible_angle_y) {
            return false;
        }
    
    }

    // * ange x (vertical)
    bool visible_angle_x = false;

    if (face.visiblity_angle_x_add == 180) {
        visible_angle_x = true;
    } else {
        int face_center_y = (face.point1.y + face.point2.y + face.point3.y) / 3;
        int face_center_z = (face.point1.z + face.point2.z + face.point3.z) / 3;

        int dist_y = y - face_center_y;
        int dist_z = z - face_center_z;

        // get angle from dist
        float radians_x = atan2(dist_y, dist_z);
        int face_angle_x = radians_x * (180.0f / M_PI) + 180;
        
        // get start and end angle
        int start_angle = face.visiblity_angle_x - face.visiblity_angle_x_add;
        int end_angle = face.visiblity_angle_x + face.visiblity_angle_x_add;
        
        // set visibility
        if (start_angle < 0) {
            if (face_angle_x == clamp(face_angle_x, 360 + start_angle, 360)) {
                visible_angle_x = true;
            }
        }
        if (end_angle > 360) {
            if (face_angle_x == clamp(face_angle_x, 0, end_angle - 360)) {
                visible_angle_x = true;
            }
        } else {
            if (face_angle_x == clamp(face_angle_x, start_angle, end_angle)) {
                visible_angle_x = true;
            }
        }

        if (!visible_angle_x) {
            return false;
        }
    }

    return (visible_angle_y && visible_angle_x);
}

// Fast FOV check using dot product instead of acos
inline bool point_in_view(const vec3& point, float cosHalfFov)
{
    float vx = point.x;
    float vz = -point.z; // flipped so points in front have positive Z in this space

    float lenSq = vx * vx + vz * vz;
    if (lenSq == 0.0f)
        return true; // Point at camera

    // Normalize only vz / sqrt(lenSq) is used, so compute reciprocal sqrt once
    float invLen = 1.0f / std::sqrt(lenSq);
    float vzNorm = vz * invLen;

    float dot = vzNorm * -1.0f;

    // Check if within half-FOV using precomputed cos
    return dot >= cosHalfFov;
}

// Optimized triangle FOV check
inline bool Camera::triangle_in_fov(const vec3& p1, const vec3& p2, const vec3& p3)
{
    return (
        point_in_view(p1, cosHalfFov) ||
        point_in_view(p2, cosHalfFov) ||
        point_in_view(p3, cosHalfFov)
    );
}

optional<ProjectedFace2d> Camera::full_face_projection(RawFace3d& face) {
    // rotate
    vec3 rotated_point1 = point_rotation(face.point1, true);
    vec3 rotated_point2 = point_rotation(face.point2, true);
    vec3 rotated_point3 = point_rotation(face.point3, true);

    // all points are in front
    if (rotated_point1.z > near_plane && rotated_point2.z > near_plane && rotated_point3.z > near_plane) {
        // chekc frustum culling
        if (!triangle_in_fov(rotated_point1, rotated_point2, rotated_point3)) {
            return nullopt;
        }
        // check face visible on anlge
        if (!face_visible(face)) {
            return nullopt;
        }
        
        // project
        vec2 projected_point1 = point_projection(rotated_point1);
        vec2 projected_point2 = point_projection(rotated_point2);
        vec2 projected_point3 = point_projection(rotated_point3);

        ProjectedFace2d projected_face = {
            projected_point1, 
            projected_point2,
            projected_point3,
            {},
            false,
            // rotated point for sorting
            rotated_point1,
            rotated_point2,
            rotated_point3,
            
            // texture
            face.t_id,//face.t_name,
            face.t_pos1, face.t_pos2, face.t_pos3,
            
            face.normal,
            
            // color 
            face.point1_color, face.point2_color, face.point3_color,
            face.sun_light,
            face.light,

            // block and chunk data
            face.block_x, face.block_y, face.block_z,
            face.chunk_ind,
        };

        return projected_face;
    } 

    // check clipping or return null
    else {
        // all poins behind
        if (rotated_point1.z <= near_plane && rotated_point2.z <= near_plane && rotated_point3.z <= near_plane) {
            return nullopt;
        } 

        // chekc frustum culling
        if (!triangle_in_fov(rotated_point1, rotated_point2, rotated_point3)) {
            return nullopt;
        }

        // check face visible on anlge
        if (!face_visible(face)) {
            return nullopt;
        }

        // clip face
        vector<vec3> points = face_clipping(rotated_point1, rotated_point2, rotated_point3);
        size_t points_count = points.size();

        // * project

        // face with 3 points
        if (points_count == 3) {
            vec2 projected_point1 = point_projection(points[0]);
            vec2 projected_point2 = point_projection(points[1]);
            vec2 projected_point3 = point_projection(points[2]);

            ProjectedFace2d projected_face = {
                projected_point1, 
                projected_point2,
                projected_point3,
                {},
                false,
                // rotated point for sorting
                rotated_point1,
                rotated_point2,
                rotated_point3,
                // texture
                face.t_id,//face.t_name,
                face.t_pos1, face.t_pos2, face.t_pos3,

                face.normal,

                // color 
                face.point1_color, face.point2_color, face.point3_color,
                face.sun_light,
                face.light,

                // block and chunk data
                face.block_x, face.block_y, face.block_z,
                face.chunk_ind,
            };

            return projected_face;
        }
        // face with 4 points
        vec2 projected_point1 = point_projection(points[0]);
        vec2 projected_point2 = point_projection(points[1]);
        vec2 projected_point3 = point_projection(points[2]);
        vec2 projected_point4 = point_projection(points[3]);

        ProjectedFace2d projected_face = {
            projected_point1, 
            projected_point2,
            projected_point3,
            projected_point4,
            true,
            // rotated point for sorting
            rotated_point1,
            rotated_point2,
            rotated_point3,
            // texture
            face.t_id,//face.t_name,
            face.t_pos1, face.t_pos2, face.t_pos3,

            face.normal,

            // color 
            face.point1_color, face.point2_color, face.point3_color,
            face.sun_light,
            face.light,

            // block and chunk data
            face.block_x, face.block_y, face.block_z,
            face.chunk_ind,
        };

        return projected_face;
    }
}

optional<ProjectedPoint2d> Camera::full_point_projection(RawPoint3d& point) {
    // rotate
    vec3 rotated_point = point_rotation(point.pos, true);

    // check if behind
    if (rotated_point.z <= near_plane) {
        return nullopt;
    }

    // project
    vec2 projected_point = point_projection(rotated_point);

    ProjectedPoint2d projected_point_2d = {
        projected_point,
        rotated_point
    };
    return projected_point_2d;
}

vec3 Camera::line_clipping(vec3& start, vec3& end) {
    float t = (near_plane - start.z) / (end.z - start.z);
    vec3 clipped_start;
    clipped_start.x = start.x + t * (end.x - start.x);
    clipped_start.y = start.y + t * (end.y - start.y);
    clipped_start.z = near_plane;

    return clipped_start;
}

optional<ProjectedLine2d> Camera::full_line_projection(RawLine3d& line) {
    // rotate
    vec3 rotated_point1 = point_rotation(line.start, true);
    vec3 rotated_point2 = point_rotation(line.end, true);

    // * clipping
    // all behind
    if (rotated_point1.z <= near_plane && rotated_point2.z <= near_plane) {
        return nullopt;
    }

    // start behind
    if (rotated_point1.z <= near_plane) {
        rotated_point1 = line_clipping(rotated_point1, rotated_point2);
    }
    // end behind
    if (rotated_point2.z <= near_plane) {
        rotated_point2 = line_clipping(rotated_point2, rotated_point1);
    }
    // all visible
    // project
    vec2 projected_point1 = point_projection(rotated_point1);
    vec2 projected_point2 = point_projection(rotated_point2);

    ProjectedLine2d projected_line_2d = {
        projected_point1,
        projected_point2,

        rotated_point1,
        rotated_point2,

        line.color,
    };
    return projected_line_2d;
}

void Camera::update_shaking(float dt) {
    if (!on_shaking) { 
        return;
    }
    // increase and limit shaking angle
    shaking_angle += shaking_speed * dt;
    if (shaking_angle > 360) {
        shaking_angle -= 360;
    }
    // update angle sin and cos
    shaking_angle_sin = sin(shaking_angle * (M_PI / 180));

    
}

void Camera::update(float dt) {
    // * update angles sin and cos
    // angle x
    if (angle_x != last_angle_x) {
        angle_x_sin = sin(angle_x * (M_PI / 180));
        angle_x_cos = cos(angle_x * (M_PI / 180));

        last_angle_x = angle_x;
    }

    // angle y
    if (angle_y != last_angle_y) {
        angle_y_sin = sin(angle_y * (M_PI / 180));
        angle_y_cos = cos(angle_y * (M_PI / 180));

        last_angle_y = angle_y;
    }

    update_shaking(dt);
}