/*      math.cpp
 *
 *
 *
 */

#include "main.h"
#include "util_math.h"

void inline SinCos(float radians, float *sine, float *cosine)
{
    double __cosr, __sinr;
    __asm ("fsincos" : "=t" (__cosr), "=u" (__sinr) : "0" (radians));
    
    *sine = __sinr;
    *cosine = __cosr;
}

float float_rand(float min, float max)
{
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * (max - min);      /* [min, max] */
}

float get_distance(Vector a, Vector b)
{
    // Gets the distance between 2 vectors in meters
    float dist = sqrt( pow( a.x - b.x, 2 ) + pow( a.y - b.y, 2 ) + pow( a.z - b.z, 2 ) ) * 0.0254f;
    return dist;
}

void AngleVectors(const QAngle &angles, Vector& forward)
{
    Assert(s_bMathlibInitialized);
    Assert(forward);
    
    float sp, sy, cp, cy;
    
    SinCos(DEG2RAD(angles[PITCH]), &sp, &cp);
    SinCos(DEG2RAD(angles[YAW]), &sy, &cy);
    
    forward.x = cp * cy;
    forward.y = cp * sy;
    forward.z = -sp;
}

void NormalizeAngles(QAngle& angle)
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

void ClampAngles(QAngle& angle)
{
    if (angle.x > 89.0f)
        angle.x = 89.0f;
    else if (angle.x < -89.0f)
        angle.x = -89.0f;
    
    if (angle.y > 180.0f)
        angle.y = 180.0f;
    else if (angle.y < -180.0f)
        angle.y = -180.0f;
    
    angle.z = 0;
}

void NormalizeVector(Vector& vecIn)
{
    for (int axis = 0; axis < 3; ++axis)
    {
        while (vecIn[axis] > 180.f)
            vecIn[axis] -= 360.f;
        
        while (vecIn[axis] < -180.f)
            vecIn[axis] += 360.f;
        
    }
    
    vecIn[2] = 0.f;
}

void ClampYaw (float& val)
{
    while (val < 0)
        val += 360.0f;
    while (val > 360.0f)
        val -= 360.0f;
}

void CorrectMovement(QAngle vOldAngles, CUserCmd* pCmd, float fOldForward, float fOldSidemove)
{
    // side/forward move correction
    float deltaView;
    float f1;
    float f2;
    
    if (vOldAngles.y < 0.f)
        f1 = 360.0f + vOldAngles.y;
    else
        f1 = vOldAngles.y;
    
    if (pCmd->viewangles.y < 0.0f)
        f2 = 360.0f + pCmd->viewangles.y;
    else
        f2 = pCmd->viewangles.y;
    
    if (f2 < f1)
        deltaView = abs(f2 - f1);
    else
        deltaView = 360.0f - abs(f1 - f2);
    
    deltaView = 360.0f - deltaView;
    
    pCmd->forwardmove = cos(DEG2RAD(deltaView)) * fOldForward + cos(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
    pCmd->sidemove    = sin(DEG2RAD(deltaView)) * fOldForward + sin(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
}

float GetFov(const QAngle& viewAngle, const QAngle& aimAngle)
{
    QAngle delta = aimAngle - viewAngle;
    NormalizeAngles(delta);
    
    return sqrtf(powf(delta.x, 2.0f) + powf(delta.y, 2.0f));
}

void VectorAngles(const Vector& forward, QAngle &angles)
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

float DotProduct(Vector &v1, const float* v2)
{
    return v1.x * v2[0] + v1.y * v2[1] + v1.z * v2[2];
}

void VectorTransform (Vector &in1, const matrix3x4_t& in2, Vector &out)
{
    out.x = DotProduct(in1, in2[0]) + in2[0][3];
    out.y = DotProduct(in1, in2[1]) + in2[1][3];
    out.z = DotProduct(in1, in2[2]) + in2[2][3];
}

QAngle CalcAngle(Vector src, Vector dst)
{
    QAngle angles;
    Vector delta = src - dst;
    
    VectorAngles(delta, angles);
    
    delta.Normalize();
    
    return angles;
}

Vector GetHitboxPosition(C_BasePlayer* player, int Hitbox)
{
    matrix3x4_t matrix[128];
    
    if(!player)
        return Vector(0, 0, 0);
    
    if (!player->SetupBones(matrix, 128, 0x100, pGlobals->curtime))
        return Vector(0, 0, 0);
    
    model_t* model = player->GetModel();
    
    if(!model)
        return Vector(0, 0, 0);
    
    studiohdr_t* hdr = pModelInfo->GetStudioModel(model);
    
    if(!hdr)
        return Vector(0, 0, 0);
    
    mstudiohitboxset_t* set = hdr->pHitboxSet(0);
    
    if(!set)
        return Vector(0, 0, 0);
    
    mstudiobbox_t* hitbox = set->pHitbox(Hitbox);
    
    if (!hitbox)
        return Vector(0, 0, 0);
    
    Vector vMin, vMax, vCenter, sCenter;
    VectorTransform(hitbox->bbmin, matrix[hitbox->bone], vMin);
    VectorTransform(hitbox->bbmax, matrix[hitbox->bone], vMax);
    vCenter = (vMin + vMax) *0.5f;
    
    float scale = 50.f; // vars.rage.multipoint ? vars.rage.pointscale :
    
    float ptwoz = 50 - scale;
    float zval = (ptwoz * vMin.z + scale * vMax.z) / 50;
    vCenter.z = zval;
    
    
    return vCenter;
}

float GetCurTime()
{
    if(!Global::local || !Global::cmd)
        return 0;
    
    int tick = 0;
    static CUserCmd* last_cmd = nullptr;
    if (!last_cmd || last_cmd->hasbeenpredicted)
    {
        tick = (float)Global::local->GetTickBase();
    }
    else
    {
        ++tick;
    }
    last_cmd = Global::cmd;
    return tick * pGlobals->interval_per_tick;
}

void FixMovement(QAngle& oang, CUserCmd* pCmd)
{
    Vector vMove(pCmd->forwardmove, pCmd->sidemove, pCmd->upmove);
    float flSpeed = sqrt(vMove.x * vMove.x + vMove.y * vMove.y), flYaw;
    QAngle vMove2;
    VectorAngles(vMove, vMove2);
    
    flYaw = DEG2RAD(pCmd->viewangles.y - oang.y + vMove2.y);
    pCmd->forwardmove = cos(flYaw) * flSpeed;
    pCmd->sidemove = sin(flYaw) * flSpeed;
    
    if (pCmd->viewangles.x < -90.f || pCmd->viewangles.x > 90.f)
        pCmd->forwardmove = -pCmd->forwardmove;
}

void ClampMoves(float& flForward, float& flSide, float& flUp)
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

