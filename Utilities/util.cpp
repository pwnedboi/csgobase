/*      util.cpp
 *
 *
 *
 */
#include "main.h"
#include "util.h"
#include "util_math.h"

void print(string str, Color col, string prefix)
{
    if(!pCvar)
        return;
    
    prefix = "[" + prefix + "] ";
    pCvar->ConsoleColorPrintf(col, prefix.c_str());
    pCvar->ConsoleDPrintf("%s\n", str.c_str());
}

bool WorldToScreen(Vector& in, Vector& out)
{
    return !pOverlay->ScreenPosition(in, out);
}

bool IsPlayerVisible(C_BasePlayer* entity)
{
    Ray_t ray;
    trace_t trace;
    CTraceFilter filter;
    filter.pSkip = Global::local;
    
    ray.Init(Global::local->GetEyePosition(), entity->GetEyePosition());
    pEngineTrace->TraceRay(ray, 0x4600400B, &filter, &trace);
    return (trace.m_pEnt == entity || trace.fraction > 0.99f);
}

bool IsHitboxVisible(C_BasePlayer* player, int hitbox)
{
    Ray_t ray;
    trace_t trace;
    CTraceFilter filter;
    filter.pSkip = Global::local;
    
    ray.Init(Global::local->GetEyePosition(), GetHitboxPosition(player, hitbox));
    pEngineTrace->TraceRay(ray, 0x4600400B, &filter, &trace);
    return (trace.m_pEnt == player || trace.fraction > 0.99f);
}

bool IsPointVisible(Vector point)
{
    Ray_t ray;
    trace_t trace;
    CTraceFilter filter;
    filter.pSkip = Global::local;
    
    ray.Init(Global::local->GetEyePosition(), point);
    pEngineTrace->TraceRay(ray, 0x4600400B, &filter, &trace);
    return (trace.fraction > 0.97f);
}

// Credit's to dude719 & keybode
bool get_box(C_BaseEntity* pEntity, box_t& box)
{
    if (!pEntity)
        return false;
    
    Vector vOrigin = pEntity->GetVecOrigin();
    Vector min = pEntity->GetCollideable()->OBBMins() + vOrigin;
    Vector max = pEntity->GetCollideable()->OBBMaxs() + vOrigin;
    
    Vector points[] = {
        Vector(min.x, min.y, min.z),
        Vector(min.x, max.y, min.z),
        Vector(max.x, max.y, min.z),
        Vector(max.x, min.y, min.z),
        Vector(max.x, max.y, max.z),
        Vector(min.x, max.y, max.z),
        Vector(min.x, min.y, max.z),
        Vector(max.x, min.y, max.z)
    };
    
    Vector flb; // flb = front-left-bottom
    Vector brt; // brt = back-right-top
    Vector blb; // blb = back-left-bottom
    Vector frt; // frt = front-right-top
    Vector frb; // frb = front-right-bottom
    Vector brb; // brb = back-right-bottom
    Vector blt; // blt = back-left-top
    Vector flt; // flt = front-left-top
    
    
    if (!WorldToScreen(points[0], blb) || !WorldToScreen(points[1], brb) || !WorldToScreen(points[2], frb) ||!WorldToScreen(points[3], flb) ||
        !WorldToScreen(points[4], frt) || !WorldToScreen(points[5], brt) || !WorldToScreen(points[6], blt) || !WorldToScreen(points[7], flt))
        return false;
    
    Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };
    
    float left   = flb.x;   // left
    float top    = flb.y;   // top
    float right  = flb.x;   // right
    float bottom = flb.y;   // bottom
    
    for (int i = 1; i < 8; i++)
    {
        if (left > arr[i].x)
            left = arr[i].x;
        if (bottom < arr[i].y)
            bottom = arr[i].y;
        if (right < arr[i].x)
            right = arr[i].x;
        if (top > arr[i].y)
            top = arr[i].y;
    }
    
    box.x = left;
    box.y = top;
    box.w = right - left;
    box.h = bottom - top;
    return true;
}

long get_timestamp()
{
    return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
}

Color ImVecToColor(ImVec4 col, bool alpha)
{
    return Color(col.x * 255, col.y * 255, col.z * 255, alpha ? col.w * 255 : 255);
}

C_BaseCombatWeapon* GetActiveWeapon(C_BasePlayer* player)
{
    void* weaponHandle = player->GetActiveWeapon();
    
    if (!weaponHandle)
        return nullptr;
    
    return (C_BaseCombatWeapon*)pEntList->GetClientEntityFromHandle(weaponHandle);
}

char* C_BasePlayer::GetName()
{
    player_info_t info;
    pEngine->GetPlayerInfo(this->GetIndex(), &info);
    return (char*)info.name;
}









