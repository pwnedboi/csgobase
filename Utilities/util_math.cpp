/*      math.cpp
 *
 *
 *
 */

#include "main.h"

float random_float(float min, float max)
{
    srand((int)(time(0) + (getpid() * clock())));
    float scale = rand() / (float)RAND_MAX; /* [0, 1.0] */
    return min + scale * (max - min);       /* [min, max] */
}

inline void sin_cos(float radians, float* sine, float* cosine)
{
    double __cosr, __sinr;
    __asm ("fsincos" : "=t" (__cosr), "=u" (__sinr) : "0" (radians));
    
    *sine   = __sinr;
    *cosine = __cosr;
}

void angle_vectors(const QAngle& angles, Vector& forward)
{
    Assert(s_bMathlibInitialized);
    Assert(forward);
    
    float sp, sy, cp, cy;
    
    sin_cos(DEG2RAD(angles[PITCH]), &sp, &cp);
    sin_cos(DEG2RAD(angles[YAW]),   &sy, &cy);
    
    forward.x = cp * cy;
    forward.y = cp * sy;
    forward.z = -sp;
}

void angle_vectors(const QAngle& angles, Vector& forward, Vector& right, Vector& up)
{
    float sp, sy, sr, cp, cy, cr;
    
    sin_cos(DEG2RAD(angles.x), &sp, &cp);
    sin_cos(DEG2RAD(angles.y), &sy, &cy);
    sin_cos(DEG2RAD(angles.z), &sr, &cr);
    
    forward.x = cp * cy;
    forward.y = cp * sy;
    forward.z = -sp;
    
    right.x = -1 * sr * sp * cy + -1 * cr * -sy;
    right.y = -1 * sr * sp * sy + -1 * cr * cy;
    right.z = -1 * sr * cp;
    
    up.x = cr * sp * cy + -sr * -sy;
    up.y = cr * sp * sy + -sr * cy;
    up.z = cr * cp;
}

void vector_angles(const Vector& forward, QAngle& angles)
{
    if (forward[1] == 0.0f && forward[0] == 0.0f)
    {
        angles[0] = (forward[2] > 0.0f) ? 270.0f : 90.0f; // Pitch (up/down)
        angles[1] = 0.0f;  //yaw left/right
    }
    else
    {
        angles[0] = atan2(-forward[2], forward.Length2D()) * -180 / M_PI;
        angles[1] = atan2(forward[1], forward[0]) * 180 / M_PI;
        
        if (angles[1] > 90)
            angles[1] -= 180;
        else if (angles[1] < 90)
            angles[1] += 180;
        else if (angles[1] == 90)
            angles[1] = 0;
    }
    
    angles[2] = 0.0f;
}

void normalize_angles(QAngle& angle)
{
    while (angle.x > 89.0f)
        angle.x -= 180.f;
    
    while (angle.x < -89.0f)
        angle.x += 180.f;
    
    while (angle.y > 180.f)
        angle.y -= 360.f;
    
    while (angle.y < -180.f)
        angle.y += 360.f;
}

void normalize_angle(float& angle)
{
    while (angle > 180.f)
        angle -= 360.f;
    
    while (angle < -180.f)
        angle += 360.f;
}

void normalize_vectors(Vector& vec)
{
    for (int axis = 0; axis < 3; ++axis)
    {
        while (vec[axis] > 180.f)
            vec[axis] -= 360.f;
        
        while (vec[axis] < -180.f)
            vec[axis] += 360.f;
        
    }
    
    vec[2] = 0.f;
}

void clamp_yaw(float& val)
{
    while(val > 180)
        val -= 360;
    while(val < -180)
        val += 360;
}

void clamp_angles(QAngle& angle)
{
    if (angle.x > 89.0f)
        angle.x = 89.0f;
    if (angle.x < -89.0f)
        angle.x = -89.0f;
    if (angle.y > 180.0f)
        angle.y -= 360;
    if (angle.y < -180.0f)
        angle.y += 360;
    
    angle.z = 0;
}

void clamp_moves(float& flForward, float& flSide, float& flUp)
{
    if(flForward > 450)
        flForward = 450;
    
    if(flSide > 450)
        flSide = 450;
    
    if(flUp > 450)
        flUp = 450;
    
    if(flForward < -450)
        flForward = -450;
    
    if(flSide < -450)
        flSide = -450;
    
    if(flUp < -450)
        flUp = -450;
}

inline float dot_product(Vector &v1, const float* v2)
{
    return v1.x * v2[0] + v1.y * v2[1] + v1.z * v2[2];
}

void vector_transform(Vector &in1, const matrix3x4_t& in2, Vector &out)
{
    out.x = dot_product(in1, in2[0]) + in2[0][3];
    out.y = dot_product(in1, in2[1]) + in2[1][3];
    out.z = dot_product(in1, in2[2]) + in2[2][3];
}

void transform_matrix(Vector input, matrix3x4_t matrix, Vector& output)
{
    output.x = input.dot(matrix[0]) + matrix[0][3];
    output.y = input.dot(matrix[1]) + matrix[1][3];
    output.z = input.dot(matrix[2]) + matrix[2][3];
}

