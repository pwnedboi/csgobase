/*
 *  util_math.h
 */
#pragma once


void inline SinCos(float radians, float *sine, float *cosine);
void AngleVectors(const QAngle &angles, Vector &forward);
void NormalizeAngles(QAngle& angle);
void NormalizeVector(Vector& vecIn);
void ClampAngles(QAngle& angle);
void CorrectMovement(QAngle vOldAngles, CUserCmd* pCmd, float fOldForward, float fOldSidemove);
void FixMovement(QAngle& oang, CUserCmd* pCmd);
void ClampMoves(float& flForward, float& flSide, float& flUp);
void ClampYaw(float& val);

float GetFov(const QAngle &viewAngle, const QAngle &aimAngle);
float DotProduct(Vector &v1, const float* v2);

void VectorAngles(const Vector &forward, QAngle &angles);
void VectorTransform (Vector &in1, const matrix3x4_t& in2, Vector &out);

QAngle CalcAngle(Vector src, Vector dst);

float float_rand( float min, float max );
float get_distance(Vector a, Vector b);
float GetCurTime();

Vector GetHitboxPosition(C_BasePlayer* player, int Hitbox);


template<class T, class U>
T clamp(T in, U low, U high)
{
    if (in <= low)
        return low;
    
    if (in >= high)
        return high;
    
    return in;
}


