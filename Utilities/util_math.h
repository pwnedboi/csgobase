/*
 *  util_math.h
 */
#pragma once

float random_float(float min, float max);
inline void sin_cos(float radians, float* sine, float* cosine);

void angle_vectors(const QAngle& angles, Vector& forward);
void angle_vectors(const QAngle& angles, Vector& forward, Vector& right, Vector& up);
void vector_angles(const Vector &forward, QAngle &angles);

void normalize_angle(float& angle);
void normalize_angles(QAngle& angle);
void normalize_vectors(Vector& vecIn);

void clamp_yaw(float& val);
void clamp_angles(QAngle& angle);
void clamp_moves(float& forward, float& side, float& up);

inline float dot_product(Vector &v1, const float* v2);
void vector_transform(Vector &in1, const matrix3x4_t& in2, Vector &out);
void transform_matrix(Vector input, matrix3x4_t matrix, Vector& output);

void fix_movement(QAngle& ang, CUserCmd* cmd);
void correct_movement(QAngle old_angles, CUserCmd* cmd, float old_forward, float old_sidemove);

QAngle calculate_angle(Vector src, Vector dst);
QAngle angle_between(const Vector& a, const Vector& b);

float get_fov(const QAngle &viewAngle, const QAngle &aimAngle);
float get_distance(Vector a, Vector b);

float lerp(float a, float b, float f);
Vector lerp(Vector start, Vector end, float percent);

Vector get_hitbox_position(C_BasePlayer* player, int Hitbox);
Vector calculate_hitbox(matrix3x4_t matrix[128], mstudiobbox_t* hitbox, Vector offset = Vector(0,0,0));
mstudiohitboxset_t* get_hitbox_handle(C_BaseEntity* ent, matrix3x4_t matrix[128]);


template<class T, class U>
T clamp(T in, U low, U high)
{
    if (in <= low)
        return low;
    
    if (in >= high)
        return high;
    
    return in;
}