void fix_movement(QAngle& oang, CUserCmd* pCmd)
{
    Vector vMove(pCmd->forwardmove, pCmd->sidemove, pCmd->upmove);
    float flSpeed = sqrt(vMove.x * vMove.x + vMove.y * vMove.y), flYaw;
    QAngle vMove2;
    vector_angles(vMove, vMove2);
    
    flYaw = DEG2RAD(pCmd->viewangles.y - oang.y + vMove2.y);
    pCmd->forwardmove = cos(flYaw) * flSpeed;
    pCmd->sidemove = sin(flYaw) * flSpeed;
    
    if (pCmd->viewangles.x < -90.f || pCmd->viewangles.x > 90.f)
        pCmd->forwardmove = -pCmd->forwardmove;
}

void correct_movement(QAngle old_angles, CUserCmd* cmd, float old_forward, float old_sidemove)
{
    // side/forward move correction
    float deltaView;
    float f1;
    float f2;
    
    if (old_angles.y < 0.f)
        f1 = 360.0f + old_angles.y;
    else
        f1 = old_angles.y;
    
    if (cmd->viewangles.y < 0.0f)
        f2 = 360.0f + cmd->viewangles.y;
    else
        f2 = cmd->viewangles.y;
    
    if (f2 < f1)
        deltaView = abs(f2 - f1);
    else
        deltaView = 360.0f - abs(f1 - f2);
    
    deltaView = 360.0f - deltaView;
    
    cmd->forwardmove = cos(DEG2RAD(deltaView)) * old_forward + cos(DEG2RAD(deltaView + 90.f)) * old_sidemove;
    cmd->sidemove    = sin(DEG2RAD(deltaView)) * old_forward + sin(DEG2RAD(deltaView + 90.f)) * old_sidemove;
}

QAngle calculate_angle(Vector src, Vector dst)
{
    QAngle angles;
    Vector delta = src - dst;
    
    vector_angles(delta, angles);
    delta.Normalize();
    
    return angles;
}

/*
 *  angle_between
 *  Returns the angle between 2 points
 */
QAngle angle_between(const Vector& a, const Vector& b)
{
    QAngle angles;
    
    float distanceX = (b.x - a.x);
    float distanceY = (b.y - a.y);
    float distanceZ = (b.z - a.z);
    
    float hipotenuseXY = sqrtf(distanceX * distanceX + distanceY * distanceY);
    
    angles.x = atanf(distanceZ / hipotenuseXY) * (180.0f / M_PI_F) * -1.0f;
    angles.y = atanf(distanceY / distanceX) * (180.0f / M_PI_F);
    
    if (distanceX < 0)
        angles.y += 180.0f;
    
    angles.z = 0;
    
    return angles;
}

float get_fov(const QAngle& viewAngle, const QAngle& aimAngle)
{
    QAngle delta = aimAngle - viewAngle;
    normalize_angles(delta);
    return sqrtf(powf(delta.x, 2.0f) + powf(delta.y, 2.0f));
}

/*
 *  get_distance
 *  Returns the distance between 2 points in meters
 */
float get_distance(Vector a, Vector b)
{
    return sqrt( pow( a.x - b.x, 2 ) + pow( a.y - b.y, 2 ) + pow( a.z - b.z, 2 ) ) * 0.0254f;
}

float lerp(float a, float b, float p)
{
    return (a + p * (b - a));
}

Vector lerp(Vector start, Vector end, float percent)
{
    return (start + percent * (end - start));
}

mstudiohitboxset_t* get_hitbox_handle(C_BaseEntity* ent, matrix3x4_t matrix[128])
{
    if (!ent->SetupBones(matrix, 128, 0x100, pGlobals->curtime))
        return nullptr;
    
    auto model = ent->GetModel();
    
    if (!model)
        return nullptr;
    
    auto studio = pModelInfo->GetStudioModel(model);
    
    if (!studio)
        return nullptr;
    
    mstudiohitboxset_t* hitbox_set = studio->pHitboxSet(ent->get_hitbox_set());
    
    return hitbox_set;
}

Vector get_hitbox_position(C_BasePlayer* player, int Hitbox)
{
    matrix3x4_t matrix[128];
    
    if(!player)
        return Vector(0, 0, 0);
    
    if (!player->SetupBones(matrix, 128, 0x100, pGlobals->curtime))
        return Vector(0, 0, 0);
    
    mstudiohitboxset_t* set = get_hitbox_handle(player, matrix);;
    
    if(!set)
        return Vector(0, 0, 0);
    
    mstudiobbox_t* hitbox = set->pHitbox(Hitbox);
    
    if (!hitbox)
        return Vector(0, 0, 0);
    
    Vector vMin, vMax, vCenter, sCenter;
    vector_transform(hitbox->bbmin, matrix[hitbox->bone], vMin);
    vector_transform(hitbox->bbmax, matrix[hitbox->bone], vMax);
    vCenter = (vMin + vMax) *0.5f;
    
    float scale = 50.f;
    
    float ptwoz = 50 - scale;
    float zval = (ptwoz * vMin.z + scale * vMax.z) / 50;
    vCenter.z = zval;
    
    return vCenter;
}

Vector calculate_hitbox(matrix3x4_t matrix[128], mstudiobbox_t* hitbox, Vector offset)
{
    Vector min, max;
    transform_matrix(hitbox->bbmin, matrix[hitbox->bone], min);
    transform_matrix(hitbox->bbmax, matrix[hitbox->bone], max);
    
    return (min + max) / 2.f + offset;
}

